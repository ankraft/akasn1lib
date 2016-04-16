
# source directories and files
SRCDIR = src
OBJDIR = obj
BINDIR = bin
DOCDIR = doc
TESTDIR = test
INSTALLROOT = /usr/local

DEPS =  $(SRCDIR)/akasn1.h

OUT    = $(BINDIR)/libakasn1lib.a


C_FILES   := $(wildcard $(SRCDIR)/*.c)
OBJ_FILES := $(addprefix $(OBJDIR)/,$(notdir $(C_FILES:.c=.o)))
 
# C++ compiler, flags
CC = gcc
CFLAGS = -g -O2 -Wall
INCLUDES = -I./src  -I/usr/local/include
 
# Linker paths, flags
LIBS = -L../ -L/usr/local/lib -lm
LDFLAGS = -g

# Other commands
MKDIR_P = mkdir -p
RMDIR   = rmdir
DOCGEN	= doxygen Doxyfile
 
.SUFFIXES: .c
.PHONY: clean directories install
 

default: directories $(OUT) documentation
 
.c.o: 
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

$(OBJ_FILES): $(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@
 
$(OUT): $(OBJ_FILES)
	ar rcs $(OUT) $(OBJ_FILES)

# Install

install: $(OUT)
	cp $(OUT) $(INSTALLROOT)/lib
	cp $(DEPS) $(INSTALLROOT)/include

# Clean

clean:
	-rm -f $(OBJ_FILES) $(OUT)
	-rm -r ${DOCDIR}
	-rm ${TESTDIR}/a.out
	-${RMDIR} $(OBJDIR) $(BINDIR)

# Documentation
documentation:
	${DOCGEN}


# Create directories

directories: ${OBJDIR} ${BINDIR} ${DOCDIR}

${OBJDIR}:
	${MKDIR_P} ${OBJDIR}

${BINDIR}:
	${MKDIR_P} ${BINDIR}

${DOCDIR}:
	${MKDIR_P} ${DOCDIR}
