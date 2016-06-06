#include "eventlistener.h"

#include <SDL2/SDL_events.h>
#include <algorithm>

void EventsListener::addKeyboardEvent(const KeyboardEvent &event){
  key_events_.insert(std::pair<SDL_Keycode, KeyboardEvent>(event.key_code, event));
}

bool EventsListener::listen(){
  bool new_event = false;
  SDL_Event event;
  for(auto &key_event : key_events_){
    key_event.second.released = false;
    key_event.second.pressed = false;
  }
  while (SDL_PollEvent(&event)) {
    switch(event.type){
    case SDL_KEYDOWN:
    {
      new_event = true;
      auto key_it = key_events_.find(event.key.keysym.sym);
      if(key_it != key_events_.end()){
        key_it->second.pressed = true;
        key_it->second.on = true;
      }
    }
      break;

    case SDL_KEYUP:
    {
      new_event = true;
      auto key_it = key_events_.find(event.key.keysym.sym);
      if(key_it != key_events_.end()){
        key_it->second.on = false;
        key_it->second.released = true;
      }
    }
      break;

    case SDL_QUIT:
      new_event = true;
      quit_ = true;
      break;

    case SDL_MOUSEBUTTONDOWN:
      new_event = true;
      switch(event.button.button){
      case SDL_BUTTON_LEFT:
        mouse_event_.left_click = true;
        break;
      case SDL_BUTTON_RIGHT:
        mouse_event_.right_click = true;
        break;
      default:
        break;
      }
      break;

    case SDL_MOUSEBUTTONUP:
      new_event = true;
      switch(event.button.button){
      case SDL_BUTTON_LEFT:
        mouse_event_.left_click = false;
        break;
      case SDL_BUTTON_RIGHT:
        mouse_event_.right_click = false;
        break;
      default:
        break;
      }
      break;

    case SDL_MOUSEMOTION:
      new_event = true;
      mouse_event_.pos.x = event.motion.x;
      mouse_event_.pos.y = event.motion.y;
      break;

    default:
      break;
    }
  }
  return new_event;
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

const MouseEvent& EventsListener::mouseEvent() const {
  return mouse_event_;
}
