# Person 3 integration draft: move this file to the repository root.
CXX := g++
TARGET := taskforge

CPPFLAGS := -Iinclude
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic -g -MMD -MP

SOURCES := $(wildcard src/*.cpp src/*/*.cpp) main.cpp
OBJECTS := $(SOURCES:.cpp=.o)
DEPENDENCIES := $(OBJECTS:.o=.d)

.PHONY: all clean run valgrind

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

clean:
	rm -f $(OBJECTS) $(DEPENDENCIES) $(TARGET)

-include $(DEPENDENCIES)
