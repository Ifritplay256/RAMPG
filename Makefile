CFLAGS = -Wall -O3 -march=native

app: main.c
	gcc $(CFLAGS) main.c -o app

clean:
	rm -f app