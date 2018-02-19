/* COMP10002 Assignment 1, April 2017.
 Yurong Song, student ID: 828777
 
 This program includes 5 stages in order to demonstrate
 the skyline points in a set of points
 */

/* algorithms are fun */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIV "==========" /* stage header */
/* stage numbers */
#define STAGE_NUM_ONE 1
#define STAGE_NUM_TWO 2
#define STAGE_NUM_THREE 3
#define STAGE_NUM_FOUR 4
#define STAGE_NUM_FIVE 5

#define READ_OK 1 /* reading point succeeded */
#define READ_FAILED 0 /* reading point failed */

#define MAX_NUM_POINTS 99 /* maximum number of points */
#define MAX_NUM_DIMENSIONS 10 /* maximum number of dimensions */

#define CALC_PERCENT 100 /* to calculate percentage */

#define MAX_ONE_DIGIT 9 /* maximum one digit integer */

#define DOMINATED 0 /* the point has been dominated */
#define NOT_DOMINATED 1 /* the point has not been dominated */

#define DOMINATE 1 /* the point dominates other point(s) */
#define NOT_DOMINATE 0 /* the point does not dominate other point(s) */


typedef double point_t[MAX_NUM_DIMENSIONS];
typedef int checker_t[MAX_NUM_POINTS];

/* function prototypes */
void stage_one(point_t one_point, int *num_points, int num_dimensions);
void stage_two(point_t points[], int *num_points, int num_dimensions,
               double *coordinate_sums);
void stage_three(double *coordinate_sums, int num_points);
void stage_four(point_t points[], int num_points, int num_dimensions);
void stage_five(point_t points[], int num_points, int num_dimensions);

void print_stage_heading(int stage);
int read_one_point(point_t one_point, int num_dimensions);

int dominate_checker(double array1[], double array2[], int num_dimensions);

void test_domination(point_t points[], int checker[],
                     int num_points, int num_dimensions);

void test_domination_2(point_t points[], int num_points,
                       int num_dimensions, checker_t dominate_counter[]);

int dominate_other_point(double array1[], double array2[], int num_dimensions);

void int_swap(int *p1, int *p2);

/* main program binds it all together */
int
main(int argc, char *argv[]) {
    
    /* storage for the input data */
    int num_dimensions;
    point_t points[MAX_NUM_POINTS];
    
    /* storage for statistics */
    int num_points = 0; /* number of points read in */
    double coordinate_sums[MAX_NUM_POINTS]; /* coordinate sums of the points */
    
    /* read the first line - number of dimensions */
    scanf("%d", &num_dimensions);
    
    /* stage 1 */
    stage_one(points[0], &num_points, num_dimensions);
    
    /* stage 2 */
    stage_two(points, &num_points, num_dimensions,
              coordinate_sums);
    
    /* stage 3 */
    stage_three(coordinate_sums, num_points);
    
    /* stage 4 */
    stage_four(points, num_points, num_dimensions);
    
    /* stage 5 */
    stage_five(points, num_points, num_dimensions);
    
    /* and done! */
    return 0;
}

/* print out a stage heading, with a prior blank line once the stage number
 goes plus one
 */
void
print_stage_heading(int stage) {
    /* main job is to print the stage number passed as an argument */
    if(stage > STAGE_NUM_ONE) {
        /* separate the stages */
        printf("\n");
    }
    printf("Stage %d\n%s\n", stage, DIV);
}

/* read the coordinates of one point, store them in one_point
 */
int
read_one_point(point_t one_point, int num_dimensions) {
    int i = 0;
    
    /* keep reading until num_dimensions numbers have been obtained */
    while(i < num_dimensions) {
        if (scanf("%lf", one_point+i) != 1) {
            return READ_FAILED;
        }
        i++;
    }
    
    return READ_OK;
}

/* stage 1 - read in and print one point
 */
void
stage_one(point_t one_point, int *num_points, int num_dimensions) {
    /* print stage heading for stage 1 */
    print_stage_heading(STAGE_NUM_ONE);
    
    /* add your code here for stage 1 */
    int index;
    
    /* call read_one_point to read one_point and check if it reads
     successfully  */
    if(read_one_point(one_point, num_dimensions) == READ_OK) {
        /* print the title of the line  */
        printf("Point 0%d: <", *num_points+1);
        
        /* iterate over one_point and print its each coordinate with correct
         format */
        for(index=0; index<num_dimensions-1; index++) {
            printf("%.2f, ", one_point[index]);
        }
        printf("%.2f>", one_point[index]);
    }
    
    /* fail to read and exit the program */
    else {
        exit(EXIT_FAILURE);
    }
    printf("\n");
    
}

/* stage 2 - read in the rest of the points and visualise them
 */
