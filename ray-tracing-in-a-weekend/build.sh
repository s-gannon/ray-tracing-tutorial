#clang -g -Wall -pedantic -o main main.c `sdl2-config --cflags --libs`
clang -g -Wall -pedantic -o main main.c pnm.c
