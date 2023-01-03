/**
 * Copyright (C) 2005 Andras Varga
 * Copyright (C) 2005 Wei Yang, Ng
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include "inet/networklayer/icmpv6/Ipv6NeighbourDiscovery.h"

#include <string>
#include "inet/common/ModuleAccess.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/networklayer/common/HopLimitTag_m.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/networklayer/icmpv6/Icmpv6.h"
#include "inet/networklayer/ipv6/Ipv6Header.h"
#include "inet/networklayer/ipv6/Ipv6InterfaceData.h"
#include "inet/networklayer/ipv6/Ipv6RoutingTable.h"
#include "inet/linklayer/common/MacAddressTag_m.h"

#include <algorithm>


#include "inet/linklayer/common/MacAddressTag_m.h"

#ifdef WITH_xMIPv6
#include "inet/networklayer/xmipv6/xMIPv6.h"
#endif /* WITH_xMIPv6 */

namespace inet {

#define MK_ASSIGN_LINKLOCAL_ADDRESS    0
#define MK_SEND_PERIODIC_RTRADV        1
#define MK_SEND_SOL_RTRADV             2
#define MK_INITIATE_RTRDIS             3
#define MK_DAD_TIMEOUT                 4
#define MK_RD_TIMEOUT                  5
#define MK_NUD_TIMEOUT                 6
#define MK_AR_TIMEOUT                  7

#define MK_ADDR_REGIST_RETRANS         8
#define MK_ADDR_REGIST_TIMEOUT         9
#define MK_MULTI_DAD_TIMEOUT          10
#define MK_DECISION_MAKER             11
#define MK_ND_TIMEOUT                 12
#define MK_START_MULTIHOP_DAD         13

Define_Module(Ipv6NeighbourDiscovery);

// signals

simsignal_t Ipv6NeighbourDiscovery::startDadSignalTime = registerSignal("startDadSignalTime");
simsignal_t Ipv6NeighbourDiscovery::startDadSignalId = registerSignal("startDadSignalId");
simsignal_t Ipv6NeighbourDiscovery::receivedDadSignalTime = registerSignal("receivedDadSignalTime");
simsignal_t Ipv6NeighbourDiscovery::receivedDadSignalId = registerSignal("receivedDadSignalId");
simsignal_t Ipv6NeighbourDiscovery::responseDadSignalTime = registerSignal("responseDadSignalTime");
simsignal_t Ipv6NeighbourDiscovery::finishDadSignalTime = registerSignal("finishDadSignalTime");
simsignal_t Ipv6NeighbourDiscovery::responseDadSignalId = registerSignal("responseDadSignalId");
simsignal_t Ipv6NeighbourDiscovery::finishDadSignalId = registerSignal("finishDadSignalId");
simsignal_t Ipv6NeighbourDiscovery::numDadMessageForwardedSignal = registerSignal("numDadMessageForwardedSignal");

//ND messages exchanged between different modules
simsignal_t Ipv6NeighbourDiscovery::numSentSignal = registerSignal("numSentSignal");
simsignal_t Ipv6NeighbourDiscovery::numReceivedSignal = registerSignal("numReceivedSignal");

double s1;
double signal;
int id1;

Ipv6NeighbourDiscovery::Ipv6NeighbourDiscovery()
    : neighbourCache(*this)
{

}


Ipv6NeighbourDiscovery::~Ipv6NeighbourDiscovery()
{
    // FIXME delete the following data structures, cancelAndDelete timers in them etc.
    // Deleting the data structures my become unnecessary if the lists store the
    // structs themselves and not pointers.

    //   RaTimerList raTimerList;
    for (const auto & elem : raTimerList) {
        cancelAndDelete(elem);
        delete (elem);
    }

    //   DadList dadList;
    for (const auto & elem : dadList) {
        cancelAndDelete((elem)->timeoutMsg);
        delete (elem);
    }

    //   RdList rdList;
    for (const auto & elem : rdList) {
        cancelAndDelete((elem)->timeoutMsg);
        delete (elem);
    }

    //   AdvIfList advIfList;
    for (const auto & elem : advIfList) {
        cancelAndDelete((elem)->raTimeoutMsg);
        delete (elem);
    }
}

void Ipv6NeighbourDiscovery::initialize(int stage)
{
    cSimpleModule::initialize(stage);
//    std::cout <<"Ipv6NeighbourDiscovery.cc Initialization! "<<std::endl;

    // dadTime = registerSignal("dadTime");

    if (stage == INITSTAGE_LOCAL) {
        const char *crcModeString = par("crcMode");


        if (!strcmp(crcModeString, "declared"))
            crcMode = CRC_DECLARED_CORRECT;
        else if (!strcmp(crcModeString, "computed"))
            crcMode = CRC_COMPUTED;
        else
            throw cRuntimeError("unknown CRC mode: '%s'", crcModeString);
    }
    else if (stage == INITSTAGE_NETWORK_LAYER) {
        bool isOperational;
        NodeStatus *nodeStatus = dynamic_cast<NodeStatus *>(findContainingNode(this)->getSubmodule("status"));
        isOperational = (!nodeStatus) || nodeStatus->getState() == NodeStatus::UP;
        if (!isOperational)
            throw cRuntimeError("This module doesn't support starting in node DOWN state");
    }
    else if (stage == INITSTAGE_NETWORK_LAYER_3) {
        ift = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this);
        rt6 = getModuleFromPar<Ipv6RoutingTable>(par("routingTableModule"), this);
        icmpv6 = getModuleFromPar<Icmpv6>(par("icmpv6Module"), this);

#ifdef WITH_xMIPv6
        if (rt6->isMobileNode())
            mipv6 = getModuleFromPar<xMIPv6>(par("xmipv6Module"), this);
#endif /* WITH_xMIPv6 */

        pendingQueue.setName("pendingQueue");

#ifdef WITH_xMIPv6
        //MIPv6Enabled = par("MIPv6Support");    // (Zarrar 14.07.07)
        /*if(rt6->isRouter()) // 12.9.07 - CB
           {
            minRAInterval = par("minIntervalBetweenRAs"); // from the omnetpp.ini file (Zarrar 15.07.07)
            maxRAInterval = par("maxIntervalBetweenRAs"); // from the omnetpp.ini file (Zarrar 15.07.07)
            //WATCH (MIPv6Enabled);    // (Zarrar 14.07.07)
            WATCH(minRAInterval);    // (Zarrar 15.07.07)
            WATCH(maxRAInterval);    // (Zarrar 15.07.07)
           }*/
#endif /* WITH_xMIPv6 */

        for (int i = 0; i < ift->getNumInterfaces(); i++) {
            InterfaceEntry *ie = ift->getInterface(i);

            if (ie->ipv6Data()->getAdvSendAdvertisements() && !(ie->isLoopback())) {
                createRaTimer(ie);
            }
        }

        //This simulates random node bootup time. Link local address assignment
        //takes place during this time.
        cMessage *msg = new cMessage("assignLinkLocalAddr", MK_ASSIGN_LINKLOCAL_ADDRESS);

        //We want routers to boot up faster!
        if (rt6->isRouter()) {
            scheduleAt(simTime() + uniform(0, 0.3), msg); //Random Router bootup time

        }
        else
            scheduleAt(simTime() + uniform(0.4, 1), msg); //Random Host bootup time
    }
}

void Ipv6NeighbourDiscovery::handleMessage(cMessage *msg)
{
    // all messages are received here (sent with send() or scheduled (timer from self)).

    if (msg->isSelfMessage()) {
        EV_TRACE << "  Self message received!\n";


        if (msg->getKind() == MK_SEND_PERIODIC_RTRADV) {
//            EV_INFO << "Sending periodic RA\n";
//            sendPeriodicRa(msg);
        }
        else if (msg->getKind() == MK_SEND_SOL_RTRADV) {
            EV_INFO << "Sending solicited RA\n";
//            std::cout << " ===== Sending solicited RA\n";
            sendSolicitedRa(msg);
        }
        else if (msg->getKind() == MK_ASSIGN_LINKLOCAL_ADDRESS) {
            EV_INFO << "Assigning Link Local Address\n";
//            std::cout << " ===== Assigning Link Local Address\n";
            assignLinkLocalAddress(msg);
        }
        else if (msg->getKind() == MK_DAD_TIMEOUT) {
            EV_INFO << "DAD Timeout message received\n";
//            std::cout << " ===== DAD Timeout message received\n";
            processDadTimeout(msg);
        }
        else if (msg->getKind() == MK_RD_TIMEOUT) {
            EV_INFO << "Router Discovery message received\n";
//            std::cout << " ===== Router Discovery message received\n";
            processRdTimeout(msg);
        }
        else if (msg->getKind() == MK_INITIATE_RTRDIS) {
            EV_INFO << "initiate router discovery.\n";
//            std::cout << " ====== initiate router discovery.\n";
            initiateRouterDiscovery(msg);
        }
        else if (msg->getKind() == MK_NUD_TIMEOUT) {
            EV_INFO << "NUD Timeout message received\n";
//            std::cout << " ===== NUD Timeout message received\n";
            processNudTimeout(msg);
        }
        else if (msg->getKind() == MK_AR_TIMEOUT) {
            EV_INFO << "Address Resolution Timeout message received\n";
//            std::cout << " ====== Address Resolution Timeout message received\n";
            processArTimeout(msg);
        }
        else if (msg->getKind() == MK_ADDR_REGIST_RETRANS) {
            EV_INFO << "Address Resolution Timeout message received\n";
//            std::cout << " ====== Address Resolution Timeout message received\n";
            processAddrRegistRetransmit(msg);
        }

        else if (msg->getKind() == MK_MULTI_DAD_TIMEOUT) {
            EV_INFO << "Multihop DAD Timeout message received\n";
//            std::cout << " ====== Multihop DAD Timeout message received\n";
            processMultihopDadTimeout(msg);
        }

        else if (msg->getKind() == MK_ADDR_REGIST_TIMEOUT) {
            EV_INFO << "Address Registration Timeout! Delete NCE!\n";
//            std::cout << " ===== Address Registration Timeout! Delete NCE!\n";
            processAddrRegistTimeout(msg);
        }
        else if (msg->getKind() == MK_DECISION_MAKER) {
            EV_INFO << "Start to select neighbor!\n";
//            std::cout << " ==== Start to select neighbor!\n";
            delayProcessNaFromNeighbor(msg);
        }
        else if (msg->getKind() == MK_ND_TIMEOUT) {
            EV_INFO << "Restart to find neighbor!\n";
//            std::cout << " ====  Restart to find neighbor!\n";
            processNdTimeout(msg);
        }

        else if (msg->getKind() == MK_START_MULTIHOP_DAD) {
            EV_INFO << "Start multihop dad!\n";
//            std::cout << " ===== Start multihop dad!\n";
            msgTriggerForMultihopDAD(msg);

        }

        else
            throw cRuntimeError("Unrecognized Timer"); //stops sim w/ error msg.
    }
    else if (auto packet = dynamic_cast<Packet *>(msg)) {
        auto protocol = packet->getTag<PacketProtocolTag>()->getProtocol();
        EV_INFO<<"Packet Protocol is :"<< protocol->getName()<<endl;
        if (protocol == &Protocol::icmpv6) {
            //This information will serve as input parameters to various processors.
            const auto& ndMsg = packet->peekAtFront<Icmpv6Header>();
            processNDMessage(packet, ndMsg.get()); // KLUDGE: remove get()
            numReceived++;
            emit(numReceivedSignal, numReceived);
        }
        else {    // not ND message
            processIpv6Datagram(packet);
        }
    }
    else
        throw cRuntimeError("Unknown message type received.\n");
}

void Ipv6NeighbourDiscovery::processNDMessage(Packet *packet, const Icmpv6Header *icmpv6Header)
{
    if (auto rs = dynamic_cast<const Ipv6RouterSolicitation *>(icmpv6Header)) {
        processRsPacket(packet, rs);
    }
    else if (auto ra = dynamic_cast<const Ipv6RouterAdvertisement *>(icmpv6Header)) {
        processRaPacket(packet, ra);
    }
    else if (auto ns = dynamic_cast<const Ipv6NeighbourSolicitation *>(icmpv6Header)) {
        processNsPacket(packet, ns);
    }
    else if (auto na = dynamic_cast<const Ipv6NeighbourAdvertisement *>(icmpv6Header)) {
        processNaPacket(packet, na);
    }
    else if (auto redirect = dynamic_cast<const Ipv6Redirect *>(icmpv6Header)) {
        processRedirectPacket(redirect);
    }
    //discard DAR and DAC
    else if (auto dar = dynamic_cast<const Ipv6DuplicateAddrReq *>(icmpv6Header)) {
        processDARPacket(packet, dar);
    }
    else if (auto dac = dynamic_cast<const Ipv6DuplicateAddrConfirm *>(icmpv6Header)) {
        processDACPacket(packet, dac);
    }
    else {
        throw cRuntimeError("Unrecognized ND message!");
    }
}

bool Ipv6NeighbourDiscovery::handleOperationStage(LifecycleOperation *operation, int stage, IDoneCallback *doneCallback)
{
    throw cRuntimeError("Lifecycle operation support not implemented");
}

void Ipv6NeighbourDiscovery::finish()
{
    //Exam Add you simulation Data recording
//    std::cout <<"Neigbour Discovery finish operation!!!" <<std::endl;
}

void Ipv6NeighbourDiscovery::processIpv6Datagram(Packet *packet)
{
    const auto& msg = packet->peekAtFront<Ipv6Header>();
    EV_INFO << "Packet " << packet << " arrived from Ipv6 module.\n";

    Ipv6NdControlInfo *ctrl = check_and_cast<Ipv6NdControlInfo *>(packet->getControlInfo());
    int nextHopIfID = ctrl->getInterfaceId();
    Ipv6Address nextHopAddr = ctrl->getNextHop();
    //bool fromHL = ctrl->getFromHL();

    if (nextHopIfID == -1 || nextHopAddr.isUnspecified()) {
        EV_INFO << "Determining Next Hop" << endl;
        nextHopAddr = determineNextHop(msg->getDestAddress(), nextHopIfID);
        ctrl->setInterfaceId(nextHopIfID);
        ctrl->setNextHop(nextHopAddr);
    }

    if (nextHopIfID == -1) {
        //draft-ietf-ipv6-2461bis-04 has omitted on-link assumption.
        //draft-ietf-v6ops-onlinkassumption-03 explains why.
        delete packet->removeControlInfo();
        icmpv6->sendErrorMessage(packet, ICMPv6_DESTINATION_UNREACHABLE, NO_ROUTE_TO_DEST);
        return;
    }

    EV_INFO << "Next Hop Address is: " << nextHopAddr << " on interface: " << nextHopIfID << endl;

    //RFC2461: Section 5.2 Conceptual Sending Algorithm
    //Once the IP address of the next-hop node is known, the sender examines the
    //Neighbor Cache for link-layer information about that neighbor.
    Neighbour *nce = neighbourCache.lookup(nextHopAddr, nextHopIfID);

    if (nce == nullptr) {
        EV_INFO << "No Entry exists in the Neighbour Cache.\n";
        InterfaceEntry *ie = ift->getInterfaceById(nextHopIfID);
        if (ie->isPointToPoint()) {
            //the sender creates one, sets its state to STALE,
            EV_DETAIL << "Creating an STALE entry in the neighbour cache.\n";
            nce = neighbourCache.addNeighbour(nextHopAddr, nextHopIfID, MacAddress::UNSPECIFIED_ADDRESS);
        }
        else {
            //the sender creates one, sets its state to INCOMPLETE,
            EV_DETAIL << "Creating an INCOMPLETE entry in the neighbour cache.\n";
            nce = neighbourCache.addNeighbour(nextHopAddr, nextHopIfID);

            //initiates Address Resolution,
            EV_DETAIL << "Initiating Address Resolution for:" << nextHopAddr
                      << " on Interface:" << nextHopIfID << endl;
            initiateAddressResolution(msg->getSrcAddress(), nce);
        }
    }

    /*
     * A host is capable of sending packets to a destination in all states except INCOMPLETE
     * or when there is no corresponding NC entry. In INCOMPLETE state the data packets are
     * queued pending completion of address resolution.
     */
    switch (nce->reachabilityState) {
    case Ipv6NeighbourCache::INCOMPLETE:
        EV_INFO << "Reachability State is INCOMPLETE. Address Resolution already initiated.\n";
        EV_INFO << "Add packet to entry's queue until Address Resolution is complete.\n";
        bubble("Packet added to queue until Address Resolution is complete.");
        nce->pendingPackets.push_back(packet);
        pendingQueue.insert(packet);
        break;
    case Ipv6NeighbourCache::STALE:
        EV_INFO << "Reachability State is STALE.\n";
        send(packet, "ipv6Out");
        initiateNeighbourUnreachabilityDetection(nce);
        break;
    case Ipv6NeighbourCache::REACHABLE:
        EV_INFO << "Next hop is REACHABLE, sending packet to next-hop address.";
        send(packet, "ipv6Out");
        break;
    case Ipv6NeighbourCache::DELAY:
        EV_INFO << "Next hop is in DELAY state, sending packet to next-hop address.";
        send(packet, "ipv6Out");
        break;
    case Ipv6NeighbourCache::PROBE:
        EV_INFO << "Next hop is in PROBE state, sending packet to next-hop address.";
        send(packet, "ipv6Out");
        break;
    default:
        throw cRuntimeError("Unknown Neighbour cache entry state.");
        break;
    }
}

Ipv6NeighbourDiscovery::AdvIfEntry *Ipv6NeighbourDiscovery::fetchAdvIfEntry(InterfaceEntry *ie)
{
    for (auto advIfEntry : advIfList) {
        if (advIfEntry->interfaceId == ie->getInterfaceId()) {
            return advIfEntry;
        }
    }
    return nullptr;
}

Ipv6NeighbourDiscovery::RdEntry *Ipv6NeighbourDiscovery::fetchRdEntry(InterfaceEntry *ie)
{
    for (auto rdEntry : rdList) {
        if (rdEntry->interfaceId == ie->getInterfaceId()) {
            return rdEntry;
        }
    }
    return nullptr;
}

Ipv6NeighbourDiscovery::AddrRegistEntry *Ipv6NeighbourDiscovery::fetchAddrRegistEntry(InterfaceEntry *ie)
{
    for (auto addrRegistEntry : addrRegistList) {
        if (addrRegistEntry->interfaceId == ie->getInterfaceId()) {
            return addrRegistEntry;
        }
    }
    return nullptr;
}


const MacAddress& Ipv6NeighbourDiscovery::resolveNeighbour(const Ipv6Address& nextHop, int interfaceId)
{
    Enter_Method("resolveNeighbor(%s,if=%d)", nextHop.str().c_str(), interfaceId);

    Neighbour *nce = neighbourCache.lookup(nextHop, interfaceId);
    //InterfaceEntry *ie = ift->getInterfaceById(interfaceId);

    if (!nce || nce->reachabilityState == Ipv6NeighbourCache::INCOMPLETE)
        return MacAddress::UNSPECIFIED_ADDRESS;

    if (nce->reachabilityState == Ipv6NeighbourCache::STALE) {
        initiateNeighbourUnreachabilityDetection(nce);
    }
    else if (nce->reachabilityState == Ipv6NeighbourCache::REACHABLE &&
             simTime() > nce->reachabilityExpires)
    {

        nce->reachabilityState = Ipv6NeighbourCache::STALE;
        initiateNeighbourUnreachabilityDetection(nce);
    }
    else if (nce->reachabilityState != Ipv6NeighbourCache::REACHABLE) {
        //reachability state must be either in DELAY or PROBE
        ASSERT(nce->reachabilityState == Ipv6NeighbourCache::DELAY ||
                nce->reachabilityState == Ipv6NeighbourCache::PROBE ||
                nce->reachabilityState == Ipv6NeighbourCache::TENTATIVE);
        EV_INFO << "NUD in progress.\n";
    }

    //else the entry is REACHABLE and no further action is required here.
    return nce->macAddress;
}

void Ipv6NeighbourDiscovery::reachabilityConfirmed(const Ipv6Address& neighbour, int interfaceId)
{
    Enter_Method("reachabilityConfirmed(%s,if=%d)", neighbour.str().c_str(), interfaceId);
    //hmmm... this should only be invoked if a TCP ACK was received and NUD is
    //currently being performed on the neighbour where the TCP ACK was received from.

    Neighbour *nce = neighbourCache.lookup(neighbour, interfaceId);
    if (!nce)
        throw cRuntimeError("Model error: not found in cache");

    cMessage *msg = nce->nudTimeoutEvent;
    if (msg != nullptr) {
        EV_INFO << "NUD in progress. Cancelling NUD Timer\n";
        bubble("Reachability Confirmed via NUD.");
        cancelAndDelete(msg);
        nce->nudTimeoutEvent = nullptr;
    }

    // TODO (see header file for description)
    /*A neighbor is considered reachable if the node has recently received
       a confirmation that packets sent recently to the neighbor were
       received by its IP layer.  Positive confirmation can be gathered in
       two ways: hints from upper layer protocols that indicate a connection
       is making "forward progress", or receipt of a Neighbor Advertisement
       message that is a response to a Neighbor Solicitation message.

       A connection makes "forward progress" if the packets received from a
       remote peer can only be arriving if recent packets sent to that peer
       are actually reaching it.  In TCP, for example, receipt of a (new)
       acknowledgement indicates that previously sent data reached the peer.
       Likewise, the arrival of new (non-duplicate) data indicates that

       earlier acknowledgements are being delivered to the remote peer.  If
       packets are reaching the peer, they must also be reaching the
       sender's next-hop neighbor; thus "forward progress" is a confirmation
       that the next-hop neighbor is reachable.  For off-link destinations,
       forward progress implies that the first-hop router is reachable.
       When available, this upper-layer information SHOULD be used.

       In some cases (e.g., UDP-based protocols and routers forwarding
       packets to hosts) such reachability information may not be readily
       available from upper-layer protocols.  When no hints are available
       and a node is sending packets to a neighbor, the node actively probes
       the neighbor using unicast Neighbor Solicitation messages to verify
       that the forward path is still working.

       The receipt of a solicited Neighbor Advertisement serves as
       reachability confirmation, since advertisements with the Solicited
       flag set to one are sent only in response to a Neighbor Solicitation.
       Receipt of other Neighbor Discovery messages such as Router
       Advertisements and Neighbor Advertisement with the Solicited flag set
       to zero MUST NOT be treated as a reachability confirmation.  Receipt
       of unsolicited messages only confirm the one-way path from the sender
       to the recipient node.  In contrast, Neighbor Unreachability
       Detection requires that a node keep track of the reachability of the
       forward path to a neighbor from the its perspective, not the
       neighbor's perspective.  Note that receipt of a solicited
       advertisement indicates that a path is working in both directions.
       The solicitation must have reached the neighbor, prompting it to
       generate an advertisement.  Likewise, receipt of an advertisement
       indicates that the path from the sender to the recipient is working.
       However, the latter fact is known only to the recipient; the
       advertisement's sender has no direct way of knowing that the
       advertisement it sent actually reached a neighbor.  From the
       perspective of Neighbor Unreachability Detection, only the
       reachability of the forward path is of interest.*/
}

Ipv6Address Ipv6NeighbourDiscovery::determineNextHop(const Ipv6Address& destAddr, int& outIfID)
{
    Ipv6Address nextHopAddr;
    simtime_t expiryTime;

    //RFC 2461 Section 5.2
    //Next-hop determination for a given unicast destination operates as follows.

    //The sender performs a longest prefix match against the Prefix List to
    //determine whether the packet's destination is on- or off-link.
    EV_INFO << "Find out if supplied dest addr is on-link or off-link.\n";
    const Ipv6Route *route = rt6->doLongestPrefixMatch(destAddr);

    InterfaceEntry *ie = ift->getInterfaceByName("nic");
    Neighbour *nce = neighbourCache.lookup(destAddr, ie->getInterfaceId());

    //figure out if this msg is relay or not
    bool isRelay = false;
    if (nce!=nullptr && !nce->relayAddr.isUnspecified())
        isRelay = true;

    if (route != nullptr && !isRelay) {
        expiryTime = route->getExpiryTime();
        outIfID = route->getInterface() ? route->getInterface()->getInterfaceId() : -1;

        //If the destination is on-link, the next-hop address is the same as the
        //packet's destination address.
        if (route->getNextHop().isUnspecified()) {
            EV_INFO << "Dest is on-link, next-hop addr is same as dest addr.\n";
            nextHopAddr = destAddr;
        }
        else {
            EV_INFO << "A next-hop address was found with the route, dest is off-link\n";
            EV_INFO << "Assume next-hop address as the selected default router.\n";
            nextHopAddr = route->getNextHop();
        }
    }
    //set relay address as nexthop
    else if (isRelay) {
        nextHopAddr = nce->relayAddr;
        outIfID = nce->nceKey->interfaceID;
    }
    else {
        //Otherwise, the sender selects a router from the Default Router List
        //(following the rules described in Section 6.3.6).

        EV_INFO << "No routes were found, Dest addr is off-link.\n";
        nextHopAddr = selectDefaultRouter(outIfID);
        expiryTime = 0;

        if (outIfID == -1)
            EV_INFO << "No Default Routers were found.";
        else
            EV_INFO << "Default router found.\n";
    }


    /*the results of next-hop determination computations are saved in the Destination
       Cache (which also contains updates learned from Redirect messages).*/
    rt6->updateDestCache(destAddr, nextHopAddr, outIfID, expiryTime);
    return nextHopAddr;
}

