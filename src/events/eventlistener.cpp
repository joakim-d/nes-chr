#include "eventlistener.h"

#include <SDL2/SDL_events.h>
#include <algorithm>

void EventsListener::addKeyboardEvent(const KeyboardEvent &event){
  key_events_.insert(std::pair<SDL_Keycode, KeyboardEvent>(event.key_code, event));
}

void EventsListener::listen(){
  SDL_Event event;
  for(auto &key_event : key_events_){
    key_event.second.released = false;
  }
  while (SDL_PollEvent(&event)) {
    switch(event.type){
    case SDL_KEYDOWN:
    {
      auto key_it = key_events_.find(event.key.keysym.sym);
      if(key_it != key_events_.end()){
        key_it->second.pressed = true;
      }
    }
      break;
    case SDL_KEYUP:
    {
      auto key_it = key_events_.find(event.key.keysym.sym);
      if(key_it != key_events_.end()){
        key_it->second.pressed = false;
        key_it->second.released = true;
      }
    }
      break;
    case SDL_QUIT:
      quit_ = true;
    }
  }

}

bool EventsListener::quit() const {
  return quit_;
}

const KeyboardEvent& EventsListener::keyboardEvent(SDL_Keycode code) const {
  auto key_it = key_events_.find(code);
  if(key_it == key_events_.end()){
    throw std::runtime_error("Wrong key_code asked");
  }
  return key_it->second;
}
