#ifndef idD97BB412751E422A9E6D27F0237C0670_H
#define idD97BB412751E422A9E6D27F0237C0670_H

#include <cstdint>
#include <vector>

#include "sprite.h"

class Header;

class Chr {
public:
  Chr(const std::vector<uint8_t> &data, const Header &header);

  std::vector<Sprite>& sprites();
  std::vector<uint8_t>& data();
  void applyChanges();
private:
  std::vector<uint8_t> data_;
  std::vector<Sprite> sprites_;
};

#endif // idD97BB412751E422A9E6D27F0237C0670_H
