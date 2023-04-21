CC		= gcc
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -lSDL -lSDL_image -lGLU -lGL -lm

BINDIR	= bin/
SRCDIR	= src/
OBJDIR	= obj/

# Fichiers TD 05

# Fichiers exercice 01a
OBJ_TD05_EX01a= ex01a/td05_ex01a.o
EXEC_TD05_EX01a= td05_ex01a.out

# Fichiers exercice 01b
OBJ_TD05_EX01b= ex01b/td05_ex01b.o
EXEC_TD05_EX01b= td05_ex01b.out

# Fichiers exercice 02
OBJ_TD05_EX02= ex02/td05_ex02.o
EXEC_TD05_EX02= td05_ex02.out


# Regles compilation TD 05

all : ex01a

ex01a : $(OBJDIR)$(OBJ_TD05_EX01a)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_TD05_EX01a) -o $(BINDIR)$(EXEC_TD05_EX01a) $(LDFLAGS)

ex01b : $(OBJDIR)$(OBJ_TD05_EX01b)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_TD05_EX01b) -o $(BINDIR)$(EXEC_TD05_EX01b) $(LDFLAGS)

ex02 : $(OBJDIR)$(OBJ_TD05_EX02)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_TD05_EX02) -o $(BINDIR)$(EXEC_TD05_EX02) $(LDFLAGS)


clean :
	rm -rf *~
	rm -rf $(SRCDIR)*/*~
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)*

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p `dirname $@`
	$(CC) -o $@ -c $< $(CFLAGS)
