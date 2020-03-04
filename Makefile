.PHONY: clean

CPP = g++
LD = g++

CPPFLAGS = -DNDEBUG -std=c++14 -O2 -Wall -pedantic -c

LDFLAGS =
LDLIBS =

SOURCES = monty_hall.cpp

OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = monty-hall

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@echo " [LD ] $@"
	@$(LD) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $@

%.o : %.cpp
	@echo " [CPP] $<"
	@$(CPP) $(CPPFLAGS) -o $@ $<

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
