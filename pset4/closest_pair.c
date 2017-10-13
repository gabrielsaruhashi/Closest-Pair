#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <float.h>


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
 * in the order they appear in the source list.
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

/**
* Based on the y-coordinates, 
* checks if it is possible that two points are closer to each other
* than the current smallest distance
*
* @param initial_y y-coordinate of one of the points being assessded
* @param next_y y-coordinate of the other point being assessed 
* @param d a pointer to the value of the smallest distance
*/
bool is_feasible_point(int initial_y, int next_y, const double *d);

/** 
* Updates the smallest distance. It checks the lowest x-coordinate
* (and the lowest y-coordinate if necessary) to print the points in the right order
* 
* @param d a pointer to the smallest distance seen so far in main()
* @param p1 a pointer to one of the two points that are closes to each other
* @param p2 a pointer to one of the two points that are closes to each other
* @param smallerDistance double representing the new smallest distance
* @param new_p1 one of the two points that have the new smallest distance
* @param new_p2 one of the two points that have the new smallest distance
*/
void updateSmallestDistance(double *d, point *p1, point *p2, 
      double smallerDistance, point new_p1, point new_p2);


/** 
* Updates the values associated with the smallest distance (points and distance) 
* 
* @param d a pointer to the smallest distance seen so far in main()
* @param p1 a pointer to one of the two points that are closes to each other
* @param p2 a pointer to one of the two points that are closes to each other
* @param smallerDistance double representing the new smallest distance
* @param new_p1 one of the two points that have the new smallest distance
* @param new_p2 one of the two points that have the new smallest distance
*/
void updateValues(double *d, point *p1, point *p2, 
  double smallerDistance, point new_p1, point new_p2); 

/**
* Given an input stream, reads a float chacter by character to ensure
* there are no invalid sequences
*
* @param floaty, a pointer to the float in main()
* @param stream, a pointer to an input stream
* @return true if float was read correctly, false otherwise
*/
bool read_single_float(float *floaty, FILE *stream);

/**
* Searches an ordered list of points for any repeated points
*
* @param plist a pointer to a list of points to be checked
* @param stream a pointer to an input stream
* @return true if list has any repetitions, false otherwise
*/
bool hasRepetitions(const plist *list, int size);

