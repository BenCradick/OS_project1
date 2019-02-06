//
// Created by Ben Cradick on 2019-02-05.
//

#ifndef CRADICK_1_STACK_H
#define CRADICK_1_STACK_H


struct Stack;

//Did this because I went down a rabbit hole, no real need but now I know how.
//Need to have the struct reference itself so that I don't need to pass the struct to itself every time.
typedef struct Stack {
    int size;
    int capacity;
    int* array;

    int isFullPtr;
    int isEmptyPtr;

    void(*push)(struct Stack*, int);
    int(*pop)(struct Stack*);
    int(*isEmpty)(struct Stack*);
    int(*isFull)(struct Stack*);


}Stack;


Stack createStack(Stack*, int);

#endif //CRADICK_1_STACK_H
