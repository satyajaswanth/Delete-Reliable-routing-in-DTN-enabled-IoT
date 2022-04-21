/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */ 
#ifndef COMMONMETH_H
#define COMMONMETH_H
#include <iostream>
#include <ctime>
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"

#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/mobility-module.h"
#include "ns3/internet-module.h"
#include "ns3/netanim-module.h"
#include <stdio.h>  
#include <stdlib.h>
#include <time.h>
using namespace std;
namespace ns3 {

/* ... */

class Distancecal
{

private:
 uint32_t resz;
public:



void Setresz(const uint32_t resz);
uint32_t Getresz(void) const;
int * distancefromselectedsensor(NodeContainer wsn,Ptr<Node> sn);

};


}

#endif /* COMMONMETH_H */

