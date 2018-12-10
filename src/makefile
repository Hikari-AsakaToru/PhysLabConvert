CXX = g++
TARGET = converter
CXXFLAGS = -Wall -std=gnu++17 -O2
SRCS = main.cpp
OBJS := $(SRCS:.cpp=.o)



$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS)
clean: main.cpp
	rm -rf $(TARGET) $(OBJS)
