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
		if ((visited_cities[i] == 0)    /* If the current city has not been visited */
      && (times[i] <= min_time)) {  /* If the current city's time is less than the minmum time */

			min_time = times[i];  /* Update the value of min_time */
			min_index = i;        /* Consider the current city takes the shortest time */
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
	// initialize taken_time 
  int i;
  for (i = 0; i < num_entries; i++) {
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
  // The capital 
  taken_time[0] = 0;

	// I use Dijkstra's shortest path algorithm to go through the graph
  // The discription will be shown in the attached README file

  
	for (i = 0; i < num_entries - 1; i++) {
    // Since 
    int k = find_minimum_city(taken_time, num_entries, visited);

    visited[k] = 1;

    int j;
    for (j = 0; j < num_entries; j++) {

      int sum = taken_time[k] + map_graph[k][j];

      if ((visited[j] == 0)
        && (map_graph[k][j] != 0)
        && (taken_time[k] != INT_MAX)
        && (sum < taken_time[j])) {

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
 * Usage: after compiling file, using "temp filename" to run this program
 */

int main(int argc, char **argv) {

  // First, check whether the argument is given in proper
  // If the number of arguments is less than 2,
  // print out error and exit from the program

  if (argc < 2) {
    fprintf(stdout, "\nPlease give a file name\n\n");
    exit(0);
  }

  // Then we have the file name, open and read the file
  
  FILE *f = fopen(argv[1], "r+");

  // If the file cannot be opened
  // print out the error and exit from the program

  if (f == NULL) {
    fprintf(stderr, "\nProblem: Cannot open the file.\n\n");
    exit(0);
  }

  // This is the string that is used to read the first line from file
  char entry_char[32];

  // The first line is always mean the number of elements in the graph
  // Get the first line as a string and transfer it to integer
  fgets(entry_char, 32, f); 
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

  // The string that is used to store the line read from the file
  char line[MAX_LEN]; 
  // Varialbe count is used to define the current read line 
  int count = 0;

  // read from the given file to receive the graph
  while ((fgets(line, sizeof(line), f))) {
    // define the variable part to get the part of string
    char *part;

    // Variable col count the column number of the graph
    int col = 0;

    // save the taken time from file into the adjacency matrix
    part = strtok(line, " ");

    while (part != NULL) {
      // If the current element is x, there's no edge between two cities
      // Set the time as 0
      if (!strcmp(part, "x")) {
        map_graph[count + 1][col] = 0;
      }
      // Else, there is an edge between two cities
      // Read from file and use atoi() to trans from string to integer
      else {
        map_graph[count + 1][col] = atoi(part);
       }

       // keep getting the part from read line
      part = strtok(NULL, " ");
      col++;
    } /* While loop*/

    // add the row number
    count++;

  } /* While loop */

  fclose(f);

  /* Copy the lower triangle's content to the upper part of matrix */
  for (i = 0; i < num_entries; i++) {
    for (j = 0; j < num_entries; j++) {
      if (j < i) {
        map_graph[j][i] = map_graph[i][j];
      }
    }
  }

  // Finding the shortest path
  int shortest_time = searching_time(map_graph);

  printf("The shortest taken time is: %d\n", shortest_time);

  return 0;
}
