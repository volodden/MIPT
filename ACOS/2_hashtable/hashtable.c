#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"

int hashkey (char* nkey, int* skey, int CP)
{
    int tkey = 0;
    char* key = malloc((strlen(nkey) + 1) * sizeof(char*));
    if (key == NULL)
    {
        return ERROR_HASHKEY_NOT_CREATED;
    }
    strcpy(key, nkey);
    while (strlen(key))
    {
        char c = key[strlen(key)-1];
        key[strlen(key)-1] = '\0';
        tkey += ((int)c) * MY_CONST;
        tkey = ((tkey >= 0) ? tkey : -tkey);
    }
    while (tkey >= CP)
    {
        tkey %= CP;
    }

    (*skey) = tkey;
//    printf("HASHKEY: %5d CP: %2d KEY: %s\n", tkey, CP, nkey);
	free(key);
//	printf("malloc and free in hashkey\n");
    return SUCCESS_HASHKEY_CREATED;
}

struct HT* createHashTable(int *t)
{
//	printf("---CREATE HASHTABLE---\n");
    struct HT* newHT = (struct HT*) malloc(sizeof(struct HT));
    if (newHT == NULL)
    {
        *t = ERROR_HASHTABLE_NOT_CREATED;
        return NULL;
    }
    newHT->SZ = 0;
    newHT->CP = MAX_HASH_TABLE;
    newHT->hshtbl = (struct myList**) malloc(newHT->CP * sizeof(struct myList*));
    if (newHT->hshtbl == NULL)
    {
        *t = ERROR_HASHTABLE_NOT_CREATED;
        return NULL;
    }
//	printf("2 malloc in createHashTable: hashtable and table\n");
    int i = 0;
    for (i = 0; i < newHT->CP; ++i)
    {
        newHT->hshtbl[i] = newList();
        if (newHT->hshtbl[i] == NULL)
        {
            return NULL;
        }
    }
    *t = SUCCESS_HASHTABLE_CREATED;
//	printf("---END CREATED HASH TABLE---\n"); 
    return newHT;
}

int addElementInHashTable(struct HT* newHT, char* key, char* val)
{
//	printf("---ADD ELEMENT---\n");
    int skey = 0;
//	printf("1CP = %d\n", newHT->CP);
    if (newHT->SZ * 2 > newHT->CP)
    {
        char** masKEY = (char**) malloc(newHT->SZ * sizeof(char*));
        if (masKEY == NULL)
        {
            return ERROR_ADD_ELEMENT;
        }
        char** masVAL = (char**) malloc(newHT->SZ * sizeof(char*));
        if (masVAL == NULL)
        {
            return ERROR_ADD_ELEMENT;
        }
        int j = 0;
        int k = -1;
        for (j = 0; j < newHT->CP; ++j)
	{
//	printf("j = %d\n", j);
            while(newHT->hshtbl[j]->sz != 0)
            {
                ++k;
                masKEY[k] = (char*) malloc((strlen(newHT->hshtbl[j]->last->key) + 1) * sizeof(char));
                if (masKEY[k] == NULL)
                {
                    return ERROR_ADD_ELEMENT;
                }
//	printf("k = %d\n", k);
//	printf("%s\n", newHT->hshtbl[j]->last->key);
                strcpy(masKEY[k], newHT->hshtbl[j]->last->key);
  //              printf("strcpy\n");
		if (pop(newHT->hshtbl[j], &(masVAL[k])) != 0)
                {
                    return ERROR_ADD_ELEMENT;
                }
//	printf("end while\n");
            }
        }
        if (k+1 != newHT->SZ)
        {
            return ERROR_ADD_ELEMENT;
        }
	for (j = 0; j < newHT->CP; ++j)
	{
	    clearList(newHT->hshtbl[j]);
	    free(newHT->hshtbl[j]);
	}
	free(newHT->hshtbl);
        newHT->CP *= 4;
	newHT->hshtbl = (struct myList**) malloc(newHT->CP * sizeof(struct myList*));
	if (newHT->hshtbl == NULL)
	{
		return ERROR_ADD_ELEMENT;
	}
	for (j = 0; j < newHT->CP; ++j)
	{
		newHT->hshtbl[j] = newList();
		if (newHT->hshtbl[j] == NULL)
		{
			return ERROR_ADD_ELEMENT;
		}	
	}
	newHT->SZ = 0;
        for (j = 0; j <= k; ++j)
        {
            if (addElementInHashTable(newHT, masKEY[j], masVAL[j]) != 0)
            {
                return ERROR_ADD_ELEMENT;
            }
	   free(masKEY[j]);
	   free(masVAL[j]);
        }
	free(masKEY);
	free(masVAL);
    }

    newHT->SZ += 1;
    int t = hashkey(key, &skey, newHT->CP);
    if (t)
    {
        return ERROR_ADD_ELEMENT;
    }
    t = push(newHT->hshtbl[skey], key, val);
    if (t)
    {
        return ERROR_ADD_ELEMENT;
    }
//	printf("SIZE: %d\n",newHT->SZ);
//	printf("CP2 = %2d\n", newHT->CP);
//	printf("---END ADD ELEMENT---\n");
    return SUCCESS_ADD_ELEMENT;
}

