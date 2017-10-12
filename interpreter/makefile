CC = gcc

SRCDIR = src
SRCEXT = c
BUILDDIR = build

TARGET = bin/wRinterp
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

CFLAGS = -g -Wall -ansi -pedantic
HEAD = -Iinclude

$(TARGET): $(OBJECTS)
	@echo "$(CC) $^ -o $(TARGET) $(LIB_LOOK) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB_LOOK) $(LIB);
	
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo "$(CC) $(CFLAGS) $(INC) $(HEAD) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) $(HEAD) -c -o $@ $<

clean:
	@echo "$(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)
