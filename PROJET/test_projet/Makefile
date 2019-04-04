# project name (generate executable with this name)
TARGET   = test_salle

CC       = gcc
# compiling flags here
CFLAGS   = -std=c99 -Wall -I.

LINKER   = gcc
# linking flags here
LFLAGS   = -Wall -I. -lm -lncurses

# change these to proper directories where each file should be
SRCDIR   = ../Projet/src
OBJDIR   = obj
BINDIR   = bin
TEST_DIR = ../

DIRS	 = $(OBJDIR) $(BINDIR)

.PHONY: DIRS
all: $(DIRS) $(BINDIR)/$(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)
$(BINDIR):
	mkdir -p $(BINDIR)

SOURCES := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)

rm       = rm -f
SRC := $(filter-out($(SRCDIR)/jeu.c ,$(SOURCES)) test_salle.c
#SRC = projectile.c montre.c joueur.c coordonnees.c salle.c map.c liste_ptr.c test_salle.c


OBJECTS  := $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
#OBJETS :=$(substr .c,.o,$(SRC))
#OBJETS :=$(substr src,obj, $(OBJETS))

$(BINDIR)/$(TARGET): $(OBJECTS) test_salle.o
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"

test_salle.o : test_salle.c
	@$(LINKER) -c $< $(LFLAGS) -o $@

$(OBJECTS): $(OBJDIR)/%.o : $(SRC)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
