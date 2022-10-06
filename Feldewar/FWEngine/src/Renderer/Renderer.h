#ifndef RENDERER_H
#define RENDERER_H

#include "DebugMacros.h"
#include "RendererOpenGL.h"
#include "Shader.h"
#include "Settings.h"
#include "Camera.h"


#include <memory>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace ENGINE
{

class Mesh;
class Renderer
{

public:
    Renderer(std::shared_ptr<Camera>& camera);
    ~Renderer();

    // Initialize graphics API
    const bool Init(WindowSettings& settings);

    // Clear screen
    void ClearScreen(glm::vec4 color, int settings) const;

    // Draw rectangle
    void DrawRect(
        const glm::mat4& transform,
        const glm::vec3& position,
        const Mesh& mesh
    );

    // Load vertex data to the GPU
    static const bool LoadData(
        const std::vector<float>& vertices,
        const std::vector<unsigned int>& indices,
        BufferObject& buf
    );

    // Get basic mesh shader with lights support
    const Shader& GetMeshShader() const { return *m_lightMeshShader; }

private:
    // Activate shader and set projection matrix
    void activateShader(std::shared_ptr<Shader>& shader);

    // Translate a matrix
    void applyTranslations(
        std::shared_ptr<Shader>& shader,
        const glm::mat4& transform,
        const glm::vec3& position
    );

    // Currently used renderer API
    RenderAPI m_rendererType = RenderAPI::Unknown;

    // OpenGL renderer object
    std::unique_ptr<RendererOpenGL> m_rendererOpenGL = nullptr;

    // Camera object
    std::shared_ptr<Camera> m_camera = nullptr;

    // Window settings object
    WindowSettings m_windowSettings;

    // Shaders
    std::shared_ptr<Shader> m_lightShader = nullptr;
    std::shared_ptr<Shader> m_lightMeshShader = nullptr;

    static RenderAPI s_rendererType;
};

}

#endif // RENDERER_H