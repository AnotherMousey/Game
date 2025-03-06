CXX = gcc
CFLAGS = -g -IC:/SDL2/include
LDFLAGS = -LC:/SDL2/lib -lmingw32 -lSDL2main -lSDL2

PROG = grid_app

SRCDIR = src
OBJDIR = obj
HEADERDIR = headers

SRCS = $(HEADERDIR)/grid.c $(SRCDIR)/main.c
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
OBJS := $(patsubst $(HEADERDIR)/%.c, $(OBJDIR)/%.o, $(OBJS))

# Ensure obj directory exists before compilation
$(shell mkdir -p $(OBJDIR))

all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $(PROG) $(LDFLAGS)

# Compilation rule for source files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CXX) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@

$(OBJDIR)/%.o: $(HEADERDIR)/%.c
	$(CXX) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@

clean:
	rm -f $(PROG) $(OBJDIR)/*.o