int main(int argc, char **argv)
{
  // program does not need any arguments
  if (argc > 1) 
  {
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

  // checks if all points were valid and that there at least two points
  if (plist_size(list_x) < n || plist_size(list_x) < 2) 
  {
    fprintf(stderr, "At main: Error reading inputs. Expected size %i, but there were %i valid elements\n", n, plist_size(list_x));
    return 3;
  }

  // sort list
  plist_sort(list_x, point_compare_x);
 
  // check for distinctness, ensure no repeated points
  if (hasRepetitions(list_x, plist_size(list_x))) 
  {
    fprintf(stderr, "Error reading inputs: repeated points.\n");
    return 4;
  }

  // make list_y a copy of list_x
  copy_list(list_y, list_x);

  
  if (plist_size(list_y) == n)
  {
    // sort the y-list
    plist_sort(list_y, point_compare_y);

    // declare the points
    point p1, p2;

    // initialize d to highest value of double
    double d = DBL_MAX;
    
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
  plist *x_left = plist_create(), *x_right = plist_create(), *y_left = plist_create(), *y_right = plist_create();
  
  // populate left/right lists
  split_list_x(list_x, x_left, x_right);

  split_list_y(list_y, x_left, x_right, y_left, y_right);
  
  // recursively find closest pair in two halves and keep the closer of those
  point p1_left, p2_left;
  double d_left = DBL_MAX;
  closest_pair(x_left, y_left, &p1_left, &p2_left, &d_left);
  
  point p1_right, p2_right;
  double d_right = DBL_MAX;
  closest_pair(x_right, y_right, &p1_right, &p2_right, &d_right);

  // determine which pair is closer together
  if (d_left <= d_right) 
  {
    *d = d_left;
    *p1 = p1_left;
    *p2 = p2_left;
  }

  else 
  {
    *d = d_right;
    *p1 = p1_right;
    *p2 = p2_right; 
  }

  // mid is the average of x-coordinate of last element of x_left and first element of x_right
  double mid = ((p1_right.x - p2_left.x) / 2.0) + p2_left.x;

  // create the list of points in the middle
  plist *middle = plist_create();
  
  // populate that list
  make_middle(list_y, middle, mid - *d, mid + *d);


  // search the list of points in middle for a closer pair
  search_middle(middle, p1, p2, d);

  // clean up, free all the points
  plist_destroy(middle);
  plist_destroy(x_left);
  plist_destroy(x_right);
  plist_destroy(y_left);
  plist_destroy(y_right);
}

// @return a negative number if p1 comes before p2, positive if p1 comes
// * before p2, and 0 if they are the same
int point_compare_x(const point *p1, const point *p2) 
{
  if (p1->x > p2->x) 
  {
    return 1;
  } 
  else if (p1->x < p2->x) 
  {
    return -1;
  } 
  // if they are the same, return 0
  else {
    return 0;
  }
}

// @return a negative number if p1 comes before p2, positive if p1 comes
// before p2, and 0 if they are the same
int point_compare_y(const point *p1, const point *p2) 
{
  // p1 comes BEFORE p2
  if (p1->y < p2->y) 
  {
    return -1;
  }
  // p1 come AFTER p2
  else if (p1->y > p2->y) 
  {
    return 1;
  }
  else {
    return 0;
  }
}

void read_points(FILE *stream, plist *l, int n) 
{

  for (int i = 0; i < n; i++)
  {
    float x = FLT_MAX;
    float y = FLT_MAX;
    
    point newPoint;
    
    bool isValid_x = read_single_float(&x, stream);
    bool isValid_y = read_single_float(&y, stream);

    // ensure that both floats were successfully read
    if (!isValid_x || !isValid_y) 
    {
      fprintf(stderr, "Error parsing points\n");
      return;
    }
    // populate new point
    newPoint.x = x;
    newPoint.y = y;

    // add point to array
    plist_add_end(l ,&newPoint);

    // support variable
    char iterator;

    // skip all trailing whitespace until newline or EOF
    while ((iterator = getc(stream)) != '\n' && iterator != EOF) 
    {

      // ignore trailing whitespace until you can move to new line
      if (iterator != ' ' && iterator != '\t') 
      {
        fprintf(stderr, "Error reading input line at char %c\n", iterator);
        return;
      }
    }

    // if last iteration
    if (i == n - 1) {
      return;
    }
    // unget newline or EOF for next iteration
    else 
    {
      ungetc(iterator, stream);
    }
  }

}


void copy_list(plist *dest, const plist* source) 
{


  for (int i = 0; i < plist_size(source); i++) 
  {
    point newPoint;

    // get point i from source
    plist_get(source, i, &newPoint);


    // add to end of dest
    plist_add_end(dest, &newPoint);
  }
  
}

void closest_pair_brute_force(const plist *l, point *p1, point *p2, double *d) 
{

  // initialize support variables
  int size = plist_size(l); 
  double distance_temp;
  point p1_temp;
  point p2_temp;

  // brute force compare each element in plist l
  for (int i = 0; i < size - 1; i++) {

    for (int j = i + 1; j < size; j++ ) {

      // get consecutive points
      plist_get(l, i, &p1_temp);
      plist_get(l, j, &p2_temp);

      // check distance between them
      distance_temp = point_distance(&p1_temp, &p2_temp);
      
      // if first iteration, or these set of points is closer to each other than the current one
      if (distance_temp < *d) 
      {
        updateSmallestDistance(d, p1, p2, distance_temp, p1_temp, p2_temp);
       
      }

    }
  }
}

void split_list_x(const plist *l, plist *left, plist *right) 
{
  // TODO what if last left and first right are the same x
  int middle = plist_size(l) / 2;


  for (int i = 0; i < plist_size(l); i++) 
  {
    point newPoint;

    plist_get(l, i, &newPoint);
    if (i < middle) {
      plist_add_end(left, &newPoint);
    
    } 
    else 
    {
      plist_add_end(right, &newPoint);

    }
  }

}

void split_list_y(const plist *l, const plist *x_left, const plist *x_right,
      plist *y_left, plist *y_right) 
{

  // get last element of x-left
  point last_x_left;
  point first_x_right;
  plist_get(x_left, plist_size(x_left) - 1, &last_x_left);
  plist_get(x_right, 0, &first_x_right);

  // get middle x value
  float middle = (last_x_left.x + first_x_right.x) / 2;
  int size = plist_size(l);

  for (int i = 0; i < size; i++) 
  {
    point nextPoint;

    // get the point at index i of y_list
    plist_get(l, i, &nextPoint);

    // allocate it  to left if its x is less or equal to middle
    if (nextPoint.x <= middle) 
    {
      plist_add_end(y_left, &nextPoint);
    } 
    // else place it in the right list
    else 
    {
      plist_add_end(y_right, &nextPoint);
    }

  }

  
}


void make_middle(const plist *list_y, plist *middle, double left, double right) {
  
  for (int i = 0; i < plist_size(list_y); i++) 
  {
    point pointElement;

    plist_get(list_y, i, &pointElement);

    // add every point that is within the range
    if (pointElement.x >= left && pointElement.x <= right) 
    {
      // adds to end and updates size
      plist_add_end(middle, &pointElement);
    }
  }


}

//TODO
// If there are multiple pairs of points with the same distance 
// then the one output should be the first one when all such pairs are sorted by first x-coordinate, then first y-coordinate, then second x-coordinate, then second y-coordinate.
void search_middle(const plist *middle, point *p1, point *p2, double *d) 
{
  // list must be ordered by Y
  int size = plist_size(middle);
  // support variables
  point initialPoint;
  point nextPoint;


  for (int i = 0; i < size - 1; i++) {
    
    plist_get(middle, i, &initialPoint);
    for (int j = i + 1; j < size; j++) 
    {

      // getting the nextPoint
      plist_get(middle, j, &nextPoint);
      // check if point is a feasible smaller distance
      if (is_feasible_point(initialPoint.y, nextPoint.y, d)) 
      {
        double distance = point_distance(&initialPoint, &nextPoint);

        // if distance is smaller d
        if (distance < *d) 
        {

          updateSmallestDistance(d, p1, p2, distance, initialPoint, nextPoint);
         
        }
    }
      // otherwise, move to next iteration as the list is ordered by y
      else 
      {
        continue;
      }

    }
  }

}

bool is_feasible_point(int initial_y, int next_y, const double *d) 
{
  // distance between the two points
  float difference = next_y - initial_y;

  if (exp(*d) - exp(difference) <= 0) 
  {
    return false;
  }

  return true;
}

void updateSmallestDistance(double *d, point *p1, point *p2, 
  double smallerDistance, point initialPoint, point nextPoint) 
{
  
  // if same x, order by lowest y-coordinate
  if (initialPoint.x == nextPoint.x) 
  {
    if (initialPoint.y < nextPoint.y) 
    {
      updateValues(d, p1, p2, smallerDistance, initialPoint, nextPoint);
    }
    else 
    {
      updateValues(d, p1, p2, smallerDistance, nextPoint, initialPoint);

    }
  }

  // if initial point has lowest x-coordinate
  else if (initialPoint.x < nextPoint.x) 
  {
    updateValues(d, p1, p2, smallerDistance, initialPoint, nextPoint);
  }

  // else, next point has the lowest x-coordinate
  else 
  {
    updateValues(d, p1, p2, smallerDistance, nextPoint, initialPoint);

  }
  
}

void updateValues(double *d, point *p1, point *p2, 
  double smallerDistance, point new_p1, point new_p2) 
{
  // update the variable values
  *d = smallerDistance;
  *p1 = new_p1;
  *p2 = new_p2;
}


bool read_single_float(float *floaty, FILE *stream) 
{

  char *float_string = malloc(sizeof(char) * 50);
  int size = 0;
  char iterator;
  bool isNegative = false;
  bool hasDecimalCase = false;

  // ignore the first newline, unless EOF. In that case, return
  if ((iterator = getc(stream)) == EOF) 
  {
    return false;
  }


  // skips whitespace before x 
  while (!isdigit(iterator = getc(stream))) 
  {
  
    // only skip valid whitespaces, otherwise break functions
    if (iterator != ' ' && iterator != '\t') 
    {

      // check for valid negative sign
      if (iterator == '-') 
      {
        char supportIterator = getc(stream);

        if (isdigit(supportIterator)) 
        {
          ungetc(supportIterator, stream);
          isNegative = true;
          break;
        }
      } 
      else 
      {
        fprintf(stderr, "Error reading input line at char %c\n", iterator);
        return false;
      }    
      
    }
  }


  if (isNegative) 
  {
    float_string[size] = '-';
    size += 1;
    float_string[size] = '\0';
  }
  // else skip whitespace stopped because of a digit
  else 
  {
    // unget first digit
    ungetc(iterator, stream);
    float_string[size] = '\0';

  }

  // add characters to float y
  while(isdigit(iterator = getc(stream)) ||
   (iterator == '.' && !hasDecimalCase)) 
  {

    float_string[size] = iterator;
    size += 1;
    float_string[size] = '\0';

    if (iterator == '.') 
    {
      hasDecimalCase = true;
    }
  }

  // unget last char that is not a digit of float x
  ungetc(iterator, stream);

  // convert string into a float
  *floaty = atof(float_string);

  free(float_string);
  return true;
}


bool hasRepetitions(const plist *list, int size)
{
  point currentElement;
  point lastElement;

  plist_get(list, 0, &lastElement);

  // iterate through entire list to ensure there are no repeated points
  for (int i = 1; i < size; i++)
  {
    plist_get(list, i, &currentElement);
    if (lastElement.x == currentElement.x && 
      lastElement.y == currentElement.y)
    {

     point_fprintf(stderr, "%.3f", &lastElement);
      point_fprintf(stderr, "%.3f", &currentElement);

     return true;
    }
    else
    {
      lastElement = currentElement;
    }
  }

  return false;
}




