#include "chr.h"
#include "header.h"

#include <stdexcept>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

Chr::Chr(const std::string &file_path, bool create, uint32_t size) : file_path_(file_path) {
  if(create){
    size *= 8192;
    if(size == 0 || size > 8192 * 16){
      std::stringstream ss;
      ss << "Can't create chr file of size " << size << " bytes";

      throw runtime_error(ss.str());
    }
    ofstream ofs(file_path, ios::binary|ios::ate);

    if(!ofs.is_open()){
      throw runtime_error("Failed to create + file_path");
    }

    data_.resize(size, 0);
    ofs.write(reinterpret_cast<char *>(data_.data()), data_.size());
  }
  else{
    ifstream ifs(file_path, ios::binary|ios::ate);

    if(!ifs.is_open()){
      throw runtime_error("Failed to open " + file_path);
    }

    ifstream::pos_type pos = ifs.tellg();

    data_ = vector<uint8_t>(pos);

    ifs.seekg(0, ios::beg);
    ifs.read(reinterpret_cast<char *>(&data_[0]), pos);
  }

  createSpritesFromData();
}

Chr::Chr(const std::vector<uint8_t> &data, const Header &header) {
  data_.resize(header.chr_size(), 0);

  uint32_t offset = header.trainer() ? 16 + 512 + header.prg_size() : 16 + header.prg_size();

  if(header.chr_size() == 0){
    throw std::runtime_error("No chr in Rom");
  }

  if(header.chr_size() + offset > data.size()){
    throw std::runtime_error("File corrupted, chr size too big.");
  }

  memcpy(data_.data(), data.data() + offset, header.chr_size());

  createSpritesFromData();
}

std::vector<Sprite>& Chr::sprites() {
  return sprites_;
}

void Chr::applyChanges() {
  auto index = 0;
  for(auto &sprite : sprites_){
    memcpy(data_.data() + index * 16, sprite.toChrData().data(), 16);
    index++;
  }
}

std::vector<uint8_t>& Chr::data() {
  return data_;
}

void Chr::createSpritesFromData() {
  for (auto i = 0; i < data_.size() / 16; i++){
    sprites_.push_back(Sprite(8, 8, data_.data() + i * 16));
  }
}

void Chr::save(){
  if(file_path_ == ""){
    throw runtime_error("Trying to save Chr with empty path");
  }
  applyChanges();
  ofstream ofs(file_path_, ios::binary);

  if(!ofs.is_open()){
    throw runtime_error("Failed to save.");
  }

  ofs.write(reinterpret_cast<char *>(data_.data()), data_.size());
}
