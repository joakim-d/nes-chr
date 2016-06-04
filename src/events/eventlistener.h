#ifndef id7D1345231E8F4FC79FBFA69EAF83782F_H
#define id7D1345231E8F4FC79FBFA69EAF83782F_H

#include <map>
#include "keyboardevent.h"
#include "mouseevent.h"

/*!
 * \brief The EventsListener class
 */
//! TODO DOCUMENTING!!!

class EventsListener {
public:
  void addKeyboardEvent(const KeyboardEvent &event);
  void listen();

  bool quit() const;
  const KeyboardEvent &keyboardEvent(SDL_Keycode code) const;
  const MouseEvent &mouseEvent() const;

private:
  std::map<SDL_Keycode, KeyboardEvent> key_events_;
  MouseEvent mouse_event_;
  bool quit_{};
};

#endif // id7D1345231E8F4FC79FBFA69EAF83782F_H
