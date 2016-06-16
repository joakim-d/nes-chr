#include <iostream>
#include <cerrno>
#include <sstream>

#include "core/rom.h"
#include "core/chr.h"
#include "engine/engine.h"
#include "views/paintview.h"
#include "gfx/renderer.h"

int main(int argc, char *argv[]){
  if(argc < 2){
    std::cout << "Usage : " << argv[0] << " [options] " << "<file_path>" << std::endl << std::endl;
    std::cout << "\t\toptions:" << std::endl;
    std::cout << "\t\t\t\t--chr \t\t open <file_path> as CHR file" << std::endl;
    std::cout << "\t\t\t\t--new=<size> \t create a new CHR file of path <file_path> and size \"<size> * 8192\" bytes (<size> must be in the 1-16 range)" << std::endl;
    return -1;
  }

  bool chr = false;
  bool new_file = false;
  uint32_t chr_size = 0;

  for(int i = 1; i < argc - 1; i++){
    if(std::string(argv[i]) == "--chr"){
      chr = true;
    }
    else if(std::string(argv[i]).find("--new=") != std::string::npos){
      new_file = true;
      chr = true;
      std::string chr_size_str(argv[i] + 6);
      std::stringstream ss;
      ss << chr_size_str;
      ss >> chr_size;
    }
  }

  std::string file_path(argv[argc - 1]);

  try {
    PaintView *paint_view = nullptr;
    Engine engine;

    if(chr){
      paint_view = new PaintView(engine, std::unique_ptr<Chr> (new Chr(file_path, new_file, chr_size)));
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
