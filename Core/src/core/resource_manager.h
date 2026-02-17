#pragma once
#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

#include <map>
#include <memory>
#include <string>

#include "resource.h"
#include "renderer/renderer.h"

namespace Engine {

	template <typename Resource, typename Identifier>
	class ResourceManager
	{
		public:
			ResourceManager();
			~ResourceManager();

			void load(Identifier id, const std::string& filepath);

			

		private:
			// testear metodos que manejen recursos
			//cargar recurso
			//obtener recurso ya cargado

			std::map<TextureType::ID, std::unique_ptr<Renderer::Texture>> m_TextureMap;


	};
	template<typename Resource, typename Identifier>
	inline ResourceManager<Resource, Identifier>::ResourceManager()
	{
	}
	template<typename Resource, typename Identifier>
	inline ResourceManager<Resource, Identifier>::~ResourceManager()
	{
	}
	template<typename Resource, typename Identifier>
	inline void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string& filepath)
	{
	}
}
#endif

