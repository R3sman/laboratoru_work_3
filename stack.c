


#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "sort.h"
#include "operations.h"

Stack* create_stack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        return NULL;
    }
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

void push(Stack* stack, int value) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        return;
    }
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

int pop(Stack* stack) {
    if (is_empty(stack)) {
        return -1; // Или другое значение ошибки
    }
    StackNode* temp = stack->top;
    int value = temp->data;
    stack->top = temp->next;
    free(temp);
    stack->size--;
    return value;
}

int is_empty(Stack* stack) {
    return stack->top == NULL;
}

void clear_stack(Stack* stack) {
    while (!is_empty(stack)) {
        pop(stack);
    }
}

void print_stack(Stack* stack) {
    if (is_empty(stack)) {
        printf("The stack is empty\n");
        return;
    }
    
    // Создаем временный стек для печати
    Stack* temp = create_stack();
    StackNode* current = stack->top;
    
    printf("Stack (top to bottom): ");
    while (current != NULL) {
        printf("%d ", current->data);
        push(temp, current->data);
        current = current->next;
    }
    printf("\n");
    
    clear_stack(temp);
    free(temp);
}

Stack* array_to_stack(int* arr, int n) {
    Stack* stack = create_stack();
    for (int i = n - 1; i >= 0; i--) {
        push(stack, arr[i]);
    }
    return stack;
}

int* stack_to_array(Stack* stack) {
    int* arr = (int*)malloc(stack->size * sizeof(int));
    if (arr == NULL) {
        return NULL;
    }
    
    StackNode* current = stack->top;
    int i = stack->size - 1;
    
    while (current != NULL && i >= 0) {
        arr[i] = current->data;
        current = current->next;
        i--;
    }
    
    return arr;
}