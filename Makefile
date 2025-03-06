all:
	g++ -I SDL2/include -L SDL2/lib -o main src/main.c headers/grid.c \
	-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer
