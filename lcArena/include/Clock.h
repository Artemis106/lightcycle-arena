
#ifndef CLOCK_INCLUDED
#define CLOCK_INCLUDED
 
#define WIN32_LEAN_AND_MEAN
#include <windows.h> 
#include<MMSystem.h>

#pragma comment (lib, "Winmm.lib")

class  Clock
{
  
public:
  Clock();
  ~Clock();
  void Initialise();
  float GetTime();
  
private:
  bool PerfTime;
  LONGLONG Frq,Time0,Time1;
  float OneTick,dt;
};

#endif