#include <stdio.h>
#include "Console.h"

#define W 80
#define H 24

#include <unistd.h>

void print_mem_usage() {
    FILE* fp = fopen("/proc/self/statm", "r");
    if (fp) {
        long size, resident, share, text, lib, data, dt;
        if (fscanf(fp, "%ld %ld %ld %ld %ld %ld %ld",
            &size, &resident, &share, &text, &lib, &data, &dt) == 7) 
        {
            printf("Физическая память (RSS): %ld байт\n", resident * 4096);
        }
        fclose(fp);
    }
}


char symbols[W * H * 20 + H + 1];

char* write_int(char* ptr, int value) {
    *ptr++ = (value / 100) + '0';
    *ptr++ = ((value / 10) % 10) + '0';
    *ptr++ = (value % 10) + '0';
    return ptr;
}

char* printchar(char *ptr, char character, int R, int G, int B){
    
    *ptr++ = 27;
    *ptr++ = '[';
    *ptr++ = '3';
    *ptr++ = '8';
    *ptr++ = ';';
    *ptr++ = '2';
    *ptr++ = ';';

    ptr = write_int(ptr, R);

    *ptr++ = ';';

    ptr = write_int(ptr, G);

    *ptr++ = ';';

    ptr = write_int(ptr, B);

    *ptr++ = 'm';

    *ptr++ = character;

    return ptr;
}

void set_char(int x, int y, char char_, int R, int G, int B){
    char *ptr = symbols + (y * (W * 20 + 1) + x * 20);
    printchar(ptr, char_, R, G, B);
}

void render_console(){
    printf("\033[H");

    char *ptr = symbols;

    for (int y = 0; y < H; y++){
        for (int x = 0; x < W; x++){
            ptr = printchar(ptr, ' ', 100, 100, 100);
        }
        *ptr++ = '\n';
    }

    *ptr++ = '\0';
    fwrite(symbols, 1, sizeof(symbols), stdout);
    fflush(stdout);
    print_mem_usage();
}

void update_console(){
    printf("\033[H");
    fwrite(symbols, 1, sizeof(symbols), stdout);
    fflush(stdout);
    print_mem_usage();
}