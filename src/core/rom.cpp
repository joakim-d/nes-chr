#include "rom.h"

#include "header.h"
#include "chr.h"

#include <fstream>

using namespace std;

Rom::Rom(const std::string &file_path) {
  ifstream ifs(file_path, ios::binary|ios::ate);

  if(!ifs.is_open()){
    throw runtime_error("Failed to open " + file_path);
  }

  ifstream::pos_type pos = ifs.tellg();

  data_ = vector<uint8_t>(pos);

  ifs.seekg(0, ios::beg);
  ifs.read(reinterpret_cast<char *>(&data_[0]), pos);

  header_.reset(new Header(data_));
  chr_.reset(new Chr(data_, *header_));
}

Rom::~Rom() = default;
