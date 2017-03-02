all: clean mycolor mybufferMem

mycolor:
	g++ -o myColor buildITB/bufferMem.cpp buildITB/mColor.cpp buildITB/color.cpp -std=c++11

mybufferMem :
	g++ -o mybufferMem buildITB/color.cpp buildITB/bufferMem.cpp buildITB/mBufferMem.cpp buildITB/Point.cpp -std=c++11
	
clean:
	$(RM) mycolor mybufferMem
