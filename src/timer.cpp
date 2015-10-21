//////////////////////////////////////////////////////////////////////////////
// Timer.cpp
// =========
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

#include "timer.h"
#include <stdlib.h>




/*! \brief Get current date/time, format is YYYY-MM-DD.HH:mm:ss */
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}



/*! \brief Constructor*/
Timer::Timer(){
#ifdef WIN32
    QueryPerformanceFrequency(&frequency);
    startCount.QuadPart = 0;
    endCount.QuadPart = 0;
#else
    startCount.tv_sec = startCount.tv_usec = 0;
    endCount.tv_sec = endCount.tv_usec = 0;
#endif

    stopped = 0;
    startTimeInMicroSec = 0;
    endTimeInMicroSec = 0;
}

/*! \brief Destructor*/
Timer::~Timer(){
}



/*! \brief Start timer*/
void Timer::start(){
    stopped = 0; // reset stop flag
#ifdef WIN32
    QueryPerformanceCounter(&startCount);
#else
    gettimeofday(&startCount, NULL);
#endif
}



/*! \brief Stop the timer */
void Timer::stop(){
    stopped = 1; // set timer stopped flag

#ifdef WIN32
    QueryPerformanceCounter(&endCount);
#else
    gettimeofday(&endCount, NULL);
#endif
}




/*! \brief Get elapsed time in micro-second */
double Timer::getElapsedTimeInMicroSec(){
#ifdef WIN32
    if(!stopped)
        QueryPerformanceCounter(&endCount);

    startTimeInMicroSec = startCount.QuadPart * (1000000.0 / frequency.QuadPart);
    endTimeInMicroSec = endCount.QuadPart * (1000000.0 / frequency.QuadPart);
#else
    if(!stopped)
        gettimeofday(&endCount, NULL);

    startTimeInMicroSec = (startCount.tv_sec * 1000000.0) + startCount.tv_usec;
    endTimeInMicroSec = (endCount.tv_sec * 1000000.0) + endCount.tv_usec;
#endif

    return endTimeInMicroSec - startTimeInMicroSec;
}



/*! \brief Get elapsed time in milli-second */
double Timer::getElapsedTimeInMilliSec(){
    return this->getElapsedTimeInMicroSec() /1000;
}



/*! \brief Get elapsed time in second (same as getElapsedTime) */
double Timer::getElapsedTimeInSec(){
    return this->getElapsedTimeInMicroSec() * 0.000001;
}



/*! \brief Get elapsed time in second */
double Timer::getElapsedTime(){
    return this->getElapsedTimeInSec();
}
