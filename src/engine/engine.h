#ifndef idDB67ADC76BAD4F6DBF909403C3C31A2A_H
#define idDB67ADC76BAD4F6DBF909403C3C31A2A_H

#include <memory>

class Renderer;
class EventsListener;

/*!
 * \brief The Engine class
 */
//! TODO DOCUMENTING!!!

class Engine {
public:
  Engine();
  ~Engine();
  Renderer& renderer() const;
  EventsListener& eventsListener() const;

  void run();

private:
  class EnginePrivate;
  std::unique_ptr<EnginePrivate> d_;
};

#endif // idDB67ADC76BAD4F6DBF909403C3C31A2A_H
