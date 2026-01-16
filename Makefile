CFLAGS = -Os -march=native -static

app: main.c
	gcc $(CFLAGS) Main/3drender.c Main/Console.c main.c -o app

clean:
	rm -f app