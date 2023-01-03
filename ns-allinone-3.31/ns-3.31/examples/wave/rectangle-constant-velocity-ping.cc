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

double sim_time = 20.0;

void CheckBound(Ptr< ConstantVelocityMobilityModel > mob ){
    Vector m_position = mob->GetPosition();
    Vector m_velocity = mob->GetVelocity();
    if (m_position.y >= 50 || m_position.y<0.001)
        {
           m_velocity.y *= -1;
           mob->SetVelocity(m_velocity);
        }
}

int main (int argc, char *argv[]) {
	std::string phyMode ("OfdmRate6MbpsBW10MHz");
NodeContainer nodes;
nodes.Create (2);
NetDeviceContainer devices;
MobilityHelper mobility;
mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
                             "MinX", DoubleValue (0.0),
                             "MinY", DoubleValue (0.0),
                             "DeltaX", DoubleValue (50),
                             "DeltaY", DoubleValue (50),
                             "GridWidth", UintegerValue (2),
                             "LayoutType", StringValue ("RowFirst"));

mobility.SetMobilityModel ("ns3::ConstantVelocityMobilityModel");

mobility.Install (nodes);
for (uint n=0 ; n < nodes.GetN() ; n++)
 {
    Ptr<ConstantVelocityMobilityModel> mob = nodes.Get(n)->GetObject<ConstantVelocityMobilityModel>();
    mob->SetVelocity(Vector(0, 10, 0));
 }
for (uint n=0 ; n < nodes.GetN() ; n++)
 {
    Ptr<ConstantVelocityMobilityModel> cvMob = nodes.Get(n)->GetObject<ConstantVelocityMobilityModel>();
    for(double i=1; i<sim_time-1; i++){
    	Simulator::Schedule(Seconds(i), &CheckBound, cvMob);
    }

 }


/////////////

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

    wifiPhy.EnablePcap ("rectangle-constant-velocity-ping", devices);

    InternetStackHelper internetv6;
    internetv6.SetIpv4StackInstall (false);
    internetv6.Install (nodes);

    Ipv6AddressHelper ipv6;
    ipv6.SetBase (Ipv6Address ("2001:1::"), Ipv6Prefix (64));
    Ipv6InterfaceContainer i = ipv6.Assign (devices);

    uint32_t packetSize = 10;
    uint32_t maxPacketCount = 30;
    Time interPacketInterval = Seconds (1.);
    Ping6Helper ping6;

    ping6.SetLocal (i.GetAddress (0, 1));
    ping6.SetRemote (i.GetAddress (1, 1));

    ping6.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
    ping6.SetAttribute ("Interval", TimeValue (interPacketInterval));
    ping6.SetAttribute ("PacketSize", UintegerValue (packetSize));
    ApplicationContainer apps = ping6.Install (nodes.Get (0));
    apps.Start(Seconds(3.0));

    apps.Stop (Seconds (20.0));


///////////


AnimationInterface anim("rectangle-constant-velocity-ping.xml");
Simulator::Stop (Seconds (sim_time));
Simulator::Run ();
Simulator::Destroy ();
}
