// Tomas Chmelevski.Student
// Transformacja Burrowsa-Wheelera
// 2023-06-21
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

const char STX = '\002', ETX = '\003';

int compareStrings(const void *a, const void *b);
int BWT(const char *s, char r[]);
void inverse(const char *r, char s[]);
void makePrintable(const char *s, char t[]);

int main(void) {
    int i, res, len;
    char *tests[6], *t, *r, *s;
    tests[0] = "banana";
    tests[1] = "milk";
    tests[2] = "bread white";
    tests[3] = "TO BE OR NOT TO BE OR WANT TO BE OR NOT?";
    tests[4] = "SIX.FIVE.FOUR.THREE.TWO.ONE",
    tests[5] = "\002BBC\003";
    for (i = 0; i < 6; ++i) {
        len = (int)strlen(tests[i]);
        t = calloc((long unsigned int)len + 1, sizeof(char));
        makePrintable(tests[i], t);
        printf("%s\n", t);
        printf(" --> ");
        r = calloc((long unsigned)(len + 3), sizeof(char));
        res = BWT(tests[i], r);
        if (res == 1) {
            printf("ERROR: String can't contain STX or ETX\n");
        }
        else {
            makePrintable(r, t);
            printf("%s\n", t);
        }
        s = calloc((long unsigned)(len + 1), sizeof(char));
        inverse(r, s);
        makePrintable(s, t);
        printf(" --> %s\n\n", t);
        free(t);
        free(r);
        free(s);
    }
    return 0;
}

int compareStrings(const void *a, const void *b) {
    char *aa = *(char **)a;
    char *bb = *(char **)b;
    return strcmp(aa, bb);
}

int BWT(const char *s, char r[]) {
    int len = strlen(s);
    char *t = malloc((len + 2) * sizeof(char));
    strcpy(t, s);
    strcat(t, "\002");
    strcat(t, "\003");

    char **suffixes = malloc(len * sizeof(char *));
    for (int i = 0; i < len; i++) {
        suffixes[i] = malloc((len + 1) * sizeof(char));
        strcpy(suffixes[i], t + i);
    }

    qsort(suffixes, len, sizeof(char *), compareStrings);

    for (int i = 0; i < len; i++) {
        r[i] = suffixes[i][len - 1];
    }
    r[len] = '\0';

    for (int i = 0; i < len; i++) {
        free(suffixes[i]);
    }
    free(suffixes);
    free(t);

    return 0;
}


void inverse(const char *r, char s[]) {
    int len = strlen(r);
    char *t = malloc((len + 3) * sizeof(char));

    strcpy(t, r);
    qsort(t, len, sizeof(char), compareStrings);

    for (int i = 0; i < len; i++) {
        char c = t[i];
        int count = 1;
        while (i < len - 1 && t[i] == t[i+1]) {
            count++;
            i++;
        }
        s[i] = count + '0';
        s[i+1] = c;
        i++;
    }
    s[len] = '\0';

    free(t);
}


void makePrintable(const char *s, char t[]) {
    strcpy(t, s);
    for ( ; *t != '\0'; ++t) {
        if (*t == STX) *t = '^';
        else if (*t == ETX) *t = '|';
    }
}
