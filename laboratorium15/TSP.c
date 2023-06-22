#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to swap two elements
void swap(int *a, int *b);
// Function to reverse the sub-array starting from i to j
void reverse(int arr[], int i, int j);

// Function to find the lexicographically next permutation of a sequence
int next_permutation(int arr[], int n);

// Function to find the minimum cost of traversing a given set of cities
int tsp(int graph[][4], int n);

// Driver code
int main(void) {
    // Create a graph of 4 cities
    int graph[4][4] = {
        {0, 10, 20, 20},
        {10, 0, 40, 25},
        {20, 40, 0, 30},
        {20, 25, 30, 0}
    };

    // Find the minimum cost of traversing the cities
    int min_cost = tsp(graph, 4);

    // Print the minimum cost
    printf("The minimum cost of traversing the cities is %d\n", min_cost);

    return 0;
}


// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to reverse the sub-array starting from i to j
void reverse(int arr[], int i, int j) {
    while (i < j) {
        swap(&arr[i], &arr[j]);
        i++;
        j--;
    }
}

// Function to find the lexicographically next permutation of a sequence
int next_permutation(int arr[], int n) {
    // Find the largest index i such that arr[i-1] is less than arr[i]
    int i = n - 1;
    while (i > 0 && arr[i - 1] >= arr[i]) {
        i--;
    }

    // If i is 0, the sequence is in descending order, so there is no next permutation
    if (i == 0) {
        return 0;
    }

    // Find the largest index j such that arr[j] is greater than arr[i-1]
    int j = n - 1;
    while (arr[j] <= arr[i - 1]) {
        j--;
    }

    // Swap arr[i-1] and arr[j]
    swap(&arr[i - 1], &arr[j]);

    // Reverse the sub-array arr[i..n-1]
    reverse(arr, i, n - 1);

    // Return true as the next permutation is found
    return 1;
}

// Function to find the minimum cost of traversing a given set of cities
int tsp(int graph[][4], int n) {
    // Create an array of size n-1 containing cities 1 to n-1
    int arr[n - 1];
    for (int i = 0; i < n - 1; i++) {
        arr[i] = i + 1;
    }

    // Initialize min_cost to infinity
    int min_cost = INT_MAX;

    // Find the minimum cost by generating all permutations of the array
    do {
        // Initialize cost to 0
        int cost = 0;

        // Add the cost of traversing from the starting city to the first city in the permutation
        cost += graph[0][arr[0]];

        // Add the cost of traversing from each city in the permutation to the next city
        for (int i = 0; i < n - 2; i++) {
            cost += graph[arr[i]][arr[i + 1]];
        }

        // Add the cost of traversing from the last city in the permutation to the starting city
        cost += graph[arr[n - 2]][0];

        // Update min_cost if the current cost is less than min_cost
        if (cost < min_cost) {
            min_cost = cost;
        }
    } while (next_permutation(arr, n - 1) > 0);

    // Return the minimum cost
    return min_cost;
}
