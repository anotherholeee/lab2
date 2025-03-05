
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <windows.h>
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("использование: %s <имя файла>\n", argv[0]);
        return 1;
    }
    SetConsoleOutputCP(CP_UTF8);
    const char *filename = argv[1];

    write_to_file(filename);
    read_from_file(filename);
    find_min_word(filename);
    swap_first_two_words(filename);
    read_from_file(filename);

    return 0;
}
