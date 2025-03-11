# Compiler and flags
CC = g++
CFLAGS = -I headers -I SDL2/include -Dmain=SDL_main
LDFLAGS = -L SDL2/lib
LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# Find all .c files in src/ and headers/
SRC = $(wildcard src/*.c) $(wildcard headers/*.c)
OBJ = $(SRC:.c=.o)

# Build target
all: main.exe

main.exe: $(OBJ)
	$(CC) $(OBJ) -o main.exe $(LDFLAGS) $(LIBS)

# Compile .c files into .o
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Clean generated files (Windows-friendly)
clean:
	del /Q src\*.o headers\*.o main.exe 2>nul || echo "No files to delete"
