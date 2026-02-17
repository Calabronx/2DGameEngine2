#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <cstdint>
#include <filesystem>

namespace Renderer {

    struct Texture
    {
        GLuint Handle = 0;
        uint32_t Width = 0;
        uint32_t Height = 0;
    };

    struct Framebuffer
    {
        GLuint Handle = 0;
        Texture ColorAttachment;
    };

    struct Sprite
    {
        std::string name;
        Texture texture;
        Framebuffer framebuffer;
    };

    Texture CreateTexture(int width, int height);
    Texture LoadTexture(const std::filesystem::path& path);
    Framebuffer CreateFramebufferWithTexture(const Texture texture);
    bool AttachTextureToFramebuffer(Framebuffer& framebuffer, const Texture texture);
    void BlitFramebufferToSwapchain(const Framebuffer framebuffer);
    void Render(Texture& texture, uint32_t shader, uint32_t vao, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color);
}

#endif