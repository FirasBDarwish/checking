/*

This is a script to find the closest pair of points and corresponding distance for a set of 2D points.
This is based on section 4.4 of Algorithm Design.

This was implemented using: https://www.geeksforgeeks.org/closest-pair-of-points-onlogn-implementation/
Incredible video: https://www.youtube.com/watch?v=6u_hWxbOc7E&ab_channel=iDeer7

*/

// A divide and conquer program in C++ to find the smallest distance from a
// given set of points.
 
#include <iostream>
#include <float.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
 
// A structure to represent a Point in 2D plane
struct Point
{
    int x, y;
};

/* Following two functions are needed for library function qsort().
   Refer: http://www.cplusplus.com/reference/clibrary/cstdlib/qsort/ */
 


/*
The use of const void* as the parameter type in the comparison function allows for greater flexibility in using the function with different data types.

In C, a void* is a generic pointer type that can be used to point to any data type without specifying its exact type. By using const void* as the parameter type, the comparison function can be applied to arrays of different types, not just arrays of Point structures.

The const keyword indicates that the data pointed to by the void* pointers (a and b) should not be modified within the comparison function. It ensures that the comparison function does not modify the original data in the array being sorted.

When the comparison function is called, the void* pointers are casted to Point* inside the function to access the members of the Point structure. This casting is possible because the function assumes that the pointers actually point to Point structures.

So, while the parameter type is const void* to allow for greater flexibility, the function itself treats the parameters as Point* to perform the necessary comparison based on the x and y coordinates of the points.

If the parameter type were declared as const Point*, it would restrict the usage of the comparison function to only arrays of Point structures. By using const void*, the function becomes more generic and can be used with different types, provided appropriate casting is done inside the function to access the necessary members.
*/

/*

The (Point *)a expression in the code is performing a type cast. It is casting the void* pointer a to a Point* pointer.

In the context of the comparison function, a and b are void* pointers that can point to any type of data. However, in this specific usage, the function assumes that a and b actually point to Point structures.

*/

// Needed to sort array of points according to X coordinate
int compareX(const void* a, const void* b)
{
    Point *p1 = (Point *)a,  *p2 = (Point *)b;
    return (p1->x != p2->x) ? (p1->x - p2->x) : (p1->y - p2->y);
}
// Needed to sort array of points according to Y coordinate
int compareY(const void* a, const void* b)
{
    Point *p1 = (Point *)a,   *p2 = (Point *)b;
    return (p1->y != p2->y) ? (p1->y - p2->y) : (p1->x - p2->x);
}


// A utility function to find the distance between two points
float dist(Point p1, Point p2)
{
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) +
                 (p1.y - p2.y)*(p1.y - p2.y)
               );
}

// A Brute Force method to return the smallest distance between two points
// in P[] of size n
//change Point P[] to Point *P
float bruteForce(Point *P, int n)
{
    float min = FLT_MAX;
    //pre-increment vs post-increment makes no difference here
    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n; ++j)
            if (dist(P[i], P[j]) < min)
                min = dist(P[i], P[j]);
    return min;
}

// A utility function to find a minimum of two float values
float min(float x, float y)
{
    return (x < y)? x : y;
}

// A utility function to find the distance between the closest points of
// strip of a given size. All points in strip[] are sorted according to
// y coordinate. They all have an upper bound on minimum distance as d.
// Note that this method seems to be a O(n^2) method, but it's a O(n)
// method as the inner loop runs at most 6 times
float stripClosest(Point *strip, int size, float d)
{
    float min = d;
    for(int i =0; i<size; i++)
    {
        for(int j=i+1; j<size && (strip[j].y - strip[i].y) < min; j++)
        {
            if(dist(strip[i], strip[j]) < min)
            {
                min=dist(strip[i], strip[j]);
            }
        }
    }

    return min;

}

float closest_util(Point *Px, Point*Py, int n)
{
    if (n<=3)
    {
        return bruteForce(Px, n);
    }
    int mid = n/2;
    Point midpoint = Px[mid];

    Point Pyl[mid];
    Point Pyr[n-mid];
    int li=0, ri = 0;

    for(int i=0; i<n;i++)
    {
        if((Py[i].x < midpoint.x || (Py[i].x == midpoint.x && Py[i].y < midpoint.y)) && li<mid)
        {
            Pyl[li++] = Py[i];
        }
        else
        {
            Pyr[ri++] = Py[i];
        }
    }

    float dl = closest_util(Px, Pyl, mid);
    float dr = closest_util(Px + mid, Pyr, n-mid);

    float d = min(dl, dr);

    Point strip[n];
    int j = 0;

    for(int i=0; i<n; i++)
    {
        if(abs(Py[i].x - midpoint.x) < d)
        {
            strip[j] = Py[i];
            j++;
        }
    }

    // Find the closest points in strip.  Return the minimum of d and closest
    // distance is strip[]
    return stripClosest(strip, j, d);

}

// The main function that finds the smallest distance
// This method mainly uses closestUtil()
float closest(Point *P, int n)
{
    Point Px[n];
    Point Py[n];
    for (int i = 0; i < n; i++)
    {
        Px[i] = P[i];
        Py[i] = P[i];
    }
 
    qsort(Px, n, sizeof(Point), compareX);
    qsort(Py, n, sizeof(Point), compareY);
 
    // Use recursive function closestUtil() to find the smallest distance
    return closest_util(Px, Py, n);
}

// Driver program to test above functions
int main()
{
    Point P[] = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}}; //it knows to convert them into P and assign first value to x and second value to y
    int n = sizeof(P) / sizeof(P[0]);
    cout << "The smallest distance is " << closest(P, n);
    return 0;
}