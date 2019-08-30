/**************************************************************************/
/* @filename gzTime.cpp
/* @author Victor Flores 
/* @date 2019/08/29
/**************************************************************************/

#include "gzTime.h"

namespace gzEngineSDK {

  const double MICROSEC_TO_SEC = 1.0 / 1000000.0;

  Time::Time()
  {
    m_timer = new Timer();
    m_appStartTime = m_timer->getStartMs();
    m_lastFrameTime = m_timer->getMicroseconds();
  }

  Time::~Time()
  {
    delete(m_timer);
  }

  void 
  Time::update()
  {
    uint64 currentTime = m_timer->getMicroseconds();
    m_delta = 
      static_cast<float>((currentTime - m_lastFrameTime) * MICROSEC_TO_SEC);
    m_timeSinceStart = (currentTime / 1000) / 1000.0f;
    m_lastFrameTime = currentTime;
  }

  GZ_UTILITY_EXPORT Time & g_Time()
  {
    return Time::instance();
  }

}