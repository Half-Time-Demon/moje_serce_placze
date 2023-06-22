// Transformacja Burrowsa-Wheelera

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
    // realizacja algorytmu BWT do kompresji lancucha
}

void inverse(const char *r, char s[]) {
    //  realizacja algorytmu BWT do dekompresji lancucha
}

void makePrintable(const char *s, char t[]) {
    strcpy(t, s);
    for ( ; *t != '\0'; ++t) {
        if (*t == STX) *t = '^';
        else if (*t == ETX) *t = '|';
    }
}
