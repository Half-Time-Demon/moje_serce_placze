/*
  * Imie: Edvinas
  * Opis: Zaimplementowanie algorytmu kompresji Huffman + LZ77
  * Data: 2023-06-20
  * Nazwa pliku: LZ77_Huffman.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1000

void huffman_lz77_algorithm(char* input_string);

int main(void) {
  char *input;
  input = "TO BE OR NOT TO BE OR WANT TO BE OR NOT?";

  huffman_lz77_algorithm(input);

  return 0;
}

/*
    This function implements the Huffman-LZ77 algorithm for data compression.

    Parameters:
    input_string (char*): The string to be compressed

    Returns:
    None
    */
void huffman_lz77_algorithm(char* input_string) {
    // Check if input string is empty
    if (strlen(input_string) == 0) {
        printf("Error: Input string is empty\n");
        return;
    }

    // Initialize variables
    int i, j, k, len, count, index, found, match_len, match_index;
    char window[MAX_LEN], lookahead[MAX_LEN];
    len = (int)strlen(input_string);
    count = 0;

    // Initialize window and lookahead buffers
    for (i = 0; i < len; i++) {
        if (i < MAX_LEN) {
            window[i] = input_string[i];
        } else {
            lookahead[i-MAX_LEN] = input_string[i];
        }
    }

    // Compress the input string
    while (count < len) {
        found = 0;
        match_len = 0;
        match_index = 0;

        // Search for longest match in window
        for (i = 0; i < MAX_LEN; i++) {
            if (window[i] == lookahead[0]) {
                index = i;
                for (j = 0, k = i; j < len && k < MAX_LEN; j++, k++) {
                    if (window[k] == lookahead[j]) {
                        match_len++;
                    } else {
                        break;
                    }
                }
                if (match_len > 0 && match_len > found) {
                    found = match_len;
                    match_index = index;
                }
            }
        }

        // Output match or literal
        if (found > 0) {
            printf("<%d,%d>", MAX_LEN-match_index, found);
            count += found;
        } else {
            printf("%c", lookahead[0]);
            count++;
        }

        // Shift window and lookahead buffers
        for (i = 0; i < MAX_LEN-1; i++) {
            window[i] = window[i+1];
        }
        window[MAX_LEN-1] = lookahead[0];
        for (i = 0; i < len-MAX_LEN-1; i++) {
            lookahead[i] = lookahead[i+1];
        }
        if (len-count > MAX_LEN) {
            lookahead[len-MAX_LEN-1] = input_string[MAX_LEN+count];
        } else {
            lookahead[len-MAX_LEN-1] = input_string[count];
        }
    }
}
