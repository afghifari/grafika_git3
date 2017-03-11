SOURCES = datastructure/base/base_color.cpp datastructure/base/base_line.cpp datastructure/base/base_point.cpp datastructure/canvas.cpp datastructure/color.cpp datastructure/line.cpp datastructure/minmap.cpp datastructure/point.cpp datastructure/shape.cpp main.cpp
HEADERS = datastructure/base/base_color.h datastructure/base/base_line.h datastructure/base/base_point.h datastructure/canvas.h datastructure/color.h datastructure/line.h datastructure/minmap.h datastructure/point.h datastructure/shape.h

all: $(SOURCES) $(HEADERS)
	g++ -o main $(SOURCES) -lpthread -lm -std=c++0x -pthread -O2

clean:
	rm main