void Ipv6NeighbourDiscovery::initiateNeighbourUnreachabilityDetection(Neighbour *nce)
{
    ASSERT(nce->reachabilityState == Ipv6NeighbourCache::STALE);
    ASSERT(nce->nudTimeoutEvent == nullptr);
    const Key *nceKey = nce->nceKey;
    EV_INFO << "Initiating Neighbour Unreachability Detection";
// g   std::cout << "Initiating Neighbour Unreachability Detection\n";

    InterfaceEntry *ie = ift->getInterfaceById(nceKey->interfaceID);
    EV_INFO << "Setting NCE state to DELAY.\n";
    /*The first time a node sends a packet to a neighbor whose entry is
       STALE, the sender changes the state to DELAY*/
    nce->reachabilityState = Ipv6NeighbourCache::DELAY;

    /*and sets a timer to expire in DELAY_FIRST_PROBE_TIME seconds.*/
    cMessage *msg = new cMessage("NUDTimeout", MK_NUD_TIMEOUT);
    msg->setContextPointer(nce);
    nce->nudTimeoutEvent = msg;
    scheduleAt(simTime() + ie->ipv6Data()->_getDelayFirstProbeTime(), msg);
}

void Ipv6NeighbourDiscovery::processNudTimeout(cMessage *timeoutMsg)
{
    EV_INFO << "NUD has timed out\n";
    Neighbour *nce = (Neighbour *)timeoutMsg->getContextPointer();

    const Key *nceKey = nce->nceKey;
    if (nceKey == nullptr)
        throw cRuntimeError("The nceKey is nullptr at nce->MAC=%s, isRouter=%d",
                nce->macAddress.str().c_str(), nce->isRouter);

    InterfaceEntry *ie = ift->getInterfaceById(nceKey->interfaceID);

    if (nce->reachabilityState == Ipv6NeighbourCache::DELAY) {
        /*If the entry is still in the DELAY state when the timer expires, the
           entry's state changes to PROBE. If reachability confirmation is received,
           the entry's state changes to REACHABLE.*/
        EV_DETAIL << "Neighbour Entry is still in DELAY state.\n";
        EV_DETAIL << "Entering PROBE state. Sending NS probe.\n";
        nce->reachabilityState = Ipv6NeighbourCache::PROBE;
        nce->numProbesSent = 0;
    }

    /*If no response is received after waiting RetransTimer milliseconds
       after sending the MAX_UNICAST_SOLICIT solicitations, retransmissions cease
       and the entry SHOULD be deleted. Subsequent traffic to that neighbor will
       recreate the entry and performs address resolution again.*/
    if (nce->numProbesSent == (int)ie->ipv6Data()->_getMaxUnicastSolicit()) {
        EV_DETAIL << "Max number of probes have been sent." << endl;
        EV_DETAIL << "Neighbour is Unreachable, removing NCE." << endl;
        neighbourCache.remove(nceKey->address, nceKey->interfaceID); // remove nce from cache, cancel and delete timeoutMsg;
        return;
    }

    /*Upon entering the PROBE state, a node sends a unicast Neighbor Solicitation
       message to the neighbor using the cached link-layer address.*/
    createAndSendNsPacket(nceKey->address, nceKey->address,
            ie->ipv6Data()->getPreferredAddress(), ie);
    nce->numProbesSent++;
    /*While in the PROBE state, a node retransmits Neighbor Solicitation messages
       every RetransTimer milliseconds until reachability confirmation is obtained.
       Probes are retransmitted even if no additional packets are sent to the
       neighbor.*/
    scheduleAt(simTime() + ie->ipv6Data()->_getRetransTimer(), timeoutMsg);
}

Ipv6Address Ipv6NeighbourDiscovery::selectDefaultRouter(int& outIfID)
{
    EV_INFO << "Selecting default router...\n";
//    std::cout << "--->< Selecting default router...\n";

    //draft-ietf-ipv6-2461bis-04.txt Section 6.3.6
    /*The algorithm for selecting a router depends in part on whether or not a
       router is known to be reachable. The exact details of how a node keeps track
       of a neighbor's reachability state are covered in Section 7.3.  The algorithm
       for selecting a default router is invoked during next-hop determination when
       no Destination Cache entry exists for an off-link destination or when
       communication through an existing router appears to be failing.  Under normal
       conditions, a router would be selected the first time traffic is sent to a
       destination, with subsequent traffic for that destination using the same router
       as indicated in the Destination Cache modulo any changes to the Destination
       Cache caused by Redirect messages.

       The policy for selecting routers from the Default Router List is as
       follows:*/

    /*1) Routers that are reachable or probably reachable (i.e., in any state
       other than INCOMPLETE) SHOULD be preferred over routers whose reachability
       is unknown or suspect (i.e., in the INCOMPLETE state, or for which no Neighbor
       Cache entry exists). An implementation may choose to always return the same
       router or cycle through the router list in a round-robin fashion as long as
       it always returns a reachable or a probably reachable router when one is
       available.*/
    DefaultRouterList& defaultRouters = neighbourCache.getDefaultRouterList();
    for (auto it = defaultRouters.begin(); it != defaultRouters.end(); ) {
        Neighbour& nce = *it;
        if (simTime() > nce.routerExpiryTime) {
            EV_INFO << "Found an expired default router. Deleting entry...\n";
            ++it;
            neighbourCache.remove(nce.nceKey->address, nce.nceKey->interfaceID);
            continue;
        }
        if (nce.reachabilityState != Ipv6NeighbourCache::INCOMPLETE) {
            EV_INFO << "Found a probably reachable router in the default router list.\n";
            defaultRouters.setHead(*nce.nextDefaultRouter);
            outIfID = nce.nceKey->interfaceID;
            return nce.nceKey->address;
        }
        ++it;
    }

    /*2) When no routers on the list are known to be reachable or probably
       reachable, routers SHOULD be selected in a round-robin fashion, so that
       subsequent requests for a default router do not return the same router until
       all other routers have been selected.

       Cycling through the router list in this case ensures that all available
       routers are actively probed by the Neighbor Unreachability Detection algorithm.
       A request for a default router is made in conjunction with the sending of a
       packet to a router, and the selected router will be probed for reachability
       as a side effect.*/
    Neighbour *defaultRouter = defaultRouters.getHead();
    if (defaultRouter != nullptr) {
        EV_INFO << "Found a router in the neighbour cache (default router list).\n";
        defaultRouters.setHead(*defaultRouter->nextDefaultRouter);
        outIfID = defaultRouter->nceKey->interfaceID;
        return defaultRouter->nceKey->address;
    }

    EV_INFO << "No suitable routers found.\n";
    outIfID = -1;
    return Ipv6Address::UNSPECIFIED_ADDRESS;
}

void Ipv6NeighbourDiscovery::timeoutPrefixEntry(const Ipv6Address& destPrefix,
        int prefixLength)    //REDUNDANT
{
//    std::cout <<"---->< timeoutPrefixEntry\n"  <<std::endl;
    //RFC 2461: Section 6.3.5
    /*Whenever the invalidation timer expires for a Prefix List entry, that
       entry is discarded.*/
    rt6->deleteOnLinkPrefix(destPrefix, prefixLength);
    //hmmm... should the unicast address associated with this prefix be deleted
    //as well?-TODO: The address should be timeout/deleted as well!!

    /*No existing Destination Cache entries need be updated, however. Should a
       reachability problem arise with an existing Neighbor Cache entry, Neighbor
       Unreachability Detection will perform any needed recovery.*/
}

void Ipv6NeighbourDiscovery::timeoutDefaultRouter(const Ipv6Address& addr,
        int interfaceID)
{
    //RFC 2461: Section 6.3.5
    /*Whenever the Lifetime of an entry in the Default Router List expires,
       that entry is discarded.*/
    neighbourCache.remove(addr, interfaceID);

    /*When removing a router from the Default Router list, the node MUST update
       the Destination Cache in such a way that all entries using the router perform
       next-hop determination again rather than continue sending traffic to the
       (deleted) router.*/
    rt6->purgeDestCacheEntriesToNeighbour(addr, interfaceID);
}

void Ipv6NeighbourDiscovery::initiateAddressResolution(const Ipv6Address& dgSrcAddr,
        Neighbour *nce)
{

    const Key *nceKey = nce->nceKey;
    InterfaceEntry *ie = ift->getInterfaceById(nceKey->interfaceID);
    Ipv6Address neighbourAddr = nceKey->address;
    int ifID = nceKey->interfaceID;

    //RFC2461: Section 7.2.2
    //When a node has a unicast packet to send to a neighbor, but does not
    //know the neighbor's link-layer address, it performs address
    //resolution.  For multicast-capable interfaces this entails creating a
    //Neighbor Cache entry in the INCOMPLETE state(already created if not done yet)
    //WEI-If entry already exists, we still have to ensure that its state is INCOMPLETE.
    nce->reachabilityState = Ipv6NeighbourCache::INCOMPLETE;

    //and transmitting a Neighbor Solicitation message targeted at the
    //neighbor.  The solicitation is sent to the solicited-node multicast
    //address "corresponding to"(or "derived from") the target address.
    //(in this case, the target address is the address we are trying to resolve)
    EV_INFO << "Preparing to send Address Resolution NS message."<<endl;
    EV_INFO << "Preparing to send NS to solicited-node multicast group\n";
    EV_INFO << "on the next hop interface\n";
    Ipv6Address nsDestAddr = neighbourAddr.formSolicitedNodeMulticastAddress();    //for NS datagram
    Ipv6Address nsTargetAddr = neighbourAddr;    //for the field within the NS
    Ipv6Address nsSrcAddr;

    /*If the source address of the packet prompting the solicitation is the
       same as one of the addresses assigned to the outgoing interface,*/
    if (ie->ipv6Data()->hasAddress(dgSrcAddr))
        /*that address SHOULD be placed in the IP Source Address of the outgoing
           solicitation.*/
        nsSrcAddr = dgSrcAddr;
    else
        /*Otherwise, any one of the addresses assigned to the interface
           should be used.*/
        nsSrcAddr = ie->ipv6Data()->getPreferredAddress();
    ASSERT(ifID != -1);
    //Sending NS on specified interface.

    createAndSendNsPacket(nsTargetAddr, nsDestAddr, nsSrcAddr, ie);
    nce->numOfARNSSent = 1;
    nce->nsSrcAddr = nsSrcAddr;

    /*While awaiting a response, the sender SHOULD retransmit Neighbor Solicitation
       messages approximately every RetransTimer milliseconds, even in the absence
       of additional traffic to the neighbor. Retransmissions MUST be rate-limited
       to at most one solicitation per neighbor every RetransTimer milliseconds.*/
    cMessage *msg = new cMessage("arTimeout", MK_AR_TIMEOUT);    //AR msg timer
    nce->arTimer = msg;
    msg->setContextPointer(nce);
    scheduleAt(simTime() + ie->ipv6Data()->_getRetransTimer(), msg);
}

void Ipv6NeighbourDiscovery::processArTimeout(cMessage *arTimeoutMsg)
{
    //AR timeouts are cancelled when a valid solicited NA is received.
    Neighbour *nce = (Neighbour *)arTimeoutMsg->getContextPointer();
    const Key *nceKey = nce->nceKey;
    Ipv6Address nsTargetAddr = nceKey->address;
    InterfaceEntry *ie = ift->getInterfaceById(nceKey->interfaceID);
    EV_INFO << "Num Of NS Sent:" << nce->numOfARNSSent << endl;
    EV_INFO << "Max Multicast Solicitation:" << ie->ipv6Data()->_getMaxMulticastSolicit() << endl;

    if (nce->numOfARNSSent < ie->ipv6Data()->_getMaxMulticastSolicit()) {
        EV_INFO << "Sending another Address Resolution NS message" << endl;
        Ipv6Address nsDestAddr = nsTargetAddr.formSolicitedNodeMulticastAddress();
        createAndSendNsPacket(nsTargetAddr, nsDestAddr, nce->nsSrcAddr, ie);
        nce->numOfARNSSent++;
        scheduleAt(simTime() + ie->ipv6Data()->_getRetransTimer(), arTimeoutMsg);
        return;
    }

    EV_WARN << "Address Resolution has failed." << endl;

    dropQueuedPacketsAwaitingAr(nce);
    EV_INFO << "Deleting AR timeout msg\n";
    delete arTimeoutMsg;
}

void Ipv6NeighbourDiscovery::dropQueuedPacketsAwaitingAr(Neighbour *nce)
{
    const Key *nceKey = nce->nceKey;
    //RFC 2461: Section 7.2.2
    /*If no Neighbor Advertisement is received after MAX_MULTICAST_SOLICIT
       solicitations, address resolution has failed. The sender MUST return ICMP
       destination unreachable indications with code 3 (Address Unreachable) for
       each packet queued awaiting address resolution.*/
    MsgPtrVector& pendingPackets = nce->pendingPackets;
    EV_INFO << "Pending Packets empty:" << pendingPackets.empty() << endl;

    while (!pendingPackets.empty()) {
        auto i = pendingPackets.begin();
        Packet *msg = (*i);
        //Assume msg is the packet itself. I need the datagram's source addr.
        //The datagram's src addr will be the destination of the unreachable msg.
        EV_INFO << "Sending ICMP unreachable destination." << endl;
        pendingPackets.erase(i);
        pendingQueue.remove(msg);
        icmpv6->sendErrorMessage(msg, ICMPv6_DESTINATION_UNREACHABLE, ADDRESS_UNREACHABLE);
    }

    //RFC 2461: Section 7.3.3
    /*If address resolution fails, the entry SHOULD be deleted, so that subsequent
       traffic to that neighbor invokes the next-hop determination procedure again.*/
    EV_INFO << "Removing neighbour cache entry" << endl;
    neighbourCache.remove(nceKey->address, nceKey->interfaceID);
}

void Ipv6NeighbourDiscovery::sendPacketToIpv6Module(Packet *msg, const Ipv6Address& destAddr,
        const Ipv6Address& srcAddr, int interfaceId)
{
    delete msg->removeTagIfPresent<DispatchProtocolReq>();
    msg->addTagIfAbsent<InterfaceReq>()->setInterfaceId(interfaceId);
    msg->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::icmpv6);
    auto addressReq = msg->addTagIfAbsent<L3AddressReq>();
    addressReq->setSrcAddress(srcAddr);
    addressReq->setDestAddress(destAddr);
    EV_INFO<<"Sending packet to ipv6 module, dest address is: "<< destAddr <<endl;

    InterfaceEntry *ie = ift->getInterfaceById(interfaceId);
    msg->addTagIfAbsent<MacAddressReq>()->setSrcAddress(ie->getMacAddress());

    //Since we use global address in NCE, so sometimes we need to change link-local address into global address to look up NCE
    //TODO can be improved
    Ipv6Address newAddr = destAddr;
    newAddr.setPrefix(Ipv6Address("aaaa:0:64::"), 64);
    Neighbour *neighbourEntry = neighbourCache.lookup(newAddr, interfaceId);
    if (neighbourEntry!=nullptr)
        msg->addTagIfAbsent<MacAddressReq>()->setDestAddress(neighbourEntry->macAddress);

    msg->addTagIfAbsent<HopLimitReq>()->setHopLimit(255);
    send(msg, "ipv6Out");
    numSent++;
    emit(numSentSignal, numSent);

}

/**Not used yet-unsure if we really need it. --DELETED, Andras*/

void Ipv6NeighbourDiscovery::sendQueuedPacketsToIpv6Module(Neighbour *nce)
{
    MsgPtrVector& pendingPackets = nce->pendingPackets;

    while (!pendingPackets.empty()) {
        auto i = pendingPackets.begin();
        cMessage *msg = (*i);
        pendingPackets.erase(i);
        pendingQueue.remove(msg);
        EV_INFO << "Sending queued packet " << msg << endl;
        send(msg, "ipv6Out");
        numSent++;
        emit(numSentSignal, numSent);
    }
}

void Ipv6NeighbourDiscovery::assignLinkLocalAddress(cMessage *timerMsg)
{
    //Node has booted up. Start assigning a link-local address for each
    //interface in this node.
    for (int i = 0; i < ift->getNumInterfaces(); i++) {
        InterfaceEntry *ie = ift->getInterface(i);

        //Skip the loopback interface.
        if (ie->isLoopback())
            continue;

        Ipv6Address linkLocalAddr = ie->ipv6Data()->getLinkLocalAddress();
        EV_INFO << "Link local address already existed: " <<linkLocalAddr<< endl;
        if (linkLocalAddr.isUnspecified()) {
            //if no link local address exists for this interface, we assign one to it.
            EV_INFO << "No link local address exists. Forming one" << endl;
            linkLocalAddr = Ipv6Address().formLinkLocalAddress(ie->getInterfaceToken());
            ie->ipv6Data()->assignAddress(linkLocalAddr, true, SIMTIME_ZERO, SIMTIME_ZERO);

        }

        //Assign global address with shared prefix for routers in initiation
        //update own adv prefix and routelist
        if (rt6->isRouter()&& !(ie->isLoopback())) {
            Ipv6Address linkLocalAddress = ie->ipv6Data()->getLinkLocalAddress();
            ASSERT(linkLocalAddress.isUnspecified() == false);
            EV_INFO << "Interface name is: " << ie->getInterfaceName() << endl;

            if (strncmp("nic", ie->getInterfaceName(), 3) == 0) {
                Ipv6Address newAddr = linkLocalAddress.setPrefix(Ipv6Address("aaaa:0:64::"), 64);
                ie->ipv6Data()->assignAddress(newAddr, false,
                                       simTime(), simTime(), true);
                //update routelist with this shared-prefix
                rt6->addOrUpdateOwnAdvPrefix(Ipv6Address("aaaa:0:64::"), 64, ie->getInterfaceId(), SIMTIME_ZERO);

            }
            else if (strncmp("eth", ie->getInterfaceName(), 3) == 0) {
                for (int i = 0; i < ie->ipv6Data()->getNumAdvPrefixes(); i++) {
                    Ipv6Address globalAddress = ie->ipv6Data()->autoConfRouterGlobalScopeAddress(i);
                    ie->ipv6Data()->assignAddress(globalAddress, false, 0, 0);
                }
            }
        }

//        if (rt6->isRouter() && !(ie->isLoopback())) {
//            for (int i = 0; i < ie->ipv6Data()->getNumAdvPrefixes(); i++) {
//                Ipv6Address globalAddress = ie->ipv6Data()->autoConfRouterGlobalScopeAddress(i);
//                ie->ipv6Data()->assignAddress(globalAddress, false, 0, 0);
//                // ie->ipv6Data()->deduceAdvPrefix(); //commented out but the above two statements can be replaced with this single statement. But i am using the above two statements for clarity reasons.
//            }
//        }

        //Before we can use this address, we MUST initiate DAD first.

//       if (ie->ipv6Data()->isTentativeAddress(linkLocalAddr)) {
//            if (ie->ipv6Data()->getDupAddrDetectTransmits() > 0)
//                initiateDad(linkLocalAddr, ie);
//            else
//                makeTentativeAddressPermanent(linkLocalAddr, ie);
//        }

        if (rt6->isRouter() == false) {
            EV_INFO << "creating router discovery message timer\n";
            cMessage *rtrDisMsg = new cMessage("initiateRTRDIS", MK_INITIATE_RTRDIS);
            rtrDisMsg->setContextPointer(ie);
            simtime_t interval = uniform(0, ie->ipv6Data()->_getMaxRtrSolicitationDelay());    // random delay
            scheduleAt(simTime() + interval, rtrDisMsg);
        }

    }
    delete timerMsg;
}

void Ipv6NeighbourDiscovery::initiateDad(const Ipv6Address& tentativeAddr, InterfaceEntry *ie)
{


#ifdef WITH_xMIPv6
    Enter_Method_Silent();
    EV_INFO << "----------INITIATING DUPLICATE ADDRESS DISCOVERY----------" << endl;
    ie->ipv6Data()->setDadInProgress(true);
#endif /* WITH_xMIPv6 */
//    std::cout << "----------INITIATING DUPLICATE ADDRESS DISCOVERY----------" << endl;


    // const MacAddress& getMacAddress() const { return macAddr; }

    DadEntry *dadEntry = new DadEntry();
    dadEntry->interfaceId = ie->getInterfaceId();
    dadEntry->address = tentativeAddr;
    dadEntry->numNSSent = 0;
    dadList.insert(dadEntry);
    /*
       RFC2462: Section 5.4.2
       To check an address, a node sends DupAddrDetectTransmits Neighbor
       Solicitations, each separated by RetransTimer milliseconds. The
       solicitation's Target Address is set to the address being checked,
       the IP source is set to the unspecified address and the IP
       destination is set to the solicited-node multicast address of the
       target address.*/
    Ipv6Address destAddr = tentativeAddr.formSolicitedNodeMulticastAddress();
    //Send a NS
    EV_INFO << "Sending DAD NS messages" << endl;
    createAndSendNsPacket(tentativeAddr, destAddr,
            Ipv6Address::UNSPECIFIED_ADDRESS, ie);
    dadEntry->numNSSent++;

// idea: simtime pasarlo a double y como tenemos la id de cada nodo emitir:
    // la suma del timestamp con el id y emitir el id por separado,
    //entonces para saber el tiempo, restamos el id (que sabremos su numero)
    // de lo recibido porla señal del timestamp + id


    s1 = simTime().dbl();


    id1 = ie->getMacAddress().getInt();
    // id1 = ie->getInterfaceId();

    signal = s1 + id1;
    emit(startDadSignalTime, signal);
    emit(startDadSignalId, id1);

    cMessage *msg = new cMessage("dadTimeout", MK_DAD_TIMEOUT);
    msg->setContextPointer(dadEntry);

#ifndef WITH_xMIPv6
    scheduleAt(simTime() + ie->ipv6Data()->getRetransTimer(), msg);
#else /* WITH_xMIPv6 */
    // update: added uniform(0, IPv6_MAX_RTR_SOLICITATION_DELAY) to account for joining the solicited-node multicast
    // group which is delay up to one 1 second (RFC 4862, 5.4.2) - 16.01.08, CB
    scheduleAt(simTime() + ie->ipv6Data()->getRetransTimer() + uniform(0, IPv6_MAX_RTR_SOLICITATION_DELAY), msg);
#endif /* WITH_xMIPv6 */


}


//initiate multihopDAD
void Ipv6NeighbourDiscovery::initiateMultihopDad(const Ipv6Address& tentativeAddr,Ipv6Address& destAddr, InterfaceEntry *ie)
{



#ifdef WITH_xMIPv6
    Enter_Method_Silent();
    EV_INFO << "----------INITIATING MULTIHOP DUPLICATE ADDRESS DISCOVERY----------" << endl;
    ie->ipv6Data()->setDadInProgress(true);
#endif /* WITH_xMIPv6 */
//    std::cout << "----------INITIATING MULTIHOP DUPLICATE ADDRESS DISCOVERY----------" << endl;


    multihopDadEntry *multihopdadEntry = new multihopDadEntry();
    multihopdadEntry->interfaceId = ie->getInterfaceId();
    multihopdadEntry->address = tentativeAddr;
    multihopdadEntry->numNSSent = 0;
    multihopdadList.insert(multihopdadEntry);

//    AddrRegistEntry *addrRegistEntry = new AddrRegistEntry();
//    addrRegistEntry->interfaceId = ie->getInterfaceId();
//    addrRegistEntry->numNSSent = 0;
//    addrRegistEntry->numNSSent++;

    EV_INFO << "Sending unicast DAD NS messages with ARO" << endl;
    EV_INFO << "NS source address is: " << ie->ipv6Data()->getAddress(0)<< endl;
    EV_INFO << "NS dest address is: " << destAddr << endl;

    //change to global address
//    createAndSendNsPacket(tentativeAddr, destAddr, ie->ipv6Data()->getLinkLocalAddress(), ie);
    createAndSendNsPacket(tentativeAddr, destAddr, ie->ipv6Data()->getPreferredAddress(), ie);
    multihopdadEntry->numNSSent++;

    s1 = simTime().dbl();


    id1 = ie->getMacAddress().getInt();
    // id1 = ie->getInterfaceId();
    signal = s1 + id1;
    emit(startDadSignalTime, signal);
    emit(startDadSignalId, id1);


    //address registration
//    cMessage *msg = new cMessage("AddrRegistRetransmit", MK_ADDR_REGIST_RETRANS);
//    msg->setContextPointer(ie);
//    addrRegistEntry->timeoutMsg = msg;
//    addrRegistList.insert(addrRegistEntry);
////    nce->nudTimeoutEvent = msg;
//    scheduleAt(simTime() + 20 +uniform(0.000001,0.00002), msg);


    //multihop dad timeout
    cMessage *msg2 = new cMessage("multihopDadTimeout", MK_MULTI_DAD_TIMEOUT);
    msg2->setContextPointer(multihopdadEntry);

    #ifndef WITH_xMIPv6

        scheduleAt(simTime() + ie->ipv6Data()->getRetransTimer(), msg2);

    #else /* WITH_xMIPv6 */
        // update: added uniform(0, IPv6_MAX_RTR_SOLICITATION_DELAY) to account for joining the solicited-node multicast
        // group which is delay up to one 1 second (RFC 4862, 5.4.2) - 16.01.08, CB
            scheduleAt(simTime() + uniform(0.005, 0.01)+uniform(0.0001,0.001), msg2);
    #endif /* WITH_xMIPv6 */


//    scheduleAt(simTime() + ie->ipv6Data()->_getDelayFirstProbeTime(), msg2);

//    scheduleAt(simTime() + ie->ipv6Data()->getRetransTimer(), msg2);
//    neighbour->routerExpiryTime = simTime() + ra->getRouterLifetime();


//Hide original functions

//    cMessage *msg = new cMessage("dadTimeout", MK_DAD_TIMEOUT);
//    msg->setContextPointer(dadEntry);
//
//#ifndef WITH_xMIPv6
//    scheduleAt(simTime() + ie->ipv6Data()->getRetransTimer(), msg);
//#else /* WITH_xMIPv6 */
//    // update: added uniform(0, IPv6_MAX_RTR_SOLICITATION_DELAY) to account for joining the solicited-node multicast
//    // group which is delay up to one 1 second (RFC 4862, 5.4.2) - 16.01.08, CB
//    scheduleAt(simTime() + ie->ipv6Data()->getRetransTimer() + uniform(0, IPv6_MAX_RTR_SOLICITATION_DELAY), msg);
//#endif /* WITH_xMIPv6 */
//


//Hide END
}


