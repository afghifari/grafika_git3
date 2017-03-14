SOURCES = main.cpp datastructure/base/base_color.cpp datastructure/base/base_line.cpp datastructure/base/base_point.cpp datastructure/canvas.cpp datastructure/color.cpp datastructure/line.cpp datastructure/minmap.cpp datastructure/point.cpp datastructure/shape.cpp datastructure/circle.cpp datastructure/drawer.cpp datastructure/helicopter.cpp datastructure/itbmap.cpp datastructure/heli_propeller.cpp datastructure/explosion.cpp datastructure/credit.cpp
HEADERS = datastructure/base/base_color.h datastructure/base/base_line.h datastructure/base/base_point.h datastructure/canvas.h datastructure/color.h datastructure/line.h datastructure/minmap.h datastructure/point.h datastructure/shape.h datastructure/drawer.h datastructure/itbmap.h datastructure/helicopter.h datastructure/heli_propeller.h datastructure/circle.h datastructure/explosion.h datastructure/animatable.h datastructure/credit.h

main: $(SOURCES) $(HEADERS)
	g++ -o main $(SOURCES) -lpthread -lm -std=c++0x -pthread -O2

maindebug: $(SOURCES) $(HEADERS)
	g++ -o maindebug $(SOURCES) -lpthread -lm -std=c++0x -pthread -O2 -g

clean:
	rm main
