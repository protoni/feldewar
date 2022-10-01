
#include "Application.h"
#include "DebugMacros.h"
#include "Error.h"
#include "Settings.h"

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
    ENGINE::Application app;

    // Create application settings
    ENGINE::Settings settings;
    
    // Create window
    ENGINE::Error err;
    settings.window.name = "Feldewar";
    settings.window.width = 1600;
    settings.window.height = 800;
    ///if (!app.CreateWindow(settings.window, err)) {
    ///    err.Print();
    ///}

    // Create a scene


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

    // Load playable main player entity ( default cube )
    ///FW::Player player = app.LoadPlayer(err);
    ///if (err.IsErr()) {
    ///    err.Print();
    ///}

    while (app.Run()) {

    }

    return 1;
}