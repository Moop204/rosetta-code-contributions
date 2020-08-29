#include <string> 
#include <iomanip> 
#include <iostream>


#define HEIGHT        16
#define WIDTH         6
#define ASCII_START   32
#define ASCII_END     128
// ASCII special characters
#define SPACE         32 
#define DELETE        127

std::string displayAscii(int ascii) {
  switch(ascii) {
    case SPACE:
      return "Spc";
    case DELETE:
      return "Del";
    default:
      return std::string(1,char(ascii));
  }
}

int main(void) {

  for(int row = 0; row < HEIGHT; ++row) {
    for(int col = 0; col < WIDTH; ++col) {
      int ascii = ASCII_START + row + col*HEIGHT; 
      std::cout << std::right << std::setw(3) << ascii << " : " \
        << std::left << std::setw(6) << displayAscii(ascii);   
    }
    std::cout << std::endl;
  }
}