void Ipv6NeighbourDiscovery::initiateAddressRegistration(const Ipv6Address& myIpv6Addr, Ipv6Address& destAddr, InterfaceEntry *ie)
{
    EV_INFO << "----------INITIATING ADDRESS REGISTRATION WITHOUT DAD----------" << endl;

    ie->ipv6Data()->setDadInProgress(false);
    AddrRegistEntry *addrRegistEntry = new AddrRegistEntry();
    addrRegistEntry->interfaceId = ie->getInterfaceId();
    addrRegistEntry->numNSSent = 0;
    addrRegistEntry->numNSSent++;

    EV_INFO << "Sending unicast AR NS messages with ARO" << endl;
    EV_INFO << "NS source address is: " << ie->ipv6Data()->getAddress(0)<< endl;
    EV_INFO << "NS dest address is: " << destAddr << endl;
    createAndSendNsPacket(myIpv6Addr, destAddr, ie->ipv6Data()->getAddress(0), ie);

    /*and sets a timer to expire in DELAY_FIRST_PROBE_TIME seconds.*/
    cMessage *msg = new cMessage("AddrRegistRetransmit", MK_ADDR_REGIST_RETRANS);
    msg->setContextPointer(ie);
    addrRegistEntry->timeoutMsg = msg;
    addrRegistList.insert(addrRegistEntry);
    //    nce->nudTimeoutEvent = msg;
    scheduleAt(simTime() + 20 +uniform(0.000001,0.00002), msg);
}

//vehicles need to resend address registration msg to maintain its registration
void Ipv6NeighbourDiscovery::processAddrRegistRetransmit(cMessage *msg)
{
    EV_INFO <<"Process Address Registration Update!"<< endl;
//    simtime_t interval = uniform(ie->ipv6Data()->getMinRtrAdvInterval(), ie->ipv6Data()->getMaxRtrAdvInterval());
    simtime_t interval = 5;

    //CN do not process address registration
#ifdef WITH_xMIPv6
    if (!rt6->isMobileNode()) {
        delete msg;
        return;
    }

#endif
    InterfaceEntry *ie = ift->getInterfaceByName("nic");
    AddrRegistEntry *addrRegistEntry = fetchAddrRegistEntry(ie);

    if (addrRegistEntry==nullptr) {
        EV_INFO <<"addrRegistEntry is null."<< endl;
    }

    if (addrRegistEntry!=nullptr && addrRegistEntry->numNSSent < 2) {
        EV_INFO <<"Sending another NS address registration message."<< endl;
        Ipv6Address destAddr;
        if (neighbourCache.getDefaultRouterList().begin() != neighbourCache.getDefaultRouterList().end()) {
            auto it =neighbourCache.getDefaultRouterList().begin();
            Neighbour& nce = *it;
            //if default router is not null, set router's address as nexthop
            destAddr = nce.nceKey->address;
        }
        else
            destAddr = Ipv6Address::ALL_NODES_2;

        //for simulation test
        addrRegistEntry->numNSSent==1? interval = 18:interval = 3;

        Ipv6Address tentativeAddr = ie->ipv6Data()->getPreferredAddress();
        Ipv6Address srcAddr = ie->ipv6Data()->getPreferredAddress();
        addrRegistEntry->numNSSent++;
        createAndSendNsPacket(tentativeAddr, destAddr, srcAddr, ie);
        simtime_t nextScheduledTime = simTime() + interval + uniform(0.000001,0.00002);
        scheduleAt(nextScheduledTime, msg);

    }

    else {
        EV_INFO <<"Max number of NS messages sent, address registration no reply from router."<< endl;
        delete addrRegistEntry;
        addrRegistList.erase(addrRegistEntry);
        delete msg;

        //delete default router when address registration failed
        if (neighbourCache.getDefaultRouterList().begin() != neighbourCache.getDefaultRouterList().end()) {
            auto it =neighbourCache.getDefaultRouterList().begin();
            Neighbour& nce = *it;
            Ipv6Address routerAddr = nce.nceKey->address;
            neighbourCache.remove(routerAddr, ie->getInterfaceId());
//            std::cout<< "delete default router successful!"<<endl;
        }

        //Restart Router Discovery
        EV_INFO << "creating router discovery message timer\n";
        cMessage *rtrDisMsg = new cMessage("initiateRTRDIS", MK_INITIATE_RTRDIS);
        rtrDisMsg->setContextPointer(ie);
        simtime_t interval = uniform(0, ie->ipv6Data()->_getMaxRtrSolicitationDelay());    // random delay
        scheduleAt(simTime() + interval, rtrDisMsg);

    }

}

//RSU need to delete NCE if didn't receive update message from this vehicle
void Ipv6NeighbourDiscovery::processAddrRegistTimeout(cMessage *msg)  {
   Neighbour *nce = (Neighbour *)msg->getContextPointer();
   const Key *nceKey = nce->nceKey;

   if (simTime() > nce->registLifeTime &&nceKey!=nullptr) {
        neighbourCache.remove(nceKey->address, nceKey->interfaceID);
        EV_INFO << "Delete NCE for: "<< nce->macAddress <<endl;
   }
   delete msg;

}

void Ipv6NeighbourDiscovery::processDadTimeout(cMessage *msg)
{
    DadEntry *dadEntry = (DadEntry *)msg->getContextPointer();
    InterfaceEntry *ie = ift->getInterfaceById(dadEntry->interfaceId);
    Ipv6Address tentativeAddr = dadEntry->address;
    //Here, we need to check how many DAD messages for the interface entry were
    //sent vs. DupAddrDetectTransmits
    EV_DETAIL << "numOfDADMessagesSent is: " << dadEntry->numNSSent << endl;
    EV_DETAIL << "dupAddrDetectTrans is: " << ie->ipv6Data()->getDupAddrDetectTransmits() << endl;

    if (dadEntry->numNSSent < ie->ipv6Data()->getDupAddrDetectTransmits()) {
        bubble("Sending another DAD NS message.");
        Ipv6Address destAddr = tentativeAddr.formSolicitedNodeMulticastAddress();
        createAndSendNsPacket(dadEntry->address, destAddr, Ipv6Address::UNSPECIFIED_ADDRESS, ie);
        dadEntry->numNSSent++;

        s1 = simTime().dbl();

        id1 = ie->getMacAddress().getInt();
        // id1 = ie->getInterfaceId();

        signal = s1 + id1;
        emit(startDadSignalTime, signal);
        emit(startDadSignalId, id1);


        //Reuse the received msg
        scheduleAt(simTime() + ie->ipv6Data()->getRetransTimer(), msg);
    }
    else {
        bubble("Max number of DAD messages for interface sent. Address is unique.");

        dadList.erase(dadEntry);
        EV_DETAIL << "delete dadEntry and msg\n";
        delete dadEntry;
        delete msg;


        s1 = simTime().dbl();

        id1 = ie->getMacAddress().getInt();
        // id1 = ie->getInterfaceId();

        signal = s1 + id1;
        emit(finishDadSignalTime, signal);
        emit(finishDadSignalId, id1);

        makeTentativeAddressPermanent(tentativeAddr, ie);
    }
}

void Ipv6NeighbourDiscovery::processMultihopDadTimeout(cMessage *msg)
{

    multihopDadEntry *multihopdadEntry = (multihopDadEntry *)msg->getContextPointer();
    InterfaceEntry *ie = ift->getInterfaceById(multihopdadEntry->interfaceId);

    if (!ie->ipv6Data()->isDadInProgress()) {
        delete msg;
        return;
    }

    Ipv6Address tentativeAddr = multihopdadEntry->address;
//    std::cout << "PROCESS MULTIHOP DAD TIMEOUT: "<<tentativeAddr <<endl;

    //Here, we need to check how many DAD messages for the interface entry were
    //sent vs. DupAddrDetectTransmits
//    std::cout << "numOfMultihopDADMessagesSent is: " << multihopdadEntry->numNSSent << endl;

//    if (multihopdadEntry->numNSSent < ie->ipv6Data()->getDupAddrDetectTransmits()) {
    if (multihopdadEntry->numNSSent <= 2) {
        bubble("Sending another Multihop DAD NS message.");

        if (neighbourCache.getDefaultRouterList().begin() != neighbourCache.getDefaultRouterList().end()) {
            EV_INFO<<"start Multihop DAD for: "<<ie->ipv6Data()->getLinkLocalAddress()<< endl;
            auto it =neighbourCache.getDefaultRouterList().begin();
            Neighbour& nce = *it;
            Ipv6Address destAddr = nce.nceKey->address;
            createAndSendNsPacket(ie->ipv6Data()->getPreferredAddress(), destAddr ,ie->ipv6Data()->getAddress(0),  ie);
            multihopdadEntry->numNSSent++;


            s1 = simTime().dbl();

            id1 = ie->getMacAddress().getInt();
            // id1 = ie->getInterfaceId();


            signal = s1 + id1;
            emit(startDadSignalTime, signal);
            emit(startDadSignalId, id1);


            //Reuse the received msg
            scheduleAt(simTime() + uniform(0.005,0.01)+uniform(0.0001,0.001), msg);
//            scheduleAt(simTime() + ie->ipv6Data()->getRetransTimer(), msg);
        }
        else
            delete msg;
    }
    else {
        bubble("Max number of multihop DAD messages for interface sent. Cancel DAD.");
        multihopdadList.erase(multihopdadEntry);
        EV_DETAIL << "delete dadEntry and msg\n";



        s1 = simTime().dbl();

        id1 = ie->getMacAddress().getInt();
        // id1 = ie->getInterfaceId();

        signal = s1 + id1;
        emit(finishDadSignalTime, signal);
        emit(finishDadSignalId, id1);


        delete multihopdadEntry;
        delete msg;

    }
}

void Ipv6NeighbourDiscovery::makeTentativeAddressPermanent(const Ipv6Address& tentativeAddr, InterfaceEntry *ie)
{
    ie->ipv6Data()->permanentlyAssign(tentativeAddr);

#ifdef WITH_xMIPv6
    if (ie->ipv6Data()->isDadInProgress()== true){
        //dadFinishTime = simTime();
       // emit(dadFinishTimeSignal, dadFinishTime);
    }
    ie->ipv6Data()->setDadInProgress(false);

    // update 28.09.07 - CB
    // after the link-local address was verified to be unique
    // we can assign the address and initiate the MIPv6 protocol
    // in case there are any pending entries in the list
    auto it = dadGlobalList.find(ie);
    if (it != dadGlobalList.end()) {
        DadGlobalEntry& entry = it->second;

        ie->ipv6Data()->assignAddress(entry.addr, false, simTime() + entry.validLifetime,
                simTime() + entry.preferredLifetime, entry.hFlag);

        // moved from processRAPrefixInfoForAddrAutoConf()
        // we can remove the old CoA now
        if (!entry.CoA.isUnspecified())
            ie->ipv6Data()->removeAddress(entry.CoA);

        // set addresses on this interface to tentative=false
        for (int i = 0; i < ie->ipv6Data()->getNumAddresses(); i++) {
            // TODO improve this code so that only addresses are permanently assigned
            // which are formed based on the new prefix from the RA
            Ipv6Address addr = ie->ipv6Data()->getAddress(i);
            ie->ipv6Data()->permanentlyAssign(addr);
        }

        // if we have MIPv6 protocols on this node we will eventually have to
        // call some appropriate methods
        if (rt6->isMobileNode()) {
            if (entry.hFlag == false) // if we are not in the home network, send BUs
                mipv6->initiateMipv6Protocol(ie, tentativeAddr);
            /*
               else if ( entry.returnedHome ) // if we are again in the home network
               {
                ASSERT(entry.CoA.isUnspecified() == false);
                mipv6->returningHome(entry.CoA, ie); // initiate the returning home procedure
               }*/
        }

        dadGlobalList.erase(it->first);
    }

    // an optimization to make sure that the access router on the link gets our L2 address
    //sendUnsolicitedNA(ie);

    // =================================Start: Zarrar Yousaf 08.07.07 ===============================================
    /* == Calling the routine to assign global scope adddresses to the the routers only. At present during the simulation initialization, the Ipv6FlatNetworkConfigurator assigns a 64 bit prefix to the routers but for xMIPv6 operation, we need full 128bit global scope address, only for routers. The call to  autoConfRouterGlobalScopeAddress() will autoconfigure the full 128 bit global scope address, which will be used by the MN in its BU message destination address, especially for home registeration.
     */
    if (rt6->isRouter() && !(ie->isLoopback())) {
        for (int i = 0; i < ie->ipv6Data()->getNumAdvPrefixes(); i++) {
            Ipv6Address globalAddress = ie->ipv6Data()->autoConfRouterGlobalScopeAddress(i);
            ie->ipv6Data()->assignAddress(globalAddress, false, 0, 0);
            // ie->ipv6Data()->deduceAdvPrefix(); //commented out but the above two statements can be replaced with this single statement. But i am using the above two statements for clarity reasons.
        }
    }
    // ==================================End: Zarrar Yousaf 08.07.07===========================================
#endif /* WITH_xMIPv6 */

    /*RFC 2461: Section 6.3.7 2nd Paragraph
       Before a host sends an initial solicitation, it SHOULD delay the
       transmission for a random amount of time between 0 and
       MAX_RTR_SOLICITATION_DELAY.  This serves to alleviate congestion when
       many hosts start up on a link at the same time, such as might happen
       after recovery from a power failure.*/
    //TODO: Placing these operations here means fast router solicitation is
    //not adopted. Will relocate.
    if (ie->ipv6Data()->getAdvSendAdvertisements() == false) {
        EV_INFO << "creating router discovery message timer\n";
        cMessage *rtrDisMsg = new cMessage("initiateRTRDIS", MK_INITIATE_RTRDIS);
        rtrDisMsg->setContextPointer(ie);
        simtime_t interval = uniform(0, ie->ipv6Data()->_getMaxRtrSolicitationDelay());    // random delay
        scheduleAt(simTime() + interval, rtrDisMsg);
    }
}

void Ipv6NeighbourDiscovery::createAndSendRsPacket(InterfaceEntry *ie)
{
    ASSERT(ie->ipv6Data()->getAdvSendAdvertisements() == false);
    //RFC 2461: Section 6.3.7 Sending Router Solicitations
    //A host sends Router Solicitations to the All-Routers multicast address. The
    //IP source address is set to either one of the interface's unicast addresses
    //or the unspecified address.
    Ipv6Address myIPv6Address = ie->ipv6Data()->getPreferredAddress();

    if (myIPv6Address.isUnspecified())
        myIPv6Address = ie->ipv6Data()->getLinkLocalAddress(); //so we use the link local address instead

    if (ie->ipv6Data()->isTentativeAddress(myIPv6Address))
        myIPv6Address = Ipv6Address::UNSPECIFIED_ADDRESS; //set my Ipv6 address to unspecified.

    Ipv6Address destAddr = Ipv6Address::ALL_ROUTERS_2;    //all_routers multicast
    auto rs = makeShared<Ipv6RouterSolicitation>();
    rs->setChunkLength(ICMPv6_HEADER_BYTES);

    //XIANG ZHONG
    //6LoWPAN 5.3 SLLAO must be included
    rs->setSourceLinkLayerAddress(ie->getMacAddress());
    rs->setChunkLength(ICMPv6_HEADER_BYTES + IPv6ND_LINK_LAYER_ADDRESS_OPTION_LENGTH);

    //The Source Link-Layer Address option SHOULD be set to the host's link-layer
    //address, if the IP source address is not the unspecified address.
    if (!myIPv6Address.isUnspecified()) {
        rs->setSourceLinkLayerAddress(ie->getMacAddress());
        rs->setChunkLength(ICMPv6_HEADER_BYTES + IPv6ND_LINK_LAYER_ADDRESS_OPTION_LENGTH);
    }

    //Construct a Router Solicitation message
    auto packet = new Packet("RSpacket");
    Icmpv6::insertCrc(crcMode, rs, packet);
    packet->insertAtFront(rs);
    sendPacketToIpv6Module(packet, destAddr, myIPv6Address, ie->getInterfaceId());
}

void Ipv6NeighbourDiscovery::initiateRouterDiscovery(cMessage *msg)
{
    EV_INFO << "Initiating Router Discovery" << endl;
    InterfaceEntry *ie = (InterfaceEntry *)msg->getContextPointer();
    delete msg;
    //RFC2461: Section 6.3.7
    /*When an interface becomes enabled, a host may be unwilling to wait for the
       next unsolicited Router Advertisement to locate default routers or learn
       prefixes.  To obtain Router Advertisements quickly, a host SHOULD transmit up
       to MAX_RTR_SOLICITATIONS Router Solicitation messages each separated by at
       least RTR_SOLICITATION_INTERVAL seconds.(FIXME:Therefore this should be invoked
       at the beginning of the simulation-WEI)*/
    RdEntry *rdEntry = new RdEntry();
    rdEntry->interfaceId = ie->getInterfaceId();
    rdEntry->numRSSent = 0;
    createAndSendRsPacket(ie);
    rdEntry->numRSSent++;

    //Create and schedule a message for retransmission to this module
    cMessage *rdTimeoutMsg = new cMessage("processRDTimeout", MK_RD_TIMEOUT);
    rdTimeoutMsg->setContextPointer(ie);
    rdEntry->timeoutMsg = rdTimeoutMsg;
    rdList.insert(rdEntry);
    /*Before a host sends an initial solicitation, it SHOULD delay the
       transmission for a random amount of time between 0 and
       MAX_RTR_SOLICITATION_DELAY.  This serves to alleviate congestion when
       many hosts start up on a link at the same time, such as might happen
       after recovery from a power failure.  If a host has already performed
       a random delay since the interface became (re)enabled (e.g., as part
       of Duplicate Address Detection [ADDRCONF]) there is no need to delay
       again before sending the first Router Solicitation message.*/
    //simtime_t rndInterval = uniform(0, ie->ipv6Data()->_getMaxRtrSolicitationDelay());

    //simulation test
//    scheduleAt(simTime() + ie->ipv6Data()->_getRtrSolicitationInterval(), rdTimeoutMsg);
    scheduleAt(simTime() + 0.5, rdTimeoutMsg);
}

void Ipv6NeighbourDiscovery::cancelRouterDiscovery(InterfaceEntry *ie)
{
    //Next we retrieve the rdEntry with the Interface Entry.
    RdEntry *rdEntry = fetchRdEntry(ie);
    if (rdEntry != nullptr) {
        EV_DETAIL << "rdEntry is not nullptr, RD cancelled!" << endl;
        cancelAndDelete(rdEntry->timeoutMsg);
        rdList.erase(rdEntry);
        delete rdEntry;
    }
    else
        EV_DETAIL << "rdEntry is nullptr, not cancelling RD!" << endl;
}


//If neighbor discovery timeout, start again
void Ipv6NeighbourDiscovery::processNdTimeout(cMessage *msg)
{
    InterfaceEntry *ie = (InterfaceEntry *)msg->getContextPointer();
    if (neighbourCache.getDefaultRouterList().begin() == neighbourCache.getDefaultRouterList().end()) {
        EV_INFO <<"Process Neighbor Discovery Timeout!"<<endl;
//        std::cout <<"Process Neighbor Discovery Timeout!"<<endl;
        Ipv6Address tentativeAddr = ie->ipv6Data()->getLinkLocalAddress();
        createAndSendNsPacket(tentativeAddr, Ipv6Address::ALL_NODES_2,
                            tentativeAddr, ie);

        cMessage *ndTimeout = new cMessage ("ND Timeout",MK_ND_TIMEOUT);
        ndTimeout->setContextPointer(ie);
        scheduleAt(simTime() + 2, ndTimeout);

        //create timeout message
        cMessage *decisionMsg = new cMessage("Decision Maker", MK_DECISION_MAKER);
        decisionMsg->setContextPointer(ie);
        scheduleAt(simTime() + 1.5, decisionMsg);

    }
    delete msg;

}

//for performance evaluation, we need to trigger multihop dad at the same time for vehicles
void Ipv6NeighbourDiscovery::msgTriggerForMultihopDAD(cMessage *msg) {

    InterfaceEntry *ie = ift->getInterfaceByName("nic");
    initiateMultihopDad(ie->ipv6Data()->getPreferredAddress(), dadDest, ie);
//    std::cout <<" ====>>> msgTriggerForMultihopDAD " <<std::endl;
    delete msg;
}

void Ipv6NeighbourDiscovery::processRdTimeout(cMessage *msg)
{
    InterfaceEntry *ie = (InterfaceEntry *)msg->getContextPointer();
    RdEntry *rdEntry = fetchRdEntry(ie);

    //simulation test
    if (rdEntry->numRSSent < ie->ipv6Data()->_getMaxRtrSolicitations()) {
//    if (rdEntry->numRSSent < 1) {
        bubble("Sending another RS message.");
        createAndSendRsPacket(ie);
        rdEntry->numRSSent++;

        //Need to find out if this is the last RS we are sending out.
        if (rdEntry->numRSSent == ie->ipv6Data()->_getMaxRtrSolicitations())

        //simulation test, reduce the retransmission interval
//        if (rdEntry->numRSSent == 1)
//            scheduleAt(simTime() + ie->ipv6Data()->_getMaxRtrSolicitationDelay(), msg);
            scheduleAt(simTime() + 0.5, msg);
        else
//            scheduleAt(simTime() + ie->ipv6Data()->_getRtrSolicitationInterval(), msg);
            scheduleAt(simTime() + 0.5, msg);
    }
    else {
        //RFC 2461, Section 6.3.7
        /*If a host sends MAX_RTR_SOLICITATIONS solicitations, and receives no Router
           Advertisements after having waited MAX_RTR_SOLICITATION_DELAY seconds after
           sending the last solicitation, the host concludes that there are no routers
           on the link for the purpose of [ADDRCONF]. However, the host continues to
           receive and process Router Advertisements messages in the event that routers
           appear on the link.*/
        bubble("Max number of RS messages sent");
        EV_INFO << "No RA messages were received. Assume no routers are on-link";
        delete rdEntry;
        rdList.erase(rdEntry);
        delete msg;

        //Assumption: if no router on-link, start neighbor discovery to look for vehicle neighbors who can work as relay vehicle for me
        Ipv6Address tentativeAddr = ie->ipv6Data()->getLinkLocalAddress();
        createAndSendNsPacket(tentativeAddr, Ipv6Address::ALL_NODES_2,
                    tentativeAddr, ie);

        cMessage *ndTimeout = new cMessage ("ND Timeout",MK_ND_TIMEOUT);
        ndTimeout->setContextPointer(ie);
        scheduleAt(simTime() + 2, ndTimeout);

        //to receive replies from many vehicles and choose the closest neighbor, we need to wait for 1.5 seconds to make the decision of the relay vehicle
        cMessage *decisionMsg = new cMessage("Decision Maker", MK_DECISION_MAKER);
        decisionMsg->setContextPointer(ie);
        scheduleAt(simTime() + 1.5, decisionMsg);

    }
}

