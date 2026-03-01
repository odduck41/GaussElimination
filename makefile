compiler = gcc #clang on macos
flags = -std=c23

main.out: main.c
	$(compiler) $(flags) main.c -o main.out
