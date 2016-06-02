#include <iostream>
#include <cerrno>

#include "core/rom.h"
#include "core/chr.h"
#include "gfx/renderer.h"
#include "views/paintview.h"

int main(int argc, char *argv[]){
  if(argc < 2){
    std::cout << "Usage : " << argv[0] << " " << "rom_file" << std::endl;
    return -1;
  }

  std::string file_path(argv[1]);

  try {
    Rom rom(file_path);
    Renderer renderer;

    auto paintView = new PaintView;
    ViewUPtr view(paintView);
    renderer.setView(std::move(view));
    paintView->setNesSprites(rom.chr().sprites());



    renderer.run();
  }
  catch(std::exception &e){
    std::cerr << e.what() << std::endl;
    return -1;
  }

  return 0;
}
