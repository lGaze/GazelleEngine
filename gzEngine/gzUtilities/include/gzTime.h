/**************************************************************************/
/* @filename gzTime.h
/* @author Victor Flores 
/* @date 2019/08/29
/* @brief This class manages all time related functionality.
/**************************************************************************/
#pragma once

#include "gzPrerequisitesUtilities.h"
#include "gzTimer.h"
#include "gzModule.h"

namespace gzEngineSDK {
class GZ_UTILITY_EXPORT Time : public Module<Time>
{
 public:
 
  /**
   * @brief default constructor
   */
  Time();

  /**
   * @brief default destructor
   */
  ~Time();

  /************************************************************************/
  /* Time functions                                                       */
  /************************************************************************/

  /**
   * @brief Gets the time elapsed since application start. Only gets updated once per frame.
   * @return  The time since application start, in seconds.
   */
  float
  getTime() const {
    return m_timeSinceStart;
  }

  float 
  getDelta() const {
    return m_delta;
  }

  /**
   * @brief Called every frame. Should only be called by Application.
   */
  void
  update();


  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 private:

  float m_timeSinceStart;
  float m_delta;
  uint64 m_timeSinceStartMs;
  uint64 m_appStartTime;
  uint64 m_lastFrameTime;
  Timer * m_timer;
 };

 /**
  * @brief Easier way to access the Time module.
  */
 GZ_UTILITY_EXPORT Time& g_Time();
}

