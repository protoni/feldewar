#include "Renderer/Renderer.h"
#include "OpenGL.h"

#include <iostream>

namespace ENGINE
{

Renderer::Renderer()
{
    // Init renderer API type
    RendererType = RenderAPI::Unknown;
}

Renderer::~Renderer()
{
}

const bool Renderer::Init(const RenderAPI rendererType)
{
    RendererType = rendererType;
    bool ret = false;

    switch (RendererType)
    {
    case RenderAPI::OpenGL:
        break;

    case RenderAPI::Unknown:
    default:
        std::cout << "Unknown renderer API given!" << std::endl;
        break;
    }

    return ret;
}

} // namespace ENGINE