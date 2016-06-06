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
  d_->events_listener_.addKeyboardEvent(KeyboardEvent(SDLK_0));
  d_->events_listener_.addKeyboardEvent(KeyboardEvent(SDLK_1));
  d_->events_listener_.addKeyboardEvent(KeyboardEvent(SDLK_2));
  d_->events_listener_.addKeyboardEvent(KeyboardEvent(SDLK_3));
  d_->events_listener_.addKeyboardEvent(KeyboardEvent(SDLK_s));
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
    bool new_event = d_->events_listener_.listen();
    if(new_event && d_->renderer_.render()) {
      break;
    }

    SDL_Delay(16);
  }

}
