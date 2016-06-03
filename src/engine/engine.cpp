#include "engine.h"
#include "../events/eventlistener.h"
#include "../events/keyboardevent.h"
#include "../gfx/renderer.h"
#include "SDL2/SDL.h"

class Engine::EnginePrivate {
public:
  Renderer renderer_;
  EventsListener events_listener_;
};

Engine::Engine() : d_(new EnginePrivate){
  d_->events_listener_.addKeyboardEvent(KeyboardEvent(SDLK_UP));
  d_->events_listener_.addKeyboardEvent(KeyboardEvent(SDLK_DOWN));
  d_->events_listener_.addKeyboardEvent(KeyboardEvent(SDLK_LEFT));
  d_->events_listener_.addKeyboardEvent(KeyboardEvent(SDLK_RIGHT));
}

Engine::~Engine() = default;

Renderer& Engine::renderer() const {
  return d_->renderer_;
}

EventsListener& Engine::eventsListener() const {
  return d_->events_listener_;
}

void Engine::run() {
  while(true){
    d_->events_listener_.listen();
    if(d_->renderer_.render()) {
      break;
    }

    SDL_Delay(40);
  }

}
