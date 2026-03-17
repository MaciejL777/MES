# Simple Makefile for building the MES project (C++14).
# Default builds with g++ and optional OpenMP. Usage:
#   make           # build
#   make run       # build and run (Linux/macOS)
#   make clean
#
CXX ?= g++
CXXFLAGS := -std=c++14 -Wall
# Enable OpenMP by calling: make OPENMP=1
ifeq ($(OPENMP),1)
CXXFLAGS += -fopenmp
endif

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
EXEC := mes

.PHONY: all clean run

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run: all
	./$(EXEC)

clean:
	-rm -f $(OBJS) $(EXEC)
