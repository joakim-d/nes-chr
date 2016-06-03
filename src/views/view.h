#ifndef id8CD645E9ECCF4C5A9DAFC5BD5D7F8612_H
#define id8CD645E9ECCF4C5A9DAFC5BD5D7F8612_H

#include <memory>

class Engine;
class View;
using ViewUPtr = std::unique_ptr<View>;

/*!
 * \brief The View class
 */
//! TODO DOCUMENTING!!!

class View {
public:
  View(Engine& engine);

  class Action;
  virtual Action render() = 0;

  class Action {
  public:
    enum ActionType {
      NONE,
      QUIT,
      CHANGE
    };

    Action(ActionType type);
    Action(ActionType type, ViewUPtr &&view);

    ActionType type() const;
    ViewUPtr view();
  private:
    ActionType type_;
    ViewUPtr view_;
  };

protected:
  Engine &engine() const;

private:
  Engine &engine_;
};



#endif // id8CD645E9ECCF4C5A9DAFC5BD5D7F8612_H
