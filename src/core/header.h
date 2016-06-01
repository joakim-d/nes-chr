#ifndef idF6606FAD7F254071AD7EEF99EB3BE8B7_H
#define idF6606FAD7F254071AD7EEF99EB3BE8B7_H

#include <cstdint>
#include <vector>
#include <array>

/*!
 * \brief The Header class
 */
//! TODO DOCUMENTING!!!

class Header {
public:
  Header(const std::vector<uint8_t> &data);
  ~Header();

  uint32_t prg_size() const;
  uint32_t chr_size() const;
  bool trainer() const;

private:
  std::array<uint8_t, 16> data_;
};

#endif // idF6606FAD7F254071AD7EEF99EB3BE8B7_H
