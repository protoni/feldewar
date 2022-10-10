
#include "FWEngine.h"
#include "DebugMacros.h"
#include "EngineUtils.h"

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
    settings.data.modelPath = "Feldewar/Models";
    settings.data.texturePath = "Feldewar/Textures";
    if (!Application::LoadData(settings.data, err)) {
        err.Print();
    }

    // Create a scene
    Scene& scene = app.CreateScene(err);

    // Create test rect
    Entity rect = scene.AddRectangle2D("Rect2d");
    
    // Create test cube
    Entity cube = scene.AddCube3D("Cube3d");

    // Load terrain
    settings.terrain.heightMap = "heightmap.png";
    settings.terrain.texture = "grass.png";
    settings.terrain.size = 800.0f;
    Entity terrain = scene.AddTerrain(settings.terrain);

    // Load playable main player entity ( default cube )
    Entity player = scene.AddPlayer(cube, "Player1");

    // Setup player movement keys
    //app.SetupPlayer(player);

    player.RotateTo(glm::vec3(90.0f, 90.0f, 90.0f));

    float movePtr = 0.0f;
    float moveAmount = 0.01f;
    float rotateAmount = 1.0f;
    while (app.Run()) {
        app.ProcessInput();


        if (movePtr <= 2.0f) {
            rect.MoveLeft(moveAmount);
            //player.RotateLeft(rotateAmount);
            //player.MoveLeft(moveAmount);
            //cube.MoveLeft(moveAmount*0.1);
        }
        else if (movePtr > 2.0f && movePtr <= 4.0f) {
            rect.MoveUp(moveAmount);
            //terrain.MoveUp(moveAmount);
        }
        else if (movePtr > 4.0f && movePtr <= 6.0f) {
            rect.MoveRight(moveAmount);
            //terrain.MoveRight(moveAmount);
        }
        else if (movePtr > 6.0f && movePtr <= 8.0f) {
            rect.MoveDown(moveAmount);
            //terrain.MoveDown(moveAmount);
        }
        else
            movePtr = 0.0f;

       movePtr += moveAmount;
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