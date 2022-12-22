#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/traffic-control-module.h"
using namespace ns3;
NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");
int main (int argc, char *argv[])
{
CommandLine cmd;
cmd.Parse (argc, argv);
NodeContainer nodes; 
nodes.Create (4);
InternetStackHelper stack; 
stack.Install (nodes);
PointToPointHelper pointToPoint; 
pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
pointToPoint.SetChannelAttribute ("Delay", StringValue ("4ms"));
pointToPoint.SetQueue("ns3::DropTailQueue","MaxPackets",UintegerValue(10));
Ipv4AddressHelper address; 
address.SetBase ("10.1.1.0", "255.255.255.0");
NetDeviceContainer devices; 
devices = pointToPoint.Install (nodes.Get(0),nodes.Get(1));
Ipv4InterfaceContainer interfaces = address.Assign (devices);
devices = pointToPoint.Install (nodes.Get(1),nodes.Get(2)); 
address.SetBase ("10.1.2.0", "255.255.255.0"); 
interfaces = address.Assign (devices);
devices = pointToPoint.Install (nodes.Get(2),nodes.Get(3));
address.SetBase ("10.1.3.0", "255.255.255.0"); 
interfaces = address.Assign (devices);
Ptr<RateErrorModel> em = CreateObject<RateErrorModel>();
em –›SetAttribute("ErrorRate",DoubleValue(0.001));
devices.Get (0) –›SetAttribute("ReceiveErrorModel",PointerValue(em));
devices.Get(1)–›SetAttribute("ReceiveErrorModel",PointerValue(em));
Ipv4GlobalRoutingHelper::PopulateRoutingTables();
UdpEchoServerHelper echoServer (9);
ApplicationContainer serverApps = echoServer.Install (nodes.Get(3));
serverApps.Start (Seconds (1.0));
serverApps.Stop (Seconds (10.0));
UdpEchoClientHelper echoClient (interfaces.GetAddress (1), 9);
echoClient.SetAttribute ("MaxPackets", UintegerValue (500));
echoClient.SetAttribute ("Interval", TimeValue (Seconds (0.0)));
echoClient.SetAttribute ("PacketSize", UintegerValue (1024));
ApplicationContainer clientApps = echoClient.Install (nodes.Get (0));
clientApps.Start (Seconds (2.0));
clientApps.Stop (Seconds (10.0));
AsciiTraceHelper ascii;
pointToPoint.EnableAsciiAll(ascii.CreateFileStream("ccn1.tr"));
Simulator::Run ();
Simulator::Destroy ();
return 0;
}
