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


// CHECARRRRR DEPOIS const void *p1, e depois tem que castear
int point_compare_x(const point *p1, const point *p2);

/**
 * Compares the two given points based on y-coordinate.
 *
 * @param p1 a pointer to a point, non-NULL
 * @param p2 a pointer to a point, non-NULL
 * @return a negative number if p1 comes before p2, positive if p1 comes
 * after p2, and 0 if they are the same
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

bool is_feasible_point(int initial_y, int next_y, const double *d);

void updateSmallestDistance(double *d, point *p1, point *p2, 
      double smallerDistance, point *new_p1, point *new_p2);

int main(int argc, char **argv)
{
  // program does not need any arguments
  if (argc > 1) {
    fprintf(stderr, "Usage ./ClosestPair < file.txt");
    return 2;
  }
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

  // TODO scheck if all points were valid
  if (plist_size(list_x) < n) {
    fprintf(stderr, "At main: Error reading inputs\n");
    return 3;
  }

  // sort list
  plist_sort(list_x, point_compare_x);

  // check for distinctness, ensure no repeated points
  
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
  plist *x_left = NULL, *x_right = NULL, *y_left = NULL, *y_right = NULL;
  
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
  *d = (d_right > d_left) ? d_right : d_left;

  // mid is the average of x-coordinate of last element of x_left and first element of x_right
  point left_last, right_first;
  plist_get(x_left, plist_size(x_left) - 1, &left_last);
  plist_get(x_right, plist_size(x_right) - 1, &right_first);
  double mid = (left_last.x - right_first.x) / 2;

  // create the list of points in the middle
  plist *middle = NULL;
  
  // populate that list
  make_middle(list_y, middle, mid - *d, mid + *d);

  // search the list of points in middle for a closer pair
  search_middle(middle, p1, p2, d);

  // clean up, free all the points
}

// @return a negative number if p1 comes before p2, positive if p1 comes
// * before p2, and 0 if they are the same
int point_compare_x(const point *p1, const point *p2) {
  if (p1->x > p2->x) {
    return -1;
  } 
  else if (p1->x < p2->x) {
    return 1;
  } 
  // if they are the same, return 0
  else {
    return 0;
  }
}

// @return a negative number if p1 comes before p2, positive if p1 comes
// before p2, and 0 if they are the same
int point_compare_y(const point *p1, const point *p2) {
  // p1 comes BEFORE p2
  if (p1->y < p2->y) {
    return -1;
  }
  // p1 come AFTER p2
  else if (p1->y > p2->y) {
    return 1;
  }
  else {
    return 0;
  }
}

void read_points(FILE *stream, plist *l, int n) {
  //FILE *fp;
  float x;
  float y;
  char iterator;

  /*
  fp = fopen(stream, "r");

  if (fp == 0) {
    
    perror("Error opening file");
    exit(2);
  } */

  /* else everything is ok, so add points */
  for (int i = 0; i < n; i++) {
    point newPoint;

    printf("Iteration %i out of %i\n", i, n);

    // ignore the first newline, unless EOF. In that case, return
    if ((iterator = getc(stream)) == EOF) {
      return;
    }

    // skips whitespace before x 
    while (!isdigit(iterator = getc(stream))) {
     //if (iterator == EOF || iterator == '\n' || isalpha(iterator)) 
      // only skip valid whitespaces, otherwise break functions
      if (iterator != ' ' && iterator != '\t') {
        //fprintf(stderr, "Error reading input line at char %c", iterator);
        return;
      }
    }
  

    // unget first digit
    ungetc(iterator, stream);

    // allocate the digits to the array
    // TODO decide on number to malloc
    char *floatX = malloc(sizeof(char) * 50);
  

    // add characters to floatx string, ex: 4.500
    while(isdigit(iterator = getc(stream))) {
      //printf("current char is %c\n",iterator);
      floatX[strlen(floatX)] = iterator;
      floatX[strlen(floatX)] = '\0';
    }

    // unget last char that is not a digit of float x
    ungetc(iterator, stream);
    // convert string into a float
    x = atof(floatX);

    printf("x-coordinate is %f\n",x);

    // remove trailing whitespace
    while (!isdigit(iterator = getc(stream))) {
      if (iterator != ' ' && iterator != '\t') {
        //fprintf(stderr,"Error reading input line at char %c", iterator);
        return;
      }
    }

    // unget last char that is int
    ungetc(iterator, stream);

    // allocate the digits to the array
    char *floatY = malloc(sizeof(char) * 50);
    floatY[0] = '\0';

    while(isdigit(iterator = getc(stream))) {
      //printf("current char for y is %c\n",iterator);
      floatY[strlen(floatY)] = iterator;
      floatY[strlen(floatY)] = '\0';
    }

    // unget last element that is not part of float y
    ungetc(iterator, stream);

    // get the y point
    y = atof(floatY);

    printf("y-coordinate is %f\n", y);

    // populate new point
    newPoint.x = x;
    newPoint.y = y;

    // add point to array
    plist_add_end(l ,&newPoint);


    // skip all trailing whitespace until newline or EOF
    while ((iterator = getc(stream)) != '\n' && iterator != EOF) {
     printf("here with char %c\n", iterator);

      // ignore trailing whitespace until you can move to new line
      if (iterator != ' ' && iterator != '\t') {
        fprintf(stderr, "Error reading input line at char %c", iterator);
        return;
      }
    }

    // if last iteration
    if (i == n - 1) {
      printf("returning");
      return;
    }
    // unget newline or EOF for next iteration
    else 
    {
      printf("i is %i\n", i);
      ungetc(iterator, stream);
    }
  }

}

