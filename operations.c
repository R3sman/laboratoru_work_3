


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "stack.h"
#include "sort.h"
#include "operations.h"

int* read_array_from_file(const char* filename, int* n) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("File opening error: %s\n", filename);
        *n = 0;
        return NULL;
    }
    
    // Считаем количество чисел
    int count = 0;
    int temp;
    while (fscanf(file, "%d", &temp) == 1) {
        count++;
    }
    
    rewind(file);
    
    int* arr = (int*)malloc(count * sizeof(int));
    if (arr == NULL) {
        fclose(file);
        *n = 0;
        return NULL;
    }
    
    for (int i = 0; i < count; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    
    fclose(file);
    *n = count;
    return arr;
}

void write_array_to_file(const char* filename, int* arr, int n) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("File creation error: %s\n", filename);
        return;
    }
    
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", arr[i]);
    }
    
    fclose(file);
    printf("The array is written to a file: %s\n", filename);
}

void save_previous_run(int* arr, int n) {
    FILE* file = fopen("previous_run.txt", "w");
    if (file == NULL) {
        printf("Error saving the previous launch\n");
        return;
    }
    
    fprintf(file, "%d\n", n);
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", arr[i]);
    }
    
    fclose(file);
}

int* load_previous_run(int* n) {
    FILE* file = fopen("previous_run.txt", "r");
    if (file == NULL) {
        *n = 0;
        return NULL;
    }
    
    fscanf(file, "%d", n);
    int* arr = (int*)malloc(*n * sizeof(int));
    
    for (int i = 0; i < *n; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    
    fclose(file);
    return arr;
}

void generate_test_files() {
    srand(time(NULL));
    
    int sizes[] = {100, 500, 1000, 5000, 10000, 50000, 100000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    for (int i = 0; i < num_sizes; i++) {
        char filename[50];
        sprintf(filename, "test_files/test_%d.txt", sizes[i]);
        
        FILE* file = fopen(filename, "w");
        if (file == NULL) {
            printf("Failed to create a file: %s\n", filename);
            continue;
        }
        
        for (int j = 0; j < sizes[i]; j++) {
            fprintf(file, "%d ", rand() % 10000);
        }
        
        fclose(file);
    }
}