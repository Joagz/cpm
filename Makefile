# Compiler to use
CC		= gcc

CFLAGS	= -Wall -D_FORTIFY_SOURCE=2 -Werror=implicit-function-declaration

BINS	= main.o

MAIN 	= c-project-manager

ROOT	= ./libs

# ============= GENERIC ACTIONS (BETTER KEEP) =============

all: $(MAIN)

$(MAIN): $(BINS)
	$(CC) $(CFLAGS) -o $(MAIN) $(BINS)

%.o: $(ROOT)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean: 
	rm -f $(BINS) $(MAIN)


