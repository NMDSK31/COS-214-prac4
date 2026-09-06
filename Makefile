CXX := g++
TARGET := taskforge

INCLUDE_DIRS := \
	include/core \
	include/domain \
	include/task \
	include/state \
	include/decorator \
	include/iterator
CPPFLAGS := $(addprefix -I,$(INCLUDE_DIRS))
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic -g -MMD -MP

SOURCES := $(wildcard src/*.cpp src/*/*.cpp) main.cpp
OBJECTS := $(SOURCES:.cpp=.o)
DEPENDENCIES := $(OBJECTS:.o=.d)

.PHONY: all clean run test sanitize valgrind

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

test:
	$(MAKE) -C tests test

sanitize:
	$(MAKE) -C tests sanitize

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

clean:
	rm -f $(OBJECTS) $(DEPENDENCIES) $(TARGET)
	rm -rf $(TARGET).dSYM

-include $(DEPENDENCIES)
