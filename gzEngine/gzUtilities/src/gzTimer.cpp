/**************************************************************************/
/* @filename gzTimer.cpp
/* @author Victor Flores 
/* @date 2019/08/29
/**************************************************************************/

#include "gzTimer.h"

namespace gzEngineSDK {
  using namespace std::chrono;

  Timer::Timer() {
    reset();
  }

  void
  Timer::reset() {
    m_startTime = m_highResClock.now();
  }

  uint64
  Timer::getMilliseconds() const {
    auto newTime = m_highResClock.now();
    duration<double> dur = newTime - m_startTime;
    return duration_cast<milliseconds>(dur).count();
  }

  uint64
  Timer::getMicroseconds() const {
    auto newTime = m_highResClock.now();
    duration<double> dur = newTime - m_startTime;
    return duration_cast<microseconds>(dur).count();
  }

  uint64
  Timer::getStartMs() const {
    nanoseconds startTimeNs = m_startTime.time_since_epoch();
    return duration_cast<milliseconds>(startTimeNs).count();
  }
}