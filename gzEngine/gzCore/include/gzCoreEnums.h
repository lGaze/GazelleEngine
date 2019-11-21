/**************************************************************************/
/* @filename gzGraphicsEnums.h
/* @author Victor Flores
/* @date 2019/11/21
/* @brief This file contains all the enums for core
/**************************************************************************/
#pragma once

namespace gzEngineSDK {
namespace COMPONENT_TYPE {
  enum E
  {
    kMeshComponent = 0,
  };
}

namespace CAMERA_MOVEMENT {
  enum E
  {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
  };
}

namespace KEYBOARDBUTTONS {
  enum E
  {
    kKeyA,
    kKeyB,
    kKeyC,
    kKeyD,
    kKeyE,
    kKeyF,
    kKeyG,
    kKeyH,
    kKeyI,
    kKeyJ,
    kKeyK,
    kKeyL,
    kKeyM,
    kKeyN,
    kKeyO,
    kKeyP,
    kKeyQ,
    kKeyR,
    kKeyS,
    kKeyT,
    kKeyU,
    kKeyV,
    kKeyW,
    kKeyX,
    kKeyY,
    kKeyZ,
    kKeySpace,
    kArrowUp,
    kArrowDown,
    kArrowLeft,
    kArrowRight
  };
}

namespace MOUSEBUTTONS {
  enum E {
    kMouseButtonLeft,
    kMouseButtonMiddle,
    kMouseButtonRight,
    kMouseButtonWheelDown,
    kMouseButtonWheelUp,
  };
}
}
