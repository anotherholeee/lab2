#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

#define MAX_WORDS 100
#define MAX_WORD_LEN 50

void write_to_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("ошибка открытия файла");
        return;
    }

    printf("введите слова (через пробел, окончание ввода - enter):\n");
    char word[MAX_WORD_LEN];
    while (scanf("%s", word) == 1) {
        fprintf(file, "%s ", word);
        if (getchar() == '\n') break;
    }

    fclose(file);
}

void read_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("ошибка открытия файла");
        return;
    }

    printf("содержимое файла:\n");
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    printf("\n");

    fclose(file);
}

void find_min_word(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("ошибка открытия файла");
        return;
    }

    char word[MAX_WORD_LEN], min_word[MAX_WORD_LEN];
    int first = 1;

    while (fscanf(file, "%s", word) == 1) {
        if (first || strlen(word) < strlen(min_word)) {
            strcpy(min_word, word);
            first = 0;
        }
    }

    fclose(file);

    if (!first) {
        printf("минимальное слово: %s\n", min_word);
    } else {
        printf("файл пуст.\n");
    }
}

void swap_first_two_words(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("ошибка открытия файла");
        return;
    }

    char words[MAX_WORDS][MAX_WORD_LEN];
    int count = 0;

    while (count < MAX_WORDS && fscanf(file, "%s", words[count]) == 1) {
        count++;
    }
    fclose(file);

    if (count < 2) {
        printf("в файле недостаточно слов для замены.\n");
        return;
    }


    char temp[MAX_WORD_LEN];
    strcpy(temp, words[0]);
    strcpy(words[0], words[1]);
    strcpy(words[1], temp);


    file = fopen(filename, "w");
    if (!file) {
        perror("ошибка открытия файла");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s ", words[i]);
    }

    fclose(file);
}