#include "Renderer.h"

#include <iostream>


namespace ENGINE
{

Renderer::Renderer()
{
    // Create graphics API object
    m_rendererOpenGL = std::make_unique<RendererOpenGL>();

    // Build shaders
    m_lightShader = std::make_shared<Shader>("Shaders/shader.vs", "Shaders/lightShader.fs");
    m_lightMeshShader = std::make_shared<Shader>("Shaders/lightMeshShader.vs", "Shaders/lightMeshShader.fs");
}

Renderer::~Renderer()
{
}

const bool Renderer::Init(const RenderAPI rendererType)
{
    m_rendererType = rendererType;
    bool ret = false;

    switch (m_rendererType)
    {
    case RenderAPI::OpenGL:
        ret = m_rendererOpenGL->Init();
        break;

    case RenderAPI::Unknown:
    default:
        std::cout << "Unknown renderer API given!" << std::endl;
        break;
    }

    return ret;
}

void Renderer::ClearScreen(glm::vec4 color, int settings) const
{
    switch (m_rendererType)
    {
    case RenderAPI::OpenGL:
        m_rendererOpenGL->ClearScreen(color, settings);
        break;

    case RenderAPI::Unknown:
    default:
        std::cout << "Can't ClearScreen! Unknown renderer API given!" << std::endl;
        break;
    }
}

void Renderer::DrawRect(const glm::mat4& transform, const glm::vec3& position)
{
    switch (m_rendererType)
    {
    case RenderAPI::OpenGL:
        //m_rendererOpenGL->DrawRect(transform, position);
        glm::translate(transform, position);
        m_lightMeshShader->use();
        m_lightMeshShader->setMat4("model", transform);
        break;

    case RenderAPI::Unknown:
    default:
        std::cout << "Can't ClearScreen! Unknown renderer API given!" << std::endl;
        break;
    }
}

} // namespace ENGINE