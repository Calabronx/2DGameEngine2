#include "renderer.h"
#include <iostream>

#include "glad/glad.h"
#include <stb_image.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Renderer {
    
    Texture CreateTexture(int width, int height)
    {
        Texture result;
        result.Width = width;
        result.Height = height;

        glCreateTextures(GL_TEXTURE_2D, 1, &result.Handle);

        glTextureStorage2D(result.Handle, 1, GL_RGBA32F, width, height);

        glTextureParameteri(result.Handle, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(result.Handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(result.Handle, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTextureParameteri(result.Handle, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        return result;
    }

    Texture LoadTexture(const std::filesystem::path& path)
    {
        int width, height, channels;
        std::string filepath = path.string();

        // stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

        if (!data)
        {
            std::cerr << "Failed to load texture: " << filepath << "\n";
            return {};
        }

        GLenum format = channels == 4 ? GL_RGBA : 
            channels == 3 ? GL_RGB : 
            channels == 1 ? GL_RED : 0;

        Texture result;
        result.Width = width;
        result.Height = height;

        glCreateTextures(GL_TEXTURE_2D, 1, &result.Handle);

        glTextureStorage2D(result.Handle, 1, (format == GL_RGBA ? GL_RGBA8 : GL_RGB8), width, height);

        glTextureSubImage2D(result.Handle, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);

        glTextureParameteri(result.Handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(result.Handle, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glGenerateTextureMipmap(result.Handle);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        stbi_image_free(data);

        return result;
    }

    Framebuffer CreateFramebufferWithTexture(const Texture texture)
    {
        return Framebuffer();
    }

    bool AttachTextureToFramebuffer(Framebuffer& framebuffer, const Texture texture)
    {
        return false;
    }

    void BlitFramebufferToSwapchain(const Framebuffer framebuffer)
    {
    }
    
    void Render(Texture& texture, uint32_t shader,uint32_t vao, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
    {
        glUseProgram(shader);
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3(position, 0.0f));

        model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
        model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

        model = glm::scale(model, glm::vec3(size, 1.0f));

        glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, false, glm::value_ptr(model));
        glUniform3f(glGetUniformLocation(shader, "spriteColor"), color.x, color.y, color.z);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.Handle);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
}