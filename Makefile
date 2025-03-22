all:
	g++ -I sdl/include -L sdl/lib -o main src/main.cpp -lmingw32 -lSDL3_test -lSDL3 -lSDL3_ttf -lSDL3_image