#include <stdlib.h>
#include <string.h>

#include "plist.h"
#define PLIST_INITIAL_SIZE 2

struct plist {
  int size;
  int capacity;
  point *pointsArray;
};

// return a pointer to newly made plist
plist *plist_create() {

  // declare variables
  plist *newPlist;
  point *newPointsArray;

  // allocate memory memory for plist
  newPlist = malloc(sizeof(struct plist));

  // create point array and allocate memory
  newPointsArray = malloc(sizeof(point) * PLIST_INITIAL_SIZE);

  // populate new plist
  newPlist->pointsArray = newPointsArray;
  newPlist->size = 0;
  newPlist->capacity = PLIST_INITIAL_SIZE;
  
  // return a reference to the structure
  return newPlist;
}


// frees all memory
void plist_destroy(plist *l) {
  // frees array
  free(l->pointsArray);

  // frees pointer to array
  free(l);
}


int plist_size(const plist *l) {
  // return the size property
  return l->size;
}

bool plist_add_end(plist *l, const point *p) {

  // if plist has reached its capacity, double the capacity and reallocate the array
  if (plist_size(l) == l->capacity) {

    // double capacity
    int largerCap = l->capacity * 2;

    // reallocate points memory block to the larger memory block
     point *largerPointsArray = realloc(l->pointsArray, sizeof(point) * largerCap);

    // ensure reallocation worked correctly
    if (largerPointsArray != NULL ){

        // update array and capacity
        l->pointsArray = largerPointsArray;
        l->capacity = largerCap;
    } 
    // else something went wrong
    else
    {
      return false;
    }
  
  }

  // add point to the end of plist and increase size
  if (plist_size(l) < l->capacity)
  {
    l->pointsArray[plist_size(l)] = *p;
    l->size++;
  }

  return true;

}

void plist_get(const plist *l, int i, point *p) {

  // populate pointer
  *p = l->pointsArray[i];

}

bool plist_contains(const plist *l, const point *p) 
{

  // iterate through plist l to check for the point 
  for (int i = 0; i < l->size; i++) {

    // get the reference for the point in the array
    point *pointObject = &l->pointsArray[i];

    // check for equality
    if (pointObject->x == p->x && pointObject->y == p->y) 
    {
      return true;
    } 

  }

  return false;

}

void plist_fprintf(FILE *stream, const char *fmt, const plist *l) {
    
    // ensures that formatter *fmt does not have \n
    char *formatter = malloc(sizeof(char) * strlen(fmt));

    // copy fmt to formatter
    if (fmt[strlen(fmt) - 1] == '\n') {
      strncpy(formatter, fmt, strlen(fmt) - 1);
    }

    int len = strlen(formatter);

    // add null terminator
    formatter[len] = '\0';
    
    int size = plist_size(l);
    fprintf(stream, "%c", '[');

    // print all the points, separated by commas
    for (int i = 0; i < size; i++) 
    {
      point currentPoint;
      plist_get(l, i, &currentPoint);

      point_fprintf(stream, formatter, &currentPoint);

      if (i != size - 1) {
        fprintf(stream, "%c ", ',');
      }
    }

    fprintf(stream, "%c\n ", ']');

    // free the memory block
    free(formatter);


    
}

void plist_sort(plist *l, int (*compare)(const point* point1, const point* point2)) {
 // cast function pointer parameters to void in order to use qsort
 qsort(l->pointsArray, l->size, sizeof(point), (int (*) (const void *, const void *)) compare);
}









