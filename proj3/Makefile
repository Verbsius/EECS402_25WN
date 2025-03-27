CXX = g++
CXXFLAGS = -std=c++98 -Wall 


TARGET = proj3.exe


SRCS = main.cpp Image.cpp Color.cpp
OBJS = $(SRCS:.cpp=.o)  

all: $(TARGET)


$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

