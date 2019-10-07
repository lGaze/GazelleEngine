#include <gzBaseApp.h>
#include "gzGraphicsTestApp.h"

using namespace gzEngineSDK;

int32 main()
{
  BaseApp::startUp<GrapichsTestApp>(1920, 1080, "GazelleEngine", -7, 0);
  BaseApp::instance().runMainLoop();
  BaseApp::shutDown();
}