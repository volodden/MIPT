#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include "list.h"

#define MY_CONST                                13
#define MAX_HASH_TABLE                          17
#define SUCCESS_HASHTABLE_CREATED               0
#define ERROR_HASHTABLE_NOT_CREATED             1
#define SUCCESS_HASHKEY_CREATED                 0
#define ERROR_HASHKEY_NOT_CREATED               1
#define SUCCESS_ADD_ELEMENT                     0
#define ERROR_ADD_ELEMENT                       1
#define SUCCESS_FIND_ELEMENT                    0
#define ERROR_FIND_ELEMENT                      1
#define NO_ELEMENT_FIND                         2
#define SUCCESS_DELETE_ELEMENT                  0
#define ERROR_DELETE_ELEMENT                    1
#define NO_ELEMENT_DELETE                       2

struct HT
{
    struct myList** hshtbl;
    int CP;
    int SZ;
};

int hashkey(char* nkey, int* skey, int CP);
struct HT* createHashTable(int* t);
int addElementInHashTable(struct HT* newHT, char* key, char* val);
int findElementInHashTable(struct HT* newHT, char* key, char** val);
int deleteElementInHashTable(struct HT* newHT, char* s);
void deleteHashTable(struct HT* newHT);

#endif // HASHTABLE_H_INCLUDED

