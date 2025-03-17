#include <stdio.h>
#include "functions.h"



int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Using: %s <file_name>\n", argv[0]);
        return 1;
    }

    char* filename = argv[1];


    // Запись в файл
    inputfile(filename);
    printf("Result is recorded '%s'.\n", filename);

    // Чтение из файла
    outputfile(filename);

    // Подсчёт суммы цифр
    sum_numbers(filename);

    swap_spaces(filename);

    puts("Result:");
    outputfile(filename);



    
    return 0;
}
