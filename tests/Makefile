CXX := g++

INCLUDE_DIRS := \
	../include/core \
	../include/domain \
	../include/task \
	../include/state \
	../include/decorator \
	../include/iterator
CPPFLAGS := $(addprefix -I,$(INCLUDE_DIRS))
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic -g
SANITIZER_FLAGS := -fsanitize=undefined -fno-omit-frame-pointer

TARGET := iterator_tests
SANITIZED_TARGET := iterator_tests_sanitized
SOURCES := \
	$(wildcard ../src/*/*.cpp) \
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
	rm -rf $(TARGET).dSYM $(SANITIZED_TARGET).dSYM
