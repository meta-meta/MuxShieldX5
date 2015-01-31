/*
 MuxShield.h - Library for using Mayhew Labs' Mux Shield.
 Created by Mark Mayhew, December 20, 2012.
 Released into the public domain.
 */
#ifndef MuxShield_h
#define MuxShield_h

#include "Arduino.h"

#define DIGITAL_IN   0
#define DIGITAL_OUT  1
#define ANALOG_IN    2
#define DIGITAL_IN_PULLUP    3


class MuxShield
{
public:
    MuxShield();
    MuxShield(int S0, int S1, int S2, int S3, int OUTMD, int IOS1, int IOS2, int IOS3, int IOS4, int IOS5, int IOS6, int IOS7, int IOS8, int IOS9, int IOS10, int IOS11, int IOS12, int IOS13, int IOS14, int IOS15, int IO1, int IO2, int IO3);
    void setMode(int mux, int mode);
    void digitalWriteMS(int mux, int chan, int val);
    int digitalReadMS(int mux, int chan);
    int analogReadMS(int mux, int chan);
    
private:
    int _OUTMD;
    int _S[4];
    int IOS[15];
    int IO[3];
    int _LE1,_LE2,_LE3,_M1,_M2,_M3;    
};

#endif