int findElementInHashTable(struct HT* newHT, char* key, char** val)
{
//	printf("---FIND ELEMEMT---\n");
    int skey = 0;
    int t = hashkey(key, &skey, newHT->CP);
    if (t)
    {
        return ERROR_FIND_ELEMENT;
    }
    if (newHT->hshtbl[skey]->sz == 0)
    {
        return NO_ELEMENT_FIND;
    }
    int i = 0;
    if (*val != NULL)
    {
        free(*val);
    }
    *val = 0;

    struct dList* fd = newHT->hshtbl[skey]->first;
    if (strcmp(key, fd->key) == 0)
    {
        *val = (char*) malloc((strlen(fd->val) + 1) * sizeof(char));
        if (*val == NULL)
        {
            return ERROR_FIND_ELEMENT;
        }
//	printf("1 malloc in findElement: val\n");
        strcpy(*val, fd->val);
//	printf("11 FOUND: %s\n", fd->val);
//	printf("12 FOUND: %s\n", *val);
//	printf("---END FIND ELEMENT---\n");
        return SUCCESS_FIND_ELEMENT;
    }

    while(fd->next != 0)
    {
        fd = fd->next;
        if (strcmp(key, fd->key) == 0)
        {
            *val = (char*) malloc((strlen(fd->val) + 1) * sizeof(char));
            if (*val == NULL)
            {
                return ERROR_FIND_ELEMENT;
            }
//		printf("1 malloc in findElement: val\n");
            strcpy(*val, fd->val);
//		printf("21: %s\n", fd->val);
//		printf("22: %s\n", *val);
//		printf("---END FIND ELEMENT---\n");
            return SUCCESS_FIND_ELEMENT;
        }
    }
    return NO_ELEMENT_FIND;
}

int deleteElementInHashTable(struct HT* newHT, char* key)
{
//	printf("---DELETE ELEMENT---\n");
    int skey = 0;
    int t = hashkey(key, &skey, newHT->CP);
    if ((t != 0) || (newHT->SZ == 0))
    {
        return ERROR_DELETE_ELEMENT;
    }
    if (newHT->hshtbl[skey]->sz == 0)
    {
        return NO_ELEMENT_DELETE;
    }

    int i = 0;

    struct dList* fd = newHT->hshtbl[skey]->first;
    if (strcmp(key, fd->key) == 0)
    {
        char* temp = 0;
        if (shift(newHT->hshtbl[skey], &temp))
        {
            return ERROR_DELETE_ELEMENT;
        }
	free(temp);
//	printf("1 free in deleteElement: val\n");
        newHT->SZ -= 1;
//	printf("---END DELETE ELEMENT---\n");
        return SUCCESS_DELETE_ELEMENT;
    }

    while(fd->next != 0)
    {
        fd = fd->next;
        if (strcmp(key, fd->key) == 0)
        {
            if (deleteElement(newHT->hshtbl[skey], fd))
            {
                return ERROR_DELETE_ELEMENT;
            }
            newHT->SZ -= 1;
//		printf("---END DELETE ELEMENT---\n");
            return SUCCESS_DELETE_ELEMENT;
        }
    }
    return ERROR_DELETE_ELEMENT;
}

void deleteHashTable(struct HT* newHT)
{
//	printf("---DELETE TABLE---\n");
    int i = 0;
    for (i = newHT->CP - 1; i >= 0; --i)
    {
        clearList(newHT->hshtbl[i]);
        free(newHT->hshtbl[i]);
//	printf("1 free in deleteHashTable: list\n");
    }
//	printf("1 free in deleteHashTable: table\n");
    free(newHT->hshtbl);
//	printf("---END DELETE TABLE---\n");
}
