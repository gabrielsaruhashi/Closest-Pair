#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>

#include "point.h"
#include "plist.h"

// The functions below are *suggestions* and as such may be incompletely
// or overly specified.  Those functions that have the skeleton of a body
// provided may be incomplete with sections that you must add.

/**
 * Compares the two given points based on x-coordinate.
 *
 * @param p1 a pointer to a point, non-NULL
 * @param p2 a pointer to a point, non-NULL
 * @return a negative number if p1 comes before p2, positive if p1 comes
 * before p2, and 0 if they are the same
 */
int point_compare_x(const point *p1, const point *p2);

/**
 * Compares the two given points based on y-coordinate.
 *
 * @param p1 a pointer to a point, non-NULL
 * @param p2 a pointer to a point, non-NULL
 * @return a negative number if p1 comes before p2, positive if p1 comes
 * before p2, and 0 if they are the same
 */
int point_compare_y(const point *p1, const point *p2);

/**
 * Reads point from the given stream and adds them to the given list.
 *
 * @param stream a pointer to an input stream
 * @param l a pointer to a list
 * @param n a non-negative integer
 */
void read_points(FILE *stream, plist *l, int n);

/**
 * Copies the points from the source list to the destination list
 * in the order they appear in the destination list.
 *
 * @param dest a pointer to a list, non-NULL
 * @param source a pointer to a list, non-NULL
 */
void copy_list(plist *dest, const plist* source);

/**
 * Returns the closest pair of points among those on the given list.
 * The closest pair are returned in p1 and p2 and their distance is
 * returned in d.  This implementation uses the O(n log n) divide-and-conquer
 * algorithm.
 *
 * @param l a pointer to a list of at least 2 points
 * @param p1 a pointer to a point, non-NULL
 * @param p2 a pointer to a point, non-NULL
 * @param d a pointer to a double, non-NULL
 */
void closest_pair(const plist *list_x, const plist *list_y, point *p1, point *p2, double *d);

/**
 * Returns the closest pair of points among those on the given list.
 * The closest pair are returned in p1 and p2 and their distance is
 * returned in d.  This implementation uses the Theta(n^2) brute force
 * algorithm.
 *
 * @param l a pointer to a list of at least 2 points
 * @param p1 a pointer to a point, non-NULL
 * @param p2 a pointer to a point, non-NULL
 * @param d a pointer to a double, non-NULL
 */
void closest_pair_brute_force(const plist *l, point *p1, point *p2, double *d);

/**
 * Splits the given list by adding the leftmost half of the points
 * in order of increasing x-coordinate to the end of left and the
 * rightmost half of the points in order of increasing x-coordinate
 * to to the end of right.
 *
 * @param l a pointer to a list sorted by x-coordinate, non-NULL
 * @param left a pointer to a list, non-NULL
 * @param right a pointer to a list, non-NULL
 */
void split_list_x(const plist *l, plist *left, plist *right);

/**
 * Splits the given list by adding the leftmost half of the points
 * in order of increasing y-coordinate to the end of y_left_y and the
 * rightmost half of the points in order of increasing y-coordinate
 * to to the end of y_right.
 *
 * @param l a pointer to a list sorted by y-coordinate, non-NULL
 * @param x_left a pointer to a list containing the leftmost half of the points
 * on l in order of increasing x-coordinate
 * @param x_right a pointer to a list containing the rightmost half of the
 * points on l in order of increasing x-coordinate
 * @param y_left a pointer to a list
 * @param y_right a pointer to a list
 * 
 * @param end a pointer to a list, non-NULL
 */
void split_list_y(const plist *l, const plist *x_left, const plist *x_right,
		  plist *y_left, plist *y_right);

/**
 * Adds the points in the first given list with x-coordinates in the given
 * range to the second list in order of increasing y-coordinate
 *
 * @param list_y a pointer to a list of points sorted by y-coordinate, non-NULL
 * @param middle a pointer to a list, non-NULL
 * @param left a real number
 * @param right a real number greater than or equal to left
 */
void make_middle(const plist *list_y, plist *middle, double left, double right);

/**
 * Searches the given list for a pair of points closer than d units.
 * If such a pair is found, p1 and p2 are updated to the closest such pair
 * and d is updated to their distance.
 *
 * @param middle a pointer to a list of points sorted by y-coordinate, non-NULL
 * @param p1 a pointer to a point, non-NULL
 * @param p2 a pointer to a point, non-NULL
 * @param d a pointer to a positive real number, non-NULL
 */
void search_middle(const plist *middle, point *p1, point *p2, double *d);

