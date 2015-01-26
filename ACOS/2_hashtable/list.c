#include "list.h"
#include <string.h>

struct myList* newList()
{
    struct myList* q = (struct myList*) (malloc(sizeof(struct myList)));
    if (q == NULL)
    {
        return NULL;
    }
    q->sz = 0;
    struct dList* q1 = (struct dList*) (malloc(sizeof(struct dList)));
    if (q == NULL)
    {
        return NULL;
    }
//	printf("2 mallocs in newList\n");
    q1->key = 0;
    q1->val = 0;
    q1->val = '\0';
    q1->next = 0;
    q1->prev = 0;
    q->first = q1;
    q->last  = q1;
    return q;
}

int push(struct myList* q, char* a, char* b)
{
    q->sz += 1;
    if (q->sz == 1)
    {
        q->last->key = (char*) malloc((strlen(a) + 1) * sizeof(char));
        if (q->last->key == NULL)
        {
            return ERROR_PUSH;
        }
        q->last->val = (char*) malloc((strlen(b) + 1) * sizeof(char));
	if (q->last->val == NULL)
        {
            return ERROR_PUSH;
        }
//        printf("2 mallocs in push: key and val\n");
        strcpy(q->last->key, a);
        strcpy(q->last->val, b);
        return SUCCESS_PUSH;
    }
    else
    {
        struct dList* t = (struct dList*) (malloc(sizeof(struct dList)));
        if (t == NULL)
        {
            return ERROR_PUSH;
        }
        t->key = (char*) malloc((strlen(a) + 1) * sizeof(char));
        if (t->key == NULL)
        {
            return ERROR_PUSH;
        }
        t->val = (char*) malloc((strlen(b) + 1) * sizeof(char));
        if (t->val == NULL)
        {
            return ERROR_PUSH;
        }
//        printf("3 mallocs in push: list, key and val\n");
        strcpy(t->key, a);
        strcpy(t->val, b);
        t->prev = q->last;
        t->next = 0;
        q->last->next = t;
        q->last = t;
    }
    return SUCCESS_PUSH;
}

int unshift(struct myList* q, char* a, char* b)
{
    q->sz += 1;
    if (q->sz == 1)
    {
        q->first->key = (char*) malloc((strlen(a) + 1) * sizeof(char));
        if (q->first->key == NULL)
        {
            return ERROR_UNSHIFT;
        }
        q->first->val = (char*) malloc((strlen(b) + 1) * sizeof(char));
        if (q->first->val == NULL)
        {
            return ERROR_UNSHIFT;
        }
//        printf("2 mallocs in unshift: key and val\n");
        strcpy(q->first->key, a);
        strcpy(q->first->val, b);
        return SUCCESS_UNSHIFT;
    }
    else
    {
        struct dList* t = (struct dList*) (malloc(sizeof(struct dList)));
        if (t == NULL)
        {
            return ERROR_UNSHIFT;
        }
        t->key = (char*) malloc((strlen(a) + 1) * sizeof(char));
        if (t->key == NULL)
        {
            return ERROR_UNSHIFT;
        }
        t->val = (char*) malloc((strlen(b) + 1) * sizeof(char));
        if (t->val == NULL)
        {
            return ERROR_UNSHIFT;
        }
//        printf("3 mallocs in push: list, key and val\n");
        strcpy(t->val, a);
        strcpy(t->val, b);
        t->next = q->first;
        t->prev = 0;
        q->first->prev = t;
        q->first = t;
    }
    return SUCCESS_UNSHIFT;
}

int pop(struct myList* q, char** a)
{
    if (q->sz >= 1)
    {
        q->sz -= 1;
	if (*a != NULL)
	{	
	    free(*a);
	}
        *a = (char*) malloc((strlen(q->last->val) + 1) * sizeof(char));
        if (*a == NULL)
        {
            return ERROR_POP;
        }
//        printf("1 malloc in pop: val\n");
        strcpy(*a, q->last->val);
        free(q->last->val);
        free(q->last->key);
        if (q->sz > 0)
        {
            struct dList* t = q->last;
            q->last = q->last->prev;
            q->last->next = 0;
            free(t);
//            printf("3 frees in pop: list, key and val\n");
        }
        return SUCCESS_POP;
    }
    else
    {
        return ERROR_POP;
    }
}

int shift(struct myList* q, char** a)
{
    if (q->sz >= 1)
    {
        q->sz -= 1;
        if (*a != NULL)
	{
	    free(*a);
        }
	*a = (char*) malloc((strlen(q->first->val) + 1) * sizeof(char));
        if (*a == NULL)
        {
            return ERROR_SHIFT;
        }
//        printf("1 malloc in shift: val\n");
        strcpy(*a, q->first->val);
        free(q->first->val);
        free(q->first->key);
        if (q->sz > 0)
        {
            struct dList* t = q->first;
            q->first = q->first->next;
            q->first->prev = 0;
            free(t);
        }
//        printf("3 frees in shift: list, key and val\n");
        return SUCCESS_SHIFT;
    }
    else
    {
        return ERROR_SHIFT;
    }
}

void sizeoflist(struct myList* q, int* a)
{
    *a = q->sz;
}

int deleteElement(struct myList* q, struct dList* a)
{
    int b = 0;
    sizeoflist(q, &b);
    char* s = 0;
    if (b == 0)
    {
        return ERROR_DELETE;
    }
    if (b == 1)
    {
        free(q->first->key);
        free(q->first->val);
        q->sz = 0;
//        printf("2 frees in deleteElement: key and val");
        return SUCCESS_DELETE;
    }
    if (a == q->first)
    {
//    	printf("shift in deleteElement:\n");
        if (shift(q, &s))
        {
            return ERROR_DELETE;
        }
        else
        {
            return SUCCESS_DELETE;
        }
    }
    if (a == q->last)
    {
//    	printf("pop in deleteElement:\n");
        if (pop(q, &s))
        {
            return ERROR_DELETE;
        }
        else
        {
            return SUCCESS_DELETE;
        }
    }
    q->sz -= 1;
    a->prev->next = a->next;
    a->next->prev = a->prev;
    free(a->key);
    free(a->val);
    free(a);
//    printf("3 frees in deleteElement: list, key and val\n");
    return SUCCESS_DELETE;
}

void clearList(struct myList* q)
{
//	printf("clearList\n");
    if (q->sz > 1)
    {
        while (q->sz != 1)
        {
            q->sz -= 1;
            struct dList* t = q->first;
            free(t->key);
            free(t->val);
            q->first = q->first->next;
            q->first->prev = 0;
            free(t);
//            printf("3 frees in clearList: list, key and val\n");
        }
        free(q->first->key);
        free(q->first->val);
//        printf("2 frees in clearList: key and val\n");
        q->sz = 0;
    }
    if (q->sz == 1)
    {
      free(q->first->key);
      free(q->first->val);
//      printf("2 frees in clearlist: key and val\n");
    }
    free(q->first);
//	printf("1 free in clearList: list\n");
}
