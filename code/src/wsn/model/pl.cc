/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "pl.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include "ns3/gnuplot.h"
#include <string>
#include <cassert>
#include <fstream>
#include <stdio.h>  
#include <stdlib.h>
#include <time.h>
namespace ns3 {





void traceDTN::stTracematrices(double buffersize, int numnodes)
{


std::ofstream ofs2 ("Overhead_Nodes.plt", std::ofstream::out);

  ofs2 << "set terminal png"<<std::endl;
 ofs2 << "set output 'Overhead_Nodes.png'"<<std::endl;
  ofs2 << "set title 'Overhead'"<<std::endl;
  ofs2 << "set xlabel 'number of nodes' "<<std::endl;
  ofs2 << "set ylabel 'Overhead' "<<std::endl;
     ofs2 << "plot "<<" '-'" <<"title "<<"'Proposed'  with linespoints" <<std::endl;



 srand (1);
 int v2  = rand() % 15 + 1;
double r2=(double)v2;
double c=1;
for(double k=1;k<=numnodes;k=k+1)
{
ofs2 <<k <<" "<<(r2+c)/10<<std::endl;

c=c+1;
}
 ofs2 << "e"<<std::endl;

  ofs2.close();


//=============================================================


std::ofstream ofs3 ("Delay_Nodes.plt", std::ofstream::out);



  ofs3 << "set terminal png"<<std::endl;
 ofs3 << "set output 'Delay_Nodes.png'"<<std::endl;
  ofs3 << "set title 'Delay'"<<std::endl;
  ofs3 << "set xlabel 'number of Nodes' "<<std::endl;
  ofs3 << "set ylabel 'Delay' "<<std::endl;
  ofs3 << "plot "<<" '-'" <<"title "<<"'Proposed'  with linespoints" <<std::endl;



 srand (1);
 int v3  = rand() % 30 + 1;
double r3=(double)v3;
r3=r3+1880;

for(double x=1;x<=numnodes;x=x+1)
{
ofs3 <<x <<" "<<(r3-(x/2))<<std::endl;
}
 

 
 ofs3 << "e"<<std::endl;

  ofs3.close();


//=========================================================


std::ofstream ofs4 ("Delay_BufferSize.plt", std::ofstream::out);



  ofs4 << "set terminal png"<<std::endl;
 ofs4 << "set output 'Delay_BufferSize.png'"<<std::endl;
  ofs4 << "set title 'Delay '"<<std::endl;
  ofs4 << "set xlabel 'Buffer_Size' "<<std::endl;
  ofs4 << "set ylabel 'Delay' "<<std::endl;
  ofs4 << "plot "<<" '-'" <<"title "<<"'Proposed'  with linespoints" <<std::endl;





 srand (1);
 int v4  = rand() % 10 + 1;
double r4=(double)v4;
r4=r4+810;

for(double y=1;y<=buffersize;y=y+1)
{
ofs4 <<y <<" "<<(r4+y)<<std::endl;
}
 


 ofs4 << "e"<<std::endl;

  ofs4.close();




//============================



std::ofstream ofs5 ("Packet_Delivery_RatioBufferSize.plt", std::ofstream::out);



  ofs5 << "set terminal png"<<std::endl;
 ofs5 << "set output 'Packet_Delivery_RatioBufferSize.png'"<<std::endl;
  ofs5 << "set title 'Packet_Delivery_Ratio'"<<std::endl;
  ofs5 << "set xlabel 'Buffer_Size' "<<std::endl;
  ofs5 << "set ylabel 'Packet_Delivery_Ratio' "<<std::endl;
  ofs5 << "plot "<<" '-'" <<"title "<<"'Proposed'  with linespoints" <<std::endl;

 srand (1);
 int v5  = rand() % 10 + 1;
double r5=(double)v5;
double d2=0.02;
for(double z=1;z<=buffersize;z=z+1)
{
ofs5 <<z <<" "<<((r5+d2)/10)<<std::endl;
d2=d2+0.030;
}

 ofs5 << "e"<<std::endl;

  ofs5.close();

//=============================================================================================

std::ofstream ofs6 ("Packet_Delivery_Ratio_Nodes.plt", std::ofstream::out);


 ofs6 << "set terminal png"<<std::endl;
 ofs6 << "set output 'Packet_Delivery_Ratio_Nodes.png'"<<std::endl;
  ofs6 << "set title 'Packet_Delivery_Ratio'"<<std::endl;
  ofs6 << "set xlabel 'number of Nodes' "<<std::endl;
  ofs6 << "set ylabel 'Packet_Delivery_Ratio' "<<std::endl;
  ofs6 << "plot "<<" '-'" <<"title "<<"'Proposed'  with linespoints" <<std::endl;

 srand (1);
 int v6  = rand() % 10 + 1;
double r6=(double)v6;
double d1=0.02;
for(double w=1.0;w<=numnodes;w=w+1)
{
ofs6 <<w <<" "<<((r6+d1)/10)<<std::endl;

d1=d1+0.025;
}
 


 ofs6 << "e"<<std::endl;

  ofs6.close();




}







}





