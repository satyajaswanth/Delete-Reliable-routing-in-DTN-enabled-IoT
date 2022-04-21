/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef WSN_H
#define WSN_H
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

class FLCwsn
{

public:
void Centroid_Method(NodeContainer achn,int n, int refernodes[]);
void Weighted_Centroid_Method(NodeContainer achn,int n, int refernodes[], int wtz[]);
void Combined_Circle_Intersection(NodeContainer achn,int n, int refernodes[],Ptr<Node> sn);
void Fuzzy(NodeContainer achn,int n, int refernodes[],int rss ,int wt);
void CombinedCircle_Weighted_Centroid_Method(NodeContainer achn,int n, int refernodes[],int wtz[]);
void setNetAnimationCentraoid( AnimationInterface * pAnim,NodeContainer wsn);
void Fuzzy(NodeContainer achn,int n, int refernodes[],int rss ,int wt,Ptr<Node> sn);
double min(double a[], int n);
double max(double a[], int n);
int fuzzyRule(int power,int mob,int cent);
int * proposed_ALG(int num_rounds,NodeContainer wsn);
void successful_NL(double NL[],int numnods);
void E2ED( double delay[],int size);
void minplotres(double min,int nodes);
void maxplotres(double min,int nodes);
};


}

#endif /* WSN_H */

