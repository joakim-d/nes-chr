#include "renderer.h"

#include <SDL2/SDL.h>
#include "../views/view.h"

class Renderer::RendererPrivate {
public:
  RendererPrivate(){
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      throw std::runtime_error("Failed to initialize SDL");
    }

    window_ = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (window_ == nullptr){
        throw std::runtime_error("SDL_CreateWindow Error: " + std::string(SDL_GetError()));
    }
  }



  ViewUPtr view_;
  SDL_Window *window_;
};

Renderer::Renderer() : d_(new RendererPrivate()){}

Renderer::~Renderer() = default;

void Renderer::run(){
  while(true){

  }
}

void Renderer::setView(ViewUPtr &&view){
  d_->view_ = std::move(view);
}