void Ipv6NeighbourDiscovery::processRsPacket(Packet *packet, const Ipv6RouterSolicitation *rs)
{
//    std::cout <<"----->< processRsPacket" <<std::endl;
    if (validateRsPacket(packet, rs) == false) {
        delete packet;
        return;
    }

    //Find out which interface the RS message arrived on.
    InterfaceEntry *ie = ift->getInterfaceById(packet->getTag<InterfaceInd>()->getInterfaceId());
    AdvIfEntry *advIfEntry = fetchAdvIfEntry(ie);    //fetch advertising interface entry.

    //RFC 2461: Section 6.2.6
    //A host MUST silently discard any received Router Solicitation messages.
    if (ie->ipv6Data()->getAdvSendAdvertisements()) {
        EV_INFO << "This is an advertising interface, processing RS\n";

        if (validateRsPacket(packet, rs) == false) {
            delete packet;
            return;
        }

        EV_INFO << "RS message validated\n";

        //First we extract RS specific information from the received message
        MacAddress macAddr = rs->getSourceLinkLayerAddress();
        EV_INFO << "MAC Address '" << macAddr << "' extracted\n";

        /*A router MAY choose to unicast the response directly to the soliciting
           host's address (if the solicitation's source address is not the unspecified
           address), but the usual case is to multicast the response to the
           all-nodes group. In the latter case, the interface's interval timer is
           reset to a new random value, as if an unsolicited advertisement had just
           been sent(see Section 6.2.4).*/

        /*In all cases, Router Advertisements sent in response to a Router
           Solicitation MUST be delayed by a random time between 0 and
           MAX_RA_DELAY_TIME seconds. (If a single advertisement is sent in
           response to multiple solicitations, the delay is relative to the
           first solicitation.)  In addition, consecutive Router Advertisements
           sent to the all-nodes multicast address MUST be rate limited to no
           more than one advertisement every MIN_DELAY_BETWEEN_RAS seconds.*/

        /*A router might process Router Solicitations as follows:
           - Upon receipt of a Router Solicitation, compute a random delay
           within the range 0 through MAX_RA_DELAY_TIME. If the computed
           value corresponds to a time later than the time the next multicast
           Router Advertisement is scheduled to be sent, ignore the random
           delay and send the advertisement at the already-scheduled time.*/


  //---------------------------------------------------------------------------------------//

//        cMessage *msg = new cMessage("sendSolicitedRA", MK_SEND_SOL_RTRADV);
//        msg->setContextPointer(ie);
//        simtime_t interval = uniform(0, ie->ipv6Data()->_getMaxRaDelayTime());
//
//        //XIANG
//        simtime_t nextScheduledTime;
//        nextScheduledTime = simTime() + interval;
//        scheduleAt(nextScheduledTime, msg);
//
//        if (interval < advIfEntry->nextScheduledRATime) {
//            //XIANG
////            simtime_t nextScheduledTime;
////            nextScheduledTime = simTime() + interval;
////            scheduleAt(nextScheduledTime, msg);
//            advIfEntry->nextScheduledRATime = nextScheduledTime;
//        }

  //----------------------------------------------------------------------------------------//
        //change the broadcast RA into unicast
        EV_INFO << "Send Solicited RA!\n";
//        Ipv6Address destAddr = Ipv6Address("FF02::1");
        Ipv6Address destAddr = packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6();
        EV_DETAIL << "Testing not invoked by cMessage!\n";
        createAndSendRaPacket(destAddr, ie);

        //else we ignore the generate interval and send it at the next scheduled time.

        //We need to keep a log here each time an RA is sent. Not implemented yet.
        //Assume the first course of action.
        /*- If the router sent a multicast Router Advertisement (solicited or
           unsolicited) within the last MIN_DELAY_BETWEEN_RAS seconds,
           schedule the advertisement to be sent at a time corresponding to
           MIN_DELAY_BETWEEN_RAS plus the random value after the previous
           advertisement was sent. This ensures that the multicast Router
           Advertisements are rate limited.

           - Otherwise, schedule the sending of a Router Advertisement at the
           time given by the random value.*/
    }
    else {
        EV_INFO << "This interface is a host, discarding RA message\n";
    }
    delete packet;
}

bool Ipv6NeighbourDiscovery::validateRsPacket(Packet *packet, const Ipv6RouterSolicitation *rs)
{
    bool result = true;
    /*6.1.1.  Validation of Router Solicitation Messages
       A router MUST silently discard any received Router Solicitation
       messages that do not satisfy all of the following validity checks:

       - The IP Hop Limit field has a value of 255, i.e., the packet
       could not possibly have been forwarded by a router.*/
    if (packet->getTag<HopLimitInd>()->getHopLimit() != 255) {
        EV_WARN << "Hop limit is not 255! RS validation failed!\n";
        result = false;
    }

    //- ICMP Code is 0.
    if (packet->getTag<PacketProtocolTag>()->getProtocol() != &Protocol::icmpv6) {
        EV_WARN << "ICMP Code is not 0! RS validation failed!\n";
        result = false;
    }

    //- If the IP source address is the unspecified address, there is no
    //source link-layer address option in the message.
    if (packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6().isUnspecified()) {
        EV_WARN << "IP source address is unspecified\n";

        if (rs->getSourceLinkLayerAddress().isUnspecified() == false) {
            EV_WARN << " but source link layer address is provided. RS validation failed!\n";
        }
    }

    return result;
}

void Ipv6NeighbourDiscovery::createAndSendRaPacket(const Ipv6Address& destAddr, InterfaceEntry *ie)
{
    EV_INFO << "Create and send RA invoked!\n";
    //Must use link-local addr. See: RFC2461 Section 6.1.2


    Ipv6Address sourceAddr = ie->ipv6Data()->getLinkLocalAddress();
    //This operation includes all options, regardless whether it is solicited or unsolicited.
    if (ie->ipv6Data()->getAdvSendAdvertisements()) {    //if this is an advertising interface
        //Construct a Router Advertisment message
        auto ra = makeShared<Ipv6RouterAdvertisement>();

        //RFC 2461: Section 6.2.3 Router Advertisment Message Content
        /*A router sends periodic as well as solicited Router Advertisements out
           its advertising interfaces.  Outgoing Router Advertisements are filled
           with the following values consistent with the message format given in
           Section 4.2:*/

        //- In the Router Lifetime field: the interface's configured AdvDefaultLifetime.
        ra->setRouterLifetime(SIMTIME_DBL(ie->ipv6Data()->getAdvDefaultLifetime()));


        //- In the M and O flags: the interface's configured AdvManagedFlag and
        //AdvOtherConfigFlag, respectively.  See [ADDRCONF].
        ra->setManagedAddrConfFlag(ie->ipv6Data()->getAdvManagedFlag());
        ra->setOtherStatefulConfFlag(ie->ipv6Data()->getAdvOtherConfigFlag());

        //since vehicles may share the RSU information to remote vehicles, we need to include RSU's global address
        ra->setSrcGlobalAddress(ie->ipv6Data()->getGlobalAddress());

        if (destAddr.isGlobal())
            ra->setIsDadRequired(false);
        else
            ra->setIsDadRequired(true);

#ifdef WITH_xMIPv6
        // Configuring the HomeAgentFlag (H-bit) (RFC 3775): Zarrar 25.02.07
        if (rt6->isHomeAgent())
            ra->setHomeAgentFlag(true); //Set H-bit if the router is a HA
        else
            ra->setHomeAgentFlag(ie->ipv6Data()->getAdvHomeAgentFlag()); //else unset it, which is default
#endif /* WITH_xMIPv6 */

        //- In the Cur Hop Limit field: the interface's configured CurHopLimit.
        ra->setCurHopLimit(ie->ipv6Data()->getAdvCurHopLimit());

        //- In the Reachable Time field: the interface's configured AdvReachableTime.
        ra->setReachableTime(ie->ipv6Data()->getAdvReachableTime());

        //- In the Retrans Timer field: the interface's configured AdvRetransTimer.
        ra->setRetransTimer(ie->ipv6Data()->getAdvRetransTimer());

        //- In the options:
        /*o Source Link-Layer Address option: link-layer address of the sending
            interface.  (Assumption: We always send this)*/
        ra->setSourceLinkLayerAddress(ie->getMacAddress());
        ra->setMTU(ie->ipv6Data()->getAdvLinkMtu());

        //Add all Advertising Prefixes to the RA
        int numAdvPrefixes = ie->ipv6Data()->getNumAdvPrefixes();
        EV_DETAIL << "Number of Adv Prefixes: " << numAdvPrefixes << endl;
        ra->setPrefixInformationArraySize(numAdvPrefixes);
        for (int i = 0; i < numAdvPrefixes; i++) {
            Ipv6InterfaceData::AdvPrefix advPrefix = ie->ipv6Data()->getAdvPrefix(i);
            Ipv6NdPrefixInformation prefixInfo;
            //include the global common prefix
            //for test
            prefixInfo.setDistance(1);
            advPrefix.prefix = Ipv6Address("aaaa:0:64::");

#ifndef WITH_xMIPv6
            prefixInfo.setPrefix(advPrefix.prefix);

#else /* WITH_xMIPv6 */
            EV_DETAIL << "\n+=+=+=+= Appendign Prefix Info Option to RA +=+=+=+=\n";
            EV_DETAIL << "Prefix Value: " << advPrefix.prefix << endl;
            EV_DETAIL << "Prefix Length: " << advPrefix.prefixLength << endl;
            EV_DETAIL << "L-Flag: " << advPrefix.advOnLinkFlag << endl;
            EV_DETAIL << "A-Flag: " << advPrefix.advAutonomousFlag << endl;
            EV_DETAIL << "R-Flag: " << advPrefix.advRtrAddr << endl;
            EV_DETAIL << "Global Address from Prefix: " << advPrefix.rtrAddress << endl;

            if (rt6->isHomeAgent() && advPrefix.advRtrAddr == true)
                prefixInfo.setPrefix(advPrefix.rtrAddress); //add the global-scope address of the HA's interface in the prefix option list of the RA message.
            else
                prefixInfo.setPrefix(advPrefix.prefix); //adds the prefix only of the router's interface in the prefix option list of the RA message.
#endif /* WITH_xMIPv6 */

            prefixInfo.setPrefixLength(advPrefix.prefixLength);

            //- In the "on-link" flag: the entry's AdvOnLinkFlag.
            prefixInfo.setOnlinkFlag(advPrefix.advOnLinkFlag);
            //- In the Valid Lifetime field: the entry's AdvValidLifetime.
            prefixInfo.setValidLifetime(SIMTIME_DBL(advPrefix.advValidLifetime));
            //- In the "Autonomous address configuration" flag: the entry's
            //AdvAutonomousFlag.
            prefixInfo.setAutoAddressConfFlag(advPrefix.advAutonomousFlag);

#ifdef WITH_xMIPv6
            if (rt6->isHomeAgent())
                prefixInfo.setRouterAddressFlag(true); // set the R-bit if the node is a HA

            //- In the Valid Lifetime field: the entry's AdvValidLifetime.
            prefixInfo.setValidLifetime(SIMTIME_DBL(advPrefix.advValidLifetime));
#endif /* WITH_xMIPv6 */

            //- In the Preferred Lifetime field: the entry's AdvPreferredLifetime.
            prefixInfo.setPreferredLifetime(SIMTIME_DBL(advPrefix.advPreferredLifetime));
            //Now we pop the prefix info into the RA.
            ra->setPrefixInformation(i, prefixInfo);
        }

        ra->setChunkLength(ICMPv6_HEADER_BYTES + IPv6ND_PREFIX_INFORMATION_OPTION_LENGTH * numAdvPrefixes);

        auto packet = new Packet("RApacket");
        Icmpv6::insertCrc(crcMode, ra, packet);
        packet->insertAtFront(ra);
        sendPacketToIpv6Module(packet, destAddr, sourceAddr, ie->getInterfaceId());

        numRAsent++;
    }
}


void Ipv6NeighbourDiscovery::processRaPacket(Packet *packet, const Ipv6RouterAdvertisement *ra)
{
//    std::cout <<" =====>>. process Ra Packet " <<std::endl;
    InterfaceEntry *ie = ift->getInterfaceById(packet->getTag<InterfaceInd>()->getInterfaceId());
    EV_INFO << "Interface name is: "<< ie->getInterfaceName()<<endl;
    if (ie->ipv6Data()->getAdvSendAdvertisements()) {
        EV_INFO << "Interface is an advertising interface, dropping RA message.\n";
        delete packet;
        return;
    }
    else {
        if (validateRaPacket(packet, ra) == false) {
            delete packet;
            return;
        }

#ifdef WITH_xMIPv6
        if (ie->ipv6Data()->isDadInProgress()) {
            // in case we are currently performing DAD we ignore this RA
            // TODO improve this procedure in order to allow reinitiating DAD
            // (which means cancel current DAD, start new DAD)
            delete packet;
            return;
        }
#endif /* WITH_xMIPv6 */

        cancelRouterDiscovery(ie);    //Cancel router discovery if it is in progress.
        EV_INFO << "Interface is a host, processing RA.\n";

        processRaForRouterUpdates(packet, ra);    //See RFC2461: Section 6.3.4

        if (!ra->isDadRequired()) {
            //skip DAD
            Ipv6Address destAddr = packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6();
            initiateAddressRegistration(ie->ipv6Data()->getPreferredAddress(), destAddr, ie);
        }

        //Possible options
        //MacAddress macAddress = ra->getSourceLinkLayerAddress();
        //uint mtu = ra->getMTU();
        for (int i = 0; i < (int)ra->getPrefixInformationArraySize(); i++) {
            const Ipv6NdPrefixInformation& prefixInfo = ra->getPrefixInformation(i);
            if (prefixInfo.getAutoAddressConfFlag() == true) {    //If auto addr conf is set
#ifndef WITH_xMIPv6
                processRaPrefixInfoForAddrAutoConf(prefixInfo, ie);    //We process prefix Info and form an addr
#else /* WITH_xMIPv6 */
                processRaPrefixInfoForAddrAutoConf(prefixInfo, ie, ra->getHomeAgentFlag());    // then calling the overloaded function for address configuration. The address conf for MN is different from other nodes as it needs to classify the newly formed address as HoA or CoA, depending on the status of the H-Flag. (Zarrar Yousaf 20.07.07)
#endif /* WITH_xMIPv6 */
            }

#ifdef WITH_xMIPv6
            // When in foreign network(s), the MN needs info about its HA address and its own Home Address (HoA), when sending BU to HA and CN(s). Therefore while in the home network I intialise struct HomeNetworkInfo{} with HoA and HA address, which will eventually be used by the MN while sending BUs from within visit networks. (Zarrar Yousaf 12.07.07)
            if (ra->getHomeAgentFlag() && (prefixInfo.getRouterAddressFlag() == true)) {    //If R-Flag is set and RA is from HA
                // homeNetworkInfo now carries HoA, global unicast HA address and the home network prefix
                // update 4.9.07 - CB
                Ipv6Address HoA = ie->ipv6Data()->getGlobalAddress();    //MN's home address
                Ipv6Address HA = packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6().setPrefix(prefixInfo.getPrefix(), prefixInfo.getPrefixLength());
                EV_DETAIL << "The HoA of MN is: " << HoA << ", MN's HA Address is: " << HA
                          << " and the home prefix is " << prefixInfo.getPrefix() << endl;
                ie->ipv6Data()->updateHomeNetworkInfo(HoA, HA, prefixInfo.getPrefix(), prefixInfo.getPrefixLength());    //populate the HoA of MN, the HA global scope address and the home network prefix
            }
#endif /* WITH_xMIPv6 */
        }
    }


    delete packet;
}

void Ipv6NeighbourDiscovery::processRaForRouterUpdates(Packet *packet, const Ipv6RouterAdvertisement *ra)
{
    EV_INFO << "Processing RA for Router Updates\n";
//    std::cout << "Processing RA for Router Updates\n";
    //RFC2461: Section 6.3.4
    //Paragraphs 1 and 2 omitted.

    //On receipt of a valid Router Advertisement, a host extracts the source
    //address of the packet and does the following:
    Ipv6Address raSrcAddr = packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6();
    InterfaceEntry *ie = ift->getInterfaceById(packet->getTag<InterfaceInd>()->getInterfaceId());
    int ifID = ie->getInterfaceId();

    /*- If the address is not already present in the host's Default Router List,
       and the advertisement's Router Lifetime is non-zero, create a new entry in
       the list, and initialize its invalidation timer value from the advertisement's
       Router Lifetime field.*/
    Neighbour *neighbour = neighbourCache.lookup(raSrcAddr, ifID);

#ifdef WITH_xMIPv6
    // update 3.9.07 - CB // if (neighbour == nullptr && (ra->homeAgentFlag() == true)) //the RA is from a Router acting as a Home Agent as well
#endif /* WITH_xMIPv6 */

    if (neighbour == nullptr) {
        EV_INFO << "Neighbour Cache Entry does not contain RA's source address\n";
        if (ra->getRouterLifetime() != 0) {
            EV_INFO << "RA's router lifetime is non-zero, creating an entry in the "
                    << "Host's default router list with lifetime=" << ra->getRouterLifetime() << "\n";

#ifdef WITH_xMIPv6
            // initiate neighbour unreachability detection for existing routers and remove default route(r), 3.9.07 - CB
            // TODO improve this code
            routersUnreachabilityDetection(ie);
#endif /* WITH_xMIPv6 */

            //If a Neighbor Cache entry is created for the router its reachability
            //state MUST be set to STALE as specified in Section 7.3.3.

//use global address instead of link-local address
/*
            neighbour = neighbourCache.addRouter(raSrcAddr, ifID,
#ifndef WITH_xMIPv6
                        ra->getSourceLinkLayerAddress(), simTime() + ra->getRouterLifetime());
#else
                        ra->getSourceLinkLayerAddress(), simTime() + ra->getRouterLifetime(), ra->getHomeAgentFlag());
#endif
*/
            neighbour = neighbourCache.addRouterWithGlobalAddr(raSrcAddr, ifID,
#ifndef WITH_xMIPv6
                        ra->getSourceLinkLayerAddress(), simTime() + ra->getRouterLifetime(),ra->getSrcGlobalAddress());
#else
                        ra->getSourceLinkLayerAddress(), simTime() + ra->getRouterLifetime(), ra->getSrcGlobalAddress(), ra->getHomeAgentFlag());
#endif

            //According to Greg, we should add a default route for hosts as well!
            rt6->addDefaultRoute(raSrcAddr, ifID, simTime() + ra->getRouterLifetime());

            //update neighborRoute
            neighbourCache.addNeighborRoute(raSrcAddr, ifID, ra->getSourceLinkLayerAddress(), Ipv6Address::UNSPECIFIED_ADDRESS, 1);

            //XIANG ZHONG 19.03.04
            neighbourCache.addNeighbour(ra->getSrcGlobalAddress(), ifID);
            Neighbour *nbr = neighbourCache.lookup(ra->getSrcGlobalAddress(), ifID);
            nbr->reachabilityState = Ipv6NeighbourCache::REACHABLE;
            nbr->reachabilityExpires = 1000;
            nbr->isRouter = true;
            nbr->macAddress = ra->getSourceLinkLayerAddress();


        }
        else {
            EV_INFO << "Router Lifetime is 0, adding NON-default router.\n";
            //WEI-The router is advertising itself, BUT not as a default router.
            if (ra->getSourceLinkLayerAddress().isUnspecified())
                neighbour = neighbourCache.addNeighbour(raSrcAddr, ifID);
            else
                neighbour = neighbourCache.addNeighbour(raSrcAddr, ifID,
                            ra->getSourceLinkLayerAddress());
            neighbour->isRouter = true;
        }
    }
    else {
        //If no Source Link-Layer Address is included, but a corresponding Neighbor
        //Cache entry exists, its IsRouter flag MUST be set to TRUE.
        neighbour->isRouter = true;

        //If a cache entry already exists and is updated with a different link-
        //layer address the reachability state MUST also be set to STALE.
        if (ra->getSourceLinkLayerAddress().isUnspecified() == false &&
            neighbour->macAddress.equals(ra->getSourceLinkLayerAddress()) == false)
            neighbour->macAddress = ra->getSourceLinkLayerAddress();

        /*- If the address is already present in the host's Default Router List
           as a result of a previously-received advertisement, reset its invalidation
           timer to the Router Lifetime value in the newly-received advertisement.*/
        neighbour->routerExpiryTime = simTime() + ra->getRouterLifetime();

        /*- If the address is already present in the host's Default Router List
           and the received Router Lifetime value is zero, immediately time-out the
           entry as specified in Section 6.3.5.*/
        if (ra->getRouterLifetime() == 0) {
            EV_INFO << "RA's router lifetime is ZERO. Timing-out entry.\n";
            timeoutDefaultRouter(raSrcAddr, ifID);
        }
    }

    //Paragraph Omitted.

    //If the received Cur Hop Limit value is non-zero the host SHOULD set
    //its CurHopLimit variable to the received value.
    if (ra->getCurHopLimit() != 0) {
        EV_INFO << "RA's Cur Hop Limit is non-zero. Setting host's Cur Hop Limit to "
                << "received value.\n";
        ie->ipv6Data()->setCurHopLimit(ra->getCurHopLimit());
    }

    //If the received Reachable Time value is non-zero the host SHOULD set its
    //BaseReachableTime variable to the received value.
    if (ra->getReachableTime() != 0) {
        EV_INFO << "RA's reachable time is non-zero ";

        if (ra->getReachableTime() != SIMTIME_DBL(ie->ipv6Data()->getReachableTime())) {
            EV_INFO << " and RA's and Host's reachable time differ, \nsetting host's base"
                    << " reachable time to received value.\n";
            ie->ipv6Data()->setBaseReachableTime(ra->getReachableTime());
            //If the new value differs from the previous value, the host SHOULD
            //recompute a new random ReachableTime value.
            ie->ipv6Data()->setReachableTime(ie->ipv6Data()->generateReachableTime());
        }

        EV_INFO << endl;
    }

    //The RetransTimer variable SHOULD be copied from the Retrans Timer field,
    //if the received value is non-zero.
    if (ra->getRetransTimer() != 0) {
        EV_INFO << "RA's retrans timer is non-zero, copying retrans timer variable.\n";
        ie->ipv6Data()->setRetransTimer(ra->getRetransTimer());
    }

    /*If the MTU option is present, hosts SHOULD copy the option's value into
       LinkMTU so long as the value is greater than or equal to the minimum link MTU
       [Ipv6] and does not exceed the default LinkMTU value specified in the link
       type specific document (e.g., [Ipv6-ETHER]).*/
    //TODO: not done yet

    processRaPrefixInfo(ra, ie);
}

void Ipv6NeighbourDiscovery::processRaPrefixInfo(const Ipv6RouterAdvertisement *ra, InterfaceEntry *ie)
{
    //Continued from section 6.3.4
    /*Prefix Information options that have the "on-link" (L) flag set indicate a
       prefix identifying a range of addresses that should be considered on-link.
       Note, however, that a Prefix Information option with the on-link flag set to
       zero conveys no information concerning on-link determination and MUST NOT be
       interpreted to mean that addresses covered by the prefix are off-link. The
       only way to cancel a previous on-link indication is to advertise that prefix
       with the L-bit set and the Lifetime set to zero. The default behavior (see
       Section 5.2) when sending a packet to an address for which no information is
       known about the on-link status of the address is to forward the packet to a
       default router; the reception of a Prefix Information option with the "on-link "
       (L) flag set to zero does not change this behavior. The reasons for an address
       being treated as on-link is specified in the definition of "on-link" in
       Section 2.1. Prefixes with the on-link flag set to zero would normally have
       the autonomous flag set and be used by [ADDRCONF].*/
    Ipv6NdPrefixInformation prefixInfo;
    //For each Prefix Information option
    for (int i = 0; i < (int)ra->getPrefixInformationArraySize(); i++) {
        prefixInfo = ra->getPrefixInformation(i);
        if (!prefixInfo.getOnlinkFlag())
            break; //skip to next prefix option

        //with the on-link flag set, a host does the following:
        EV_INFO << "Fetching Prefix Information:" << i + 1 << " of "
                << ra->getPrefixInformationArraySize() << endl;
/*        std::cout << "Fetching Prefix Information:" << i + 1 << " of "
                 << ra->getPrefixInformationArraySize() << endl;*/
        uint prefixLength = prefixInfo.getPrefixLength();
        simtime_t validLifetime = prefixInfo.getValidLifetime();
        //uint preferredLifetime = prefixInfo.getPreferredLifetime();
        Ipv6Address prefix = prefixInfo.getPrefix();

        //- If the prefix is the link-local prefix, silently ignore the Prefix
        //Information option.
        if (prefix.isLinkLocal()) {
            EV_INFO << "Prefix is link-local, ignoring prefix.\n";
            return;
        }

        //- If the prefix is not already present in the Prefix List,
        if (!rt6->isPrefixPresent(prefix)) {
            //and the Prefix Information option's Valid Lifetime field is non-zero,
            if (validLifetime != 0) {
                /*create a new entry for the prefix and initialize its invalidation
                   timer to the Valid Lifetime value in the Prefix Information option.*/
                rt6->addOrUpdateOnLinkPrefix(prefix, prefixLength, ie->getInterfaceId(),
                        simTime() + validLifetime);
            }
            /*- If the Prefix Information option's Valid Lifetime field is zero,
               and the prefix is not present in the host's Prefix List,
               silently ignore the option.*/
        }
        else {
            /* If the new Lifetime value is zero, time-out the prefix immediately
               (see Section 6.3.5).*/
            if (validLifetime == 0) {
                EV_INFO << "Prefix Info's valid lifetime is 0, time-out prefix\n";
                rt6->deleteOnLinkPrefix(prefix, prefixLength);
                return;
            }

            /*- If the prefix is already present in the host's Prefix List as
               the result of a previously-received advertisement, reset its
               invalidation timer to the Valid Lifetime value in the Prefix
               Information option.*/
            rt6->addOrUpdateOnLinkPrefix(prefix, prefixLength, ie->getInterfaceId(),
                    simTime() + validLifetime);
        }

        /*Stateless address autoconfiguration [ADDRCONF] may in some
           circumstances increase the Valid Lifetime of a prefix or ignore it
           completely in order to prevent a particular denial of service attack.
           However, since the effect of the same denial of service targeted at
           the on-link prefix list is not catastrophic (hosts would send packets
           packets directly to a neighbor) the Neighbor Discovery protocol does
           not impose such a check on the prefix lifetime values.*/
    }
}

