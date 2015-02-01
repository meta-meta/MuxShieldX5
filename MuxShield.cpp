/*
 MuxShield.cpp - Library for using Mayhew Labs' Mux Shield.
 Created by Mark Mayhew, December 29, 2012.
 Released into the public domain.
 */

#include "Arduino.h"
#include "MuxShield.h"

int _shiftReg[15][16];

MuxShield::MuxShield(int S0, int S1, int S2, int S3, int OUTMD, 
        int IOS1, int IOS2, int IOS3, 
        int IOS4, int IOS5, int IOS6, 
        int IOS7, int IOS8, int IOS9, 
        int IOS10, int IOS11, int IOS12, 
        int IOS13, int IOS14, int IOS15, 
        int IO1, int IO2, int IO3,
        int IO4, int IO5, int IO6,
        int IO7, int IO8, int IO9,
        int IO10, int IO11, int IO12,
        int IO13, int IO14, int IO15
        )
{

    _S = {
        S0,
        S1,
        S2,
        S3
    };

    _OUTMD = OUTMD;

    _IOS = {
        IOS1,
        IOS2,
        IOS3,
        IOS4,
        IOS5,
        IOS6,
        IOS7,
        IOS8,
        IOS9,
        IOS10,
        IOS11,
        IOS12,
        IOS13,
        IOS14,
        IOS15
    };

    _IO = {
        IO1,
        IO2,
        IO3,
        IO4,
        IO5,
        IO6,
        IO7,
        IO8,
        IO9,
        IO10,
        IO11,
        IO12,
        IO13,
        IO14,
        IO15
    };

    for(int i = 0; i < 15; i++) {
        _shiftReg[i] = {0};
    }
    
    for(int i = 0; i < 4; i++) {
        pinMode(_S[i], OUTPUT);
    }

    pinMode(_OUTMD,OUTPUT);
    digitalWrite(_OUTMD,LOW);

    for(int i = 0; i < 15; i++) {
        pinMode(IOS[i], OUTPUT);
    }
}

MuxShield::MuxShield()
{
    _S = {
        2,
        4,
        6,
        7
    };

    _OUTMD = 8; 

    _IOS = {
        35,
        36,
        37,

        38,
        39,
        40,

        41,
        42,    
        43,

        // 44 - 46 are PWM, so save them for something else

        48,
        49,
        50,

        51,
        52,
        53
    };

    _IO = {
        A0,
        A1,
        A2,
        
        A3,
        A4,
        A5,

        A6,
        A7,
        A8,

        A9,
        A10,
        A11,

        A12,
        A13,
        A14
    };

    for(int i = 0; i < 15; i++) {
        _shiftReg[i] = {0};
    }

    for(int i = 0; i < 4; i++) {
        pinMode(_S[i], OUTPUT);
    }

    pinMode(_OUTMD,OUTPUT);
    digitalWrite(_OUTMD,LOW);
    
    for(int i = 0; i < 15; i++) {
        pinMode(IOS[i], OUTPUT);
    }
}

void MuxShield::setMode(int mux, int mode) 
{
    int i = mux - 1;

    switch (mode) {
        case DIGITAL_IN:
            pinMode(_IO[i],INPUT);
            digitalWrite(_IOS[i],LOW);
            break;
        case DIGITAL_IN_PULLUP:
            pinMode(_IO[i],INPUT_PULLUP);
            digitalWrite(_IOS[i],LOW);
            break;
        case DIGITAL_OUT:
            pinMode(_IO[i],OUTPUT);
            digitalWrite(_IOS[i],HIGH);
            break;
        case ANALOG_IN:
            digitalWrite(_IOS[i],LOW);
            break;
        default:
            break;
    }
}

void MuxShield::digitalWriteMS(int mux, int chan, int val)
{
    int i = mux - 1;
    int sIdx = i % 3;
    
    digitalWrite(_S[3],LOW);                              //S3 here is LCLK
    digitalWrite(_OUTMD,HIGH);                          //set to output mode
    

    _shiftReg[i][chan] = val;              //store value until updated again

    for (int j = 15; j >= 0; j--) {
        digitalWrite(_S[sIdx], LOW);                  //S0 here is i/o1 _sclk
        digitalWrite(_IO[i], _shiftReg[i][j]);       //put value
        digitalWrite(_S[sIdx], HIGH);                 //lactch in value
    }

    
    digitalWrite(_S[3],HIGH);                     //latch in ALL values
    digitalWrite(_OUTMD,LOW);                   //Exit output mode
}

int MuxShield::digitalReadMS(int mux, int chan)
{
    digitalWrite(_OUTMD,LOW);   //Set outmode off (i.e. set as input mode)
    
    digitalWrite(_S[0], (chan&1));    
    digitalWrite(_S[1], (chan&3)>>1); 
    digitalWrite(_S[2], (chan&7)>>2); 
    digitalWrite(_S[3], (chan&15)>>3); 

    return digitalRead(_IO[mux - 1]); 
}

int MuxShield::analogReadMS(int mux, int chan)
{
    digitalWrite(_OUTMD,LOW);

    digitalWrite(_S[0], (chan&1));    
    digitalWrite(_S[1], (chan&3)>>1); 
    digitalWrite(_S[2], (chan&7)>>2); 
    digitalWrite(_S[3], (chan&15)>>3); 
    
    return analogRead(_IO[mux - 1]); 
}