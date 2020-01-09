#include "SE_Collection.h"

SE_Collection *SE_CreateCollection(reg initialCapacity, reg elementSize, u8 flags)
{
    SE_Collection *collection = malloc(sizeof(SE_Collection));
    if (collection) {

        collection->data = malloc(initialCapacity * elementSize);
        if (collection->data) {
            collection->flags = flags;
            collection->elementSize = elementSize;
            collection->capacity = initialCapacity;
            collection->length = 0;
            return collection;
        }

        free(collection);
    }
    return nil;
}

void SE_DestroyCollection(SE_Collection *collection)
{
    if (collection->data) {
        free(collection->data);
    }
    free(collection);
}

int SE_Collection_Resize(SE_Collection *self, reg size)
{
    reg oldSize = self->elementSize * self->capacity;
    reg newSize = self->elementSize * size;

    self->data = realloc(self->data, newSize);
    if (self->data) {
        self->capacity = size;

        int difference = (signed)newSize - (signed)oldSize;
        if (difference > 0) {
            memset((u8 *)self->data + oldSize, 0, difference); // fill allocated memory with zeroes
        }

        return newSize;
    }

    return 0;
}

int SE_Collection_Push(SE_Collection *self, void *element)
{
    reg size  = self->capacity;
    if (size <= self->length) { // if no more space in collection
        if (size <= 0) {
            size  = 1;
        } else {
            if   (self->flags & SE_COLLECTION_FLAGS_GROW_BY_ONE) { size += 1; } // grow by one
            else                                                 { size *= 2; } // grow exponential (default)
        }
        if (SE_Collection_Resize(self, size) == 0) {
            return 0;
        }
    }

    /* copy new element into array buffer */
    memcpy(&((u8*)self->data)[self->length * self->elementSize], element, self->elementSize);

    return (self->length += 1);
}
