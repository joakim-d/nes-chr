#include <iostream>
#include <cerrno>

#include "core/rom.h"
#include "core/chr.h"
#include "engine/engine.h"
#include "views/paintview.h"
#include "gfx/renderer.h"

int main(int argc, char *argv[]){
  if(argc < 2){
    std::cout << "Usage : " << argv[0] << " [options] " << "file" << std::endl;
    std::cout << "\t\toptions:" << std::endl;
    std::cout << "\t\t\t\t--chr \t\t open as CHR file" << std::endl;
    return -1;
  }

  bool chr = false;

  for(int i = 1; i < argc - 1; i++){
    if(std::string(argv[i]) == "--chr"){
      chr = true;
    }
  }

  std::string file_path(argv[argc - 1]);

  try {
    PaintView *paint_view = nullptr;
    Engine engine;

    if(chr){
      paint_view = new PaintView(engine, std::unique_ptr<Chr> (new Chr(file_path)));
    }
    else {
      paint_view = new PaintView(engine, std::unique_ptr<Rom> (new Rom(file_path)));
    }

    ViewUPtr view(paint_view);
    engine.renderer().setView(std::move(view));

    engine.run();
  }
  catch(std::exception &e){
    std::cerr << e.what() << std::endl;
    return -1;
  }

  return 0;
}
