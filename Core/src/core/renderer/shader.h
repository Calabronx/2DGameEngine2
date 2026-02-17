#pragma once
#include <cstdint>
#include <filesystem>
#include <glad/glad.h>

namespace Renderer {

	
	uint32_t CreateShader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
	
}
