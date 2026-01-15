


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "stack.h"
#include "sort.h"
#include "operations.h"

#define MAX_INPUT_SIZE 1000
#define PREVIOUS_RUN_FILE "previous_run.txt"

void print_menu() {
    printf("1. Enter numbers from the keyboard\n");
    printf("2. Take numbers from a file\n");
    printf("3. Generate test files\n");
    printf("4. Compare sorting methods\n");
    printf("5. End the program execution\n");
}

void process_user_input() {
    Stack* stack = create_stack();
    char input[100];
    int num;
    
    printf("Enter the numbers separated by a space (enter 'end' to complete):\n");
    
    while (1) {
        if (scanf("%s", input) != 1) {
            break;
        }
        
        if (strcmp(input, "end") == 0) {
            break;
        }
        
        if (sscanf(input, "%d", &num) == 1) {
            push(stack, num);
        }
    }
    
    // Сохраняем предыдущий запуск
    int* arr = stack_to_array(stack);
    save_previous_run(arr, stack->size);
    
    // Сортируем и сохраняем
    printf("\nSource stack:\n");
    print_stack(stack);
    
    insertion_sort(arr, stack->size);
    printf("\nSorted array (direct inclusion):\n");
    for (int i = 0; i < stack->size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    write_array_to_file("sorted_array.txt", arr, stack->size);
    
    free(arr);
    clear_stack(stack);
    free(stack);
}

void compare_sorting_methods() {
    
    int sizes[] = {100, 500, 1000, 5000, 10000, 50000, 100000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    printf("Size | Direct Inclusion (sec) | Merge (sec) | Acceleration\n");
        
    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int* arr = malloc(n * sizeof(int));
        
        // Генерируем случайные числа
        srand(time(NULL));
        for (int j = 0; j < n; j++) {
            arr[j] = rand() % 10000;
        }
        
        // Копируем массив для второго метода
        int* arr_copy = malloc(n * sizeof(int));
        memcpy(arr_copy, arr, n * sizeof(int));
        
        // Измеряем время для insertion sort
        clock_t start = clock();
        insertion_sort(arr, n);
        clock_t end = clock();
        double insertion_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        // Измеряем время для merge sort
        start = clock();
        merge_sort(arr_copy, 0, n - 1);
        end = clock();
        double merge_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        printf("%6d | %21.6f | %14.6f | %.2fx\n", 
               n, insertion_time, merge_time, insertion_time / merge_time);
        
        free(arr);
        free(arr_copy);
    }
}

int main(int argc, char* argv[]) {
    // Обработка аргумента командной строки --file
    if (argc == 3 && strcmp(argv[1], "--file") == 0) {
        int n;
        int* previous = load_previous_run(&n);
        
        if (previous != NULL) {
            printf("Previous row: ");
            for (int i = 0; i < n; i++) {
                printf("%d ", previous[i]);
            }
            printf("\n");
            
            insertion_sort(previous, n);
            printf("Sorted row: ");
            for (int i = 0; i < n; i++) {
                printf("%d ", previous[i]);
            }
            printf("\n");
            
            free(previous);
        } else {
            printf("The previous launch was not found.\n");
        }
        
        return 0;
    }
    
    // Основной интерактивный режим
    int repeat = 1;
    char buffer[10];
    
    while (repeat) {
        print_menu();
        
        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("Incorrect input.\n");
            while (getchar() != '\n'); // Очистка буфера
            continue;
        }
        
        switch (choice) {
            case 1:
                process_user_input();
                break;
                
            case 2:
                {
                    char filename[100];
                    printf("Enter the file name: ");
                    scanf("%s", filename);
                    
                    int n;
                    int* arr = read_array_from_file(filename, &n);
                    
                    if (arr != NULL) {
                        Stack* stack = array_to_stack(arr, n);
                        printf("Stack from a file:\n");
                        print_stack(stack);
                        
                        insertion_sort(arr, n);
                        write_array_to_file("sorted_from_file.txt", arr, n);
                        
                        free(arr);
                        clear_stack(stack);
                        free(stack);
                    }
                }
                break;
                
            case 3:
                generate_test_files();
                printf("The test files are generated in the folder test_files/\n");
                break;
                
            case 4:
                compare_sorting_methods();
                break;
                
            case 5:
                repeat = 0;
                break;
                
            default:
                printf("Wrong choice. Try again.\n");
        }
        
        if (repeat && choice != 5) {
            printf("\nPress Enter to continue \n");
            getchar();
            getchar();
        }
    }
    
    return 0;
}
