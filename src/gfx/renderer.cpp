#include "renderer.h"

#include <SDL2/SDL.h>
#include "texture.h"
#include "rect.h"
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

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer_ == nullptr){
      throw std::runtime_error("SDL_CreateRenderer Error: " + std::string(SDL_GetError()));
    }
  }


  ~RendererPrivate(){
    if(window_){
      SDL_DestroyWindow(window_);
    }
    if(renderer_){
      SDL_DestroyRenderer(renderer_);
    }
  }

  ViewUPtr view_;
  SDL_Window *window_;
  SDL_Renderer *renderer_;
};

Renderer::Renderer() : d_(new RendererPrivate()){}

Renderer::~Renderer() = default;

void Renderer::run(){
  bool quit = false;
  while(!quit){
    SDL_RenderClear(d_->renderer_);

    if(d_->view_.get()){
      auto action = d_->view_->render();
      switch(action.type()){
        case View::Action::NONE:
        break;
      case View::Action::QUIT:
        quit = true;
        break;
      case View::Action::CHANGE:
        setView(action.view());
      }
    }

    SDL_RenderPresent(d_->renderer_);
    SDL_Delay(40);
  }
}

void Renderer::setView(ViewUPtr &&view){
  d_->view_ = std::move(view);
  d_->view_->setRenderer(this);
}

SDL_Renderer* Renderer::rawRenderer(){
  return d_->renderer_;
}

void Renderer::renderTexture(const Texture &texture){
  SDL_RenderCopy(d_->renderer_, texture.rawTexture(), nullptr, nullptr);
}

void Renderer::renderTexture(const Texture &texture, const Rect &src, const Rect &dst){
  SDL_RenderCopy(d_->renderer_, texture.rawTexture(), &src.rect(), &dst.rect());
}
