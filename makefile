CC = g++
FLAGS = -c -std=c++11 -g
DEPS = header.h
# add all new files
OBJ = main.o Gauss.o durchmesser.o ausgabe.o read.o newt2.o
EXECUTABLE = exec
SOURCES = Gauss.cpp ausgabe.cpp read.cpp newt.cpp main.cpp minimum.cpp gesamtkosten.cpp compare.cpp #test.cpp#$(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SOURCES))
BUILDDIR = obj

all: $(BUILDDIR)/$(EXECUTABLE)

dir:
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@

test.o : test.cpp $(DEPS) tests.h
	$(CC) $(FLAGS) $< -o $@

$(OBJECTS): $(BUILDDIR)/%.o: %.cpp $(DEPS)
	$(CC) $(FLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(BUILDDIR)/exec $(BUILDDIR)/*.o