#include "rom.h"

#include "header.h"
#include "chr.h"

#include <fstream>
#include <string.h>

using namespace std;

Rom::Rom(const std::string &file_path) : file_path_(file_path){
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

Chr& Rom::chr() const {
  return *chr_;
}

void Rom::applyChanges(){
  chr_->applyChanges();
  uint32_t offset = header_->trainer() ? 16 + 512 + header_->prg_size() : 16 + header_->prg_size();

  memcpy(data_.data() + offset, chr_->data().data(), header_->chr_size());
}

void Rom::save() {
  applyChanges();
  ofstream ofs(file_path_, ios::binary);

  if(!ofs.is_open()){
    throw runtime_error("Failed to save.");
  }

  ofs.write(reinterpret_cast<char *>(data_.data()), data_.size());
}

