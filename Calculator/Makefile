.PHONY: all debug release clean

Compiler = g++
RELEASE_FLAGS = -O2 -Wall -DNDEBUG -Iheaders
DEBUG_FLAGS   = -g -O0 -Wall -Iheaders
RELEASE_EXEC  = Calculator
DEBUG_EXEC    = Calculator-dbg
SOURCES       = main.cpp Calc.cpp

all: debug release

debug: $(DEBUG_EXEC)

$(DEBUG_EXEC): $(SOURCES)
	$(Compiler) $(DEBUG_FLAGS) $(SOURCES) -o $(DEBUG_EXEC)

release: $(RELEASE_EXEC)

$(RELEASE_EXEC): $(SOURCES)
	$(Compiler) $(RELEASE_FLAGS) $(SOURCES) -o $(RELEASE_EXEC)

clean:
	rm -f $(RELEASE_EXEC) $(DEBUG_EXEC)
