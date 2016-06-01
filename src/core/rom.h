#ifndef id4651D76EC28540D491BDB500CE6FFE21_H
#define id4651D76EC28540D491BDB500CE6FFE21_H

#include <string>
#include <vector>
#include <memory>

class Header;
class Chr;

class Rom {
public:
  Rom(const std::string &file_path);
  ~Rom();

private:
  std::vector<uint8_t> data_;
  std::unique_ptr<Header> header_;
  std::unique_ptr<Chr> chr_;
};

#endif // id4651D76EC28540D491BDB500CE6FFE21_H
