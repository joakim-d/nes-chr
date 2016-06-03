#include "view.h"

View::View(Engine &engine) : engine_(engine){}

ViewUPtr View::Action::view() {
  return std::move(view_);
}

Engine& View::engine() const {
  return engine_;
}

View::Action::Action(ActionType type) : type_(type){}

View::Action::Action(ActionType type, ViewUPtr &&view) : type_(type), view_(std::move(view)){}

View::Action::ActionType View::Action::type() const {
  return type_;
}