int main(int argc, char **argv)
{
  // create empty lists
  plist *list_x = plist_create();
  plist *list_y = plist_create();

  if (list_x == NULL || list_y == NULL)
    {
      if (list_x != NULL)
	{
	  plist_destroy(list_x);
	}
      
      if (list_y != NULL)
	{
	  plist_destroy(list_y);
	}
      
      printf("%s: could not allocate lists\n", argv[0]);
      return 1;
    }

  // read n
  int n;
  fscanf(stdin, "%d", &n);

  // read into one list
  read_points(stdin, list_x, n);

  // sort list
  plist_sort(list_x, point_compare_x);

  // check for distinctness
  
  // make list_y a copy of list_x
  copy_list(list_y, list_x);
  
  if (plist_size(list_y) == n)
    {
      // sort the y-list
      plist_sort(list_y, point_compare_y);
      
      point p1, p2;
      double d;
      
      closest_pair(list_x, list_y, &p1, &p2, &d);
      printf("(%f, %f)-(%f, %f)=%f\n", p1.x, p1.y, p2.x, p2.y, d);
    }
  else
    {
      // memory allocation must have failed when copying points
      fprintf(stdout, "%s: failed to read points\n", argv[0]);
    }

  plist_destroy(list_x);
  plist_destroy(list_y);
}


void closest_pair(const plist *list_x, const plist *list_y, point *p1, point *p2, double *d)
{
  int n = plist_size(list_x);
    
  if (n <= 3)
    {
      closest_pair_brute_force(list_x, p1, p2, d);
      return;
    }

  // make left/right lists
  plist *x_left, *x_right, *y_left, *y_right;
  
  // populate left/right lists
  split_list_x(list_x, x_left, x_right);
  split_list_y(list_y, x_left, x_right, y_left, y_right);
  
  // recursively find closest pair in two halves and keep the closer of those
  point p1_left, p2_left;
  double d_left;
  closest_pair(x_left, y_left, &p1_left, &p2_left, &d_left);
  
  point p1_right, p2_right;
  double d_right;
  closest_pair(x_right, y_right, &p1_right, &p2_right, &d_right);

  // determine which pair is closer together
  
  // create the list of points in the middle
  double mid;
  plist *middle;
  
  // populate that list
  make_middle(list_y, middle, mid - *d, mid + *d);

  // search the list of points in middle for a closer pair
  search_middle(middle, p1, p2, d);

  // clean up
}

// @return a negative number if p1 comes before p2, positive if p1 comes
// * before p2, and 0 if they are the same
int point_compare_x(const point *p1, const point *p2) {
  if (*p1->x > *p2->x) {
    return -1;
  } 
  else if (*p1->x < *p2->x) {
    return 1;
  } 
  // if they are the same, return 0
  else {
    return 0;
  }

// @return a negative number if p1 comes before p2, positive if p1 comes
// before p2, and 0 if they are the same
int point_compare_y(const point *p1, const point *p2) {
  // p1 comes BEFORE p2
  if (*p1->y < *p2->y) {
    return -1;
  }
  // p1 come AFTER p2
  else if (*p1->y > *p2->y) {
    return 1;
  }
  else {
    return 0;
  }
}

void read_points(FILE *stream, plist *l, int n) {
  FILE *fp;
  point newPoint;
  int x;
  int y;
  int iterator;

  fp = fopen(*stream, "r");

  if (f == 0) {
    /* perror is a standard C library routine */
    /* that prints a message about the last failed library routine */
    /* prepended by its argument */
    perror("Error opening file");
    exit(2);
  }

  /* else everything is ok, so add points */
  for (int i = 0; i < n; i++) {
    // get  x
    // skips whitespace and 
    while (!isdigit(iterator = getc(fp))) {
      if (iterator == EOF || iterator == '\n') {
        fprintf(stderr, "Error reading input line");
        break;
      }
    }
    // get the digit
    x = iterator;

    while (!isdigit(iterator = getc(fp))) {
      if (iterator == EOF || iterator == '\n') {
        fprintf(stderr, "Error with the input line");
        break;
      }
    }
    // get the y point
    y = iterator;

    // populate new point
    newPoint->x = x;
    newPoint->y = y;

    // add point to array
    *l[i] = newPoint;
  }


  /* not strictly necessary but it's polite */
  fclose(f);

}

// CHECK
void copy_list(plist *dest, const plist* source) {

  for (int i = 0; i < source->size; i++) {
    *dest->pointsArray[i] = source->pointsArray[i];
  }
  *dest.size = source->size;
}

void closest_pair_brute_force(const plist *l, point *p1, point *p2, double *d) {
  int i = 0;

  do
  {
    double distance = point_distance(*l->pointsArray[i], *l->pointsArray[i + 1]);

    if (i = 0 || distance < *d) 
    {
      *p1 = *l[i];
      *p2 = *l[i + 1];
      *d =  distance;
    }
    
    i++;

  } while (i < *l->size);

}

void split_list_x(const plist *l, plist *left, plist *right) {
  int middle = *l->size / 2;

  for (int i = 0; i < *l->size, i++) {
    if (i < middle) {
      *left.pointsArray[i] = *l->pointsArray[i];
      *left.size++;

    } 
    else 
    {
      *right.pointsArray[i] = *l->pointsArray[i];
      *right.size++;
    }

  }
}



