
#include "FWEngine.h"
#include "DebugMacros.h"

#include "windows.h"
#include <crtdbg.h>
#include <iostream>

#define _CRTDBG_MAP_ALLOC //to get more details

//#ifdef _DEBUG
//#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
//// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
//// allocations to be of _CLIENT_BLOCK type
//#else
//#define DBG_NEW new
//#endif

// Memory leak detection
_CrtMemState sOld;
_CrtMemState sNew;
_CrtMemState sDiff;

using namespace ENGINE;

int main(int argc, char** argv)
{
    /* Auto dump memory leak info
       ( This fixes an issue where if manually dumping memory leak info at the end of the application, it would count
       static objects as memory leaks because they will be freed after the main() execution )
    */
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // Take a snapshot of heap memory
    _CrtMemCheckpoint(&sOld);

    // Create new application
    Application app;

    // Create application settings
    Settings settings;
    
    // Create window and camera
    Error err;
    settings.window.name = "Feldewar";
    settings.window.width = 1600;
    settings.window.height = 800;
    settings.window.renderAPI = RenderAPI::OpenGL;
    if (!app.Init(settings.window, err)) {
        err.Print();
    }

    // Load models and textures, build shaders
    settings.data.modelPath = "./Models";
    settings.data.texturePath = "./Textures";
    ///if (!app.LoadData(settings.data, err)) {
    ///    err.Print();
    ///}

    // Load terrain
    settings.terrain.heightMap = "heightmap.png";
    settings.terrain.size = 800.0f;
    ///if (!app.LoadTerrain(settings.terrain)) {
    ///    err.Print();
    ///}

    // Create a scene
    Scene& scene = app.CreateScene(err);

    // Create test entity
    Entity entity = scene.CreateEntity("Test");
    entity.AddComponent<PositionComponent>(glm::vec3(0.0f, 0.0f, 0.0f));

    entity = scene.CreateEntity("Test2");
    entity.AddComponent<PositionComponent>(glm::vec3(2.0f, 0.0f, 0.0f));

    // Load playable main player entity ( default cube )
    ///FW::Player player = app.LoadPlayer(err);
    ///if (err.IsErr()) {
    ///    err.Print();
    ///}

    //Rectangle rect = scene.AddRectangle(); // Moves with the world
    //Rectangle staticRect = scene.AddStaticRectangle(); // Screen coordinates



    while (app.Run()) {
        app.ProcessInput();
    }

    app.Cleanup();

    std::cout << "Exiting.." << std::endl;

    // Re-direct possible memory leaks to sysout
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);

    return 1;
}