
#include "Clock.h"

Clock::Clock()
{
  Initialise();
}
 
Clock::~Clock()
{

}

void Clock::Initialise()
{
  PerfTime=QueryPerformanceFrequency((LARGE_INTEGER*) &Frq);
  if (PerfTime)
  {
    QueryPerformanceCounter((LARGE_INTEGER*) &Time0);
    OneTick=1.0f/Frq;
  }
  else
  {
    Time0=timeGetTime();
    OneTick=0.001f;
  }
}
 
float Clock::GetTime()
{
  if (PerfTime)
    QueryPerformanceCounter((LARGE_INTEGER*) &Time1);
  else
    Time1=timeGetTime();
 
  dt=(Time1-Time0)*OneTick;
  Time0=Time1;
  return dt;
}
