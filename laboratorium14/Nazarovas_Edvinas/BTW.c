/*
  * Imie: Edvinas
  * Opis: Zaimplementowac algorytm BTW i BTW Inverse
  * Data: 2023-06-20
  * Nazwa pliku: BWT.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  int data;
  struct node *next;
};

struct rotation {
  int index;
  char *suffix;
};

int cmpfunc(const void *a, const void *b) {
  const char *ia = (const char *)a;
  const char *ib = (const char *)b;
  return strcmp(ia, ib);
}

int cmpfuncRotate(const void *x, const void *y) {
  struct rotation *rx = (struct rotation *)x;
  struct rotation *ry = (struct rotation *)y;
  return strcmp(rx->suffix, ry->suffix);
}

int *computeSuffixArray(char *input_text, int len_text) {
  struct rotation suff[len_text];

  for (int i = 0; i < len_text; i++) {
    suff[i].index = i;
    suff[i].suffix = (input_text + i);
  }

  qsort(suff, len_text, sizeof(struct rotation), cmpfuncRotate);

  int *suffix_arr = (int *)malloc(len_text * sizeof(int));
  for (int i = 0; i < len_text; i++)
    suffix_arr[i] = suff[i].index;

  return suffix_arr;
}

char *findLastChar(char *input_text, int *suffix_arr, int n) {
  char *bwt_arr = (char *)malloc(n * sizeof(char));
  int i;
  for (i = 0; i < n; i++) {
    int j = suffix_arr[i] - 1;
    if (j < 0)
      j = j + n;

    bwt_arr[i] = input_text[j];
  }

  bwt_arr[i] = '\0';

  return bwt_arr;
}

struct node *getNode(int i) {
  struct node *nn = (struct node *)malloc(sizeof(struct node));
  nn->data = i;
  nn->next = NULL;
  return nn;
}

void addAtLast(struct node **head, struct node *nn) {
  if (*head == NULL) {
    *head = nn;
    return;
  }
  struct node *temp = *head;
  while (temp->next != NULL)
    temp = temp->next;
  temp->next = nn;
}

void *computeLShift(struct node **head, int index, int *l_shift) {
  l_shift[index] = (*head)->data;
  (*head) = (*head)->next;
}

void invert(char bwt_arr[]) {
  int i, len_bwt = strlen(bwt_arr);
  char *sorted_bwt = (char *)malloc(len_bwt * sizeof(char));
  strcpy(sorted_bwt, bwt_arr);
  int *l_shift = (int *)malloc(len_bwt * sizeof(int));

  int x = 4;

  qsort(sorted_bwt, len_bwt, sizeof(char), cmpfunc);

  struct node *arr[128] = {NULL};

  for (i = 0; i < len_bwt; i++) {
    struct node *nn = getNode(i);
    addAtLast(&arr[bwt_arr[i]], nn);
  }

  for (i = 0; i < len_bwt; i++)
    computeLShift(&arr[sorted_bwt[i]], i, l_shift);

  printf("Inverse --> ");
  for (i = 0; i < len_bwt; i++) {
    x = l_shift[x];
    printf("%c", bwt_arr[x]);
  }
}

int main() {
  char *input_text[6];
  input_text[0] = "banana$";
  input_text[1] = "milk";
  input_text[2] = "bread white";
  input_text[3] = "TO BE OR NOT TO BE OR WANT TO BE OR NOT?";
  input_text[4] = "SIX.FIVE.FOUR.THREE.TWO.ONE";
  input_text[5] = "\002BBC\003";

  for (int i = 0; i < 6; i++) {
    int len_text = strlen(input_text[i]);

    int *suffix_arr = computeSuffixArray(input_text[i], len_text);

    char *bwt_arr = findLastChar(input_text[i], suffix_arr, len_text);

    printf("\n%s\n", input_text[i]);
    printf("BWT--> %s\n", bwt_arr);
    invert(input_text[i]);
    printf("\n");
  }

  return 0;
}
