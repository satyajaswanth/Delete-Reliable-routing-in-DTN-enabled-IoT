/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "fuzzy.h"
#include <iostream>
#include <ctime>
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/csma-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/internet-module.h"
#include "ns3/netanim-module.h"

using namespace std;
namespace ns3 {

/* ... */


int FLC::fuzzyRule(double Packetcount,double cwr,double Duration)
{

//attype ===>0-Normal ,1-Malicious,2-Suspicious



int attype=0; 
 if(Packetcount==0 && cwr==2 && Duration==2  )
{
 attype=0;
}

else if(Packetcount==2 && cwr==0 && Duration==0 )
{
 attype=1;
}

else if(Packetcount==1 && cwr==1 && Duration==1 )
{
attype=2;
}


return attype;;

}

int * FLC::proposed_ALG(int num_rounds,NodeContainer wsn)
{


//int th[3]={2,2,1};
int j=0;
static int CH[10];
 srand( time( NULL ) );
for(uint32_t i=0;i<wsn.GetN ();i++){
  
 int v1  = rand() % 2 + 1;

 int v2  = rand() % 2 + 1;

 int v3  = v1-v2;
int th[3]={v1,v2,v3};
//std::cout<<v1<<":"<<v2<<":"<<v3<<std::endl;
int chance=fuzzyRule(th[0],th[1],th[2]);
//std::cout<<"Node ID"<<i<<"-->Chance :"<<chance<<std::endl;
if(chance>=2)
{
if(j<10)
{
CH[j]=(int)i;
//std::cout<<"CH :"<<CH[j]<<std::endl;
j++;
}
}


}
return CH;
}



void FLC::Position(int dev ,NodeContainer nod)
{
double arealim=1000/dev;
int z=0;
double x=0;

for (int i = 0; i < dev; ++i)
{
if(i==0)
{
 x=(arealim/2);
}
else
{
 x=(arealim/2)+(i*arealim);
}
for (int j = 0; j < dev; ++j)
{
double y=0;
if(j==0)
{
 y=(arealim/2);
}
else
{
 y=(arealim/2)+(j*arealim);
}
AnimationInterface::SetConstantPosition (nod.Get (z), x, y);
z=z+1;
}
}



}



}

