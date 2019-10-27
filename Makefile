CC := g++
# CC := clang --analyze
SRCDIR := src
BUILDDIR := build
BINDIR := bin
TARGET := bin/Simulador

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
TEST_SOURCES := $(shell find $(SRCDIR) -type f -name Camada*.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
TEST_OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(TEST_SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -Wall
LIB := -I lib
INC := -I include

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BINDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)
	@echo " $(RM) -r $(BUILDDIR) $(TEST_TARGET)"; $(RM) -r $(BUILDDIR) bin/tester

tester: $(TEST_OBJECTS)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ test/tester.cpp $(INC) $(LIB) -o bin/tester

.PHONY: clean
