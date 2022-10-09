#include "Renderer.h"
#include "Primitives.h"
#include "Terrain.h"

#include <iostream>
#include <filesystem>

namespace ENGINE
{

RenderAPI Renderer::s_rendererType = RenderAPI::OpenGL;

Renderer::Renderer(std::shared_ptr<Camera>& camera) : m_camera(camera)
{
    // Create graphics API object
    m_rendererOpenGL = std::make_unique<RendererOpenGL>();

    // Build shaders
    m_lightShader = std::make_shared<Shader>(
        "Feldewar/Shaders/shader.vs", 
        "Feldewar/Shaders/lightShader.fs"
    );

    m_lightMeshShader = std::make_shared<Shader>(
        "Feldewar/Shaders/lightMeshShader.vs",
        "Feldewar/Shaders/lightMeshShader.fs"
    );
}

Renderer::~Renderer()
{
}

const bool Renderer::Init(WindowSettings& settings)
{
    m_rendererType = settings.renderAPI;
    m_windowSettings = settings;

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

void Renderer::activateShader(std::shared_ptr<Shader>& shader)
{
    // Get the current projection matrix
    glm::mat4 projection = glm::perspective(
        glm::radians(m_camera->Zoom),
        (float)m_windowSettings.width / (float)m_windowSettings.height, 0.1f, 100.0f
    );

    // Get the current view matrix
    glm::mat4 view = m_camera->GetViewMatrix();

    shader->use();
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);
    shader->setVec3("viewPos", m_camera->Position);
}

void Renderer::applyTranslations(
    std::shared_ptr<Shader>& shader,
    const glm::mat4& transform,
    const glm::vec3& position,
    const glm::vec3& scale
)
{
    glm::mat4 model = transform;
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    shader->setMat4("model", model);
}

void Renderer::applyTranslations(
    std::shared_ptr<Shader>& shader,
    const glm::mat4& transform,
    const glm::vec3& position
)
{
    shader->setMat4("model", glm::translate(transform, position));
}

void Renderer::applyTranslations(
    std::shared_ptr<Shader>& shader,
    const glm::mat4& transform
)
{
    shader->setMat4("model", transform);
}

void Renderer::DrawMesh(const glm::mat4& transform,
    const glm::vec3& position,
    const Mesh& mesh
)
{
    switch (m_rendererType)
    {
    case RenderAPI::OpenGL:
        activateShader(m_lightMeshShader);
        applyTranslations(m_lightMeshShader, transform, position);
        m_rendererOpenGL->DrawMesh(mesh.GetBuffer());
        break;

    case RenderAPI::Unknown:
    default:
        std::cout << "Can't ClearScreen! Unknown renderer API given!" << std::endl;
        break;
    }
}

void Renderer::DrawTerrain(const glm::mat4& transform, const glm::vec3& position, const Terrain& terrain)
{
    switch (m_rendererType)
    {
    case RenderAPI::OpenGL:
        terrain.UseTexture();
        activateShader(m_lightMeshShader);
        applyTranslations(m_lightMeshShader, glm::mat4(1.0f), position, glm::vec3(0.5, 0.5, 0.5));
        m_rendererOpenGL->DrawTerrain(terrain.GetBuffer());
        break;

    case RenderAPI::Unknown:
    default:
        std::cout << "Can't ClearScreen! Unknown renderer API given!" << std::endl;
        break;
    }
}

const bool Renderer::LoadData(
    const std::vector<float>& vertices,
    const std::vector<unsigned int>& indices,
    BufferObject& buf
)
{
    bool ret = false;

    switch (s_rendererType)
    {
    case RenderAPI::OpenGL:
        RendererOpenGL::LoadData(vertices, indices, buf);
        ret = true;
        break;

    case RenderAPI::Unknown:
    default:
        std::cout << "Can't ClearScreen! Unknown renderer API given!" << std::endl;
        break;
    }

    return ret;
}

const bool Renderer::LoadData(
    const std::vector<float>& vertices,
    const std::vector<float>& textureCoords,
    const std::vector<float>& normals,
    const std::vector<unsigned int>& indices,
    BufferObjectSeparated& buf
)
{
    bool ret = false;

    switch (s_rendererType)
    {
    case RenderAPI::OpenGL:
        RendererOpenGL::LoadData(vertices, textureCoords, normals, indices, buf);
        ret = true;
        break;

    case RenderAPI::Unknown:
    default:
        std::cout << "Can't ClearScreen! Unknown renderer API given!" << std::endl;
        break;
    }

    return ret;
}

} // namespace ENGINE