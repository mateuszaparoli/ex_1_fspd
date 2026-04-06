exec: obj/main.o
	cc -o exec obj/main.o

obj/main.o: src/main.c
	mkdir -p obj
	cc -c src/main.c -o obj/main.o

clean:
	rm exec obj/main.o
