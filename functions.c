#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

void inputfile(const char *filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error");
        exit(1);
    }
    printf("Enter symbols (Enter to stop):\n");
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { // Учитываем EOF
        if (fputc(ch, file) == EOF) {
            perror("Error");
            fclose(file);
            exit(1);
        }
    }
    fclose(file);
}

void outputfile(const char *filename) {
    int ch;
    FILE*  file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error");
        exit(1);
    }

    printf("File content '%s':\n", filename);
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    putchar('\n');
}


void sum_numbers(const char *filename) {
    FILE* file = fopen(filename, "r");
    int ch;
    int sum = 0;
    while ((ch = fgetc(file)) != EOF) { // Используем fgetc()
        if (ch >= '0' && ch <= '9') {
            sum += ch - '0';
        }
    }
    fclose(file);
    printf("Sum of all numbers: %d\n", sum);
}

void swap_spaces(const char *filename) {

    int ch;
    int count=0;
    int max_count=0;
    char current_num[256] = {0};
    char longest_num[256] = {0};

    FILE* file = fopen(filename, "r+");
    if (file == NULL) {
        perror("Error");
        exit(1);
    };
    while ((ch = fgetc(file)) != EOF) { // Чтение символов из файла
        if (ch >= '0' && ch <= '9') {   // Если символ - цифра
            current_num[count++] = ch;  // Добавляем цифру в текущее число
        } else {
            current_num[count] = '\0';  // Завершаем текущее число
            if (count > max_count) {   // Сравниваем длину числа
                max_count = count;
                strcpy(longest_num, current_num); // Сохраняем самое длинное число
            }
            count = 0; // Сбрасываем счётчик
        }
    }

    // Если файл заканчивается числом, проверяем последний случай
    current_num[count] = '\0';
    if (count > max_count) {
        strcpy(longest_num, current_num);
    }



    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size == 0) {
        fclose(file);
        return; // Файл пуст
    }

    char *buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL) {
        perror("malloc failed");
        fclose(file);
        exit(1);
    }

    size_t read_size = fread(buffer, 1, file_size, file);
    if (read_size != (size_t)file_size) {
        perror("fread failed");
        free(buffer);
        fclose(file);
        exit(1);
    }
    buffer[file_size] = '\0'; // Для безопасности

    int max_start = -1;
    int max_length = 0;
    int current_start = -1;
    int current_length = 0;

    for (int i = 0; i < file_size; i++) {
        if (isdigit((unsigned char)buffer[i])) {
            if (current_start == -1) {
                current_start = i;
                current_length = 1;
            } else {
                current_length++;
            }
        } else {
            if (current_start != -1) {
                if (current_length >= max_length) {
                    max_length = current_length;
                    max_start = current_start;
                }
                current_start = -1;
                current_length = 0;
            }
        }
    }

    // Проверяем последнее число
    if (current_start != -1) {
        if (current_length >= max_length) {
            max_length = current_length;
            max_start = current_start;
        }
    }

    if (max_length > 0) {
        // Заменяем символы пробелами
        for (int i = max_start; i < max_start + max_length; i++) {
            buffer[i] = ' ';
        }

        // Записываем изменения обратно в файл
        fseek(file, 0, SEEK_SET);
        fwrite(buffer, 1, file_size, file);
        // Убедимся, что данные записаны
        fflush(file);
    }

    free(buffer);
    fclose(file);


          // 72а723497с027о4230а

 printf("Longest digit number:%s\n", longest_num);
printf("Max digit number:%d\n", max_count);
printf("Max length num swap to spaces!");








}
