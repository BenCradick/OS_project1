//
// Created by Ben Cradick on 2019-02-05.
//

#ifndef CRADICK_1_STACK_H
#define CRADICK_1_STACK_H


struct Stack_t;

//int (*isFullPtr)();
//int (*isEmptyPtr)();
typedef struct Stack {
    int size;
    int capacity;
    int* array;

    int isFullPtr;
    int isEmptyPtr;

    int(*push)(struct Stack*, int);
    int(*pop)(struct Stack*);
    int(*isEmpty)(struct Stack*);
    int(*isFull)(struct Stack*);

}Stack;


Stack* createStack(Stack*, int);
//int isFull(Stack*);
//int isEmpty(Stack*);
//void push(Stack*, int);
int pop(Stack*);

#endif //CRADICK_1_STACK_H