#ifndef WITH_xMIPv6
void Ipv6NeighbourDiscovery::processRaPrefixInfoForAddrAutoConf(const Ipv6NdPrefixInformation& prefixInfo, InterfaceEntry *ie)
{
    EV_INFO << "Processing Prefix Info for address auto-configuration.\n";
    Ipv6Address prefix = prefixInfo.getPrefix();


    uint prefixLength = prefixInfo.getPrefixLength();
    simtime_t preferredLifetime = prefixInfo.getPreferredLifetime();
    simtime_t validLifetime = prefixInfo.getValidLifetime();

    //RFC 2461: Section 5.5.3
    //First condition tested, the autonomous flag is already set

    //b) If the prefix is the link-local prefix, silently ignore the Prefix
    //Information option.
    if (prefixInfo.getPrefix().isLinkLocal() == true) {
        EV_INFO << "Prefix is link-local, ignore Prefix Information Option\n";
        return;
    }

    //c) If the preferred lifetime is greater than the valid lifetime, silently
    //ignore the Prefix Information option. A node MAY wish to log a system
    //management error in this case.
    if (preferredLifetime > validLifetime) {
        EV_INFO << "Preferred lifetime is greater than valid lifetime, ignore Prefix Information\n";
        return;
    }

    bool isPrefixAssignedToInterface = false;
    for (int i = 0; i < ie->ipv6Data()->getNumAddresses(); i++) {
        if (ie->ipv6Data()->getAddress(i).matches(prefix, prefixLength) == true)
            isPrefixAssignedToInterface = true;
    }

    /*d) If the prefix advertised does not match the prefix of an address already
         in the list, and the Valid Lifetime is not 0, form an address (and add
         it to the list) by combining the advertised prefix with the link�s
         interface identifier as follows:*/
    if (isPrefixAssignedToInterface == false && validLifetime != 0) {
        Ipv6Address linkLocalAddress = ie->ipv6Data()->getLinkLocalAddress();
        ASSERT(linkLocalAddress.isUnspecified() == false);

        Ipv6Address newAddr = linkLocalAddress.setPrefix(prefix, prefixLength);
        //TODO: for now we leave the newly formed address as not tentative,
        //according to Greg, we have to always perform DAD for a newly formed address.
        EV_INFO << "Assigning new address to: " << ie->getInterfaceName() << endl;
        ie->ipv6Data()->assignAddress(newAddr, false, simTime() + validLifetime,
                simTime() + preferredLifetime);
    }

    //TODO: this is the simplified version.
    /*e) If the advertised prefix matches the prefix of an autoconfigured
       address (i.e., one obtained via stateless or stateful address
       autoconfiguration) in the list of addresses associated with the
       interface, the specific action to perform depends on the Valid
       Lifetime in the received advertisement and the Lifetime
       associated with the previously autoconfigured address (which we
       call StoredLifetime in the discussion that follows):

       1) If the received Lifetime is greater than 2 hours or greater
          than StoredLifetime, update the stored Lifetime of the
          corresponding address.

       2) If the StoredLifetime is less than or equal to 2 hours and the
          received Lifetime is less than or equal to StoredLifetime,
          ignore the prefix, unless the Router Advertisement from which

          this Prefix Information option was obtained has been
          authenticated (e.g., via IPSec [RFC2402]). If the Router
          Advertisment was authenticated, the StoredLifetime should be
          set to the Lifetime in the received option.

       3) Otherwise, reset the stored Lifetime in the corresponding
          address to two hours.*/
}

#endif /* WITH_xMIPv6 */

void Ipv6NeighbourDiscovery::createRaTimer(InterfaceEntry *ie)
{
    cMessage *msg = new cMessage("sendPeriodicRA", MK_SEND_PERIODIC_RTRADV);
    msg->setContextPointer(ie);
    AdvIfEntry *advIfEntry = new AdvIfEntry();
    advIfEntry->interfaceId = ie->getInterfaceId();
    advIfEntry->numRASent = 0;

#ifdef WITH_xMIPv6
    // 20.9.07 - CB
    /*if ( rt6->isRouter() )
       {
        ie->ipv6()->setMinRtrAdvInterval(Ipv6NeighbourDiscovery::getMinRAInterval()); //should be 0.07 for MIPv6 Support
        ie->ipv6()->setMaxRtrAdvInterval(Ipv6NeighbourDiscovery::getMaxRAInterval()); //should be 0.03 for MIPv6 Support
       }*/
    // update 23.10.07 - CB

    if (canServeWirelessNodes(ie)) {
        EV_INFO << "This Interface is connected to a WLAN AP, hence using MIPv6 Default Values" << endl;
        simtime_t minRAInterval = par("minIntervalBetweenRAs");    //reading from the omnetpp.ini (ZY 23.07.09)
        simtime_t maxRAInterval = par("maxIntervalBetweenRAs");    //reading from the omnetpp.ini (ZY 23.07.09
        ie->ipv6Data()->setMinRtrAdvInterval(minRAInterval);
        ie->ipv6Data()->setMaxRtrAdvInterval(maxRAInterval);
    }
    else {
        EV_INFO << "This Interface is not connected to a WLAN AP, hence using default values" << endl;
        //interval = uniform( ie->ipv6()->minRtrAdvInterval(), ie->ipv6()->maxRtrAdvInterval() );
        //EV<<"\nThe random calculated RA_ND interval is: "<< interval<<" seconds\n";
    }
    // end CB
#endif /* WITH_xMIPv6 */

    simtime_t interval = uniform(ie->ipv6Data()->getMinRtrAdvInterval(), ie->ipv6Data()->getMaxRtrAdvInterval());
    advIfEntry->raTimeoutMsg = msg;

//    simtime_t nextScheduledTime = simTime() + interval;
    simtime_t nextScheduledTime = simTime() + 2;
    advIfEntry->nextScheduledRATime = nextScheduledTime;
    advIfList.insert(advIfEntry);
    EV_DETAIL << "Interval: " << interval << endl;
    EV_DETAIL << "Next scheduled time: " << nextScheduledTime << endl;
    //now we schedule the msg for whatever time that was derived
    scheduleAt(nextScheduledTime, msg);
}

void Ipv6NeighbourDiscovery::resetRaTimer(InterfaceEntry *ie)
{    //Not used yet but could be useful later on.-WEI
     //Iterate through all RA timers within the Neighbour Discovery module.
/*
    for (auto it =raTimerList.begin(); it != raTimerList.end(); it++)
    {
        cMessage *msg = (*it);
        InterfaceEntry *msgIE = (InterfaceEntry *)msg->getContextPointer();
        //Find the timer that matches the given Interface Entry.
        if (msgIE->outputPort() == ie->outputPort())
        {
            EV << "Resetting RA timer for port: " << ie->outputPort();
            cancelEvent(msg);//Cancel the next scheduled msg.
            simtime_t interval
                = uniform(ie->ipv6Data()->getMinRtrAdvInterval(),ie->ipv6Data()->getMaxRtrAdvInterval());
            scheduleAt(simTime()+interval, msg);
        }
    }
 */
}

void Ipv6NeighbourDiscovery::sendPeriodicRa(cMessage *msg)
{
    InterfaceEntry *ie = (InterfaceEntry *)msg->getContextPointer();
    AdvIfEntry *advIfEntry = fetchAdvIfEntry(ie);
    Ipv6Address destAddr = Ipv6Address("FF02::1");
    createAndSendRaPacket(destAddr, ie);
    advIfEntry->numRASent++;
    simtime_t nextScheduledTime;

    //RFC 2461, Section 6.2.4
    /*Whenever a multicast advertisement is sent from an interface, the timer is
       reset to a uniformly-distributed random value between the interface's
       configured MinRtrAdvInterval and MaxRtrAdvInterval; expiration of the timer
       causes the next advertisement to be sent and a new random value to be chosen.*/

    simtime_t interval;

#ifdef WITH_xMIPv6
    EV_DEBUG << "\n+=+=+= MIPv6 Feature: " << rt6->hasMipv6Support() << " +=+=+=\n";
#endif /* WITH_xMIPv6 */

//    interval = uniform(ie->ipv6Data()->getMinRtrAdvInterval(), ie->ipv6Data()->getMaxRtrAdvInterval());
    interval = 5;
#ifdef WITH_xMIPv6
    EV_DETAIL << "\n +=+=+= The random calculated interval is: " << interval << " +=+=+=\n";
#endif /* WITH_xMIPv6 */

    nextScheduledTime = simTime() + interval;

    /*For the first few advertisements (up to MAX_INITIAL_RTR_ADVERTISEMENTS)
       sent from an interface when it becomes an advertising interface,*/
    EV_DETAIL << "Num RA sent is: " << advIfEntry->numRASent << endl;
    EV_DETAIL << "maxInitialRtrAdvertisements is: " << ie->ipv6Data()->_getMaxInitialRtrAdvertisements() << endl;

    if (advIfEntry->numRASent <= ie->ipv6Data()->_getMaxInitialRtrAdvertisements()) {
        if (interval > ie->ipv6Data()->_getMaxInitialRtrAdvertInterval()) {
            //if the randomly chosen interval is greater than MAX_INITIAL_RTR_ADVERT_INTERVAL,
            //the timer SHOULD be set to MAX_INITIAL_RTR_ADVERT_INTERVAL instead.
            nextScheduledTime = simTime() + ie->ipv6Data()->_getMaxInitialRtrAdvertInterval();
            EV_INFO << "Sending initial RA but interval is too long. Using default value." << endl;
        }
        else
            EV_INFO << "Sending initial RA. Using randomly generated interval." << endl;
    }

    EV_DETAIL << "Next scheduled time: " << nextScheduledTime << endl;
    advIfEntry->nextScheduledRATime = nextScheduledTime;
    ASSERT(nextScheduledTime > simTime());
    scheduleAt(nextScheduledTime, msg);
}

void Ipv6NeighbourDiscovery::sendSolicitedRa(cMessage *msg)
{
    EV_INFO << "Send Solicited RA invoked!\n";
//    std::cout << "Send Solicited RA invoked!\n";
    InterfaceEntry *ie = (InterfaceEntry *)msg->getContextPointer();
    Ipv6Address destAddr = Ipv6Address("FF02::1");
    EV_DETAIL << "Testing condition!\n";
    createAndSendRaPacket(destAddr, ie);
    delete msg;
}

bool Ipv6NeighbourDiscovery::validateRaPacket(Packet *packet, const Ipv6RouterAdvertisement *ra)
{
    bool result = true;

    //RFC 2461: Section 6.1.2 Validation of Router Advertisement Messages
    /*A node MUST silently discard any received Router Advertisement
       messages that do not satisfy all of the following validity checks:*/
    Ipv6Address srcAddr = packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6();

    //- IP Source Address is a link-local address.  Routers must use
    //  their link-local address as the source for Router Advertisement
    //  and Redirect messages so that hosts can uniquely identify
    //  routers.
    if (srcAddr.isLinkLocal() == false) {
        EV_WARN << "RA source address is not link-local. RA validation failed!\n";
        result = false;
    }

    //- The IP Hop Limit field has a value of 255, i.e., the packet
    //  could not possibly have been forwarded by a router.
    if (packet->getTag<HopLimitInd>()->getHopLimit() != 255) {
        EV_WARN << "Hop limit is not 255! RA validation failed!\n";
        result = false;
    }

    //- ICMP Code is 0.
    if (packet->getTag<PacketProtocolTag>()->getProtocol() != &Protocol::icmpv6) {
        EV_WARN << "ICMP Code is not 0! RA validation failed!\n";
        result = false;
    }

#ifdef WITH_xMIPv6
    // - All included options have a length that is greater than zero.
    // CB
    if (ra->getPrefixInformationArraySize() == 0) {
        EV_WARN << "No prefix information available! RA validation failed\n";
        result = false;
    }
#endif /* WITH_xMIPv6 */

    return result;
}

void Ipv6NeighbourDiscovery::createAndSendNsPacket(const Ipv6Address& nsTargetAddr, const Ipv6Address& dgDestAddr,
        const Ipv6Address& dgSrcAddr, InterfaceEntry *ie)
{
#ifdef WITH_xMIPv6
    Enter_Method_Silent();
#endif /* WITH_xMIPv6 */

    MacAddress myMacAddr = ie->getMacAddress();

    //Construct a Neighbour Solicitation message
    auto ns = makeShared<Ipv6NeighbourSolicitation>();

    //Neighbour Solicitation Specific Information
    ns->setTargetAddress(nsTargetAddr);
    ns->setChunkLength(ICMPv6_HEADER_BYTES + B(IPv6_ADDRESS_SIZE));      // RFC 2461, Section 4.3.

    //6LoWPAN must include SLLAO in NS
    ns->setSourceLinkLayerAddress(myMacAddr);
    ns->setChunkLength(ns->getChunkLength() + IPv6ND_LINK_LAYER_ADDRESS_OPTION_LENGTH);
    ns->setIsDadMsg(ie->ipv6Data()->isDadInProgress());
    EV_INFO<< "NS is DAD message: "<< ns->isDadMsg() <<endl;

//    std::cout<< "NS is DAD message: "<< ns->isDadMsg() <<endl;


    ns->setLinkLocalAddress(ie->ipv6Data()->getLinkLocalAddress());
    if (neighbourCache.getDefaultRouterList().begin() != neighbourCache.getDefaultRouterList().end()) {
        Neighbour& router = *neighbourCache.getDefaultRouterList().begin();
        if (ns->isDadMsg()) {
            ns->setIsRelay(true);
            ns->setRelayAddress(dgDestAddr);
        }
    }

    EV_INFO<< "NS is relay message: "<< ns->isRelay() <<endl;

    /*If the solicitation is being sent to a solicited-node multicast
       address, the sender MUST include its link-layer address (if it has
       one) as a Source Link-Layer Address option.*/
    if (dgDestAddr.matches(Ipv6Address("FF02::1:FF00:0"), 104) &&    // FIXME what's this? make constant...
            !dgSrcAddr.isUnspecified()) {
        ns->setSourceLinkLayerAddress(myMacAddr);
        ns->setChunkLength(ns->getChunkLength() + IPv6ND_LINK_LAYER_ADDRESS_OPTION_LENGTH);
   }

    //ARO and Interface Token
    auto aro = ns->getARO();
    aro.setRegistLifeTime(35);
    InterfaceIdentifier ifid;
    ifid.len = ie->getInterfaceToken().length();
    ifid.low = ie->getInterfaceToken().low();
    ifid.normal = ie->getInterfaceToken().normal();
    aro.setEUI64(ifid);
    ns->setARO(aro);

    auto packet = new Packet("NSpacket");
    Icmpv6::insertCrc(crcMode, ns, packet);
    packet->insertAtFront(ns);

    delete packet->removeTagIfPresent<MacAddressReq>();
    packet->addTag<MacAddressReq>()->setSrcAddress(ie->getMacAddress());

    Neighbour *neighbourEntry = neighbourCache.lookup(dgDestAddr, ie->getInterfaceId());
    if (neighbourEntry!=nullptr) {
        packet->addTagIfAbsent<MacAddressReq>()->setDestAddress(neighbourEntry->macAddress);
        EV_INFO<<"set mac dest addr to: "<<packet->getTag<MacAddressReq>()->getDestAddress()<<endl;
    }

    sendPacketToIpv6Module(packet, dgDestAddr, dgSrcAddr, ie->getInterfaceId());

}

void Ipv6NeighbourDiscovery::processNsPacket(Packet *packet, const Ipv6NeighbourSolicitation *ns)
{
    //Control Information
    InterfaceEntry *ie = ift->getInterfaceById(packet->getTag<InterfaceInd>()->getInterfaceId());
    EV_INFO << "Process NS, interface name is: "<< ie->getInterfaceName()<< endl;
//    std::cout << "Process NS, interface name is: "<< ie->getInterfaceName()<< endl;

    Ipv6Address pktSrcAddr = packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6();

    Ipv6Address nsTargetAddr = ns->getTargetAddress();
    EV_INFO<<"NS Source Link-layer address is: "<<ns->getSourceLinkLayerAddress()<<endl;
    EV_INFO<<"NS TargetAddr is: "<<nsTargetAddr<<endl;
    Neighbour *entry = neighbourCache.lookup(nsTargetAddr, ie->getInterfaceId());

    Ipv6NdAddressRegistrationOption aro = ns->getARO();
    if (validateNsPacket(packet, ns) == false || validateARO(&aro)==false) {
        EV_INFO << "NS validation failed\n";
        delete packet;
        return;
    }

    bubble("NS validation passed.\n");
    EV_INFO << "NS validation passed.\n";

    //address resolution between road infrastructures (e.g., RSU and MA)
    if (rt6->isLocalAddress(nsTargetAddr)) {
        EV_INFO<<"this is address resolution message, send back my link layer address."<<endl;
        sendSolicitedNa(packet, ns, ie);

    }

    //MA behavior: process NS packet at MA
    else if (rt6->isHomeAgent()) {
        processNsAtMA(packet, ns, ie); //processDAR
    }
    //Router Behavior with DAD msg
    else if (rt6->isRouter() && ns->isDadMsg()) {
        EV_INFO<< "process NS for multihop DAD, interface name is: " << ie->getInterfaceName()<< endl;
        processNsForMultihopDAD(packet,ns, ie);
    }
    //Router Behavior with non-DAD mesg
    else if (rt6->isRouter()) {
        //update NCE
        EV_INFO<<"process NS to update NCE!" <<endl;
        processNsForUpdateNCE(packet, ns, ie);
    }

    //Vehicle behavior: Forward multihop DAD message to RSU for registered vehicle neighbors
    else if (!rt6->isRouter()&& entry!=nullptr) {
        Neighbour& router = *neighbourCache.getDefaultRouterList().begin();
        if (!router.nceKey->address.isUnspecified()) {
            Ipv6Address destAddr= router.nceKey->address;
            packet->addTagIfAbsent<MacAddressReq>()->setDestAddress(router.macAddress);
            //forward ND messages to neighbor
            numDadMessageForwarded++;
            emit(numDadMessageForwardedSignal, numDadMessageForwarded);
            forwardNDMessageForNeighbour(packet, destAddr, ie);
        }
        else {
            EV_INFO <<"NO router on-line!" << endl;
            delete packet;
        }

    }

    //vehicle behavior1: receive neighbor discovery from other vehicles, if my address is not tentative and default router is on-line
    //vehicle behavior2: receive forwarded msg not from direct neighbor but vehicles more than two hops
    else if (!rt6->isRouter() && entry == nullptr &&!ie->ipv6Data()->isTentativeAddress(ie->ipv6Data()->getPreferredAddress())
            &&neighbourCache.getDefaultRouterList().begin() != neighbourCache.getDefaultRouterList().end()){

        Neighbour *neighborRoute = neighbourCache.lookupNeighborRoute(nsTargetAddr, ie->getInterfaceId());

        if (ns->isDadMsg()) {
            Neighbour& router = *neighbourCache.getDefaultRouterList().begin();
            if (!router.nceKey->address.isUnspecified()) {
                Ipv6Address destAddr= router.nceKey->address;
                EV_INFO <<"rtAddress: "<< destAddr << endl;
                packet->addTagIfAbsent<MacAddressReq>()->setSrcAddress(ie->getMacAddress());
                packet->addTagIfAbsent<MacAddressReq>()->setDestAddress(router.macAddress);
                numDadMessageForwarded++;
                emit(numDadMessageForwardedSignal, numDadMessageForwarded);
                forwardNDMessageForNeighbour(packet, destAddr, ie);
                neighbourCache.addNeighborRoute (ns->getTargetAddress(), ie->getInterfaceId(),
                ns->getSourceLinkLayerAddress(), pktSrcAddr, ns->getHopDistance());
            }

        }
        //forward ND message for registered remote neighbor
        else if (neighborRoute!=nullptr) {
            Neighbour& router = *neighbourCache.getDefaultRouterList().begin();
            if (!router.nceKey->address.isUnspecified()) {
                Ipv6Address destAddr= router.nceKey->address;
                EV_INFO <<"rtAddress: "<< destAddr << endl;

                packet->addTagIfAbsent<MacAddressReq>()->setSrcAddress(ie->getMacAddress());
                packet->addTagIfAbsent<MacAddressReq>()->setDestAddress(router.macAddress);
                forwardNDMessageForNeighbour(packet, destAddr, ie);
            }

        }
        //create NCE for this neighbor, and add new neighbor route
        else {
            EV_INFO << "Process NS for Non-Tentative target address.\n";
            processNsForNonTentativeAddress(packet, ns, ie);
            Ipv6Address globalAddr = ns->getTargetAddress();
            globalAddr.setPrefix(ie->ipv6Data()->getPreferredAddress().getPrefix(64), 64);
            //XIANG ZHONG 19.07.06
            neighbourCache.addNeighborRoute (globalAddr, ie->getInterfaceId(),
            ns->getSourceLinkLayerAddress(), globalAddr, ns->getHopDistance());
        }
    }
    else {
        EV_INFO <<"Discard unknown NS messages!" << endl;
        delete packet;
    }

    //END

    //RFC 2461:Section 7.2.3
    //If target address is not a valid "unicast" or anycast address assigned to the
    //receiving interface, we should silently discard the packet.

    //original validate function
//    if (validateNsPacket(packet, ns) == false
//        || ie->ipv6Data()->hasAddress(nsTargetAddr) == false)// Problem in later one
//    {
//
//        EV_INFO << "NS validation failed\n";
//        bubble("NS validation failed\n");
//        delete packet;
//        return;
//    }

//    bubble("NS validation passed.\n");
//    EV_INFO << "NS validation passed.\n";

    /**
    * Returns true if the interface has the given address and it is tentative.
    */

}



/************Multihop Duplicate Address Detection Staff*********************************/

// discarded DAR 19.12.30
void Ipv6NeighbourDiscovery::createAndSendDARPacket(const Ipv6Address& dadTargetAddr, const Ipv6NeighbourSolicitation *ns, const Ipv6Address& destAddr,
        const Ipv6Address& srcAddr, InterfaceEntry *ie)

{
    MacAddress myMacAddr = ie->getMacAddress();

    //Construct a DAR message
    auto dar = makeShared<Ipv6DuplicateAddrReq>();

    //DAR Specific Information
//    dar->setTargetAddress(nsTargetAddr);
    dar->setChunkLength(ICMPv6_HEADER_BYTES + B(IPv6_ADDRESS_SIZE));      // RFC 2461, Section 4.3.

    if (destAddr.matches(Ipv6Address("FF02::1:FF00:0"), 104) &&    // FIXME what's this? make constant...
            !srcAddr.isUnspecified()) {
        dar->setChunkLength(dar->getChunkLength() + IPv6ND_LINK_LAYER_ADDRESS_OPTION_LENGTH);
    }

    // settings from ARO in ns
    dar->setRegistLifetime(ns->getARO().getRegistLifeTime());
    dar->setEUI64(ns->getARO().getEUI64());
    dar->setSourceAddress(srcAddr);
    dar->setDestinationAddress(destAddr);
    EV_INFO<<"dar EUI64 low: "<<dar->getEUI64().low<< endl;
    EV_INFO<<"dar EUI64 len: "<<dar->getEUI64().len<< endl;
    EV_INFO<<"dar EUI64 normal: "<<dar->getEUI64().normal<< endl;
    dar->setRegisteredAddress(dadTargetAddr);

    auto packet = new Packet("DARPacket");
    Icmpv6::insertCrc(crcMode, dar, packet);
    packet->insertAtFront(dar);

    sendPacketToIpv6Module(packet, destAddr, srcAddr, ie->getInterfaceId());
    EV_INFO<<"Sending DAR message, interface name is: "<< ie->getInterfaceName()<<endl;
//    std::cout<<"Sending DAR message, interface name is: "<< ie->getInterfaceName()<<endl;

}


