
#include <gzPrerequisitesCore.h>
#include <gzPrerequisitesUtilities.h>
#include <gzBaseApp.h>

using namespace gzEngineSDK;

int32 main()
{
  BaseApp::startUp();
  BaseApp::instance().runMainLoop();
  BaseApp::shutDown();
}