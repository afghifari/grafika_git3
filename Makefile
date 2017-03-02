all: clean mycolor mybufferMem

mycolor:
	g++ -o myColor projectUTS/bufferMem.cpp projectUTS/mColor.cpp projectUTS/color.cpp -std=c++11

mybufferMem :
	g++ -o mybufferMem projectUTS/color.cpp projectUTS/bufferMem.cpp projectUTS/mBufferMem.cpp projectUTS/Point.cpp -std=c++11
	
clean:
	$(RM) mycolor mybufferMem
