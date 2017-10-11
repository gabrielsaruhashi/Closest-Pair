
#include "plist.h"
#define PLIST_INITIAL_SIZE 2

struct plist {
  int size;
  int capacity;
  point *pointsArray;
};

// return a pointer to plist
plist *plist_create() {
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
  free(l->pointsArray);
  free(l);
}


int plist_size(const plist *l) {
  return l->size;
}

bool plist_add_end(plist *l, const point *p) {
  // if plist has reached its capacity, double the capacity and reallocate the array
  if (plist_size(l) == l->capacity) {

    int largerCap = l->capacity * 2;
    // duplicate
     point *largerPointsArray = realloc(l->pointsArray, sizeof(point) * largerCap);

    if (largerPointsArray != NULL ){
        // update array and capacity
        l->pointsArray = largerPointsArray;
        l->capacity = largerCap;
    } 
    else
    {
      return false;
    }
  
  }
  // just add
  if (plist_size(l) < l->capacity)
  {
    //printf("here2 with size %i and capacity %i\n", l->size, l->capacity);

    l->pointsArray[plist_size(l)] = *p;
   // printf("im here\n");
    l->size++;
    //printf("it's here with size %i\n", plist_size(l));

    //point_fprintf(stdout, "%.3f\n", &l->pointsArray[plist_size(l) - 1]);

  }

  return true;

}

void plist_get(const plist *l, int i, point *p) {

  *p = l->pointsArray[i];

}

bool plist_contains(const plist *l, const point *p) 
{

  for (int i = 0; i < l->size; i++) {

    // get the reference for the point in the array
    point *pointObject = &l->pointsArray[i];

    if (pointObject->x == p->x && pointObject->y == p->y) 
    {
      return true;
    } 

  }

  return false;

}

void plist_fprintf(FILE *stream, const char *fmt, const plist *l) {
    
    // official formatter
    char *formatter = malloc(sizeof(char) * strlen(fmt));

    // strip the \n from the formatter, if any
    /*for (int i = 0; i < (int) strlen(fmt); i++) {
      if (fmt[i] == '\n') 
      {
         strncpy(formatter, fmt, strlen(fmt) - 1);

      }
    } */

    if (fmt[strlen(fmt) - 1] == '\n') {
      strncpy(formatter, fmt, strlen(fmt) - 1);
    }

    int len = strlen(formatter);
    // add null terminator
    formatter[len] = '\0';
    
    int size = plist_size(l);
    fprintf(stream, "%c", '[');
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

    free(formatter);


    
}

void plist_sort(plist *l, int (*compare)(const point* point1, const point* point2)) {
 // cast it
 qsort(l->pointsArray, l->size, sizeof(point), (int (*) (const void *, const void *)) compare);
}

void plist_set_size(plist *l, int size_) {
  l->size = size_;
}

int plist_capacity(const plist *l) {
  return l->capacity;
}

void plist_set_capacity(plist *l, int capacity_) {
  l->capacity = capacity_;
}