//  INSTEAD OF processDARPacket
void Ipv6NeighbourDiscovery::processNsAtMA(Packet *packet, const Ipv6NeighbourSolicitation *ns, InterfaceEntry *ie)
{
    // received DAD

    s1 = simTime().dbl();



  //  id1 = packet->getTag<MacAddressInd>()->getSrcAddress().getInt();

    id1= packet->getTag<MacAddressReq>()->getSrcAddress().getInt();

    signal = s1 + id1;
    emit(receivedDadSignalTime, signal);
    emit(receivedDadSignalId, id1);


    Ipv6Address registeredAddr = ns->getTargetAddress();
    EV_INFO<<"MA: Registered Addr is: "<<registeredAddr<<endl;

    int status;
    Neighbour *entry = neighbourCache.lookupDadTable(registeredAddr,ie->getInterfaceId());
//    Neighbour *nce = neighbourCache.lookupNeighborRoute(registeredAddr, ie->getInterfaceId());

    //Since we do not know the ifID of the existing entry, so currently we use loop to find out the entry
    Neighbour *nce;
    for (int i = 100; i<105;i++) {
          nce = neighbourCache.lookupNeighborRoute(registeredAddr, i);
          if (nce!=nullptr) break;
    }

    //update default router in neighborRoute
    if (nce!=nullptr) {
        s1 = simTime().dbl();
        signal = s1 + id1;

        emit(responseDadSignalTime, signal);
        emit(responseDadSignalId, id1);

        nce->relayAddr = packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6();
        const Ipv6Route *route = rt6->doLongestPrefixMatch(registeredAddr);
        rt6->updateDestCache(registeredAddr,nce->relayAddr, ie->getInterfaceId(), simTime()+1000);
    }

    else if (entry == nullptr) {
        s1 = simTime().dbl();
        signal = s1 + id1;

        emit(responseDadSignalTime, signal);
        emit(responseDadSignalId, id1);

        EV_INFO << "No Entry in DAD Table, create NCE in DAD Table for: "<<registeredAddr<< endl;

        //add NCE to DAD table
        neighbourCache.addMultihopNCE(registeredAddr, ie->getInterfaceId());

        MacAddress nsMacAddr = ns->getSourceLinkLayerAddress();
        Ipv6Address nsL3SrcAddr = ns->getTargetAddress(); //link local address
        Ipv6Address relayAddr= packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6();
        int ifID = ie->getInterfaceId();
        int hop = 1;

        neighbourCache.addNeighborRoute (nsL3SrcAddr, ifID, nsMacAddr, relayAddr, hop);
        //Set the expire time to a large number in MA since vehicles will just do address registration to serving RSU
//        neighbourCache.addRelayNeighbour(nsL3SrcAddr,ns->getLinkLocalAddress(), ifID, nsMacAddr , ns->getARO().getRegistLifeTime(),relayAddr);
        neighbourCache.addRelayNeighbour(nsL3SrcAddr,ns->getLinkLocalAddress(), ifID, nsMacAddr , 500,relayAddr);
        //set status to 0 (Success)
        status = 0;
        EV_INFO <<"MA:Reply NA message."<< endl;
    //    Ipv6Address RSUAddress = packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6();
    //    EV_INFO << "RSU Addr is: " <<RSUAddress << endl;
    //    Ipv6Address srcAddr = ie->ipv6Data()->getGlobalAddress();
    //    createAndSendDACPacket(RSUAddress,srcAddr, dar, status, ie);
        sendSolicitedNa(packet, ns, ie);
    }

    // if CN resend Address Registration to MA, then MA should also can update NCE
    //todo
    else {
        //response DAD
        s1 = simTime().dbl();
        signal = s1 + id1;

        emit(responseDadSignalTime, signal);
        emit(responseDadSignalId, id1);

        error ("Entry already exists in DAD Table!");

        //set status to 1 (Duplicate Address)

        status = 1;
    }
}


void Ipv6NeighbourDiscovery::processNaFromMA(Packet *packet, const Ipv6NeighbourAdvertisement *na)
{
//    std::cout<<"------>< processNaFromMA " <<std::endl;
    int status = na->getARO().getStatus();
    Ipv6Address destAddr;
    InterfaceEntry *ie = ift->getInterfaceByName("nic");
    if (status == 0)
    {
        Ipv6Address registeredAddr = na->getTargetAddress();
        Neighbour *neighbourEntry = neighbourCache.lookup(registeredAddr, ie->getInterfaceId());
        if (neighbourEntry == nullptr) {
            EV_INFO << "NA received. Target Address not found in Neighbour Cache\n";
            EV_INFO << "Dropping NA packet.\n";
            delete packet;
            return;
        }
        //Target Address has entry in Neighbour Cache
        EV_INFO << "NA received. Target Address found in Neighbour Cache\n";
        if (neighbourEntry->reachabilityState == Ipv6NeighbourCache::TENTATIVE) {
            neighbourEntry->reachabilityState = Ipv6NeighbourCache::REACHABLE;
            EV_INFO << "Changing NCE's reachable state to REACHABLE!" << endl;
        }

        if (!neighbourEntry->relayAddr.isUnspecified())
            destAddr = neighbourEntry->relayAddr;
        else
            destAddr = neighbourEntry->linkLocalAddr;
    }
    else
        error ("ARO status not equal to 0! DAD failed!"); //DAD & Address registration failed

    forwardNDMessageForNeighbour(packet,destAddr, ie);

}

// discarded DAR 19.12.30
void Ipv6NeighbourDiscovery::processDARPacket(Packet *packet, const Ipv6DuplicateAddrReq *dar)
{
    EV_INFO <<"DAR message received!"<< endl;

    if (validateDAR(packet, dar) == false) {
        delete packet;
        return;
    }

//-------------------------------------------------------------------------------------------//
    //create NCE (copy from processNsWithSpecifiedSrcAddr)

    Ipv6Address registeredAddr = dar->getRegisteredAddress();
    InterfaceEntry *ie = ift->getInterfaceById(packet->getTag<InterfaceInd>()->getInterfaceId());

    EV_INFO<<"packet src= "<<packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6()<< endl;
    EV_INFO<<"interface name= "<<ie->getInterfaceName() <<endl;
    EV_INFO<<"interface address: "<<ie->ipv6Data()->getGlobalAddress()<< endl;

    int ifID = ie->getInterfaceId();

    delete packet->removeTagIfPresent<L3AddressInd>();
    packet->addTagIfAbsent<L3AddressInd>()->setSrcAddress(registeredAddr);
    EV_INFO<<"L3AddressInd / Registered Addr is: "<<registeredAddr<<endl;
    int status;

    //Look for the Neighbour Cache Entry
    Neighbour *entry = neighbourCache.lookupDadTable(registeredAddr, ifID);

    if (entry == nullptr) {
        /*If an entry does not already exist, the node SHOULD create a new one
           and set its reachability state to STALE as specified in Section 7.3.3.*/
        EV_INFO << "No Entry in DAD Table, create NCE in DAD Table for: "<<registeredAddr<< endl;
        neighbourCache.addMultihopNCE(registeredAddr, ifID);
        //set status to 0 (Success)
        status = 0;
        EV_INFO << "DAR status set to: "<<dar->getStatus()<< endl;
    }
    else {

        error ("Entry already exists in DAD Table!");
        //set status to 1 (Duplicate Address)
        status = 1;
        /*If an entry already exists, and the cached link-layer address differs from
           the one in the received Source Link-Layer option,*/
//        if (!(entry->macAddress.equals(nsMacAddr)) && !nsMacAddr.isUnspecified()) {
            //the cached address should be replaced by the received address
//            entry->macAddress = nsMacAddr;
            //and the entry's reachability state MUST be set to STALE.
//            entry->reachabilityState = Ipv6NeighbourCache::STALE;
        }
//-------------------------------------------------------------------------------------------//
    EV_INFO <<"Reply DAC message."<< endl;
    Ipv6Address RSUAddress = dar->getSourceAddress();
    Ipv6Address srcAddr = ie->ipv6Data()->getGlobalAddress();
    createAndSendDACPacket(RSUAddress,srcAddr, dar, status, ie);
}


// discarded DAC 19.12.30
void Ipv6NeighbourDiscovery::processDACPacket(Packet *packet, const Ipv6DuplicateAddrConfirm *dac)
{
    EV_INFO<<"DAC successfully received!"<< endl;

    if (validateDAC(packet, dac) == false) {
        delete packet;
        return;
    }

    //get interfaceEntry by name
    InterfaceEntry *ie = ift->getInterfaceByName("nic");
    auto status = dac->getStatus();
    Ipv6Address destAddr;
    if (status == 0) {
        Ipv6Address registeredAddr = dac->getRegisteredAddress();
        //First, we check if the target address in NA is found in the interface it
        //was received on is tentative.
        Neighbour *neighbourEntry = neighbourCache.lookup(registeredAddr, ie->getInterfaceId());

        if (neighbourEntry == nullptr) {
            EV_INFO << "DAC received. Target Address not found in Neighbour Cache\n";
            EV_INFO << "Dropping NA packet.\n";
            delete packet;
            return;
        }
        //Target Address has entry in Neighbour Cache
        EV_INFO << "DAC received. Target Address found in Neighbour Cache\n";
        if (neighbourEntry->reachabilityState == Ipv6NeighbourCache::TENTATIVE) {
            neighbourEntry->reachabilityState = Ipv6NeighbourCache::REACHABLE;
            EV_INFO << "Changing NCE's reachable state to REACHABLE!" << endl;
        }


        if (!neighbourEntry->relayAddr.isUnspecified())
            destAddr = neighbourEntry->relayAddr;
        else
            destAddr = neighbourEntry->linkLocalAddr;

    }
    else
        error ("DAC status not equal to 0! DAD failed!"); //DAD failed

    sendSolicitedNaForDAD(packet,destAddr, dac, ie);
}

// discarded DAC 19.12.30
// Mobility Anchor Behavior
void Ipv6NeighbourDiscovery::createAndSendDACPacket( const Ipv6Address& dgDestAddr,
        const Ipv6Address& dgSrcAddr, const Ipv6DuplicateAddrReq *dar, int status, InterfaceEntry *ie)
{
    std::cout <<" <----> MA ----> Ipv6Module !!" <<std::endl;
    MacAddress myMacAddr = ie->getMacAddress();
    //Construct a DAC message
    auto dac = makeShared<Ipv6DuplicateAddrConfirm>();
    dac->setStatus(status);
    dac->setRegistLifetime(dar->getRegistLifetime());
    dac->setRegisteredAddress(dar->getRegisteredAddress());

    dac->setEUI64(dar->getEUI64());
    EV_INFO<<"dac EUI64 len: "<<dac->getEUI64().len<< endl;
    EV_INFO<<"dac EUI64 low: "<<dac->getEUI64().low << endl;
    EV_INFO<<"dac EUI64 normal: "<<dac->getEUI64().normal <<endl;
    EV_INFO << "DAC status set to: "<<dac->getStatus()<< endl;

    //DAR Specific Information
    //    dar->setTargetAddress(nsTargetAddr);
    dac->setChunkLength(ICMPv6_HEADER_BYTES + B(IPv6_ADDRESS_SIZE));      // RFC 2461, Section 4.3.
        if (dgDestAddr.matches(Ipv6Address("FF02::1:FF00:0"), 104) &&    // FIXME what's this? make constant...
                !dgSrcAddr.isUnspecified()) {
       //        dar->setSourceLinkLayerAddress(myMacAddr);
            dac->setChunkLength(dac->getChunkLength() + IPv6ND_LINK_LAYER_ADDRESS_OPTION_LENGTH);
        }

    auto packet = new Packet("DACPacket");
    Icmpv6::insertCrc(crcMode, dac, packet);
    packet->insertAtFront(dac);
    sendPacketToIpv6Module(packet, dgDestAddr, dgSrcAddr, ie->getInterfaceId());
}
// Mobility Anchor Behavior


// discarded DAR 19.12.30
bool Ipv6NeighbourDiscovery::validateDAR(Packet *packet, const Ipv6DuplicateAddrReq *dar)
{
    bool result = true;
    //Message validation for DAR and DAC
    //ICMP code is 0
    if (packet->getTag<PacketProtocolTag>()->getProtocol() != &Protocol::icmpv6) {
            EV_INFO << "ICMP Code is not 0! DAR validation failed!\n";
            result = false;
        }

    //The Registered Address is not a multicast address
    if (dar->getRegisteredAddress().isMulticast() == true) {
        EV_INFO << "Registered address is a multicast address! DAR validation failed!\n";
        result = false;
    }

    //The IP source address is not the unspecified address, nor is it a multicast address
    if (packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6().isUnspecified() ||
            packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6().isMulticast()) {
            EV_INFO << "IP source address is unspecified\n";
            result = false;
    }

    if (result == true)
        EV_INFO<<"DAR validation success!\n";
    else
        EV_INFO<<"DAR validation failed!\n";

    return result;

    //todo
    //All included options have a length that is greater than zero
    //ICMP Length (derived from the IP length) is 32 or more bytes
    //ICMP Checksum is valid

}
// discarded DAC 19.12.30
bool Ipv6NeighbourDiscovery::validateDAC(Packet *packet, const Ipv6DuplicateAddrConfirm *dac)
{
    bool result = true;
    //Message validation for DAR and DAC
    //ICMP code is 0
    if (packet->getTag<PacketProtocolTag>()->getProtocol() != &Protocol::icmpv6) {
            EV_INFO << "ICMP Code is not 0! DAC validation failed!\n";
            result = false;
        }

    //The Registered Address is not a multicast address
    if (dac->getRegisteredAddress().isMulticast() == true) {
        EV_INFO << "Registered address is a multicast address! DAC validation failed!\n";
        result = false;
    }

    //The IP source address is not the unspecified address, nor is it a multicast address
    if (packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6().isUnspecified() ||
            packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6().isMulticast()) {
            EV_INFO << "IP source address is unspecified\n";
            result = false;
    }

    if (result == true)
        EV_INFO<<"DAC validation success!\n";
    else
        EV_INFO<<"DAC validation failed!\n";

    return result;

    //todo
    //All included options have a length that is greater than zero
    //ICMP Length (derived from the IP length) is 32 or more bytes
    //ICMP Checksum is valid

}

bool Ipv6NeighbourDiscovery::validateARO(Ipv6NdAddressRegistrationOption *aro)
{
    bool result = true;

    // if the Length Field is not two
    if (aro->getOptionLength()!=2)  {
        EV_WARN << "ARO lenth is not two! ARO validation failed!"<<endl;
        EV_WARN << "Ignore ARO!"<<endl;
        result = false;
    }

    if (result == true)
        EV_INFO << "ARO validation success!"<<endl;
    else
        EV_INFO << "ARO validation failed!"<<endl;

    return result;

    // if the EUI-64 field does not match the EUI-64 of the interface, ignore the option

}

/************Multihop Duplicate Address Detection Staff*********************************/


bool Ipv6NeighbourDiscovery::validateNsPacket(Packet *packet, const Ipv6NeighbourSolicitation *ns)
{
    bool result = true;

    /*RFC 2461:7.1.1. Validation of Neighbor Solicitations(some checks are omitted)
       A node MUST silently discard any received Neighbor Solicitation
       messages that do not satisfy all of the following validity checks:*/
    //- The IP Hop Limit field has a value of 255, i.e., the packet
    //could not possibly have been forwarded by a router.
    //XIANG ZHONG
//    if (packet->getTag<HopLimitInd>()->getHopLimit() != 255) {
//        EV_WARN << "Hop limit is not 255! NS validation failed!\n";
//        result = false;
//    }

    //- Target Address is not a multicast address.
    if (ns->getTargetAddress().isMulticast() == true) {
        EV_WARN << "Target address is a multicast address! NS validation failed!\n";
        result = false;
    }

    //- If the IP source address is the unspecified address,
    if (packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6().isUnspecified()) {
        EV_WARN << "Source Address is unspecified\n";

        //the IP destination address is a solicited-node multicast address.
        if (packet->getTag<L3AddressInd>()->getDestAddress().toIpv6().matches(Ipv6Address::SOLICITED_NODE_PREFIX, 104) == false) {
            EV_WARN << " but IP dest address is not a solicited-node multicast address! NS validation failed!\n";
            result = false;
        }
        //there is no source link-layer address option in the message.
        else if (ns->getSourceLinkLayerAddress().isUnspecified() == false) {
            EV_WARN << " but Source link-layer address is not empty! NS validation failed!\n";
            result = false;
        }
        else
            EV_WARN << "NS Validation Passed\n";
    }

    return result;
}


void Ipv6NeighbourDiscovery::processNsForTentativeAddress(Packet *packet, const Ipv6NeighbourSolicitation *ns)
{
    //Control Information
    Ipv6Address nsSrcAddr = packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6();
    //Ipv6Address nsDestAddr = nsCtrlInfo->getDestAddr();

    ASSERT(nsSrcAddr.isUnicast() || nsSrcAddr.isUnspecified());
    //solicitation is processed as described in RFC2462:section 5.4.3

    if (nsSrcAddr.isUnspecified()) {
        EV_INFO << "Source Address is UNSPECIFIED. Sender is performing DAD\n";

        //Sender performing Duplicate Address Detection
        if (rt6->isLocalAddress(nsSrcAddr)) // FIXME: isLocalAddress(UNSPECIFIED) is always false!!! Must write another check for detecting source is myself/foreign node!!!
            EV_INFO << "NS comes from myself. Ignoring NS\n";
        else {

            s1 = simTime().dbl();

            //id1 = packet->getTag<InterfaceReq>()->getInterfaceId();
            s1 = simTime().dbl();

            //id1 = packet->getTag<MacAddressInd>()->getSrcAddress().getInt();

            id1= packet->getTag<MacAddressReq>()->getSrcAddress().getInt();

            signal = s1 + id1;
            emit(receivedDadSignalTime, signal);
            emit(receivedDadSignalId, id1);


            EV_INFO << "NS comes from another node. Address is duplicate!\n";

            s1 = simTime().dbl();

            signal = s1 + id1;

            emit(responseDadSignalTime, signal);
            emit(responseDadSignalId, id1);

            throw cRuntimeError("Duplicate Address Detected! Manual Attention Required!");
        }
    }
    else if (nsSrcAddr.isUnicast()) {
        //Sender performing address resolution
        EV_INFO << "Sender is performing Address Resolution\n";
        EV_INFO << "Target Address is tentative. Ignoring NS.\n";
    }
}

void Ipv6NeighbourDiscovery::processNsForNonTentativeAddress(Packet *packet, const Ipv6NeighbourSolicitation *ns, InterfaceEntry *ie)
{
    //Neighbour Solicitation Information
    //MacAddress nsMacAddr = ns->getSourceLinkLayerAddress();

    //target addr is not tentative addr
    //solicitation processed as described in RFC2461:section 7.2.3
    if (packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6().isUnspecified()) {



        s1 = simTime().dbl();

        //id1 = packet->getTag<InterfaceReq>()->getInterfaceId();

        //id1 = packet->getTag<MacAddressInd>()->getSrcAddress().getInt();

        id1= packet->getTag<MacAddressReq>()->getSrcAddress().getInt();

        signal = s1 + id1;
        emit(receivedDadSignalTime, signal);
        emit(receivedDadSignalId, id1);


        emit(responseDadSignalTime, signal);
        emit(responseDadSignalId, id1);


        EV_INFO << "Address is duplicate! Inform Sender of duplicate address!\n";


        sendSolicitedNa(packet, ns, ie);

    }
    else
        processNsWithSpecifiedSrcAddr(packet, ns, ie);
}

void Ipv6NeighbourDiscovery::processNsForMultihopDAD(Packet *packet, const Ipv6NeighbourSolicitation *ns, InterfaceEntry *ie)
{
    //Router Behavior with DAD msg
//  std::cout <<"----->< processNsForMultihopDAD " <<std::endl;

    s1 = simTime().dbl();

    // id1 = packet->getTag<InterfaceReq>()->getInterfaceId();

    //id1 = packet->getTag<MacAddressInd>()->getSrcAddress().getInt();

    id1= packet->getTag<MacAddressReq>()->getSrcAddress().getInt();

    signal = s1 + id1;
    emit(receivedDadSignalTime, signal);
    emit(receivedDadSignalId, id1);


    Ipv6Address nsTargetAddr = ns->getTargetAddress(); //targetAddr need to do DAD
    Ipv6Address MaAddress = Ipv6Address("aaaa:2:65:0:8aa:ff:fe00:9"); //destAddr: aaaa:2:65:0:8aa:ff:fe00:9
    Ipv6Address sourceAddr = ie->ipv6Data()->getAddress(0);

    //create NCE (copy from processNsWithSpecifiedSrcAddr
    //Neighbour Solicitation Information
    MacAddress nsMacAddr = ns->getSourceLinkLayerAddress();
    Ipv6Address nsL3SrcAddr = ns->getTargetAddress(); //link local address
    EV_INFO <<"nsL3SrcAddr: "<<nsL3SrcAddr << endl;
    MacAddress destMac = packet->getTag<MacAddressReq>()->getDestAddress();
    int ifID = ie->getInterfaceId();
    //Look for the Neighbour Cache Entry
    Neighbour *entry = neighbourCache.lookup(nsL3SrcAddr, ifID);

    // If entry is none, create a tentative entry and then start multihop DAD
    if (entry == nullptr) {
        /*If an entry does not already exist, the node SHOULD create a new one
           and set its reachability state to STALE as specified in Section 7.3.3.*/
        EV_INFO << "Neighbour Entry not found. Create a Tentative Neighbour Cache Entry for: "<<nsL3SrcAddr<< endl;
        if (ns->isRelay()) {
            Ipv6Address relayAddr= packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6();
            neighbourCache.addRelayNeighbour(nsL3SrcAddr,ns->getLinkLocalAddress(), ifID, nsMacAddr , ns->getARO().getRegistLifeTime(),relayAddr);
            neighbourCache.addNeighborRoute (nsL3SrcAddr, ifID, nsMacAddr, relayAddr, hopDistance);
        }
        else {
            neighbourCache.addTentativeNeighbour(nsL3SrcAddr, ns->getLinkLocalAddress(), ifID, nsMacAddr , ns->getARO().getRegistLifeTime());
            neighbourCache.addNeighborRoute (nsL3SrcAddr, ifID, nsMacAddr, Ipv6Address::UNSPECIFIED_ADDRESS, hopDistance);
        }


        //add timeout message
        cMessage *msg = new cMessage("NeighborCacheTimeout", MK_ADDR_REGIST_TIMEOUT);

        Neighbour *cache = neighbourCache.lookup(nsL3SrcAddr, ifID);
        msg->setContextPointer(cache);
        scheduleAt(simTime() + ns->getARO().getRegistLifeTime()+ uniform(0.000001,0.00002), msg);

        ie = ift->getInterfaceByName("eth0");
        // Register Life Time
//        entry->registLifeTime = simTime() + ns->getARO().getRegistLifeTime();

//        entry->routerExpiryTime = simTime() + ie->ipv6Data()->_getReachableTime();

        auto l3AddressInd = packet->addTagIfAbsent<L3AddressInd>();
//        l3AddressInd->setSrcAddress(ie->ipv6Data()->getPreferredAddress()); //(BAM Comment)
        l3AddressInd->setDestAddress(MaAddress);
        delete packet->removeTagIfPresent<MacAddressReq>();

        numDadMessageForwarded++;
        emit(numDadMessageForwardedSignal, numDadMessageForwarded);






        s1 = simTime().dbl();
        signal = s1 + id1;

        emit(responseDadSignalTime, signal);
        emit(responseDadSignalId, id1);


        forwardNDMessageForNeighbour(packet, MaAddress, ie);

    }

    //  if the packet lost on the way back to the DAD-required vehicle
    else if (entry->reachabilityState==Ipv6NeighbourCache::REACHABLE) {
        s1 = simTime().dbl();
        signal = s1 + id1;

        emit(responseDadSignalTime, signal);
        emit(responseDadSignalId, id1);
        sendSolicitedNa(packet, ns, ie);
    }
    //need to modify
    else {
        /*If an entry already exists, and the cached link-layer address differs from
           the one in the received Source Link-Layer option,*/
        if (!(entry->macAddress.equals(nsMacAddr)) && !nsMacAddr.isUnspecified()) {
            //the cached address should be replaced by the received address
            entry->macAddress = nsMacAddr;
            //and the entry's reachability state MUST be set to STALE.
            entry->reachabilityState = Ipv6NeighbourCache::STALE;
        }
        s1 = simTime().dbl();
        signal = s1 + id1;

        emit(responseDadSignalTime, signal);
        emit(responseDadSignalId, id1);
    }
}

void Ipv6NeighbourDiscovery::forwardNDMessageForNeighbour(Packet *packet, const Ipv6Address& destAddr, InterfaceEntry *ie)  {
    //directly forward packet to neighbor
    EV_INFO << "Forward ND packet to Neighbour!" <<endl;
//    std::cout << "Forward ND packet to Neighbour!" <<endl;
    Ipv6Address dgSrcAddr = ie->ipv6Data()->getPreferredAddress();
    sendPacketToIpv6Module(packet, destAddr, dgSrcAddr, ie->getInterfaceId());
}


