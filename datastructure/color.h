#ifndef COLOR_H
#define COLOR_H

#include "base/base_color.h"

class Color : public BaseColor{
public:
	Color();
	Color(int,int,int);

	bool operator==(const Color&) const;
	bool operator!=(const Color&) const;
};

#endif
