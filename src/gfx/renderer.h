#ifndef idD48C21575D5E443AAA70BC5D36C81327_H
#define idD48C21575D5E443AAA70BC5D36C81327_H

#include <memory>

class View;
using ViewUPtr = std::unique_ptr<View>;

/*!
 * \brief The Renderer class
 */
//! TODO DOCUMENTING!!!

class Renderer {
public:
  Renderer();
  ~Renderer();

  void run();
  void setView(ViewUPtr &&view);
private:
  class RendererPrivate;
  std::unique_ptr<RendererPrivate> d_;
};

#endif // idD48C21575D5E443AAA70BC5D36C81327_H
