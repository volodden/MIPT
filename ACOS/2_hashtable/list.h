#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS_PUSH        0
#define ERROR_PUSH          1
#define SUCCESS_UNSHIFT     0
#define ERROR_UNSHIFT       1
#define SUCCESS_POP         0
#define ERROR_POP           1
#define SUCCESS_SHIFT       0
#define ERROR_SHIFT         1
#define SUCCESS_DELETE      0
#define ERROR_DELETE        1

struct dList
{
    char* key;
    char* val;
    struct dList* next;
    struct dList* prev;
};

struct myList
{
   int sz;
   struct dList* first;
   struct dList* last;
};

struct myList* newList();
int push(struct myList* q, char* a, char* b);
int unshift(struct myList* q, char* a, char* b);
int pop(struct myList* q, char** a);
int shift(struct myList* q, char** a);
void sizeoflist(struct myList* q, int* a);
void clearList(struct myList* q);
int deleteElement(struct myList* q, struct dList* a);

#endif // LIST_H_INCLUDED
