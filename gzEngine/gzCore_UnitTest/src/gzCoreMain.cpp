
#include <gzPrerequisitesCore.h>
#include <gzPrerequisitesUtilities.h>
#include <gzBaseApp.h>
#include "gzGraphicsTestApp.h"

using namespace gzEngineSDK;

int32 main()
{
  BaseApp::startUp<GrapichsTestApp>(1900, 1000, "GazelleEngine", 0, 0);
  BaseApp::instance().runMainLoop();
  BaseApp::shutDown();
}