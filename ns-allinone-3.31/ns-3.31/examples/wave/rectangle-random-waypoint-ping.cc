#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/internet-apps-module.h"
#include "ns3/wave-mac-helper.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/mobility-helper.h"
#include "ns3/wifi-80211p-helper.h"
#include "ns3/netanim-module.h"



#include <fstream>
#include <iostream>
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/aodv-module.h"
#include "ns3/olsr-module.h"
#include "ns3/dsdv-module.h"
#include "ns3/dsr-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("Ping6RandomWayPointObu");

int nodeSpeed = 20; //in m/s
int nodePause = 0; //in s

int main (int argc, char *argv[]) {
    std::string phyMode ("OfdmRate6MbpsBW10MHz");

    LogComponentEnable ("Ipv6Interface", LOG_LEVEL_INFO);
    LogComponentEnable ("Ping6Application", LOG_LEVEL_ALL);

    NS_LOG_INFO ("Create nodes.");
    NodeContainer nodes;
    NetDeviceContainer devices;
    nodes.Create (4);



    //
    NS_LOG_INFO ("Create mobility.");

    MobilityHelper mobilityAdhoc;
    int64_t streamIndex = 0; // used to get consistent mobility across scenarios

    ObjectFactory pos;
    pos.SetTypeId ("ns3::RandomRectanglePositionAllocator");
    pos.Set ("X", StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=30.0]"));
    pos.Set ("Y", StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=30.0]"));

    Ptr<PositionAllocator> taPositionAlloc = pos.Create ()->GetObject<PositionAllocator> ();
    streamIndex += taPositionAlloc->AssignStreams (streamIndex);

    std::stringstream ssSpeed;
    ssSpeed << "ns3::UniformRandomVariable[Min=0.0|Max=" << nodeSpeed << "]";
    std::stringstream ssPause;
    ssPause << "ns3::ConstantRandomVariable[Constant=" << nodePause << "]";
    mobilityAdhoc.SetMobilityModel ("ns3::RandomWaypointMobilityModel",
                                    "Speed", StringValue (ssSpeed.str ()),
                                    "Pause", StringValue (ssPause.str ()),
                                    "PositionAllocator", PointerValue (taPositionAlloc));
    mobilityAdhoc.SetPositionAllocator (taPositionAlloc);
    mobilityAdhoc.Install (nodes);
    streamIndex += mobilityAdhoc.AssignStreams (nodes, streamIndex);
    NS_UNUSED (streamIndex); // From this point, streamIndex is unused

    //

    NS_LOG_INFO ("Create channel.");
    YansWifiPhyHelper wifiPhy =  YansWifiPhyHelper::Default ();
    YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default ();
    Ptr<YansWifiChannel> channel = wifiChannel.Create ();
    wifiPhy.SetChannel (channel);
    wifiPhy.SetPcapDataLinkType (WifiPhyHelper::DLT_IEEE802_11);
    NqosWaveMacHelper wifi80211pMac = NqosWaveMacHelper::Default ();
    Wifi80211pHelper wifi80211p = Wifi80211pHelper::Default ();

    wifi80211p.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
                                        "DataMode",StringValue (phyMode),
                                        "ControlMode",StringValue (phyMode));
    devices = wifi80211p.Install (wifiPhy, wifi80211pMac, nodes);

    wifiPhy.EnablePcap ("rectangle-random-waypoint-ping", devices);

    NS_LOG_INFO ("Install IPv6 Stack.");
    InternetStackHelper internetv6;
    internetv6.SetIpv4StackInstall (false);
    internetv6.Install (nodes);

    NS_LOG_INFO ("Assign IPv6 Addresses.");
    Ipv6AddressHelper ipv6;
    ipv6.SetBase (Ipv6Address ("2001:1::"), Ipv6Prefix (64));
    Ipv6InterfaceContainer i = ipv6.Assign (devices);

    NS_LOG_INFO ("Create Applications.");
    uint32_t packetSize = 10;
    uint32_t maxPacketCount = 30;
    Time interPacketInterval = Seconds (1.);
    Ping6Helper ping6;

    ping6.SetLocal (i.GetAddress (0, 1));
    ping6.SetRemote (i.GetAddress (1, 1));

   /* ping6.SetLocal (i.GetAddress (0,1));
    ping6.SetRemote (Ipv6Address::GetAllNodesMulticast ());*/

    ping6.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
    ping6.SetAttribute ("Interval", TimeValue (interPacketInterval));
    ping6.SetAttribute ("PacketSize", UintegerValue (packetSize));
    ApplicationContainer apps = ping6.Install (nodes.Get (0));
    apps.Start(Seconds(3.0));

    apps.Stop (Seconds (16.0));
    AnimationInterface anim("rectangle-random-waypoint-ping.xml");

    /*anim.SetConstantPosition(nodes.Get(0), 10.0, 10.0);
    anim.SetConstantPosition(nodes.Get(1), 20.0, 20.0);*/

    NS_LOG_INFO ("Run Simulation.");
    Simulator::Stop (Seconds (16.0));
    Simulator::Run ();
    Simulator::Destroy ();
    NS_LOG_INFO ("Done.");
}

