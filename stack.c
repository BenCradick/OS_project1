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
Stack *createStack( Stack* stack, int capacity){
    stack =  (Stack*)malloc(sizeof(struct Stack_t));
    stack->capacity = capacity;
    stack-> size = -1;
    stack-> array = (int*)malloc(stack->capacity * sizeof(int));
    stack->isFullPtr = isFull(stack);
    stack->isEmptyPtr = isEmpty(stack);
    stack->pushPtr = push;


    return stack;

}
int isFull(Stack* self){
    return self->size == self->capacity -1;
}

int isEmpty(Stack* stack){

    return stack->size == -1;
}

void push(Stack* stack, int number){
    if(isFull(stack)){
        fprintf(stderr, "process %d : Attempt to push element into full stack.\n", getpid());
        return ;
    }
    stack->size++;
    printf("%d\n", stack->size);
    stack->array[stack->size] = number;

}
int pop(Stack* stack){
    if(isEmpty(stack)){
        fprintf(stderr,"process %d : Attempt to pop element off empty stack.\n", getpid());
        return INT_MIN;
    }
    stack->size--;
    printf("%d\n", stack->size);
    return stack->array[stack->size];
}