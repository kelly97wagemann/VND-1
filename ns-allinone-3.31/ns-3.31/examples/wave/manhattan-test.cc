#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/internet-apps-module.h"
#include "ns3/wave-mac-helper.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/mobility-helper.h"
#include "ns3/wifi-80211p-helper.h"
#include "ns3/netanim-module.h"
#include "ns3/nstime.h"
#include "ns3/ns2-mobility-helper.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("Ping6obu");

int 
main (int argc, char *argv[]) {
    CommandLine cmd;
    cmd.Parse (argc, argv); 

    std::string phyMode ("OfdmRate6MbpsBW10MHz");

    LogComponentEnable ("Ipv6Interface", LOG_LEVEL_INFO);
    LogComponentEnable ("Ping6Application", LOG_LEVEL_ALL);
    
    NS_LOG_INFO ("Create nodes.");
    NodeContainer nodes;
    NetDeviceContainer devices;
    nodes.Create (10);

    NS_LOG_INFO ("Create mobility.");
    //MobilityHelper mobility;
    Ns2MobilityHelper mobility = Ns2MobilityHelper("./examples/wave/manhattan.ns_movements");
    //Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
    //positionAlloc->Add (Vector (10.0, 10.0, 0.0));
    //positionAlloc->Add (Vector (20.0, 20.0, 0.0));
    //mobility.SetPositionAllocator (positionAlloc);
    //mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
    //mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
    //    "Bounds", RectangleValue (Rectangle (-50, 50, -50, 50)));
    mobility.Install ();

    NS_LOG_INFO ("Create channel.");
    YansWifiPhyHelper wifiPhy =  YansWifiPhyHelper::Default ();
    YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default ();
    Ptr<YansWifiChannel> channel = wifiChannel.Create ();
    wifiPhy.SetChannel (channel);
    wifiPhy.SetPcapDataLinkType (WifiPhyHelper::DLT_IEEE802_11);
    NqosWaveMacHelper wifi80211pMac = NqosWaveMacHelper::Default ();
    Wifi80211pHelper wifi80211p = Wifi80211pHelper::Default ();

    //wifi80211p.EnableLogComponents ();      // Turn on all Wifi 802.11p logging

    wifi80211p.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
                                        "DataMode",StringValue (phyMode),
                                        "ControlMode",StringValue (phyMode));
    devices = wifi80211p.Install (wifiPhy, wifi80211pMac, nodes);

    wifiPhy.EnablePcap ("manhattan", devices);

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
    uint32_t maxPacketCount = 5;
    Time interPacketInterval = Seconds (1.);
    Ping6Helper ping6;

    ping6.SetLocal (i.GetAddress (0, 1));
    ping6.SetRemote (i.GetAddress (1, 1));

    ping6.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
    ping6.SetAttribute ("Interval", TimeValue (interPacketInterval));
    ping6.SetAttribute ("PacketSize", UintegerValue (packetSize));
    ApplicationContainer apps = ping6.Install (nodes.Get (0));
    apps.Start (Seconds (5.0));
    apps.Stop (Seconds (500.0));
 
    AsciiTraceHelper ascii;
    wifiPhy.EnableAsciiAll (ascii.CreateFileStream("manhattan.tr"));
    
    AnimationInterface anim("manhattan.xml");
    anim.SetMobilityPollInterval(Time("1s"));
    //anim.SetConstantPosition(nodes.Get(0), 10.0, 10.0);
    //anim.SetConstantPosition(nodes.Get(1), 20.0, 20.0);

    NS_LOG_INFO ("Run Simulation.");
    Simulator::Stop (Seconds (500.0));
    Simulator::Run ();
    Simulator::Destroy ();
    NS_LOG_INFO ("Done.");
}
