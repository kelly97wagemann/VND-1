#include <fstream>
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-apps-module.h"
#include "ns3/wave-net-device.h"
#include "ns3/wave-mac-helper.h"
#include "ns3/wave-helper.h"
#include "ns3/node.h"
#include "ns3/packet.h"
#include "ns3/simulator.h"
#include "ns3/node-container.h"
#include "ns3/net-device-container.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/mobility-helper.h"
#include "ns3/seq-ts-header.h"
#include "ns3/wifi-80211p-helper.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("Ping6obu");

int 
main (int argc, char *argv[]) {

    LogComponentEnable ("Ipv6Interface", LOG_LEVEL_INFO);
    LogComponentEnable ("Ping6Application", LOG_LEVEL_ALL);
    
    NS_LOG_INFO ("Create nodes.");
    NodeContainer nodes;
    NetDeviceContainer devices;
    nodes.Create (2);

    NS_LOG_INFO ("Create channel.");
    YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default ();
    YansWavePhyHelper wavePhy =  YansWavePhyHelper::Default ();
    wavePhy.SetChannel (wifiChannel.Create ());
    wavePhy.SetPcapDataLinkType (WifiPhyHelper::DLT_IEEE802_11);
    QosWaveMacHelper waveMac = QosWaveMacHelper::Default ();
    WaveHelper waveHelper = WaveHelper::Default ();
    devices = waveHelper.Install (wavePhy, waveMac, nodes);
    wavePhy.EnablePcap ("obu2obu", devices);

    NS_LOG_INFO ("Create mobility.");
    MobilityHelper mobility;
    Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
    positionAlloc->Add (Vector (0.0, 0.0, 0.0));
    positionAlloc->Add (Vector (1.0, 0.0, 0.0));
    mobility.SetPositionAllocator (positionAlloc);
    mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
    mobility.Install (nodes);

    NS_LOG_INFO ("Install IPv6 Stack.");
    InternetStackHelper internetv6;
    internetv6.SetIpv4StackInstall (false);
    internetv6.Install (nodes);

    NS_LOG_INFO ("Assign IPv6 Addresses.");
    Ipv6AddressHelper ipv6;
    Ipv6InterfaceContainer i = ipv6.Assign (devices);
    
    NS_LOG_INFO ("Create Applications.");

    /* Create a Ping6 application to send ICMPv6 echo request from node zero to
    * all-nodes (ff02::1).
    */
    uint32_t packetSize = 1024;
    uint32_t maxPacketCount = 5;
    Time interPacketInterval = Seconds (1.);
    Ping6Helper ping6;    
    ping6.SetLocal (i.GetAddress (0, 1)); 
    ping6.SetRemote (i.GetAddress (0, 1));
    ping6.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
    ping6.SetAttribute ("Interval", TimeValue (interPacketInterval));
    ping6.SetAttribute ("PacketSize", UintegerValue (packetSize));
    ApplicationContainer apps = ping6.Install (nodes.Get (0));
    apps.Start (Seconds (2.0));
    apps.Stop (Seconds (10.0));
    NS_LOG_INFO ("Run Simulation.");
    Simulator::Stop (Seconds (10.0));
    Simulator::Run ();
    Simulator::Destroy ();
    NS_LOG_INFO ("Done.");
}