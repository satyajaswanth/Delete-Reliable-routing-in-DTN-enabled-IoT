/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "CommonMeth.h"
#include <iostream>
#include <ctime>
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include <fstream>
#include <iostream>
#include "ns3/netanim-module.h"
#include <cmath>
#include "ns3/gnuplot.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/internet-module.h"
#include "ns3/netanim-module.h"

using namespace std;
namespace ns3 {

/* ... */





int * Distancecal::distancefromselectedsensor(NodeContainer Anch,Ptr<Node> sn)
{

//get Sensor node position
int j=0;
static int referencenode[60];
Ptr<ConstantPositionMobilityModel> sMob = sn->GetObject<ConstantPositionMobilityModel>();
Vector s_position = sMob->GetPosition();
double x1=s_position.x;
double y1=s_position.y;

double d=0.0;
//Get Anchor node posistion
for(uint32_t i=0;i<Anch.GetN ();i++){
Ptr<ConstantPositionMobilityModel> AMob = Anch.Get(i)->GetObject<ConstantPositionMobilityModel>();
Vector m_position = AMob->GetPosition();
double x=m_position.x;
double y=m_position.y;
double xx=x1-x;
double yy=y1-y;
double x2=(xx*xx);
double y2=(yy*yy);
double sx=sqrt(x2);
double sy=sqrt(y2);
double dis=(sx+sy);
d=dis/10;

if(d<=8.94)
{


referencenode[j]=(int)i;
//std::cout<<"Anchor Node ["<<referencenode[j]<<"] as a reference nodes: d="<<d<<" \n";
j++;
}
 uint32_t sz=( uint32_t)j;
Setresz(sz);
}

return referencenode;

}



void Distancecal::Setresz(const uint32_t res)
{
resz=res;
}

uint32_t Distancecal::Getresz(void) const
{
return resz;
}




}

