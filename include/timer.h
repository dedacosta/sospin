//////////////////////////////////////////////////////////////////////////////
// Timer.h
// =======
// High Resolution Timer.
// This timer is able to measure the elapsed time with 1 micro-second accuracy
// in both Windows, Linux and Unix system 
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2003-01-13
// UPDATED: 2006-01-13
//
// Copyright (c) 2003 Song Ho Ahn
//////////////////////////////////////////////////////////////////////////////




/*!
  \file 
  \brief Defintions for all general (initialisation etc.) routines of class Timer.
*/

#ifndef TIMER_H_DEF
#define TIMER_H_DEF


#include <iostream>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <string>

#ifdef WIN32   // Windows system specific
#include <windows.h>
#else          // Unix based system specific
#include <sys/time.h>
#endif



const std::string currentDateTime();


/*! 
\class Timer
\brief Measure elapsed time
*/
class Timer{
public:
/*! \brief Constructor*/
    Timer();
/*! \brief Destructor*/
    ~Timer();          

/*! \brief Start timer*/
    void   start();
/*! \brief Stop the timer */
    void   stop(); 
/*! \brief Get elapsed time in second */
    double getElapsedTime();                   
/*! \brief Get elapsed time in second (same as getElapsedTime) */
    double getElapsedTimeInSec();     
/*! \brief Get elapsed time in milli-second */
    double getElapsedTimeInMilliSec();   
/*! \brief Get elapsed time in micro-second */
    double getElapsedTimeInMicroSec();        


protected:


private:
/*! \brief Store starting time in micro-second */
    double startTimeInMicroSec; 
/*! \brief Store ending time in micro-second */
    double endTimeInMicroSec;
/*! \brief Stop flag */
    int    stopped; 
#ifdef WIN32
    LARGE_INTEGER frequency;                    // ticks per second
    LARGE_INTEGER startCount;                   //
    LARGE_INTEGER endCount;                     //
#else
    timeval startCount;                         //
    timeval endCount;                           //
#endif
};

#endif // TIMER_H_DEF
