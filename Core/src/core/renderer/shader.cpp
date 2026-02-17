#include "shader.h"

#include <string>
#include <iostream>
#include <fstream>

namespace Renderer {

	static std::string ReadTextFile(const std::filesystem::path& path)
	{
		std::ifstream file(path);

		if (!file.is_open())
		{
			std::cerr << "Failed to open file: " << path.string() << std::endl;
			return {};
		}

		std::ostringstream contentStream;
		contentStream << file.rdbuf();
		return contentStream.str();
	}

	uint32_t Renderer::CreateShader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
	{
		std::string vertexShaderSource = ReadTextFile(vertexPath);
		std::string fragmentShaderSource = ReadTextFile(fragmentPath);

		uint32_t vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* vrtxSource = (const GLchar*)vertexShaderSource.c_str();
		glShaderSource(vertexShader, 1, &vrtxSource, NULL);
		glCompileShader(vertexShader);

		int32_t success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		uint32_t fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		const GLchar* frgmSource = (const GLchar*)fragmentShaderSource.c_str();
		glShaderSource(fragmentShader, 1, &frgmSource, NULL);
		glCompileShader(fragmentShader);

		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COPILATION_FAILED\n" << infoLog << std::endl;
		}

		uint32_t shaderProgram = glCreateProgram();

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return shaderProgram;
	}

}