void Ipv6NeighbourDiscovery::processNsWithSpecifiedSrcAddr(Packet *packet, const Ipv6NeighbourSolicitation *ns, InterfaceEntry *ie)
{
    //RFC 2461, Section 7.2.3
    /*If the Source Address is not the unspecified address and, on link layers
       that have addresses, the solicitation includes a Source Link-Layer Address
       option, then the recipient SHOULD create or update the Neighbor Cache entry
       for the IP Source Address of the solicitation.*/

    //Neighbour Solicitation Information
    MacAddress nsMacAddr = ns->getSourceLinkLayerAddress();
    Ipv6Address nsL3SrcAddr = packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6();

    int ifID = ie->getInterfaceId();

    //Look for the Neighbour Cache Entry
    Neighbour *entry = neighbourCache.lookup(nsL3SrcAddr, ifID);

    if (entry == nullptr) {

        if (!rt6->isRouter()) {
            EV_INFO << "Neighbour Entry not found. Create a Neighbour Cache Entry.\n";
//            Ipv6Address relayAddr = ie->ipv6Data()->getLinkLocalAddress();
            Ipv6Address relayAddr = ie->ipv6Data()->getPreferredAddress();

            Ipv6Address globalAddr = ns->getTargetAddress();
            globalAddr.setPrefix(ie->ipv6Data()->getPreferredAddress().getPrefix(64), 64);
            neighbourCache.addRelayNeighbour(globalAddr, ns->getLinkLocalAddress(),ifID, nsMacAddr ,
                    ns->getARO().getRegistLifeTime(),relayAddr);
        }
        else {
        /*If an entry does not already exist, the node SHOULD create a new one
           and set its reachability state to STALE as specified in Section 7.3.3.*/
        EV_INFO << "Neighbour Entry not found. Create a Neighbour Cache Entry.\n";
        neighbourCache.addNeighbour(nsL3SrcAddr, ifID, nsMacAddr);
        }
    }
    else {
        /*If an entry already exists, and the cached link-layer address differs from
           the one in the received Source Link-Layer option,*/
        if (!(entry->macAddress.equals(nsMacAddr)) && !nsMacAddr.isUnspecified()) {
            //the cached address should be replaced by the received address
            entry->macAddress = nsMacAddr;
            //and the entry's reachability state MUST be set to STALE.
            entry->reachabilityState = Ipv6NeighbourCache::STALE;
        }
    }

    /*After any updates to the Neighbor Cache, the node sends a Neighbor
       Advertisement response as described in the next section.*/
    sendSolicitedNa(packet, ns, ie);
}

void Ipv6NeighbourDiscovery::processNsForUpdateNCE(Packet *packet, const Ipv6NeighbourSolicitation *ns, InterfaceEntry *ie)
{
    Ipv6Address nsTargetAddr = ns->getTargetAddress(); //targetAddr need to do DAD

    //Neighbour Solicitation Information
    MacAddress nsMacAddr = ns->getSourceLinkLayerAddress();
    Ipv6Address nsL3SrcAddr = ns->getTargetAddress(); //link local address
    EV_INFO <<"nsL3SrcAddr: "<<nsL3SrcAddr << endl;
    int ifID = ie->getInterfaceId();
    //Look for the Neighbour Cache Entry
    Neighbour *entry = neighbourCache.lookup(nsL3SrcAddr, ifID);

    // If entry is none, create a tentative entry and then start multihop DAD
    if (entry == nullptr) {
        EV_INFO << "Neighbour Entry not found. Create a Neighbour Cache Entry for: "<<nsL3SrcAddr<< endl;
        neighbourCache.addTentativeNeighbour(nsL3SrcAddr, ns->getLinkLocalAddress(), ifID, nsMacAddr, ns->getARO().getRegistLifeTime());
        neighbourCache.addNeighborRoute (ns->getTargetAddress(), ie->getInterfaceId(),
                                ns->getSourceLinkLayerAddress(), nsL3SrcAddr, ns->getHopDistance());

        //Update default router in MA    /******* BAM Commented *******/
     /*   if (ifID==100) { //if the message came from vehicles
            Ipv6Address MaAddress = Ipv6Address("aaaa:2:66:0:8aa:ff:fe00:a"); //destAddr: aaaa:2:65:0:8aa:ff:fe00:9
            InterfaceEntry *ieEth = ift->getInterfaceByName("eth0");
            createAndSendNsPacket(nsL3SrcAddr, MaAddress, ieEth->ipv6Data()->getPreferredAddress(), ieEth);
        }*/
        sendSolicitedNa(packet, ns, ie);

    }
    //need to modify
    else {
        EV_INFO << "Neighbour Entry found! Update NCE!"<< endl;

        // if an entry already exists, update NCE
        if (entry->macAddress.equals(nsMacAddr)) {
            entry->reachabilityState = Ipv6NeighbourCache::REACHABLE;
            entry->registLifeTime = simTime() + ns->getARO().getRegistLifeTime();
            entry->reachabilityExpires = simTime() + ns->getARO().getRegistLifeTime();
            EV_INFO<<"Reset register life time!"<< endl;

            //create timeout
            cMessage *msg = new cMessage("NeighborCacheTimeout", MK_ADDR_REGIST_TIMEOUT);
            Neighbour *nce = neighbourCache.lookup(nsL3SrcAddr, ifID);
            msg->setContextPointer(nce);
            scheduleAt(simTime() + ns->getARO().getRegistLifeTime()+ uniform(0.000001,0.00002), msg);
        }

        sendSolicitedNa(packet, ns, ie);
    }

}

void Ipv6NeighbourDiscovery::sendSolicitedNa(Packet *packet, const Ipv6NeighbourSolicitation *ns, InterfaceEntry *ie)
{
//    std::cout <<"------>< sendSolicitedNa " <<std::endl;
    auto na = makeShared<Ipv6NeighbourAdvertisement>();
    na->setChunkLength(ICMPv6_HEADER_BYTES + B(IPv6_ADDRESS_SIZE));      // FIXME set correct length

    //RFC 2461: Section 7.2.4
    /*A node sends a Neighbor Advertisement in response to a valid Neighbor
       Solicitation targeting one of the node's assigned addresses.  The
       Target Address of the advertisement is copied from the Target Address
       of the solicitation.*/
    na->setTargetAddress(ns->getTargetAddress());
    na->setSourceLinkLayerAddress(ie->getMacAddress());

    /*If the solicitation's IP Destination Address is not a multicast address,
       the Target Link-Layer Address option MAY be omitted; the neighboring node's
       cached value must already be current in order for the solicitation to have
       been received. If the solicitation's IP Destination Address is a multicast
       address, the Target Link-Layer option MUST be included in the advertisement.*/
    na->setTargetLinkLayerAddress(ie->getMacAddress());    //here, we always include the MAC addr.
    na->setChunkLength(na->getChunkLength() + IPv6ND_LINK_LAYER_ADDRESS_OPTION_LENGTH);

    /*Furthermore, if the node is a router, it MUST set the Router flag to one;
       otherwise it MUST set the flag to zero.*/
    na->setRouterFlag(rt6->isRouter());

    /*If the (NS)Target Address is either an anycast address or a unicast
       address for which the node is providing proxy service, or the Target
       Link-Layer Address option is not included,*/
    //TODO:ANYCAST will not be implemented here!

    if (ns->getSourceLinkLayerAddress().isUnspecified())
        //the Override flag SHOULD be set to zero.
        na->setOverrideFlag(false);
    else
        //Otherwise, the Override flag SHOULD be set to one.
        na->setOverrideFlag(true);

    /*Proper setting of the Override flag ensures that nodes give preference to
       non-proxy advertisements, even when received after proxy advertisements, and
       also ensures that the first advertisement for an anycast address "wins".*/

    Ipv6Address naDestAddr;
    //If the source of the solicitation is the unspecified address,
    if (packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6().isUnspecified()) {
        /*the node MUST set the Solicited flag to zero and multicast the advertisement
           to the all-nodes address.*/
        na->setSolicitedFlag(false);
        naDestAddr = Ipv6Address::ALL_NODES_2;
        EV_INFO<<"NA address is: "<< naDestAddr <<endl;
    }
    else {
        /*Otherwise, the node MUST set the Solicited flag to one and unicast
           the advertisement to the Source Address of the solicitation.*/
        na->setSolicitedFlag(true);
        naDestAddr = packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6();
        EV_INFO<<"NA address is: "<< naDestAddr <<endl;
    }


    Neighbour *neighbourEntry = neighbourCache.lookup(ns->getTargetAddress(), ie->getInterfaceId());
    if (neighbourEntry!= nullptr) {
        if (neighbourEntry->relayAddr.isUnspecified() ||rt6->isLocalAddress(neighbourEntry->relayAddr))
            naDestAddr = neighbourEntry->linkLocalAddr;
        else
            naDestAddr = packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6();
//            naDestAddr = neighbourEntry->relayAddr;
    }
    EV_INFO<<"NA address is: "<< naDestAddr <<endl;


    /*If the Target Address is an anycast address the sender SHOULD delay sending
       a response for a random time between 0 and MAX_ANYCAST_DELAY_TIME seconds.*/
    /*TODO: More associated complexity for this one. We will have to delay
       sending off the solicitation. Perhaps the self message could have a context
       pointer pointing to a struct with enough info to create and send a NA packet.*/

    /*Because unicast Neighbor Solicitations are not required to include a
       Source Link-Layer Address, it is possible that a node sending a
       solicited Neighbor Advertisement does not have a corresponding link-
       layer address for its neighbor in its Neighbor Cache.  In such
       situations, a node will first have to use Neighbor Discovery to
       determine the link-layer address of its neighbor (i.e, send out a
       multicast Neighbor Solicitation).*/
    //TODO: if above mentioned happens, can addr resolution be performed for ND messages?
    //if no link-layer addr exists for unicast addr when sending solicited NA, we should
    //add the NA to the list of queued packets. What if we have a list of queued
    //packets for different unicast solicitations? each time addr resolution is
    //done we should check the destinations of the list of queued packets and send
    //off the respective ones.

//    Ipv6Address myIPv6Addr = ie->ipv6Data()->getPreferredAddress();
    Ipv6Address myIPv6Addr = ie->ipv6Data()->getLinkLocalAddress();


    //include global prefix for neighbors
    Ipv6NdPrefixInformation prefixInfo;
    EV_INFO<< "Global address prefix is: " << ie->ipv6Data()->getPreferredAddress().getPrefix(64)<< endl;
    prefixInfo.setPrefix(ie->ipv6Data()->getPreferredAddress().getPrefix(64));
    prefixInfo.setValidLifetime(60);
    prefixInfo.setPrefixLength(64);
    prefixInfo.setDistance(hopDistance);

    na->setPrefixInformationArraySize(1);
    na->setPrefixInformation(0,prefixInfo);

    if (neighbourCache.getDefaultRouterList().begin() != neighbourCache.getDefaultRouterList().end()) {
        auto it =neighbourCache.getDefaultRouterList().begin();
        Neighbour& nce = *it;
        Ipv6Address destAddr = nce.globalAddr;
        na->setRouterAddress(destAddr);
    }

    auto naPacket = new Packet("NApacket");
    Icmpv6::insertCrc(crcMode, na, packet);
    naPacket->insertAtFront(na);
    sendPacketToIpv6Module(naPacket, naDestAddr, myIPv6Addr, ie->getInterfaceId());
    delete packet;
}

void Ipv6NeighbourDiscovery::sendSolicitedNaForDAD(Packet *packet, Ipv6Address& destAddr, const Ipv6DuplicateAddrConfirm *dac,
        InterfaceEntry *ie)
{
//    std::cout <<"---->< sendSolicitedNaForDAD " <<std::endl;
    auto na = makeShared<Ipv6NeighbourAdvertisement>();
    na->setChunkLength(ICMPv6_HEADER_BYTES + B(IPv6_ADDRESS_SIZE));      // FIXME set correct length

    //RFC 2461: Section 7.2.4
    /*A node sends a Neighbor Advertisement in response to a valid Neighbor
       Solicitation targeting one of the node's assigned addresses.  The
       Target Address of the advertisement is copied from the Target Address
       of the solicitation.*/
    na->setTargetAddress(dac->getRegisteredAddress());
    Ipv6NdAddressRegistrationOption aro;
    aro.setStatus(dac->getStatus());
    na->setARO(aro);

    EV_INFO<<"na EUI64 len: "<<na->getARO().getEUI64().len<< endl;
    EV_INFO<<"na EUI64 low: "<<na->getARO().getEUI64().low << endl;
    EV_INFO<<"na EUI64 normal: "<<na->getARO().getEUI64().normal << endl;

    na->setChunkLength(na->getChunkLength() + IPv6ND_LINK_LAYER_ADDRESS_OPTION_LENGTH);

    /*Furthermore, if the node is a router, it MUST set the Router flag to one;
       otherwise it MUST set the flag to zero.*/
    na->setRouterFlag(rt6->isRouter());

    /*If the (NS)Target Address is either an anycast address or a unicast
       address for which the node is providing proxy service, or the Target
       Link-Layer Address option is not included,*/
    //TODO:ANYCAST will not be implemented here!

//    if (ns->getSourceLinkLayerAddress().isUnspecified())
   if (dac->getStatus() != 0)
        //the Override flag SHOULD be set to zero.
        na->setOverrideFlag(false);
    else
        //Otherwise, the Override flag SHOULD be set to one.
        na->setOverrideFlag(true);

    /*Proper setting of the Override flag ensures that nodes give preference to
       non-proxy advertisements, even when received after proxy advertisements, and
       also ensures that the first advertisement for an anycast address "wins".*/

    Ipv6Address naDestAddr;
    //If the source of the solicitation is the unspecified address,
    if (packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6().isUnspecified()) {
        /*the node MUST set the Solicited flag to zero and multicast the advertisement
           to the all-nodes address.*/
        na->setSolicitedFlag(false);
        naDestAddr = Ipv6Address::ALL_NODES_2;
        EV_INFO <<"ALL_NODES_2 NA dest Addr is "<< naDestAddr <<endl;
    }
    else {
        /*Otherwise, the node MUST set the Solicited flag to one and unicast
           the advertisement to the Source Address of the solicitation.*/
        na->setSolicitedFlag(true);
//        naDestAddr = packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6(); //global address
//        naDestAddr = packet->getTag<L3AddressInd>()->getDestAddress().toIpv6();
        naDestAddr = dac->getRegisteredAddress();
        EV_INFO <<"L3AddressInd NA dest Addr is "<< naDestAddr <<endl;
    }

    /*If the Target Address is an anycast address the sender SHOULD delay sending
       a response for a random time between 0 and MAX_ANYCAST_DELAY_TIME seconds.*/
    /*TODO: More associated complexity for this one. We will have to delay
       sending off the solicitation. Perhaps the self message could have a context
       pointer pointing to a struct with enough info to create and send a NA packet.*/

    /*Because unicast Neighbor Solicitations are not required to include a
       Source Link-Layer Address, it is possible that a node sending a
       solicited Neighbor Advertisement does not have a corresponding link-
       layer address for its neighbor in its Neighbor Cache.  In such
       situations, a node will first have to use Neighbor Discovery to
       determine the link-layer address of its neighbor (i.e, send out a
       multicast Neighbor Solicitation).*/
    //TODO: if above mentioned happens, can addr resolution be performed for ND messages?
    //if no link-layer addr exists for unicast addr when sending solicited NA, we should
    //add the NA to the list of queued packets. What if we have a list of queued
    //packets for different unicast solicitations? each time addr resolution is
    //done we should check the destinations of the list of queued packets and send
    //off the respective ones.

    Ipv6Address myIPv6Addr = ie->ipv6Data()->getPreferredAddress(); //global address
//    Ipv6Address myIPv6Addr = ie->ipv6Data()->getLinkLocalAddress();
    EV_INFO <<"Send solicited NA for DAD, source Addr is: "<< myIPv6Addr <<endl;

    auto naPacket = new Packet("NApacket");
    Icmpv6::insertCrc(crcMode, na, packet);
    naPacket->insertAtFront(na);
    sendPacketToIpv6Module(naPacket, destAddr, myIPv6Addr, ie->getInterfaceId());
    delete packet;

}


void Ipv6NeighbourDiscovery::sendUnsolicitedNa(InterfaceEntry *ie)
{
    //RFC 2461
    //Section 7.2.6: Sending Unsolicited Neighbor Advertisements
#ifdef WITH_xMIPv6
    Enter_Method_Silent();
#endif /* WITH_xMIPv6 */

#ifndef WITH_xMIPv6
    // In some cases a node may be able to determine that its link-layer
    // address has changed (e.g., hot-swap of an interface card) and may
    // wish to inform its neighbors of the new link-layer address quickly.
    // In such cases a node MAY send up to MAX_NEIGHBOR_ADVERTISEMENT
    // unsolicited Neighbor Advertisement messages to the all-nodes
    // multicast address.  These advertisements MUST be separated by at
    // least RetransTimer seconds.
#else /* WITH_xMIPv6 */
    auto na = makeShared<Ipv6NeighbourAdvertisement>();
    Ipv6Address myIPv6Addr = ie->ipv6Data()->getPreferredAddress();
    na->setChunkLength(ICMPv6_HEADER_BYTES + B(IPv6_ADDRESS_SIZE));
#endif /* WITH_xMIPv6 */

    // The Target Address field in the unsolicited advertisement is set to
    // an IP address of the interface, and the Target Link-Layer Address
    // option is filled with the new link-layer address.
#ifdef WITH_xMIPv6
    na->setTargetAddress(myIPv6Addr);
    na->setTargetLinkLayerAddress(ie->getMacAddress());
    na->setChunkLength(na->getChunkLength() + IPv6ND_LINK_LAYER_ADDRESS_OPTION_LENGTH);
#endif /* WITH_xMIPv6 */

    // The Solicited flag MUST be set to zero, in order to avoid confusing
    // the Neighbor Unreachability Detection algorithm.
#ifdef WITH_xMIPv6
    na->setSolicitedFlag(false);
#endif /* WITH_xMIPv6 */

    // If the node is a router, it MUST set the Router flag to one;
    // otherwise it MUST set it to zero.
#ifdef WITH_xMIPv6
    na->setRouterFlag(rt6->isRouter());
#endif /* WITH_xMIPv6 */

    // The Override flag MAY be set to either zero or one.  In either case,
    // neighboring nodes will immediately change the state of their Neighbor
    // Cache entries for the Target Address to STALE, prompting them to
    // verify the path for reachability.  If the Override flag is set to
    // one, neighboring nodes will install the new link-layer address in
    // their caches.  Otherwise, they will ignore the new link-layer
    // address, choosing instead to probe the cached address.
#ifdef WITH_xMIPv6
    na->setOverrideFlag(true);
#endif /* WITH_xMIPv6 */

    // A node that has multiple IP addresses assigned to an interface MAY
    // multicast a separate Neighbor Advertisement for each address.  In
    // such a case the node SHOULD introduce a small delay between the
    // sending of each advertisement to reduce the probability of the
    // advertisements being lost due to congestion.

    // A proxy MAY multicast Neighbor Advertisements when its link-layer
    // address changes or when it is configured (by system management or
    // other mechanisms) to proxy for an address.  If there are multiple
    // nodes that are providing proxy services for the same set of addresses
    // the proxies SHOULD provide a mechanism that prevents multiple proxies
    // from multicasting advertisements for any one address, in order to
    // reduce the risk of excessive multicast traffic.

    // Also, a node belonging to an anycast address MAY multicast
    // unsolicited Neighbor Advertisements for the anycast address when the
    // node's link-layer address changes.

    // Note that because unsolicited Neighbor Advertisements do not reliably
    // update caches in all nodes (the advertisements might not be received
    // by all nodes), they should only be viewed as a performance
    // optimization to quickly update the caches in most neighbors.  The
    // Neighbor Unreachability Detection algorithm ensures that all nodes
    // obtain a reachable link-layer address, though the delay may be
    // slightly longer.
#ifdef WITH_xMIPv6
    auto packet = new Packet("NApacket");
    Icmpv6::insertCrc(crcMode, na, packet);
    packet->insertAtFront(na);
    sendPacketToIpv6Module(packet, Ipv6Address::ALL_NODES_2, myIPv6Addr, ie->getInterfaceId());
#endif /* WITH_xMIPv6 */
}

void Ipv6NeighbourDiscovery::processNaPacket(Packet *packet, const Ipv6NeighbourAdvertisement *na)
{
//    std::cout <<"----->< processNaPacket " <<std::endl;
    static int count = 0;

    if (validateNaPacket(packet, na) == false) {
        delete packet;
        return;
    }

    //Neighbour Advertisement Information
    Ipv6Address naTargetAddr = na->getTargetAddress();
    Ipv6Address pktDestAddr = packet->getTag<L3AddressInd>()->getDestAddress().toIpv6();
    Ipv6Address pktSrcAddr = packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6();

    EV_INFO << "NA packet target address is: "<< naTargetAddr <<endl;
    EV_INFO << "NA packet dest address is: "<< pktDestAddr <<endl;
    EV_INFO << "NA packet src address is: "<< pktSrcAddr <<endl;

    //First, we check if the target address in NA is found in the interface it
    //was received on is tentative.
    InterfaceEntry *ie = ift->getInterfaceById(packet->getTag<InterfaceInd>()->getInterfaceId());
    Neighbour *neighbourEntry = neighbourCache.lookup(naTargetAddr, ie->getInterfaceId());

    //NeighborRoute
    Neighbour *neighborRoute = neighbourCache.lookupNeighborRoute(naTargetAddr, ie->getInterfaceId());

    if (ie->ipv6Data()->isDadInProgress()== true) {
        ie->ipv6Data()->setDadInProgress(false);

        EV_INFO << "set ie dad in progress to false!"<< endl;



        AddrRegistEntry *addrRegistEntry = fetchAddrRegistEntry(ie);
        if (addrRegistEntry != nullptr) {
            EV_DETAIL << "addrRegistEntry is not nullptr, reset numSent!" << endl;
            addrRegistEntry->numNSSent =0;
        }
        else
            EV_DETAIL << "addrRegistEntry is nullptr!" << endl;

        ie->ipv6Data()->permanentlyAssign (naTargetAddr);

        count++;

        //Address Registration
        AddrRegistEntry *newAddrRegistEntry = new AddrRegistEntry();
        newAddrRegistEntry->interfaceId = ie->getInterfaceId();
        newAddrRegistEntry->numNSSent = 0;
        newAddrRegistEntry->numNSSent++;

        cMessage *msg = new cMessage("AddrRegistRetransmit", MK_ADDR_REGIST_RETRANS);
        msg->setContextPointer(ie);
        newAddrRegistEntry->timeoutMsg = msg;
        addrRegistList.insert(newAddrRegistEntry);
        scheduleAt(simTime() + 17 +uniform(0.000001,0.00002), msg);
        delete packet;

    }


    // forward NDMessage for neighbour
    else if (neighbourEntry!=nullptr && rt6->isLocalAddress(neighbourEntry->relayAddr)) {

        neighbourEntry->reachabilityState = Ipv6NeighbourCache::REACHABLE;
        EV_INFO << "Change NCE State to Reachable!" << endl;
        if (neighbourEntry->relayAddr.isUnspecified() || rt6->isLocalAddress(neighbourEntry->relayAddr))
            packet->addTagIfAbsent<MacAddressReq>()->setDestAddress(neighbourEntry->macAddress);
        forwardNDMessageForNeighbour(packet, neighbourEntry->linkLocalAddr, ie);
    }
    else if (neighbourEntry!=nullptr) {
            if (neighbourEntry->reachabilityState == Ipv6NeighbourCache::INCOMPLETE)
                    processNaForIncompleteNceState(na, neighbourEntry);
            delete packet;
   }
    else  if (neighbourCache.getDefaultRouterList().begin() == neighbourCache.getDefaultRouterList().end()
            && !ie->ipv6Data()->getPreferredAddress().isGlobal()) {

        if (na->getPrefixInformation(0).getPrefix()!=Ipv6Address::LINKLOCAL_PREFIX) {
            hopDistance =na->getPrefixInformation(0).getDistance()+1;
            if (neighborHopDistance > hopDistance)
                neighborHopDistance = hopDistance;  // neighborHopDistance records the smallest hop distance
            Ipv6Address destAddr = packet->getTag<L3AddressInd>()->getSrcAddress().toIpv6();
            tentativeRouterList.push_back(tentativeRouter (na->getRouterAddress(), destAddr,
                    na->getPrefixInformation(0).getDistance()+1, na->getSourceLinkLayerAddress(), na->getPrefixInformation(0)));

            delete packet;
        }
        else {
            EV_INFO <<"Prefix is link local preifx, delete packet!"<<endl;
            delete packet;
            return;
        }
    }

    else if (neighborRoute!=nullptr) {
        Ipv6Address dest = neighborRoute->relayAddr;
        forwardNDMessageForNeighbour(packet, dest, ie);
    }

    else if (rt6->isRouter())
        processNaFromMA(packet, na);

    else {
        //temporary put address registration reply deal message  here
        AddrRegistEntry *addrRegistEntry = fetchAddrRegistEntry(ie);
        if (addrRegistEntry != nullptr) {
            EV_DETAIL << "addrRegistEntry is not nullptr, reset numSent!" << endl;
            addrRegistEntry->numNSSent =0;
        }
        else {
            EV_DETAIL << "addrRegistEntry is nullptr!" << endl;
            initiateAddressRegistration(ie->ipv6Data()->getPreferredAddress(), pktSrcAddr, ie);
        }
        delete packet;
    }

    //Hide orignal functions
//    if (ie->ipv6Data()->isTentativeAddress(naTargetAddr)) {
//        throw cRuntimeError("Duplicate Address Detected! Manual attention needed!");
//    }
    //Logic as defined in Section 7.2.5
//    Neighbour *neighbourEntry = neighbourCache.lookup(naTargetAddr, ie->getInterfaceId());
    // END

//    if (neighbourEntry == nullptr) {
//        EV_INFO << "NA received. Target Address not found in Neighbour Cache\n";
//        EV_INFO << "Dropping NA packet.\n";
//
//        delete packet;
//        return;
//    }

//    Neighbour *nce = neighbourCache.lookup(naTargetAddr, ie->getInterfaceId());
//    if (nce == nullptr)
//        std::cout <<"nce is null"<<endl;
//    if (nce->reachabilityState == Ipv6NeighbourCache::INCOMPLETE)
//        processNaForIncompleteNceState(na, nce);
//    else
//        processNaForOtherNceStates(na, neighbourEntry);
//
//    delete packet;
}


