CFLAGS = -Os -march=native -static

app: main.c
	gcc $(CFLAGS) Main/Console.c main.c -o app

clean:
	rm -f app