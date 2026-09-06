CXX := g++

CPPFLAGS := -I../../Person1 -I..
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic -g
SANITIZER_FLAGS := -fsanitize=undefined -fno-omit-frame-pointer

TARGET := iterator_tests
SANITIZED_TARGET := iterator_tests_sanitized
SOURCES := \
	../../Person1/structureVersion.cpp \
	../../Person1/workComponent.cpp \
	../../Person1/workGroup.cpp \
	../DepthFirstIterator.cpp \
	../IncompleteTaskIterator.cpp \
	IteratorTests.cpp

.PHONY: all test sanitize clean

all: test

test: $(TARGET)
	./$(TARGET)

sanitize: $(SANITIZED_TARGET)
	./$(SANITIZED_TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SOURCES) -o $@

$(SANITIZED_TARGET): $(SOURCES)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SANITIZER_FLAGS) $(SOURCES) -o $@

clean:
	rm -f $(TARGET) $(SANITIZED_TARGET)