/*When a vehicle start to look for relay neighbors, it will not process NA immediately but wait 1s
to receive all replies from neighbors, and select the nearest neighbor with least hop distances.*/
void Ipv6NeighbourDiscovery::delayProcessNaFromNeighbor(cMessage *msg) {
//    std::cout <<" ======>>> delayProcessNaFromNeighbor" <<std::endl;
    InterfaceEntry *ie = ift->getInterfaceByName("nic");

    std::sort(tentativeRouterList.begin(), tentativeRouterList.end(), sortByHopDistance());

    for (std::vector<tentativeRouter>::size_type i = 0; i < tentativeRouterList.size(); i++) {
        EV_INFO <<"sortedRouterList: " << tentativeRouterList.at(i).relayAddr << ' '<<endl;
    }

    if (tentativeRouterList.begin()!=tentativeRouterList.end()) {
        auto rt = tentativeRouterList.at(0);
        neighbourCache.addRouterWithGlobalAddr(rt.relayAddr, ie->getInterfaceId(),
                        rt.relayLinkLayerAddr, 2000, rt.routerAddr /* + ra->getRouterLifetime()*/);

        rt6->addDefaultRoute(rt.relayAddr, ie->getInterfaceId(), 2000);
        neighbourCache.addNeighborRoute(rt.relayAddr, ie->getInterfaceId(), rt.relayLinkLayerAddr, Ipv6Address::UNSPECIFIED_ADDRESS, 1);

        Neighbour *router = neighbourCache.lookup(rt.relayAddr, ie->getInterfaceId());
        if (router!=nullptr) {
            router->hopDistance = 1;
            //reset hop counts
            hopDistance = neighborHopDistance;   // smallest hopDistance, set it as its own permanent hop distance
            neighborHopDistance = 10;
            EV_INFO << "Start multihop Dad through neighbour!"<< endl;
        }

        Neighbour *nb = neighbourCache.lookup(rt.relayAddr, ie->getInterfaceId());
        if (nb!=nullptr)
            nb->reachabilityState = Ipv6NeighbourCache::REACHABLE;
        processRaPrefixInfoForAddrAutoConf(rt.prefixInfo, ie);
    }
    delete msg;

}


bool Ipv6NeighbourDiscovery::validateNaPacket(Packet *packet, const Ipv6NeighbourAdvertisement *na)
{
    bool result = true;    //adopt optimistic approach

    //RFC 2461:7.1.2 Validation of Neighbor Advertisments(some checks are omitted)
    //A node MUST silently discard any received Neighbor Advertisment messages
    //that do not satisfy all of the following validity checks:

    //- The IP Hop Limit field has a value of 255, i.e., the packet
    //  could not possibly have been forwarded by a router.

    //since we use multihop, we have to delete the original hop limit
//    if (packet->getTag<HopLimitInd>()->getHopLimit() != 255) {
//        EV_WARN << "Hop Limit is not 255! NA validation failed!\n";
//        result = false;
//    }

    //- Target Address is not a multicast address.
    if (na->getTargetAddress().isMulticast() == true) {
        EV_WARN << "Target Address is a multicast address! NA validation failed!\n";
        result = false;
    }

    //- If the IP Destination Address is a multicast address the Solicited flag
    //  is zero.
    if (packet->getTag<L3AddressInd>()->getDestAddress().toIpv6().isMulticast()) {
        if (na->getSolicitedFlag() == true) {
            EV_WARN << "Dest Address is multicast address but solicited flag is 0!\n";
            result = false;
        }
    }

    if (result == true)
        bubble("NA validation passed.");
    else
        bubble("NA validation failed.");

    return result;
}

void Ipv6NeighbourDiscovery::processNaForIncompleteNceState(const Ipv6NeighbourAdvertisement *na, Neighbour *nce)
{
    MacAddress naMacAddr = na->getTargetLinkLayerAddress();
    bool naRouterFlag = na->getRouterFlag();
    bool naSolicitedFlag = na->getSolicitedFlag();
    const Key *nceKey = nce->nceKey;
    InterfaceEntry *ie = ift->getInterfaceById(nceKey->interfaceID);

    /*If the target's neighbour Cache entry is in the INCOMPLETE state when the
       advertisement is received, one of two things happens.*/
    if (naMacAddr.isUnspecified()) {
        /*If the link layer has addresses and no Target Link-Layer address option
           is included, the receiving node SHOULD silently discard the received
           advertisement.*/
        EV_INFO << "No MAC Address specified in NA. Ignoring NA\n";
        return;
    }
    else {
        //Otherwise, the receiving node performs the following steps:
        //- It records the link-layer address in the neighbour Cache entry.
        EV_INFO << "ND is updating Neighbour Cache Entry.\n";
        nce->macAddress = naMacAddr;

        //- If the advertisement's Solicited flag is set, the state of the
        //  entry is set to REACHABLE, otherwise it is set to STALE.
        if (naSolicitedFlag == true) {
            nce->reachabilityState = Ipv6NeighbourCache::REACHABLE;
            EV_INFO << "Reachability confirmed through successful Addr Resolution.\n";
            //XIANG ZHONG 2020.01.02
            //test: set the reachable time between RSUs to a big number
//            nce->reachabilityExpires = simTime() + ie->ipv6Data()->_getReachableTime();
            nce->reachabilityExpires = simTime()+500;

        }
        else
            nce->reachabilityState = Ipv6NeighbourCache::STALE;

        //- It sets the IsRouter flag in the cache entry based on the Router
        //  flag in the received advertisement.
        nce->isRouter = naRouterFlag;
        if (nce->isDefaultRouter() && !nce->isRouter)
            neighbourCache.getDefaultRouterList().remove(*nce);

        //- It sends any packets queued for the neighbour awaiting address
        //  resolution.
        sendQueuedPacketsToIpv6Module(nce);
        cancelAndDelete(nce->arTimer);
        nce->arTimer = nullptr;
    }
}

void Ipv6NeighbourDiscovery::processNaForOtherNceStates(const Ipv6NeighbourAdvertisement *na, Neighbour *nce)
{
    bool naRouterFlag = na->getRouterFlag();
    bool naSolicitedFlag = na->getSolicitedFlag();
    bool naOverrideFlag = na->getOverrideFlag();
    MacAddress naMacAddr = na->getTargetLinkLayerAddress();
    const Key *nceKey = nce->nceKey;
    InterfaceEntry *ie = ift->getInterfaceById(nceKey->interfaceID);

    /*draft-ietf-ipv6-2461bis-04
       Section 7.2.5: Receipt of Neighbour Advertisements
       If the target's Neighbor Cache entry is in any state other than INCOMPLETE
       when the advertisement is received, the following actions take place:*/

    if (naOverrideFlag == false && !(naMacAddr.equals(nce->macAddress))
        && !(naMacAddr.isUnspecified()))
    {
        EV_INFO << "NA override is FALSE and NA MAC addr is different.\n";

        //I. If the Override flag is clear and the supplied link-layer address
        //   differs from that in the cache, then one of two actions takes place:
        //(Note: An unspecified MAC should not be compared with the NCE's mac!)
        //a. If the state of the entry is REACHABLE,
        if (nce->reachabilityState == Ipv6NeighbourCache::REACHABLE) {
            EV_INFO << "NA mac is different. Change NCE state from REACHABLE to STALE\n";
            //set it to STALE, but do not update the entry in any other way.
            nce->reachabilityState = Ipv6NeighbourCache::STALE;
        }
        else
            //b. Otherwise, the received advertisement should be ignored and
            //MUST NOT update the cache.
            EV_INFO << "NCE is not in REACHABLE state. Ignore NA.\n";
    }
    else if (naOverrideFlag == true || naMacAddr.equals(nce->macAddress)
             || naMacAddr.isUnspecified())
    {
        EV_INFO << "NA override flag is TRUE. or Advertised MAC is same as NCE's. or"
                << " NA MAC is not specified.\n";
        /*II. If the Override flag is set, or the supplied link-layer address
           is the same as that in the cache, or no Target Link-layer address
           option was supplied, the received advertisement MUST update the
           Neighbor Cache entry as follows:*/

        /*- The link-layer address in the Target Link-Layer Address option
            MUST be inserted in the cache (if one is supplied and is
            Different than the already recorded address).*/
        if (!(naMacAddr.isUnspecified()) && !(naMacAddr.equals(nce->macAddress))) {
            EV_INFO << "Updating NCE's MAC addr with NA's.\n";
            nce->macAddress = naMacAddr;
        }

        //- If the Solicited flag is set,
        if (naSolicitedFlag == true) {
            EV_INFO << "Solicited Flag is TRUE. Set NCE state to REACHABLE.\n";
            //the state of the entry MUST be set to REACHABLE.
            nce->reachabilityState = Ipv6NeighbourCache::REACHABLE;
            //We have to cancel the NUD self timer message if there is one.

            cMessage *msg = nce->nudTimeoutEvent;
            if (msg != nullptr) {
                EV_INFO << "NUD in progress. Cancelling NUD Timer\n";
                bubble("Reachability Confirmed via NUD.");
                nce->reachabilityExpires = simTime() + ie->ipv6Data()->_getReachableTime();
                cancelAndDelete(msg);
                nce->nudTimeoutEvent = nullptr;
            }
        }
        else {
            //If the Solicited flag is zero
            EV_INFO << "Solicited Flag is FALSE.\n";
            //and the link layer address was updated with a different address

            if (!(naMacAddr.equals(nce->macAddress))) {
                EV_INFO << "NA's MAC is different from NCE's.Set NCE state to STALE\n";
                //the state MUST be set to STALE.
                nce->reachabilityState = Ipv6NeighbourCache::STALE;
            }
            else
                //Otherwise, the entry's state remains unchanged.
                EV_INFO << "NA's MAC is the same as NCE's. State remains unchanged.\n";
        }
        //(Next paragraph with explanation is omitted.-WEI)

        /*- The IsRouter flag in the cache entry MUST be set based on the
           Router flag in the received advertisement.*/
        EV_INFO << "Updating NCE's router flag to " << naRouterFlag << endl;
        nce->isRouter = naRouterFlag;

        /*In those cases where the IsRouter flag changes from TRUE to FALSE as a
           result of this update, the node MUST remove that router from the Default
           Router List and update the Destination Cache entries for all destinations
           using that neighbor as a router as specified in Section 7.3.3. This is
           needed to detect when a node that is used as a router stops forwarding
           packets due to being configured as a host.*/
        if (nce->isDefaultRouter() && !nce->isRouter)
            neighbourCache.getDefaultRouterList().remove(*nce);

        //TODO: remove destination cache entries
    }
}

void Ipv6NeighbourDiscovery::createAndSendRedirectPacket(InterfaceEntry *ie)
{
    //Construct a Redirect message
    auto redirect = makeShared<Ipv6Redirect>(); // TODO: "redirectMsg");
    redirect->setChunkLength(ICMPv6_HEADER_BYTES + B(IPv6_ADDRESS_SIZE) * 2);   // RFC 2461, Section 4.5

//FIXME incomplete code
#if 0
    //Redirect Message Specific Information
    redirect->setTargetAddress();
    redirect->setDestinationAddress();

    //Possible Option
    redirect->setTargetLinkLayerAddress();
    redirect->addByteLength(IPv6ND_LINK_LAYER_ADDRESS_OPTION_LENGTH);
#endif
}

void Ipv6NeighbourDiscovery::processRedirectPacket(const Ipv6Redirect *redirect)
{
//FIXME incomplete code
#if 0
    //First we need to extract information from the redirect message
    Ipv6Address targetAddr = redirect->getTargetAddress();    //Addressed to me
    Ipv6Address destAddr = redirect->getDestinationAddress();    //new dest addr

    //Optional
    MacAddress macAddr = redirect->getTargetLinkLayerAddress();
#endif
}

#ifdef WITH_xMIPv6
//The overlaoded function has been added by zarrar yousaf on 20.07.07
void Ipv6NeighbourDiscovery::processRaPrefixInfoForAddrAutoConf(const Ipv6NdPrefixInformation& prefixInfo, InterfaceEntry *ie, bool hFlag)
{
    EV_INFO << "Processing Prefix Info for address auto-configuration.\n";
//    std::cout << "Processing Prefix Info for address auto-configuration.\n";
    Ipv6Address prefix = prefixInfo.getPrefix();
    uint prefixLength = prefixInfo.getPrefixLength();
    simtime_t preferredLifetime = prefixInfo.getPreferredLifetime();
    simtime_t validLifetime = prefixInfo.getValidLifetime();

    //EV << "/// prefix: " << prefix << std::endl; // CB

    //RFC 2461: Section 5.5.3
    //First condition tested, the autonomous flag is already set

    //b) If the prefix is the link-local prefix, silently ignore the Prefix
    //Information option.
    if (prefixInfo.getPrefix().isLinkLocal() == true) {
        EV_INFO << "Prefix is link-local, ignore Prefix Information Option\n";
        return;
    }

    //c) If the preferred lifetime is greater than the valid lifetime, silently
    //ignore the Prefix Information option. A node MAY wish to log a system
    //management error in this case.
    if (preferredLifetime > validLifetime) {
        EV_INFO << "Preferred lifetime is greater than valid lifetime, ignore Prefix Information\n";
        return;
    }

    // changed structure of code below, 12.9.07 - CB
    bool isPrefixAssignedToInterface = false;
    bool returnedHome = false;    // 4.9.07 - CB

    for (int i = 0; i < ie->ipv6Data()->getNumAddresses(); i++) {
        if (ie->ipv6Data()->getAddress(i).getScope() == Ipv6Address::LINK)
            // skip the link local address - it's not relevant for movement detection
            continue;

        /*RFC 3775, 11.5.4
           A mobile node detects that it has returned to its home link through
           the movement detection algorithm in use (Section 11.5.1), when the
           mobile node detects that its home subnet prefix is again on-link.
         */
        if (ie->ipv6Data()->getAddress(i).matches(prefix, prefixLength) == true) {
            // A MN can have the following address combinations:
            // * only a link-local address -> at home
            // * link-local plus a HoA -> at home
            // * link-local, HoA plus CoA -> at foreign network
            // The prefix of the home network can only match the HoA
            // address, and if it does (=we received a RA from the HA),
            // and we have a CoA as well (three addresses) then we have
            // returned home
            // TODO the MN can have several global scope addresses configured from
            // different prefixes advertised via a RA -> not supported with this code
            if (rt6->isMobileNode() && ie->ipv6Data()->getAddressType(i) == Ipv6InterfaceData::HoA && ie->ipv6Data()->getNumAddresses() > 2)
                returnedHome = true;
            else {
                isPrefixAssignedToInterface = true;
                EV_INFO << "The received Prefix is:" <<prefix<< endl;
                EV_INFO << "My link local address is :" <<ie->ipv6Data()->getLinkLocalAddress()<< endl;
                EV_INFO << "My global address is :" <<ie->ipv6Data()->getAddress(i)<< endl;
                EV_INFO << "The received Prefix is already assigned to the interface" << endl;    //Zarrar Yousaf 19.07.07

                break;
            }
        }
    }
    /*d) If the prefix advertised does not match the prefix of an address already
         in the list, and the Valid Lifetime is not 0, form an address (and add
         it to the list) by combining the advertised prefix with the link's
         interface identifier as follows:
     */
    if ((isPrefixAssignedToInterface == false) && (validLifetime != 0)) {
        EV_INFO << "Prefix not assigned to interface. Possible new router detected. Auto-configuring new address.\n";
        Ipv6Address linkLocalAddress = ie->ipv6Data()->getLinkLocalAddress();
        ASSERT(linkLocalAddress.isUnspecified() == false);

        EV_INFO << "The received Prefix is:" <<prefix<< endl;
        Ipv6Address newAddr = linkLocalAddress.setPrefix(prefix, prefixLength);

        Ipv6Address CoA;
        //TODO: for now we leave the newly formed address as not tentative,
        //according to Greg, we have to always perform DAD for a newly formed address.
        EV_INFO << "Assigning new address to: " << ie->getInterfaceName() << endl;

        // we are for sure either in the home network or in a new foreign network
        // -> remove CoA
        //CoA = ie->ipv6()->removeCoAAddr();
        // moved code from above to processDADTimeout()

        // 27.9.07 - CB
        if (returnedHome) {
            // we have to remove the CoA before we create a new one
            EV_INFO << "Node returning home - removing CoA...\n";
            CoA = ie->ipv6Data()->removeAddress(Ipv6InterfaceData::CoA);

            // nothing to do more wrt managing addresses, as we are at home and a HoA is
            // already existing at the interface

            // initiate the returning home procedure
            ASSERT(!CoA.isUnspecified());
            mipv6->returningHome(CoA, ie);
        }
        else {    // non-mobile nodes will never have returnedHome == true, so they will always assign a new address
            CoA = ie->ipv6Data()->getGlobalAddress(Ipv6InterfaceData::CoA);

            // form new address and initiate DAD, as we are in a foreign network

            if (ie->ipv6Data()->getNumAddresses() == 1) {

                // we only have a link-layer and no unicast address of scope > link-local
                // this means DAD is already running or has already been completed
                // create a unicast address with scope > link-local
                bool isLinkLocalTentative = ie->ipv6Data()->isTentativeAddress(linkLocalAddress);
                // if the link local address is tentative, then we make the global unicast address tentative as well

                //When a vehicle receive the prefix from RSU, this address need to be regarded as tentative address
                //before it finished multihop DAD. Thus, here we first assign this address as tentative
                ie->ipv6Data()->assignAddress(newAddr, true,
                                        simTime() + validLifetime, simTime() + preferredLifetime, hFlag);
//                ie->ipv6Data()->assignAddress(newAddr, isLinkLocalTentative,
//                        simTime() + validLifetime, simTime() + preferredLifetime, hFlag);

                if (neighbourCache.getDefaultRouterList().begin() != neighbourCache.getDefaultRouterList().end()) {
                    EV_INFO<<"start Multihop DAD for: "<<ie->ipv6Data()->getLinkLocalAddress()<< endl;
                    auto it =neighbourCache.getDefaultRouterList().begin();
                    Neighbour& nce = *it;
//                    Ipv6Address *destAddr;
//                    Ipv6Address temp = nce.nceKey->address;

                    if (nce.relayAddr.isUnspecified())
                        dadDest = nce.nceKey->address;
                    else
                        dadDest = nce.relayAddr;

                    //Since we add neighbor routing for remote vehicles, the addresses in neighbor cache should
                    //be global addresses. Thus, we directly start DAD for global addresses.
                    initiateMultihopDad(ie->ipv6Data()->getPreferredAddress(), dadDest, ie);
//                    initiateMultihopDad(ie->ipv6Data()->getLinkLocalAddress(), destAddr, ie);

                    //The following codes are designed for simulation results in VND paper
                    //The vehicles are planned to start DAD at the same time, so I use a scheduled message
                    //instead of directly initiate DAD.

//                    cMessage *msg = new cMessage("multihopDAD", MK_START_MULTIHOP_DAD);
//                    msg->setContextPointer(dadDest);
//                    scheduleAt(simTime() + uniform(0, 0.3), msg);

//                    if (simTime()<3)  //5
//                        scheduleAt(simTime() + uniform(0, 0.2), msg);
//                    else if (simTime()<10) //15
//                        scheduleAt(10+ uniform(0, 0.2), msg);
//                    else if (simTime()<25)
//                        scheduleAt(25+ uniform(0, 0.2), msg);
//                    else
//                        scheduleAt(32+ uniform(0, 0.2), msg);
                }
                else
                    EV_INFO <<"start neighbour discovery!"<<endl;

            }
            else {
                // set tentative flag for all addresses on this interface
                for (int j = 0; j < ie->ipv6Data()->getNumAddresses(); j++) {
                    // TODO improve this code so that only addresses are set to tentative which are
                    // formed based on the link-local address from above
                    ie->ipv6Data()->tentativelyAssign(j);
                    EV_INFO << "Setting address " << ie->ipv6Data()->getAddress(j) << " to tentative.\n";
                }
                initiateDad(ie->ipv6Data()->getLinkLocalAddress(), ie);

                // set MIPv6Init structure that will later on be used for initiating MIPv6 protocol after DAD was performed
                dadGlobalList[ie].hFlag = hFlag;
                dadGlobalList[ie].validLifetime = validLifetime;
                dadGlobalList[ie].preferredLifetime = preferredLifetime;
                dadGlobalList[ie].addr = newAddr;
                //dadGlobalList[ie].returnedHome = returnedHome;
                dadGlobalList[ie].CoA = CoA;
            }
        }
    }
}

void Ipv6NeighbourDiscovery::routersUnreachabilityDetection(const InterfaceEntry *ie)
{
    // remove all entries from the destination cache for this interface
    //rt6->purgeDestCacheForInterfaceID( ie->interfaceId() );
    // invalidate entries in the destination cache for this interface
    //neighbourCache.invalidateEntriesForInterfaceID( ie->interfaceId() );
    // remove default routes on this interface
    rt6->deleteDefaultRoutes(ie->getInterfaceId());
    rt6->deletePrefixes(ie->getInterfaceId());

    for (auto it = neighbourCache.begin(); it != neighbourCache.end(); ) {
        if ((*it).first.interfaceID == ie->getInterfaceId() && it->second.isDefaultRouter()) {
            // update 14.9.07 - CB
            Ipv6Address rtrLnkAddress = (*it).first.address;
            EV_INFO << "Setting router (address=" << rtrLnkAddress << ", ifID="
                    << (*it).first.interfaceID << ") to unreachable" << endl;
            ++it;

            //if ( rtrLnkAddress.isLinkLocal() )
            timeoutDefaultRouter(rtrLnkAddress, ie->getInterfaceId());

            // reset reachability state of this router
            //Neighbour* nbor = neighbourCache.lookup( (*it).first.address, (*it).first.interfaceID );
            //nbor->reachabilityState = Ipv6NeighbourCache::STALE;
            //initiateNeighbourUnreachabilityDetection(nbor);
        }
        else
            ++it;
    }
}

void Ipv6NeighbourDiscovery::invalidateNeigbourCache()
{
    //Enter_Method("Invalidating Neigbour Cache Entries");
    neighbourCache.invalidateAllEntries();
}

#endif

bool Ipv6NeighbourDiscovery::canServeWirelessNodes(InterfaceEntry *ie)
{
    if (isWirelessInterface(ie))
        return true;

    // check if this interface is directly connected to an AccessPoint.
    cModule *node = getContainingNode(this);
    cGate *gate = node->gate(ie->getNodeOutputGateId());
    ASSERT(gate != nullptr);
    cGate *connectedGate = gate->getPathEndGate();
    if (connectedGate != gate) {
        cModule *connectedNode = getContainingNode(connectedGate->getOwnerModule());
        if(!connectedNode)
            throw cRuntimeError("The connected module %s is not in a network node.", connectedGate->getOwnerModule()->getFullPath().c_str());
        if (isWirelessAccessPoint(connectedNode))
            return true;
    }

    // FIXME The AccessPoint can be connected to this router via Ethernet switches and/or hubs.

    return false;
}

bool Ipv6NeighbourDiscovery::isWirelessInterface(const InterfaceEntry *ie)
{
    // TODO should be a flag in the InterfaceEntry
    if (strncmp("wlan", ie->getInterfaceName(), 4) == 0 ){
        return true;
    }
    else if (strncmp("nic", ie->getInterfaceName(), 3) == 0 ){
        return true;
    }
    return  false;
}

bool Ipv6NeighbourDiscovery::isWirelessAccessPoint(cModule *module)
{
    // AccessPoint is defined as a node containing "relayUnit" and
    // "wlan" submodules
    return isNetworkNode(module) && module->getSubmodule("relayUnit") &&
           (module->getSubmodule("wlan", 0) || module->getSubmodule("wlan"));
}

//#endif /* WITH_xMIPv6 */

} // namespace inet

