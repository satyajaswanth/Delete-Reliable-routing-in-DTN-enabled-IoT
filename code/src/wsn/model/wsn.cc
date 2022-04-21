/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "wsn.h"
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
#include <stdio.h>     
#include <math.h>
using namespace std;
namespace ns3 {

/* ... */





// centroid Method
void FLCwsn::Centroid_Method(NodeContainer achn,int n, int refernodes[])

{

double xest=0.0;
double yest=0.0;
double sumxpos=0.0;
double sumypos=0.0;
std::cout<<"n="<<n<<std::endl;
for(int i=0;i<n;i++){


Ptr<ConstantPositionMobilityModel> FCMob = achn.Get((uint32_t )refernodes[i])->GetObject<ConstantPositionMobilityModel>();
Vector m_position = FCMob->GetPosition();
double x=m_position.x;
double y=m_position.y;
sumxpos=sumxpos+x;
sumypos=sumypos+y;

}
xest=sumxpos/(double)n;
yest=sumypos/(double)n;

std::cout<<"Xdis="<<xest<<"\n Ydis="<<yest<<"\n";

//========================LE========================

double le[n];
for(int i=0;i<n;i++){


Ptr<ConstantPositionMobilityModel> FCMob = achn.Get((uint32_t )refernodes[i])->GetObject<ConstantPositionMobilityModel>();
Vector m_position = FCMob->GetPosition();
double x=m_position.x;
double y=m_position.y;
double xest2=xest-x;
double yest2=yest-y;
double x2=(xest2*xest2);
double y2=(yest2*yest2);
le[i]=sqrt(x2+y2)/10.0;
std::cout<<"Localization Error :"<<le[i]<<std::endl;
}

double mn=min(le,  n);
std::cout<<"mnimum Error :"<<mn<<std::endl;
double mx=max(le,  n);
std::cout<<"maximum Error :"<<mx<<std::endl;
minplotres(mn ,n);
maxplotres(mn, n);
}





//Weighted_Centroid_Method
void FLCwsn::Weighted_Centroid_Method(NodeContainer achn,int n, int refernodes[],int wtz[])

{

double xest=0.0;
double yest=0.0;
double sumxpos=0.0;
double sumypos=0.0;
double sumwt=0.0;

for(int i=0;i<n;i++){
sumwt=sumwt+(double)wtz[i];
}


for(int i=0;i<n;i++){


Ptr<ConstantPositionMobilityModel> FCMob = achn.Get((uint32_t )refernodes[i])->GetObject<ConstantPositionMobilityModel>();
Vector m_position = FCMob->GetPosition();
double x=m_position.x;
double y=m_position.y;
sumxpos=sumxpos+(x*(double)wtz[i]);
sumypos=sumypos+(y*(double)wtz[i]);

}
xest=sumxpos/sumwt;
yest=sumypos/sumwt;

std::cout<<"Xdis="<<xest<<"\n Ydis="<<yest<<"\n";

//========================LE========================

double le[n];
for(int i=0;i<n;i++){


Ptr<ConstantPositionMobilityModel> FCMob = achn.Get((uint32_t )refernodes[i])->GetObject<ConstantPositionMobilityModel>();
Vector m_position = FCMob->GetPosition();
double x=m_position.x;
double y=m_position.y;
double xest2=xest-x;
double yest2=yest-y;
double x2=(xest2*xest2);
double y2=(yest2*yest2);
le[i]=sqrt(x2+y2)/10.0;
std::cout<<"Localization Error :"<<le[i]<<std::endl;
}

double mn=min(le,  n);
std::cout<<"mnimum Error :"<<mn<<std::endl;
double mx=max(le,  n);
std::cout<<"maximum Error :"<<mx<<std::endl;
minplotres(mn ,n);
maxplotres(mx, n);

}






void FLCwsn::Combined_Circle_Intersection(NodeContainer achn,int n, int refernodes[],Ptr<Node> sn)

{

double xest=0.0;
double yest=0.0;
double sumxpos=0.0;
double sumypos=0.0;
Ptr<ConstantPositionMobilityModel> sMob = sn->GetObject<ConstantPositionMobilityModel>();
Vector s_position = sMob->GetPosition();
double x1=s_position.x;
double y1=s_position.y;
for(int i=0;i<n;i++){


Ptr<ConstantPositionMobilityModel> FCMob = achn.Get((uint32_t )refernodes[i])->GetObject<ConstantPositionMobilityModel>();
Vector m_position = FCMob->GetPosition();
double x=m_position.x;
double y=m_position.y;
sumxpos=sumxpos+x+x1;
sumypos=sumypos+y+y1;

}
xest=sumxpos/(double)n;
yest=sumypos/(double)n;

std::cout<<"Xdis="<<xest<<"\n Ydis="<<yest<<"\n";

//========================LE========================

double le[n];
for(int i=0;i<n;i++){


Ptr<ConstantPositionMobilityModel> FCMob = achn.Get((uint32_t )refernodes[i])->GetObject<ConstantPositionMobilityModel>();
Vector m_position = FCMob->GetPosition();
double x=m_position.x;
double y=m_position.y;
double xest2=xest-x+x1;
double yest2=yest-y+y1;
double x2=(xest2*xest2);
double y2=(yest2*yest2);
le[i]=sqrt(x2+y2)/10.0;
std::cout<<"Localization Error :"<<le[i]<<std::endl;

}

double mn=min(le,  n);
std::cout<<"mnimum Error :"<<mn<<std::endl;
double mx=max(le,  n);
std::cout<<"maximum Error :"<<mx<<std::endl;
minplotres(mn ,n);
maxplotres(mx, n);

}





//fuzzy

void FLCwsn::Fuzzy(NodeContainer achn,int n, int refernodes[],int rss ,int wt)

{

double xest=0.0;
double yest=0.0;
double sumxpos=0.0;
double sumypos=0.0;
//double sumwt=0.0;



for(int i=0;i<n;i++){


Ptr<ConstantPositionMobilityModel> FCMob = achn.Get((uint32_t )refernodes[i])->GetObject<ConstantPositionMobilityModel>();
Vector m_position = FCMob->GetPosition();
double x=m_position.x;
double y=m_position.y;
sumxpos=sumxpos+(x);
sumypos=sumypos+(y);

}
xest=sumxpos/n;
yest=sumypos/n;
int rul=0;
if(rss ==-1 && wt==-1)
{
 rul=-1;
}else if(rss ==0 && wt==0)
{
rul=0;
}
else if(rss ==1 && wt==1)
{
rul=1;
}

else if(rss ==2 && wt==2)
{
rul=2;
}


else if(rss ==3 && wt==3)
{
rul=3;
}
std::cout<<"Xdis="<<xest<<"\n Ydis="<<yest<<"\n";

//========================LE========================

double le[n];
for(int i=0;i<n;i++){


Ptr<ConstantPositionMobilityModel> FCMob = achn.Get((uint32_t )refernodes[i])->GetObject<ConstantPositionMobilityModel>();
Vector m_position = FCMob->GetPosition();
double x=m_position.x;
double y=m_position.y;
double xest2=xest-x+rul;
double yest2=yest-y+rul;
double x2=(xest2*xest2);
double y2=(yest2*yest2);
le[i]=sqrt(x2+y2)/10.0;
std::cout<<"Localization Error :"<<le[i]<<std::endl;
}

double mn=min(le,  n);
std::cout<<"mnimum Error :"<<mn<<std::endl;
double mx=max(le,  n);
std::cout<<"maximum Error :"<<mx<<std::endl;
minplotres(mn ,n);
maxplotres(mx, n);

}





void FLCwsn::CombinedCircle_Weighted_Centroid_Method(NodeContainer achn,int n, int refernodes[],int wtz[])

{

double xest=0.0;
double yest=0.0;
double sumxpos=0.0;
double sumypos=0.0;
double sumwt=0.0;

for(int i=0;i<n;i++){
sumwt=sumwt+(double)wtz[i];
}


for(int i=0;i<n;i++){


Ptr<ConstantPositionMobilityModel> FCMob = achn.Get((uint32_t )refernodes[i])->GetObject<ConstantPositionMobilityModel>();
Vector m_position = FCMob->GetPosition();
double x=m_position.x;
double y=m_position.y;
sumxpos=sumxpos+(x*(double)wtz[i]);
sumypos=sumypos+(y*(double)wtz[i]);

}
xest=sumxpos/sumwt;
yest=sumypos/sumwt;

std::cout<<"Xdis="<<xest<<"\n Ydis="<<yest<<"\n";

//========================LE========================

double le[n];
for(int i=0;i<n;i++){


Ptr<ConstantPositionMobilityModel> FCMob = achn.Get((uint32_t )refernodes[i])->GetObject<ConstantPositionMobilityModel>();
Vector m_position = FCMob->GetPosition();
double x=m_position.x;
double y=m_position.y;
double xest2=xest-x;
double yest2=yest-y;
double x2=(xest2*xest2);
double y2=(yest2*yest2);
le[i]=sqrt(x2+y2)/10.0;
std::cout<<"Localization Error :"<<le[i]<<std::endl;
}

double mn=min(le,  n);
std::cout<<"mnimum Error :"<<mn<<std::endl;
double mx=max(le,  n);
std::cout<<"maximum Error :"<<mx<<std::endl;
minplotres(mn ,n);
maxplotres(mx, n);

}



void FLCwsn::Fuzzy(NodeContainer achn,int n, int refernodes[],int rss ,int wt,Ptr<Node> sn)

{

double xest=0.0;
double yest=0.0;
double sumxpos=0.0;
double sumypos=0.0;
//double sumwt=0.0;


Ptr<ConstantPositionMobilityModel> sMob = sn->GetObject<ConstantPositionMobilityModel>();
Vector s_position = sMob->GetPosition();
double x1=s_position.x;
double y1=s_position.y;

for(int i=0;i<n;i++){


Ptr<ConstantPositionMobilityModel> FCMob = achn.Get((uint32_t )refernodes[i])->GetObject<ConstantPositionMobilityModel>();
Vector m_position = FCMob->GetPosition();
double x=m_position.x;
double y=m_position.y;
sumxpos=sumxpos+(x+x1);
sumypos=sumypos+(y+y1);

}
xest=sumxpos/n;
yest=sumypos/n;
int rul=0;
if(rss ==-1 && wt==-1)
{
 rul=-1;
}else if(rss ==0 && wt==0)
{
rul=0;
}
else if(rss ==1 && wt==1)
{
rul=1;
}

else if(rss ==2 && wt==2)
{
rul=2;
}


else if(rss ==3 && wt==3)
{
rul=3;
}
std::cout<<"Xdis="<<xest<<"\n Ydis="<<yest<<"\n";

//========================LE========================

double le[n];
for(int i=0;i<n;i++){


Ptr<ConstantPositionMobilityModel> FCMob = achn.Get((uint32_t )refernodes[i])->GetObject<ConstantPositionMobilityModel>();
Vector m_position = FCMob->GetPosition();
double x=m_position.x;
double y=m_position.y;
double xest2=xest-x+rul;
double yest2=yest-y+rul;
double x2=(xest2*xest2);
double y2=(yest2*yest2);
le[i]=sqrt(x2+y2)/10.0;
std::cout<<"Localization Error :"<<le[i]<<std::endl;
}

double mn=min(le,  n);
std::cout<<"mnimum Error :"<<mn<<std::endl;
double mx=max(le,  n);
std::cout<<"maximum Error :"<<mx<<std::endl;
minplotres(mn ,n);
maxplotres(mx, n);

}



void FLCwsn::setNetAnimationCentraoid( AnimationInterface * pAnim,NodeContainer wsn)

{

for(uint32_t i=0;i<wsn.GetN ();i++){
pAnim->UpdateNodeDescription (wsn.Get (i), "sensor"); 
      pAnim->UpdateNodeColor (wsn.Get (i), 0, 255, 0);
}

}




void FLCwsn::minplotres(double min,int nodes)
{



std::ofstream ofs ("min.plt", std::ofstream::out);

ofs << "set terminal png"<<std::endl;
 ofs << "set output 'min.png'"<<std::endl;
  ofs << "set title ''"<<std::endl;
  ofs << "set xlabel 'Nodes' "<<std::endl;
  ofs << "set ylabel 'min' "<<std::endl;
  ofs << "plot "<<" '-'" <<"title  'Minimum Error'  with lines" <<std::endl;
ofs <<"1 " <<0<<std::endl;
 ofs <<nodes<<" " <<min<<std::endl;
ofs << "e"<<std::endl;



  ofs.close();

}



void FLCwsn::maxplotres(double min,int nodes)
{



std::ofstream ofs ("max.plt", std::ofstream::out);

ofs << "set terminal png"<<std::endl;
 ofs << "set output 'max.png'"<<std::endl;
  ofs << "set title ''"<<std::endl;
  ofs << "set xlabel 'Nodes' "<<std::endl;
  ofs << "set ylabel 'max' "<<std::endl;
  ofs << "plot "<<" '-'" <<"title  'Maximum Error'  with lines" <<std::endl;
ofs <<"1 " <<0<<std::endl;
 ofs <<nodes<<" " <<min<<std::endl;
ofs << "e"<<std::endl;



  ofs.close();

}




double FLCwsn::min(double a[], int n)
{
    if ((a == NULL) || (n <= 0))
    {
        return NAN;
    }
    else if (n == 1)
    {
        return a[0];
    }
    else
    {
        double x = a[0], y = min(&a[1], n-1);
        return x < y? x : y;
    }
}


double FLCwsn::max(double a[], int n)
{
    if ((a == NULL) || (n <= 0))
    {
        return NAN;
    }
    else if (n == 1)
    {
        return a[0];
    }
    else
    {
        double x = a[0], y = max(&a[1], n-1);
        return x > y? x : y;
    }
}






int FLCwsn::fuzzyRule(int power,int mob,int cent)
{

//Power(Remaining battery power) : 0 low ,1 Medium,2 High
//mob(Mobility):0 Low,1 moderate,2 Frequent
//cent(Cetrality):0 close ,1 Adequate,2 Far
//Chance : -1 very weak , 0 Weak,1 Lower Medium,2 Medium,3 Higher Medium,4 Strong,5 Very Stong


int chance=0; 
 if(power==0 && mob==0 && cent==0  )
{
 chance=-1;
}

else if(power==0 && mob==0 && cent==1  )
{
 chance=0;
}

else if(power==0 && mob==0 && cent==2  )
{
 chance=1;
}


else if(power==0 && mob==1 && cent==0  )
{
 chance=0;
}

else if(power==0 && mob==1 && cent==1  )
{
 chance=1;
}

else if(power==0 && mob==1 && cent==2  )
{
 chance=2;
}

else if(power==0 && mob==2 && cent==0  )
{
 chance=1;
}

else if(power==0 && mob==2 && cent==1  )
{
 chance=2;
}


else if(power==0 && mob==2 && cent==2  )
{
 chance=3;
}


else if(power==1 && mob==0 && cent==0  )
{
 chance=0;
}

else if(power==1 && mob==0 && cent==1  )
{
 chance=1;
}

else if(power==1 && mob==0 && cent==2  )
{
 chance=2;
}

else if(power==1 && mob==1 && cent==0  )
{
 chance=1;
}

else if(power==1 && mob==1 && cent==1  )
{
 chance=2;
}

else if(power==1 && mob==2 && cent==0  )
{
 chance=2;
}

else if(power==1 && mob==2 && cent==1  )
{
 chance=3;
}

else if(power==1 && mob==2 && cent==2  )
{
 chance=4;
}

else if(power==2 && mob==0 && cent==0  )
{
 chance=1;
}

else if(power==2 && mob==0 && cent==1  )
{
 chance=2;
}


else if(power==2 && mob==0 && cent==2  )
{
 chance=3;
}

else if(power==2 && mob==1 && cent==0  )
{
 chance=2;
}


else if(power==2 && mob==1 && cent==1  )
{
 chance=3;
}


else if(power==2 && mob==1 && cent==2  )
{
 chance=4;
}


else if(power==2 && mob==2 && cent==0  )
{
 chance=3;
}

else if(power==2 && mob==2 && cent==1  )
{
 chance=4;
}

else if(power==2 && mob==2 && cent==2  )
{
 chance=5;
}

return chance;

}

int * FLCwsn::proposed_ALG(int num_rounds,NodeContainer wsn)
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
std::cout<<v1<<":"<<v2<<":"<<v3<<std::endl;
int chance=fuzzyRule(th[0],th[1],th[2]);
std::cout<<"Node ID"<<i<<"-->Chance :"<<chance<<std::endl;
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








void FLCwsn::E2ED( double delay[],int size)
{

std::ofstream ofs ("E2ED.plt", std::ofstream::out);



  ofs << "set terminal png"<<std::endl;
 ofs << "set output 'E2ED.png'"<<std::endl;
  ofs << "set title 'End to end delay'"<<std::endl;
  ofs << "set xlabel 'nodes' "<<std::endl;
  ofs << "set ylabel 'Time(ms)' "<<std::endl;
  ofs << "plot "<<" '-'" <<"title "<<"'Proposed '  with linespoints " <<std::endl;

for(int i=0;i<size;i++)
{
ofs <<i <<" "<< (delay[i]*1)<<std::endl;
}
ofs << "e"<<std::endl;




  ofs.close();
}
 void FLCwsn::successful_NL(double NL[],int numnods)
{

std::ofstream ofs ("EE.plt", std::ofstream::out);



  ofs << "set terminal png"<<std::endl;
 ofs << "set output 'EE.png'"<<std::endl;
  ofs << "set title 'Energy_Efficiency'"<<std::endl;
  ofs << "set xlabel 'nodes' "<<std::endl;
  ofs << "set ylabel 'Energy_Efficiency "<<std::endl;
  ofs << "plot "<<" '-'" <<"title "<<"'Proposed '  with linespoints" <<std::endl;



for(int j=0;j<numnods;j++)
{
ofs <<j <<" "<< (NL[j]*2)/10.0<<std::endl;
}
ofs << "e"<<std::endl;




  ofs.close();
}






}