void
stage_two(point_t points[], int *num_points, int num_dimensions,
          double *coordinate_sums) {
    /* print stage heading for stage 2 */
    print_stage_heading(STAGE_NUM_TWO);
    
    point_t one_point;
    int index, i, points_count = 0;
    double sum;
    
    /* calculate the sum of first point and add it to coordinate_sum */
    sum = 0.0;
    for(i=0; i< num_dimensions; i++) {
        sum = sum + points[0][i];
    }
    coordinate_sums[points_count]=sum;
    points_count ++;
    
    /* call read_one_point to read all points into points */
    while(read_one_point(one_point, num_dimensions)) {
        
        /* calculate the sum for each point, add the points into 
         'points' and record number of points simutaneously */
        sum = 0.0;
        for(index=0; index<num_dimensions; index++) {
            sum = sum + one_point[index];
            points[points_count][index] = one_point[index];
            coordinate_sums[points_count] = sum;
        }
        points_count++; /* count the number of points read */
    }
    
    /* print the results for each point */
    for(index=0; index < points_count; index++) {
        
        /* print the part without dashed line */
        /* point number less than 10, ie, add a '0' if only one digit */
        if(index < MAX_ONE_DIGIT) {
            printf("Point 0%d, sum of coordinates (/100): %5.2f |",
                   index+1, coordinate_sums[index]/CALC_PERCENT);
        }
        else { /* point number equal or more than 10 */
            printf("Point %d, sum of coordinates (/100): %5.2f |",
                   index+1, coordinate_sums[index]/CALC_PERCENT);
        }
        /* print the dashed line part */
        for(i=1; i<coordinate_sums[index]/CALC_PERCENT+1; i++) {
            if (i % 10 == 0) { /* print a '+' at every 10th character */
                printf("+");
            }
            else {  /* otherwise print '-' */
                printf("-");
            }
        }
        printf("\n");
    }
    /* assign the number of points to num_points */
    *num_points = points_count;
}


/* stage 3 - print statistics
 */
void
stage_three(double *coordinate_sums, int num_points) {
    /* print stage heading for stage 3 */
    print_stage_heading(STAGE_NUM_THREE);
    
    /* add your code here for stage 3 */
    int i, largest_sum_coord;
    double largest_sum = 0.0;
    
    /* Iterate over coordinate_sums and find the
     largest sum and largest sum coordinate*/
    for(i=0; i < num_points; i++) {
        if(coordinate_sums[i] > largest_sum) {
            largest_sum = coordinate_sums[i];
            largest_sum_coord = i+1;
        }
    }
    /* print the total points, largets sum coordinate and 
     largest sum in correct format*/
    printf("Total: %d points\n", num_points);
    if(largest_sum_coord <= MAX_ONE_DIGIT) {
        printf("Point of largest sum of coordinates: 0%d\n",
               largest_sum_coord);
    }
    else {
        printf("Point of largest sum of coordinates: %d\n",
               largest_sum_coord);
    }
    printf("Largest sum of coordinates: %.2f\n", largest_sum);
}

/* stage 4 - find and print the skyline points
 */
void
stage_four(point_t points[], int num_points, int num_dimensions) {
    /* print stage heading for stage 4 */
    print_stage_heading(STAGE_NUM_FOUR);
    
    int i, j, checker[MAX_NUM_POINTS] = {0};
    /* checker checks if each point is dominated by other points */
    printf("Skyline points:\n");
    
    
    /* Call function test_domination and update checker to
     indicate the property of domination of the points */
    test_domination(points, checker, num_points, num_dimensions);
    
    /* iterate over 'checker' to see if each point is dominated or not */
    for(i=0; i<num_points; i++) {
        /* print out the point if it is not dominated */
        if(checker[i] != DOMINATED) {
            /* case when the point number only has one digit */
            if(i<MAX_ONE_DIGIT) {
                printf("Point 0%d: <", i+1);
            }
            else { /* case when the point number has more than one digit */
                printf("Point %d: <", i+1);
            }
            /* print out the coordinates of the points */
            for(j=0; j<num_dimensions-1; j++) {
                printf("%.2f, ", points[i][j]);
            }
            printf("%.2f>\n", points[i][j]);
        }
    }
}

/* dominate_checker - check between two points to see whether one is
 dominated by another or not, returns 1 if the first point is dominated
 by the second point*/
int dominate_checker(double array1[], double array2[], int num_dimensions) {
    int i, two_points_checker = 0;
    
    /*iterate over the coordinate between two points and recored the point
     as non-dominated as long as there is one coordinate greater than
     the other one */
    for(i=0; i<num_dimensions; i++) {
        if(array1[i]>array2[i]) {
            two_points_checker = NOT_DOMINATED;
        }
    }
    /* return if the point is dominated or not */
    return two_points_checker;
}

