#include "color.h"

Color::Color() : BaseColor(){
	//do nothing
}

Color::Color(int _R, int _G, int _B) : BaseColor(_R, _G, _B){
	//do nothing
}

bool Color::operator==(const Color& c) const {
  return getR() == c.getR() && getG() == c.getG() && getB() == c.getB();
}

bool Color::operator!=(const Color& c) const {
  return !(*this == c);
}
