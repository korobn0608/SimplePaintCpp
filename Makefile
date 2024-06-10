all:
	g++ -o main paint.cpp -I src/include -L src/lib -lmingw32 -lSDL2main -lSDL2

