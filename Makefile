all: Lwf

Lwf: lwf.c
	gcc lwf.c -o Lwf

clean:
	rm Lwf