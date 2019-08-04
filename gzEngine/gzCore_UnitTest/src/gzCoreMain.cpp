
#include <gzPrerequisitesCore.h>
#include <gzPrerequisitesUtilities.h>
#include <gzBaseApp.h>
#include <gzSceneManager.h>

using namespace gzEngineSDK;

int32 main()
{
  BaseApp::startUp( 640, 480, "GazelleEngine", 400, 200 );
  BaseApp::instance().runMainLoop();
  BaseApp::shutDown();

}