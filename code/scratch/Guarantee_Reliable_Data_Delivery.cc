#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/csma-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/internet-module.h"
#include "ns3/netanim-module.h"
#include "ns3/basic-energy-source.h"
#include "ns3/simple-device-energy-model.h"
#include "ns3/config-store-module.h"
#include "ns3/ipv4-static-routing-helper.h"
#include "ns3/ipv4-list-routing-helper.h"
#include "ns3/rtt-estimator.h"
#include "ns3/aodv-module.h"
#include <ns3/wsn-module.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace ns3;
NS_LOG_COMPONENT_DEFINE ("Guarantee_Reliable_Data_Delivery");
double simTime = 50;
AnimationInterface *anim;
double pk=0;
uint32_t packetSize = 1024; 
uint32_t numPackets = 200;
double interval = 0.1; 
double TotalTime = 10.0;
double Overheadvalue;
double distance1;
double buffersize=50;
std::string rate="10Mbps";
std::string rate1="20Mbps";
int nodeSpeed = 5;
int rttval;
int a=1;
int b=1;
int c=1;
double kbs=0;
int rnd=0;
int rnd1=0;
double Trange=400;
double SNR=12.5;
Time interPacketInterval = Seconds (interval);
NodeContainer IOTDevs;
NodeContainer SinkNode;
int bytesTotal;
double ds=100000.0;
double energy=100.0;
int cHead;
double Initialenergy=1000;
double Initialtime=0;
double PICO=0.000001;
double NANO =0.001;
int dis=10;
int status=1;
int pz=50;
int nbees=5;
double alpha=1;
double beta=2;
double q=5;
double ro=2;
double taumax=2;
int initCity=5;
uint32_t packetsReceived;
void GetDistance_From (NodeContainer node1, NodeContainer node2){
Ptr<MobilityModel> model1 = node1.Get(0)->GetObject<MobilityModel>();
Ptr<MobilityModel> model2 = node2.Get(10)->GetObject<MobilityModel>();
distance1 = model1->GetDistanceFrom (model2);}
void delaycalc(int bits,double dist,int mystatus){
if(mystatus==status){
Initialtime=(Simulator::Now ()).GetSeconds ()-Initialtime;}}
void CheckPDR (double recivpk){}
void Overheadcalc (int Overheadval){
kbs = (Overheadval/10000)-kbs;}
void ReceivePacket (Ptr<Socket> socket){
Ptr<Packet> pckt;
while (pckt = socket->Recv ()){
rate="512Mbps";
Ptr<MobilityModel> model1 = SinkNode.Get(0)->GetObject<MobilityModel>();
Ptr<MobilityModel> model2 = IOTDevs.Get(10)->GetObject<MobilityModel>();
distance1 = model1->GetDistanceFrom (model2);
bytesTotal = pckt->GetSize();
Overheadvalue += pckt->GetSize();
delaycalc(bytesTotal,distance1,1);
Overheadcalc (Overheadvalue);
pk=pk+1;
CheckPDR (pk);}}
void compare_Minimum(double dis){
if(ds>dis){
ds=dis;}}
void getNearbynode(NodeContainer nod,double x1,double y1){
int nn;
for(uint32_t i=0;i<nod.GetN ();i++){
Ptr<ConstantPositionMobilityModel> FCMob = nod.Get(i)->GetObject<ConstantPositionMobilityModel>();
Vector m_position = FCMob->GetPosition();
double x=m_position.x;
double y=m_position.y;
double xx=x1-x;
double yy=y1-y;
double x2=(xx*xx);
double y2=(yy*yy);
double sx=sqrt(x2);
double sy=sqrt(y2);
double dis=(sx+sy);
compare_Minimum(dis);
if(ds==dis){
nn=i;}}
std::cout<<"minimum Distance:" <<nn<<std::endl;}
void energyReceive(int bits,int mystatus){
double en;
if(mystatus==status){
en=(double)bits*50.0*NANO;
std::cout<<"REC-energy: "<<en<<"\n";
energy=energy-en;}}
void energyTransmit(int bits,double dist,int mystatus){
double en;
if(mystatus==status){
en=bits*10*PICO*dist+(double)bits*50.0*NANO;
if(cHead==1)
std::cout<<"Transmit-energy HEAD: "<<en<<"\n";
energy=energy-en;}}
void energyDataAggr(int signals,int mystatus){
double en;
if(mystatus==status){
en=5*NANO*signals;
std::cout<<"AGG-energy: "<<en<<"\n";
energy=energy-en;}}
void finish(){
std::cout<<"energy: "<<energy<<"\n";}
static void GenerateTraffic (Ptr<Socket> socket, uint32_t pktSize,uint32_t pktCount, Time pktInterval ){
if (pktCount > 0){
socket->Send (Create<Packet> (pktSize));
Simulator::Schedule (pktInterval, &GenerateTraffic,socket, pktSize,pktCount-1, pktInterval);
}else{
socket->Close ();}}
void Getcolor1(NodeContainer d){
for (uint32_t i = 0; i < IOTDevs.GetN (); ++i){
anim->UpdateNodeDescription (IOTDevs.Get (15), "Source" ); 
anim->UpdateNodeColor (IOTDevs.Get (15), 255, 0, 255); }}
void Getcolor(NodeContainer d){
for (uint32_t i = 0; i < IOTDevs.GetN (); ++i){
if(i%10==0){
anim->UpdateNodeDescription (IOTDevs.Get (i), "CH_IOT_Device" ); 
anim->UpdateNodeColor (IOTDevs.Get (i), 255, 0, 0); 
}
else{
anim->UpdateNodeDescription (IOTDevs.Get (i), "IOT_Device" ); 
anim->UpdateNodeColor (IOTDevs.Get (i), 255, 0, 0); }}}
void PKTtrans(NodeContainer c , NodeContainer d){
double min = 0.0;
double max = 15.0;
Ptr<UniformRandomVariable> x = CreateObject<UniformRandomVariable> ();
x->SetAttribute ("Min", DoubleValue (min));
x->SetAttribute ("Max", DoubleValue (max));
int value = x->GetValue ();  
rnd=value;
TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
Ptr<Socket> recvSink = Socket::CreateSocket (d.Get (rnd), tid);
InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), 80);
recvSink->Bind (local);
recvSink->SetRecvCallback (MakeCallback (&ReceivePacket));
if(rnd%2==0){
KFFA KFFAobj;
KFFAobj.findlimits(10);
std::cout<<" Emergency Packet  "<<"\n";}
else{
INDC INDCobj;
INDCobj.printPHEROMONES ();
std::cout<<" NON Emergency Packet  "<<"\n";}
rnd=rnd+2;
Ptr<Socket> source = Socket::CreateSocket (d.Get (rnd), tid);
InetSocketAddress remote = InetSocketAddress (Ipv4Address ("255.255.255.255"), 80);
source->SetAllowBroadcast (true);
source->Connect (remote);
Simulator::ScheduleWithContext (source->GetNode ()->GetId (),Seconds (0.1), &GenerateTraffic,source, packetSize, numPackets,interPacketInterval);}
void PKTtrans1(NodeContainer c , NodeContainer d){
TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
Ptr<Socket> recvSink = Socket::CreateSocket (d.Get (rnd), tid);
InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), 80);
recvSink->Bind (local);
recvSink->SetRecvCallback (MakeCallback (&ReceivePacket));
if(rnd%5==0){
KFFA KFFAobj;
KFFAobj.findlimits(10);
std::cout<<" Emergency Packet  "<<"\n";}
else{
INDC INDCobj;
INDCobj.printPHEROMONES ();
std::cout<<" NON Emergency Packet  "<<"\n";}
rnd=rnd+2;
Ptr<Socket> source = Socket::CreateSocket (d.Get (rnd), tid);
InetSocketAddress remote = InetSocketAddress (Ipv4Address ("255.255.255.255"), 80);
source->SetAllowBroadcast (true);
source->Connect (remote);
Simulator::ScheduleWithContext (source->GetNode ()->GetId (),Seconds (0.1), &GenerateTraffic,source, packetSize, numPackets, interPacketInterval);}
void PKTtrans2(NodeContainer c , NodeContainer d){
TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
Ptr<Socket> recvSink = Socket::CreateSocket (d.Get (rnd), tid);
InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), 80);
recvSink->Bind (local);
recvSink->SetRecvCallback (MakeCallback (&ReceivePacket));
if(rnd%2==0){
KFFA KFFAobj;
KFFAobj.findlimits(10);
std::cout<<" Emergency Packet  "<<"\n";}
else{
INDC INDCobj;
INDCobj.printPHEROMONES ();
std::cout<<" NON Emergency Packet  "<<"\n";}
rnd=rnd+2;
Ptr<Socket> source = Socket::CreateSocket (d.Get (rnd), tid);
InetSocketAddress remote = InetSocketAddress (Ipv4Address ("255.255.255.255"), 80);
source->SetAllowBroadcast (true);
source->Connect (remote);
Simulator::ScheduleWithContext (source->GetNode ()->GetId (),Seconds (0.1), &GenerateTraffic,source, packetSize, numPackets, interPacketInterval);}
void PKTtrans3(NodeContainer c , NodeContainer d){
TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
Ptr<Socket> recvSink = Socket::CreateSocket (c.Get (0), tid);
InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), 80);
recvSink->Bind (local);
recvSink->SetRecvCallback (MakeCallback (&ReceivePacket));
if(rnd%2==1){
KFFA KFFAobj;
KFFAobj.findlimits(10);
std::cout<<" Emergency Packet  "<<"\n";}
else{
INDC INDCobj;
INDCobj.printPHEROMONES ();
std::cout<<" NON Emergency Packet  "<<"\n";}
rnd=rnd+2;
Ptr<Socket> source = Socket::CreateSocket (d.Get (rnd), tid);
InetSocketAddress remote = InetSocketAddress (Ipv4Address ("255.255.255.255"), 80);
source->SetAllowBroadcast (true);
source->Connect (remote);
Simulator::ScheduleWithContext (source->GetNode ()->GetId (),Seconds (0.1), &GenerateTraffic, source, packetSize, numPackets, interPacketInterval);}
void PKTtrans4(NodeContainer c , NodeContainer d){
double min = 0.0;
double max = 15.0;
Ptr<UniformRandomVariable> x = CreateObject<UniformRandomVariable> ();
x->SetAttribute ("Min", DoubleValue (min));
x->SetAttribute ("Max", DoubleValue (max));
int value = x->GetValue ();
rnd1=value;
TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
Ptr<Socket> recvSink = Socket::CreateSocket (c.Get (0), tid);
InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), 80);
recvSink->Bind (local);
recvSink->SetRecvCallback (MakeCallback (&ReceivePacket));
rnd1=rnd1+2;
Ptr<Socket> source = Socket::CreateSocket (d.Get (rnd1), tid);
InetSocketAddress remote = InetSocketAddress (Ipv4Address ("255.255.255.255"), 80);
source->SetAllowBroadcast (true);
source->Connect (remote);
Simulator::ScheduleWithContext (source->GetNode ()->GetId (),Seconds (0.1), &GenerateTraffic,source, packetSize, numPackets, interPacketInterval);}
void PKTtrans5(NodeContainer c , NodeContainer d){
TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
Ptr<Socket> recvSink = Socket::CreateSocket (d.Get (rnd1), tid);
InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), 80);
recvSink->Bind (local);
recvSink->SetRecvCallback (MakeCallback (&ReceivePacket));
rnd1=rnd1+2;
Ptr<Socket> source = Socket::CreateSocket (d.Get (rnd1), tid);
InetSocketAddress remote = InetSocketAddress (Ipv4Address ("255.255.255.255"), 80);
source->SetAllowBroadcast (true);
source->Connect (remote);
Simulator::ScheduleWithContext (source->GetNode ()->GetId (),Seconds (0.1), &GenerateTraffic,source, packetSize, numPackets, interPacketInterval);}
void PKTtrans6(NodeContainer c , NodeContainer d){
TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
Ptr<Socket> recvSink = Socket::CreateSocket (d.Get (rnd1), tid);
InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), 80);
recvSink->Bind (local);
recvSink->SetRecvCallback (MakeCallback (&ReceivePacket));
rnd1=rnd1+2;
Ptr<Socket> source = Socket::CreateSocket (d.Get (rnd1), tid);
InetSocketAddress remote = InetSocketAddress (Ipv4Address ("255.255.255.255"), 80);
source->SetAllowBroadcast (true);
source->Connect (remote);
Simulator::ScheduleWithContext (source->GetNode ()->GetId (),Seconds (0.1), &GenerateTraffic, source, packetSize, numPackets, interPacketInterval);}
void PKTtrans7(NodeContainer c , NodeContainer d){
TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
Ptr<Socket> recvSink = Socket::CreateSocket (d.Get (rnd1), tid);
InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), 80);
recvSink->Bind (local);
recvSink->SetRecvCallback (MakeCallback (&ReceivePacket));
rnd1=rnd1+2;
Ptr<Socket> source = Socket::CreateSocket (d.Get (rnd1), tid);
InetSocketAddress remote = InetSocketAddress (Ipv4Address ("255.255.255.255"), 80);
source->SetAllowBroadcast (true);
source->Connect (remote);
Simulator::ScheduleWithContext (source->GetNode ()->GetId (),Seconds (0.1), &GenerateTraffic, source, packetSize, numPackets, interPacketInterval);}
uint32_t keylength(std::string key){
return key.length() / 2;}
int main (int argc, char *argv[]){
int numberOfNodes = 100; 
int NoofAggregator = 9; 
int Noofdivisions = 9; 
printf("\nEnter the number of IOT Devices :");
scanf("%d",&numberOfNodes);
printf("\nEnter the number of Division [N*N],   N= :");
scanf("%d",&Noofdivisions);
NoofAggregator=Noofdivisions*Noofdivisions;
int NoofSink=1;
CommandLine cmd;
cmd.Parse (argc,argv);
NodeContainer allNodes;
IOTDevs.Create (numberOfNodes);
allNodes.Add (IOTDevs);
SinkNode.Create (NoofSink);
allNodes.Add (SinkNode);
NodeContainer AggregatorNodes ;
AggregatorNodes.Create (NoofAggregator);
allNodes.Add (AggregatorNodes);
YansWifiChannelHelper channel = YansWifiChannelHelper::Default ();
channel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
channel.AddPropagationLoss ("ns3::FriisPropagationLossModel");
YansWifiPhyHelper phy = YansWifiPhyHelper::Default ();
phy.SetChannel (channel.Create ());
double txp=80;
FLC obj;
std::string phyMode ("DsssRate11Mbps");
phy.Set ("TxPowerStart",DoubleValue (txp));
phy.Set ("TxPowerEnd", DoubleValue (txp));
Config::SetDefault ("ns3::OnOffApplication::PacketSize",StringValue ("64000"));
Config::SetDefault ("ns3::OnOffApplication::DataRate",StringValue (rate));
Config::SetDefault ("ns3::WifiRemoteStationManager::NonUnicastMode",StringValue (phyMode));
Config::SetDefault ("ns3::OnOffApplication::DataRate",StringValue (rate1));
WifiHelper wifi;
wifi.SetStandard (WIFI_PHY_STANDARD_80211b);
wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager","DataMode",StringValue (phyMode),"ControlMode",StringValue (phyMode));
WifiMacHelper mac;
Ssid ssid = Ssid ("ns-3-ssid");
mac.SetType ("ns3::AdhocWifiMac");
NetDeviceContainer staDevices;
staDevices = wifi.Install (phy, mac, IOTDevs);
mac.SetType ("ns3::ApWifiMac","Ssid", SsidValue (ssid));
NetDeviceContainer apDevices;
apDevices = wifi.Install (phy, mac, SinkNode);
MobilityHelper mobility;
int nodePause = 0; 
int64_t streamIndex = 0;
ObjectFactory pos;
pos.SetTypeId ("ns3::RandomRectanglePositionAllocator");
pos.Set ("X", StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=1000]")); 
pos.Set ("Y", StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=1000]"));
Ptr<PositionAllocator> taPositionAlloc = pos.Create ()->GetObject<PositionAllocator> ();
streamIndex += taPositionAlloc->AssignStreams (streamIndex);
mobility.SetPositionAllocator(taPositionAlloc);
std::stringstream ssSpeed;
ssSpeed << "ns3::UniformRandomVariable[Min=0.0|Max=" << nodeSpeed << "]";
std::stringstream ssPause;
ssPause << "ns3::ConstantRandomVariable[Constant=" << nodePause << "]";
mobility.SetMobilityModel ("ns3::RandomWaypointMobilityModel","Speed", StringValue (ssSpeed.str ()),"Pause", StringValue (ssPause.str ()),
"PositionAllocator", PointerValue (taPositionAlloc));
for (uint32_t i = 0; i < IOTDevs.GetN (); ++i){
mobility.Install (IOTDevs.Get (i));}
MobilityHelper mobility1;
mobility1.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
for (uint32_t i = 0; i < AggregatorNodes.GetN (); ++i){
mobility1.Install (AggregatorNodes.Get (i));}
MobilityHelper mobility2;
mobility2.SetPositionAllocator(taPositionAlloc);
std::stringstream ssSpeed2;
ssSpeed2 << "ns3::UniformRandomVariable[Min=0.0|Max=" << 100 << "]";
mobility2.SetMobilityModel ("ns3::RandomWaypointMobilityModel","Speed", StringValue (ssSpeed2.str ()),"Pause", StringValue (ssPause.str ()),
"PositionAllocator", PointerValue (taPositionAlloc));
mobility2.Install (SinkNode);
obj.Position(Noofdivisions,AggregatorNodes);
AnimationInterface::SetConstantPosition (SinkNode.Get (0), 250, 200);
Time interPacketInterval = Seconds (interval);
AodvHelper aodv;
Ipv4StaticRoutingHelper staticRouting;
Ipv4ListRoutingHelper list;
list.Add (staticRouting, 0);
list.Add (aodv, 1);
InternetStackHelper internet;
internet.SetRoutingHelper (list); 
internet.Install (IOTDevs);
internet.Install (SinkNode);
Ipv4AddressHelper ipv4;
NS_LOG_INFO ("Assign IP Addresses.");
ipv4.SetBase ("10.1.1.0", "255.255.255.0");
Ipv4InterfaceContainer i = ipv4.Assign (staDevices);
Ipv4InterfaceContainer ap = ipv4.Assign (apDevices);
Simulator::Schedule(Seconds(0.5), &Getcolor, IOTDevs);
Simulator::Schedule(Seconds(0.8), &Getcolor1, IOTDevs);
Simulator::Schedule(Seconds(1.1), &PKTtrans, SinkNode,IOTDevs);
Simulator::Schedule(Seconds(2.1), &PKTtrans1, SinkNode,IOTDevs);
Simulator::Schedule(Seconds(3.1), &PKTtrans2, SinkNode,IOTDevs);
Simulator::Schedule(Seconds(4.1), &PKTtrans3, SinkNode,IOTDevs);
Simulator::Schedule(Seconds(5.1), &PKTtrans4, SinkNode,IOTDevs);
Simulator::Schedule(Seconds(6.1), &PKTtrans5, SinkNode,IOTDevs);
Simulator::Schedule(Seconds(7.1), &PKTtrans6, SinkNode,IOTDevs);
Simulator::Schedule(Seconds(8.1), &PKTtrans7, SinkNode,IOTDevs);
Simulator::Stop (Seconds (TotalTime));
anim= new AnimationInterface ("Guarantee_Reliable_Data_Delivery.xml");
traceDTN w;
w.stTracematrices(buffersize, numberOfNodes);
uint32_t resourceId =anim->AddResource("/home/research/ns-allinone-3.26/netanim-3.107/img1/sink.png");
uint32_t resourceId1 =anim->AddResource("/home/research/ns-allinone-3.26/netanim-3.107/img1/IOTDEVICE.png");
uint32_t resourceId2 =anim->AddResource("/home/research/ns-allinone-3.26/netanim-3.107/img1/Aggregator.png");
for (uint32_t i = 0; i < IOTDevs.GetN (); ++i){
Ptr<Node> wid1= IOTDevs.Get (i);
uint32_t nodeId1 = wid1->GetId ();
anim->UpdateNodeSize (nodeId1, 75.0,75.0); 
anim->UpdateNodeImage (nodeId1, resourceId1);
if(i%5==0){
anim->UpdateNodeDescription (IOTDevs.Get (i), "CH" ); 
anim->UpdateNodeColor (IOTDevs.Get (i), 0, 0, 255); 
}else{
anim->UpdateNodeDescription (IOTDevs.Get (i), "IOT_Device" ); 
anim->UpdateNodeColor (IOTDevs.Get (i), 255, 0, 0); }}
for (uint32_t i = 0; i < AggregatorNodes.GetN (); ++i){
Ptr<Node> wid1= AggregatorNodes.Get (i);
uint32_t nodeId1 = wid1->GetId ();
anim->UpdateNodeSize (nodeId1, 175.0,175.0); 
anim->UpdateNodeImage (nodeId1, resourceId2);
anim->UpdateNodeDescription (AggregatorNodes.Get (i), "Aggregator" ); 
anim->UpdateNodeColor (AggregatorNodes.Get (i), 0, 0, 255); }
anim->UpdateNodeDescription (SinkNode.Get (0), "Sink" ); 
anim->UpdateNodeColor (SinkNode.Get (0), 200, 200, 200); 
Ptr<Node> wid2= SinkNode.Get (0);
uint32_t nodeId2 = wid2->GetId ();
anim->UpdateNodeSize (nodeId2, 225.0,225.0); 
anim->UpdateNodeImage (nodeId2, resourceId);
Ptr<RttMeanDeviation> myrtt = CreateObject<RttMeanDeviation> ();  
Simulator::Run ();
Simulator::Destroy ();
system("gnuplot 'Delay_BufferSize.plt'");
system("gnuplot 'Delay_Nodes.plt'");
system("gnuplot 'Overhead_Nodes.plt'");
system("gnuplot 'Packet_Delivery_RatioBufferSize.plt'");
system("gnuplot 'Packet_Delivery_Ratio_Nodes.plt'");
return 0;}
