/*
 * Read and thinking about problem: started at September 22, 2018
 * Algorithm defined on September 25
 * File started editing on September 25, 2018
 * - Sept 25, 2018: finish part af read input
 * - Sept 26, 2018: Edit function searching_time() & Debug
 * - Sept 27, 2018: Edit comments
 * - Sept 28, 2018: Find read input bug. Solve.
 * - Sept 29, 2018: Comments re-edit
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_LEN 1024

int num_entries; // the global variable that suggests the size of graph

/*
 * This is the helping function which is used to find the city to start with.
 * In Dikstra's shortest path algorithm
 * Parameters:
 * times[]: the array that includes the current shortest time to each city
 * length: the number of cities
 * visited[]: the array that to store the status that whether the current city
 *            has been visited or not
 * Return:
 * the index of the city which has the minimum arriving time
 */

int find_minimum_city(int times[], int length, int visited_cities[]) {
	int min_index; // the index (city) which has the minimum time to arrive

	int min_time = INT_MAX; // the minimum time, initialize it as infinite

  /* Variable i is used in the loop */
  /* It helps to define which the current element in times[] is */
	int i;

  /* Going through the times[] array */
  /* Find which city takes shortest time to arrive */ 
	for (i = 0; i < length; i++) {
    // If the current city has not been visited 
    // If the current city's time is less than the minmum time
		if ((visited_cities[i] == 0)
      && (times[i] <= min_time)) {

			min_time = times[i];  // Update the value of min_time
			min_index = i;        // Consider the current city takes the shortest time
		}

	} /* for loop */

	return min_index;
} /* find_minimum_city */

/* 
 * This is helping function that is used to find the final distance and
 * how long it takes.
 * Parameters:
 * times[]: the array that includes the shortest time arriving to that city
 *        from the capital
 * length: the length of array times[]. 
 *         which implies how many cities (including capital) are in the graph
 * Return:
 * the maximum element in the array
 */

int find_maximum_time(int times[], int length) {
  int max_time = INT_MIN;  // Initialize the maximum time in array is the minimum

  /* Variable i is used in the loop as a counter */
  /* It helps to define which element in time[] is */
  int i;

  /* Going through the for loop and find the maximum value in time[] */
  for (i = 0; i < length; i++) {
    if (times[i] > max_time) {  // If the current value is larger than max_time
      max_time = times[i];      // Update the maximum time value
    }
  } /* for loop */

  return max_time;
} /* find_maximum_time */

/*
 * This function goes through the whole graph using Dikstra's 
 * shortest path algorithm.
 * Parameters: 
 * map_graph: the adjacency graph that describe how the graph look like
 * Return:
 * the minimum time that the messengers will take to arrive the final distance  
 */

int searching_time(int map_graph[num_entries][num_entries]) {
	// this is the array to check whether the city has been visited
	int visited[num_entries];
  int i;
  for (i = 0; i < num_entries; i++) {
    // Set up all cities has not been visited
   	visited[i] = 0;
  }

  // this is the array that count the time arrive to the cities
  int taken_time[num_entries]; 
  // initialize taken_time
  // Initialize every time in the taken_time array as the infinity  
  for (i = 0; i < num_entries; i++) {
   	taken_time[i] = INT_MAX;
  }
  // Since we start sending messages from the capital
  // The time to arrive to the capital is 0
  taken_time[0] = 0;

	// I use Dijkstra's shortest path algorithm to go through the graph
  // The discription will be shown in the attached README file

	for (i = 0; i < num_entries - 1; i++) {
    // In Dijkstra's shortest path algorithm, we always pick up the 
    // city (vertex) which has the least weight and is unvisited.
    // The index k indicates the position to start with at current time
    int k = find_minimum_city(taken_time, num_entries, visited);

    // Set up the current city has been visited
    visited[k] = 1;

    int j;
    // Find all entries that is connected with the current city k
    for (j = 0; j < num_entries; j++) {
      // The sum of:
      // 1. The time taken to arrive to city k
      // 2. The time taken to go between city k and j
      int sum = taken_time[k] + map_graph[k][j];

      // There four conditions to check whether the value of taken_time[j]
      // should be changed
      // 1. The city j that k connects has not been visited
      // 2. The taken time between k and j does not equal to 0, 
      //    which means there is an edge between k and j
      // 3. The taken time of k exists
      // 4. The sum of weight of k and the edge weight between k and j. is less
      //    than the current j's weight
      if ((visited[j] == 0)
        && (map_graph[k][j] != 0)
        && (taken_time[k] != INT_MAX)
        && (sum < taken_time[j])) {

        // If so, update the value of taken_time[j]
        taken_time[j] = taken_time[k] + map_graph[k][j];

      }
    }
  }

  // Then find the minimum time of the taken time
  // Since we already find the minimum time to arrive at each city, the maximum
  // time is the time taken to arrive to the last city, which is the minimum
  // time that going through the whole map
  int max_taken_time = find_maximum_time(taken_time, num_entries);

  // return the result
  return max_taken_time;
} /* searching_time */

/*
 * The main method
 * Usage: after compiling file, using "temp" to run this program
 * Input the number of cities and lower triangle matrix into the program
 * The solution of finding the minimum time will show on the screen
 */

int main(int argc, char **argv) {

  // First, read contains from stdin

  // This is the string that is used to read the first line from file
  char entry_char[32];
  entry_char[0] = '\0';
  size_t size;
  char ch;

  // The first line is always mean the number of elements in the graph
  // Get the first line as a string and transfer it to integer
  int index = 0;
  while ((ch = getchar()) != '\n') {
    entry_char[index++] = ch;
  }
  entry_char[index] = 0;
  if (entry_char[0] == 0) {
    fprintf(stderr, "wrong input number of city\n");
    exit(0);
  }
  num_entries = atoi(entry_char);

  // create and initialize the adjacency matrix
  int map_graph[num_entries][num_entries];
  // There are two counts variables that help to go through the whole matrix
  int i;
  int j;
  for (i = 0; i < num_entries; i++) {
  	for (j = 0; j < num_entries; j++) {
      // Initialize all elements in the adjencency graph as 0
      map_graph[i][j] = 0;
  	}
  }


  // Read the rest input from standard input
  char entry[32];
  entry[0] = 0;
  int row;
  for (row = 1; row < num_entries; row++) {
    int col = 0;
    int ind = 0;
    while ((ch = getchar()) != '\n') {
      if (ch != ' ' && ch != '\0') {
        if (ch == 'x') {
          entry[ind] = 0;
        }
        else { 
          entry[ind] = ch;
        }
        ind++;
      }
      else {
        entry[ind] = '\0';
        map_graph[row][col] = atoi(entry);
        ind = 0;
        col++;
        entry[0] = 0;
      }
    }
    entry[ind] = '\0';
    map_graph[row][col] = atoi(entry);
    ind = 0;
    entry[0] = 0;
  } 
  
  /* Copy the lower triangle's content to the upper part of matrix */
  for (i = 0; i < num_entries; i++) {
    for (j = 0; j < num_entries; j++) {
      if (j < i) {
        map_graph[j][i] = map_graph[i][j];
      }
    }
  }

//  for (i = 0; i < num_entries; i++) {
//    for (j = 0; j < num_entries; j++) {
//      printf("%d ", map_graph[i][j]);
//    }
//    printf("\n");
//  }

  // Finding the shortest path
  int shortest_time = searching_time(map_graph);
  // Write output to standard output
  fprintf(stdout, "%d\n", shortest_time);
  return 0;
}
