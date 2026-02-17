//#include "texture.h"
//#include <iostream>
//Texture::Texture(SDL_Renderer* renderer, std::string path)
//{
//    int flags = IMG_INIT_PNG;
//    int init_status = IMG_Init(flags);
//
//    if ((init_status & flags) != flags)
//    {
//        std::cout << "SDL_Image format not available" << std::endl;
//    }
//
//    SDL_Surface* image;
//    image = IMG_Load(path.c_str());
//
//    if (!image)
//    {
//        std::cout << "Image not loaded" << std::endl;
//    }
//
//    m_texture = SDL_CreateTextureFromSurface(renderer, image);
//    SDL_FreeSurface(image);
//}
//
//Texture::~Texture()
//{
//    SDL_DestroyTexture(m_texture);
//
//    IMG_Quit();
//}
//
//void Texture::setRectantangleTextureProperties(int x, int y, int width, int height)
//{
//    m_rect.x = x;
//    m_rect.y = y;
//    m_rect.w = width;
//    m_rect.h = height;
//}
//
//void Texture::renderTexture(SDL_Renderer* renderer)
//{
//    SDL_RenderCopy(renderer, m_texture, nullptr, &m_rect);
//}