// CHECK
void copy_list(plist *dest, const plist* source) {

  for (int i = 0; i < plist_size(source); i++) 
  {
    point *newPoint = NULL;

    // get point i from source
    plist_get(source, i, newPoint);
    // add to end of dest
    plist_add_end(dest, newPoint);
  }
  
  plist_set_size(dest, plist_size(source));
  plist_set_capacity(dest, plist_capacity(source));
}

void closest_pair_brute_force(const plist *l, point *p1, point *p2, double *d) {

  int size = plist_size(l); 
  double distance_temp;
  point *p1_temp = NULL;
  point *p2_temp = NULL;


  // brute force compare each element
  for (int i = 0; i < size - 1; i++) {

    for (int j = i + 1; j < size; j++ ) {

      plist_get(l, i, p1_temp);
      plist_get(l, j, p2_temp);
      // check distance
      distance_temp = point_distance(p1_temp, p2_temp);

      // if first iteration, or these set of points is closer to each other than the current one
      if (distance_temp < *d || i == 0) 
      {
        *d = distance_temp;
        *p1 = *p1_temp;
        *p2 = *p2_temp;
      }

    }
  }

  // free support variables
  free(p1_temp);
  free(p2_temp);


}

void split_list_x(const plist *l, plist *left, plist *right) {
  // TODO what if last left and first right are the same x
  int middle = plist_size(l) / 2;

  for (int i = 0; i < plist_size(l); i++) {
    point *newPoint = NULL;

    plist_get(l, i, newPoint);
    if (i < middle) {
      plist_add_end(left, newPoint);
    

    } 
    else 
    {
      plist_add_end(right, newPoint);

    }
  }

}

void split_list_y(const plist *l, const plist *x_left, const plist *x_right,
      plist *y_left, plist *y_right) 
{

  // get last element of x-left
  point *last_x_left = NULL;
  point *first_x_right = NULL;
  plist_get(x_left, plist_size(x_left) - 1, last_x_left);
  plist_get(x_right, 0, first_x_right);

  // get middle x value
  float middle = (last_x_left->x + first_x_right->x) / 2;
  int size = plist_size(l);

  for (int i = 0; i < size; i++) 
  {
    point *nextPoint = NULL;
    // get the point at index i of y_list
    plist_get(l, i, nextPoint);

    if (nextPoint->x <= middle) 
    {
      plist_add_end(y_left, nextPoint);
    } 
    else 
    {
      plist_add_end(y_right, nextPoint);
    }

  }

  free(last_x_left);
  free(first_x_right);
  
}


void make_middle(const plist *list_y, plist *middle, double left, double right) {

  for (int i = 0; i < plist_size(list_y); i++) {
    point *pointElement = NULL;

    plist_get(list_y, i, pointElement);

    // add every point that is within the range
    if (pointElement->x >= left && pointElement->x <= right) {
      // adds to end and updates size
      plist_add_end(middle, pointElement);
    }
    else
    {
      free(pointElement);
    }
  }

}

//TODO
// If there are multiple pairs of points with the same distance 
// then the one output should be the first one when all such pairs are sorted by first x-coordinate, then first y-coordinate, then second x-coordinate, then second y-coordinate.
void search_middle(const plist *middle, point *p1, point *p2, double *d) {
  // list must be ordered by Y
  int size = plist_size(middle);
  // support variables
  point *initialPoint = NULL;
  point *nextPoint = NULL;
  
  for (int i = 0; i < size - 1; i++) {
    
    plist_get(middle, i, initialPoint);
    for (int j = i + 1; j < size; j++) 
    {

      // getting the nextPoint
      plist_get(middle, j, nextPoint);
      // check if point is a feasible smaller distance
      if (is_feasible_point(initialPoint->y, nextPoint->y, d)) 
      {
        double distance = point_distance(initialPoint, nextPoint);

        // if distance is smaller d
        if (distance < *d) 
        {
          // if same x, order by lowest y-coordinate
          if (initialPoint->x == nextPoint->x) 
          {

            if (initialPoint->y < nextPoint->y) 
            {
              updateSmallestDistance(d, p1, p2, distance, initialPoint, nextPoint);
            }
            else 
            {
              updateSmallestDistance(d, p1, p2, distance, nextPoint, initialPoint);

            }
          }
          else if (initialPoint->x < nextPoint->x) 
          {
            updateSmallestDistance(d, p1, p2, distance, initialPoint, nextPoint);
          }
          else 
          {
            updateSmallestDistance(d, p1, p2, distance, nextPoint, initialPoint);

          }
        }
      }
      // otherwise, move to next iteration as the list is ordered by y
      else 
      {
        continue;
      }

    }
  }
  // free support variables
  free(initialPoint);
  free(nextPoint);
  
}

bool is_feasible_point(int initial_y, int next_y, const double *d) {
  // distance between the two points
  int difference = next_y - initial_y;

  if (exp(*d) - exp(difference) < 0) {
    return false;
  }

  return true;
}

void updateSmallestDistance(double *d, point *p1, point *p2, double smallerDistance, point *new_p1, point *new_p2) {
  *d = smallerDistance;
  *p1 = *new_p1;
  *p2 = *new_p2;
}



