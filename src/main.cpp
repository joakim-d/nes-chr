#include <iostream>
#include <cerrno>

#include "core/rom.h"
#include "gfx/renderer.h"

int main(int argc, char *argv[]){
  if(argc < 2){
    std::cout << "Usage : " << argv[0] << " " << "rom_file" << std::endl;
    return -1;
  }

  std::string file_path(argv[1]);

  try {
    Rom rom(file_path);
    Renderer renderer;
    renderer.run();
  }
  catch(std::exception &e){
    std::cerr << e.what() << std::endl;
    return -1;
  }

  return 0;
}
