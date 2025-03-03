#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stack {
    char data;
    struct Stack *next;
} *top = NULL;

void push(char c) {
    struct Stack *newNode = (struct Stack *)malloc(sizeof(struct Stack));
    newNode->data = c;
    newNode->next = top;
    top = newNode;
}

char pop() {
    if (top == NULL) return '\0';
    struct Stack *temp = top;
    char popped = temp->data;
    top = top->next;
    free(temp);
    return popped;
}

char peek() {
    return (top == NULL) ? '\0' : top->data;
}

int before(char symbol) {
    if (symbol == '^') return 3;
    if (symbol == '*' || symbol == '/') return 2;
    if (symbol == '+' || symbol == '-') return 1;
    return 0;
}

void infixToPostfix(char infix[]) {
    char postfix[100] = "";
    int index = 0;

    for (int i = 0; i < strlen(infix); i++) {
        char c = infix[i];

        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            postfix[index++] = c;
        } else if (c == '(') {
            push(c);
        } else if (c == ')') {
            while (top != NULL && peek() != '(') {
                postfix[index++] = pop();
            }
            pop(); 
        } else {
            while (top != NULL && before(peek()) >= before(c)) {
                postfix[index++] = pop();
            }
            push(c);
        }
    }

    while (top != NULL) {
        postfix[index++] = pop();
    }

    postfix[index] = '\0';
    printf("%s\n", postfix);
}

int main() {
    char infix[100];
    scanf("%99[^\n]", infix);
    infixToPostfix(infix);
    return 0;
}
