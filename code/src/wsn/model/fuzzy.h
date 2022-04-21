/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef FUZZY_H
#define FUZZY_H
#include <iostream>
#include <ctime>
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/csma-module.h"
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

class FLC
{

public:
int fuzzyRule(double e2e,double bat,double etx);
int * proposed_ALG(int num_rounds,NodeContainer wsn);
void Position(int dev ,NodeContainer nod);
};


}

#endif /* FUZZY_H */

