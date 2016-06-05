#include <iostream>
#include <cerrno>

#include "core/rom.h"
#include "core/chr.h"
#include "engine/engine.h"
#include "views/paintview.h"
#include "gfx/renderer.h"

int main(int argc, char *argv[]){
  if(argc < 2){
    std::cout << "Usage : " << argv[0] << " " << "rom_file" << std::endl;
    return -1;
  }

  std::string file_path(argv[1]);

  try {
    Rom rom(file_path);
    Engine engine;

    auto paintView = new PaintView(engine, rom);
    ViewUPtr view(paintView);
    engine.renderer().setView(std::move(view));

    engine.run();
  }
  catch(std::exception &e){
    std::cerr << e.what() << std::endl;
    return -1;
  }

  return 0;
}
