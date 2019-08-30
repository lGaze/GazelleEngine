/**************************************************************************/
/* @filename gzTimer.h
/* @author Victor Flores 
/* @date 2019/08/29
/* @brief Timer class used for querying high precision timers.
/**************************************************************************/

#pragma once
#include "gzPrerequisitesUtilities.h"
#include <chrono>

namespace gzEngineSDK {

  using std::chrono::high_resolution_clock;
  using std::chrono::time_point;

class GZ_UTILITY_EXPORT Timer
{
 public:
 
  /**
   * @brief default constructor
   */
   Timer();

  /**
   * @brief default destructor
   */
  ~Timer() = default;

  /************************************************************************/
  /* Timer functions                                                      */
  /************************************************************************/

  /**
   * @brief Resets the timer to zero.
   */
  void
  reset();

  /**
   * @brief Returns time in milliseconds since timer was initialized or last reset.
   */
  uint64
  getMilliseconds() const;

  /**
   * @brief Returns time in microseconds since timer was initialized or last reset.
   */
  uint64
  getMicroseconds() const;

  /**
   * @brief Returns the time at which the timer was initialized, in milliseconds.
   * @return  Time in milliseconds.
   */
  uint64
  getStartMs() const;

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 private:

  high_resolution_clock m_highResClock;
  time_point<high_resolution_clock> m_startTime;
   
 };
}
