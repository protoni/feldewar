#ifndef RENDERER_H
#define RENDERER_H

#include "DebugMacros.h"
#include "RendererOpenGL.h"
#include "Shader.h"
#include "Settings.h"

#include <memory>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace ENGINE
{
class Renderer
{

public:
    Renderer();
    ~Renderer();

    // Initialize graphics API
    const bool Init(const RenderAPI rendererType);

    // Clear screen
    void ClearScreen(glm::vec4 color, int settings) const;

    // Draw rectangle
    void DrawRect(const glm::mat4& transform, const glm::vec3& position);

private:
    RenderAPI m_rendererType = RenderAPI::Unknown;

    std::unique_ptr<RendererOpenGL> m_rendererOpenGL = nullptr;

    // Shaders
    std::shared_ptr<Shader> m_lightShader = nullptr;
    std::shared_ptr<Shader> m_lightMeshShader = nullptr;
};

}

#endif // RENDERER_H