/* test_domination checks if the points are dominated or not */
void test_domination(point_t points[], int checker[],
                     int num_points, int num_dimensions) {
    int i, j;
    
    for(i=0; i<num_points; i++) {
        for(j=0; j<num_points; j++) {
            /* check if a point is dominated by another, assign value 0 to that
             point if it is dominated by another point */
            if(i!=j && dominate_checker(points[i], points[j], num_dimensions)
               == DOMINATED) {
                checker[i] = DOMINATED;
                break; /* break if the point is dominated by another point */
            }
            else {/* otherwise the point is not dominated by any other points */
                checker[i] = NOT_DOMINATED;
            }
        }
    }
}

/* stage 5 - sort and print the skyline points by the number of points
 they dominate
 */
void
stage_five(point_t points[], int num_points, int num_dimensions) {
    /* print stage heading for stage 5 */
    print_stage_heading(STAGE_NUM_FIVE);
    
    int i, j;
    checker_t dominate_counter[MAX_NUM_POINTS];
    printf("Sorted skyline points:\n");
    
    /* call function test_domination to check if the points are
     dominated or not and record the number of points that each
     point dominates in the array dominate_counter */
    test_domination_2(points, num_points, num_dimensions,
                      dominate_counter);
    
    
    /* sort the number of points that each dominates in descending order */
    for(i=1; i<num_points; i++) {
        for(j=i-1; j>=0 && dominate_counter[0][j+1]<dominate_counter[0][j];
            j--) {
            int_swap(&dominate_counter[0][j], &dominate_counter[0][j+1]);
            int_swap(&dominate_counter[1][j], &dominate_counter[1][j+1]);
        }
    }
    
    /* if two points dominate the same number of points,
     the point appears earlier in the input move to front */
    for(i=1; i<num_points; i++) {
        for(j=i-1; j>=0; j--) {
            if(dominate_counter[0][j+1]==dominate_counter[0][j] &&
               dominate_counter[1][j+1]>dominate_counter[1][j]){
                int_swap(&dominate_counter[1][j], &dominate_counter[1][j+1]);
                int_swap(&dominate_counter[0][j], &dominate_counter[0][j+1]);
            }
        }
    }
    
    /* print the sorted skyline points and points they dominate */
    for(i=num_points-1; i>=0; i--) {
        if(dominate_counter[0][i]>=0) {
            /* case when the point number only has one digit */
            if(dominate_counter[1][i]<MAX_ONE_DIGIT) {
                printf("Point 0%d: <", dominate_counter[1][i]+1);
            }
            else { /* case when the point number has more than one digit */
                printf("Point %d: <", dominate_counter[1][i]+1);
            }
            /* print out the coordinates of the points */
            for(j=0; j<num_dimensions-1; j++) {
                printf("%.2f, ", points[dominate_counter[1][i]][j]);
            }
            printf("%.2f>\n", points[dominate_counter[1][i]][j]);
            printf("Number of points dominated: %d\n", dominate_counter[0][i]);
        }
    }
    
}


/* test_domination checks if the points are dominated or not */
void test_domination_2(point_t points[], int num_points,
                       int num_dimensions, checker_t dominate_counter[]) {
    int i, j, counter; /* counter counts the number of points that each point
                        dominates */
    
    for(i=0; i<num_points; i++) {
        counter = -1;
        
        for(j=0; j<num_points; j++) {
            /* check if a point is dominated by another, assign value -1 to
             that point if it is dominated by another point */
            if(i!=j && dominate_checker(points[i], points[j], num_dimensions)
               == DOMINATED) {
                counter = -1;
                break;
            }
            else{
                /* call function dominate_other_point to check if the point
                 dominates other point(s) */
                if(dominate_other_point(points[i], points[j], num_dimensions)) {
                    counter ++;
                }
            }
        }
        /* update dominate_counter with the number of points dominating
         on first row and corresponding point on second row */
        dominate_counter[0][i] = counter;
        dominate_counter[1][i] = i;
    }
}

/* dominate_other_point compare the coordinates of two points
 and check if the first point dominates the second point */
int dominate_other_point(double array1[], double array2[], int num_dimensions) {
    int i, dominataion_check = DOMINATE;
    
    /*iterate over the coordinate between two points and recored the point
     as 0 (not dominate) as long as there is one coordinate smaller than
     the other one */
    for(i=0; i<num_dimensions; i++) {
        if(array1[i]<array2[i]) {
            dominataion_check = NOT_DOMINATE;
        }
    }
    /* return if the point dominates other points or not */
    return dominataion_check;
}

/* Figure 6.7 in the textbook 
 Programming, Problem Solving, and Abstraction with C:
 exchange the values of the two variables indeicated by the arguments */
void int_swap(int *p1, int *p2) {
    int tmp;
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}
