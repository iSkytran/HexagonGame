CC=gcc
CFLAGS=-std=c99 -Wall -g
LDFLAGS=-lraylib -lopengl32 -lgdi32 -lwinmm

SRCDIR=src
OBJDIR=obj
BINDIR=bin

SOURCES:=$(wildcard $(SRCDIR)/*.c)
INCLUDES:=$(wildcard $(SRCDIR)/*.h)
OBJECTS:=$(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm=rm -r -f

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(CC) $(OBJECTS) -o $@ $(LFLAGS)
	@echo "Linking Complete"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" Successfully"

.PHONY: dirguard
dirguard:
	@mkdir obj
	@mkdir bin

.PHONY: clean
clean:
	@$(rm) $(OBJDIR)
	@echo "Cleanup Complete"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)
	@echo "Executable Removed"
