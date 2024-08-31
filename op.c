#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *input;
int i = 0;
char lasthandle[6], stack[50], handles[][5] = {")E(", "E*E", "E+E", "i", "E^E", "E-E", "E/E"};
int top = 0, l;
char prec[9][9] = {
/*stack +     -    *    /    ^    i    (    )    $ */
/* + */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
/* - */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
/* * */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
/* / */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
/* ^ */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
/* i */ '>', '>', '>', '>', '>', 'e', 'e', '>', '>',
/* ( */ '<', '<', '<', '<', '<', '<', '<', '>', 'e',
/* ) */ '>', '>', '>', '>', '>', 'e', 'e', '>', '>',
/* $ */ '<', '<', '<', '<', '<', '<', '<', '<', '=',
};

int getindex(char c) {
    switch (c) {
        case '+': return 0;
        case '-': return 1;
        case '*': return 2;
        case '/': return 3;
        case '^': return 4;
        case 'i': return 5;
        case '(': return 6;
        case ')': return 7;
        case '$': return 8;
        default: return -1; // Error case
    }
}

void shift() {
    stack[++top] = *(input + i++);
    stack[top + 1] = '\0';
}

int reduce() {
    int j, len, found, t;
    for (j = 0; j < 7; j++) { // Selecting handles
        len = strlen(handles[j]);
        if (stack[top] == handles[j][0] && top + 1 >= len) {
            found = 1;
            for (t = 0; t < len; t++) {
                if (stack[top - t] != handles[j][t]) {
                    found = 0;
                    break;
                }
            }
            if (found == 1) {
                stack[top - len + 1] = 'E';
                top = top - len + 1;
                strcpy(lasthandle, handles[j]);
                stack[top + 1] = '\0';
                return 1;
            }
        }
    }
    return 0;
}

void dispstack() {
    int j;
    for (j = 0; j <= top; j++)
        printf("%c", stack[j]);
}

void dispinput() {
    int j;
    for (j = i; j < l; j++)
        printf("%c", *(input + j));
}

int main() {
    input = (char *)malloc(50 * sizeof(char));
    printf("Enter the string\n");
    scanf("%s", input);
    input = strcat(input, "$");
    l = strlen(input);
    strcpy(stack, "$");
    printf("\nSTACK\tINPUT\tACTION");

    while (i <= l) {
        shift();
        printf("\n");
        dispstack();
        printf("\t");
        dispinput();
        printf("\tShift");

        if (prec[getindex(stack[top])][getindex(input[i])] == '>') {
            while (reduce()) {
                printf("\n");
                dispstack();
                printf("\t");
                dispinput();
                if (strcmp(lasthandle, ")E(") == 0) {
                    strcpy(lasthandle, "(E)");
                }
                printf("\tReduced: E -> %s", lasthandle);
            }
        }
    }

    if (strcmp(stack, "$E$") == 0)
        printf("\nAccepted\n");
    else
        printf("\nNot Accepted\n");

    free(input); // Free the allocated memory
    return 0;
}


