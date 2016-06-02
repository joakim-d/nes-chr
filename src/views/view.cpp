#include "view.h"

View::Action::Action(ActionType type) : type_(type){}

View::Action::Action(ActionType type, ViewUPtr &&view) : type_(type), view_(std::move(view)){}

View::Action::ActionType View::Action::type() const {
  return type_;
}

ViewUPtr View::Action::view() {
  return std::move(view_);
}

void View::setRenderer(Renderer *renderer) {
  renderer_ = renderer;
}

Renderer * View::renderer() const {
  return renderer_;
}
