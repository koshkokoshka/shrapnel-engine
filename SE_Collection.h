#ifndef SE_COLLECTION_H
#define SE_COLLECTION_H

#include "SE_System.h"

#define SE_COLLECTION_FLAGS_GROW_EXPONENTIAL 0
#define SE_COLLECTION_FLAGS_GROW_BY_ONE 1

typedef struct
{
    u8 flags;
    reg elementSize;
    reg capacity;
    reg length;
    void *data;

} SE_Collection;

SE_Collection *SE_CreateCollection(reg initialCapacity, reg elementSize, u8 flags);

void SE_DestroyCollection(SE_Collection *collection);

/**
 * @returns new array capacity
 */
int SE_Collection_Resize(SE_Collection *self, reg size);

/**
 * @returns index of element in array
 */
int SE_Collection_Push(SE_Collection *self, void *element);

int SE_Collection_Remove(SE_Collection *self, int i);

#define SE_Collection_Get(self, elementType, index) ( ((elementType *)((self)->data))[index] )

#define SE_Collection_Set(self, elementType, index, element) ( ((elementType *)((self)->data))[index] = element )

#endif