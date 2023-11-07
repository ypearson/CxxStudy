CXX := g++
CXXFLAGS := -std=c++17 -pedantic -Wall -Wno-unused-variable

# List of source files (manually specified)
SRCS := threadlocal1.cpp threadlocal2.cpp unique_ptr1.cpp unique_ptr2.cpp shared_ptr1.cpp implicit1.cpp implicit2.cpp implicit3.cpp

# Generate a list of corresponding executables
EXECS := $(patsubst %.cpp,%.bin,$(SRCS))

all: $(EXECS)

# Rule to compile each source file into an executable
%.bin: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	@rm -f $(EXECS)

.PHONY: all clean

