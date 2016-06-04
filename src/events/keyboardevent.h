#ifndef idDCFE0AA2C6954E1D97A730305E665013_H
#define idDCFE0AA2C6954E1D97A730305E665013_H

#include <SDL2/SDL_events.h>

/*!
 * \brief KeyboardEvent class
 */
//! TODO DOCUMENTING!!!

class KeyboardEvent {
public:
  KeyboardEvent(SDL_Keycode key_code) : key_code(key_code){}

  bool operator ==(SDL_Keycode k){
    return k == key_code;
  }

  SDL_Keycode key_code{};
  bool on{}; //< true if the key is pressed
  bool pressed{}; //< true if the key was just pressed
  bool released{}; //< true if the key was just released
};

#endif // idDCFE0AA2C6954E1D97A730305E665013_H
