# Makefile
# Student: Kemper, Michael | Clode, Ryan
# RedID: (Kemper)822 86 7065 | (Clode)820 72 7161
# CXX Make variable for compiler
CXX=g++
# Make variable for compiler options
#	-std=c++11  C/C++ variant to use, e.g. C++ 2011
#	-g          include information for symbolic debugger e.g. gdb
CXXFLAGS=-std=c++11 -g -lpthread -lrt

# Rules format:
# target : dependency1 dependency2 ... dependencyN
#     Command to make target, uses default rules if not specified

# First target is the one executed if you just type make
# make target specifies a specific target
# $^ is an example of a special variable.  It substitutes all dependencies
mizzo : producer.o consumer.o mizzo.o
	$(CXX) $(CXXFLAGS) -o mizzo $^

mizzo.o : mizzo.C

producer.o : producer.C

consumer.o : consumer.C

clean :
	rm *.o
