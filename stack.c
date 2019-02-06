//
// Created by Ben Cradick on 2019-02-05.
//

#include "stack.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>


int isFull(Stack*);
int isEmpty(Stack*);
void push(Stack*, int);
int pop(Stack*);

//needs to somehow get moved inside itself.
Stack createStack( Stack* stack, int capacity){
    stack =  (Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack-> size = -1;
    stack-> array = (int*)malloc(stack->capacity * sizeof(int));

    //pointers to the relevant functions that are found in this source file.
    stack->isFull = &isFull;
    stack->isEmpty = &isEmpty;
    stack->push = &push;
    stack->pop = &pop;


    return *stack;

}
int isFull(Stack* self){
    return self->size == self->capacity;
}

int isEmpty(Stack* stack){

    return stack->size == -1;
}

void push(Stack* stack, int number){
    printf("%d \n", number);
    if(isFull(stack)){
        fprintf(stderr, "process %d : Attempt to push element into full stack.\n", getpid());
        printf("size: %d capacity: %d to be pushed: %d \n", stack->size, stack->capacity, number);
        abort();

    }
    stack->size++;
    stack->array[stack->size] = number;

}
int pop(Stack* stack){
    if(isEmpty(stack) == 1){
        fprintf(stderr,"process %d : Attempt to pop element off empty stack.\n", getpid());
        return INT_MIN;
    }
    printf("%d \n", stack->size);
    return stack->array[stack->size--];
}