


#ifndef STACK_H
#define STACK_H

typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
    int size;
} Stack;

Stack* create_stack();
void push(Stack* stack, int value);
int pop(Stack* stack);
int is_empty(Stack* stack);
void clear_stack(Stack* stack);
void print_stack(Stack* stack);
Stack* array_to_stack(int* arr, int n);
int* stack_to_array(Stack* stack);

#endif