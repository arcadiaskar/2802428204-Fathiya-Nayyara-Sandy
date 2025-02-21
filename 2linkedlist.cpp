#include <stdio.h>
#include <stdlib.h>

struct data {
    int a;
    struct data *next;
    struct data *prev;
};

struct data *head = NULL;
struct data *tail = NULL;

// Insert at Head
void insertHead(int value) {
    struct data *newNode = (struct data*)malloc(sizeof(struct data));
    newNode->a = value;
    newNode->next = head;
    newNode->prev = NULL;
    if (head != NULL) {
        head->prev = newNode;
    } else {
        tail = newNode;
    }
    head = newNode;
}

// Insert at Tail
void insertTail(int value) {
    struct data *newNode = (struct data*)malloc(sizeof(struct data));
    newNode->a = value;
    newNode->next = NULL;
    newNode->prev = tail;
    if (tail != NULL) {
        tail->next = newNode;
    } else {
        head = newNode;
    }
    tail = newNode;
}

void insertMid(int value) {
    if (head == NULL) {
        insertHead(value);
        return;
    }
    struct data *x = head;
    struct data *y = head;
    while (y->next != NULL && y->next->next != NULL) {
        x = x->next;
        y = y->next->next;
    }
    struct data *newNode = (struct data*)malloc(sizeof(struct data));
    newNode->a = value;
    newNode->next = x->next;
    newNode->prev = x;
    if (x->next != NULL) {
        x->next->prev = newNode;
    } else {
        tail = newNode;
    }
    x->next = newNode;
}

// Delete Head
void deleteHead() {
    if (head == NULL) return;
    struct data *curr = head;
    head = head->next;
    if (head != NULL) {
        head->prev = NULL;
    } else {
        tail = NULL;
    }
    free(curr);
}

// Delete Tail
void deleteTail() {
    if (tail == NULL) return;
    struct data *curr = tail;
    tail = tail->prev;
    if (tail != NULL) {
        tail->next = NULL;
    } else {
        head = NULL;
    }
    free(curr);
}

// Delete Middle
void deleteMid(int value) {
    struct data *curr = head;
    while (curr != NULL && curr->a != value) {
        curr = curr->next;
    }
    if (curr == NULL) return;
    if (curr->prev != NULL) {
        curr->prev->next = curr->next;
    } else {
        head = curr->next;
    }
    if (curr->next != NULL) {
        curr->next->prev = curr->prev;
    } else {
        tail = curr->prev;
    }
    free(curr);
}

int main(){
	int a = 0;
	int b = 0;
	int n = 0;
	int value = 0;
	
	do{
	printf("1. insert\n");
	printf("2. delete head\n");
	printf("3. exit\n");
	printf("Input: ");
	scanf("%d", &a);
	getchar();
	
	if(a == 1){
		printf("Where do you want to insert?\n");
		printf("1. Head\n");
		printf("2. Middle\n");
		printf("3. Tail\n");
		scanf("%d", &b);
		getchar();
		
		if(b == 1){
			printf("Value: ");
			scanf("%d", &value);
			insertHead(value);
		}
		else if(b == 2){
			printf("Value: ");
			scanf("%d", &value);
			insertMid(value);
		}
		else if(b == 3){
			printf("Value: ");
			scanf("%d", &value);
			insertTail(value);
		}
		
	}
	else if(a == 2){
		printf("Where do you want to delete?\n");
		printf("1. Head\n");
		printf("2. Middle\n");
		printf("3. Tail\n");
		scanf("%d", &b);
		getchar();
		
		if(b == 1){
			deleteHead();
		}
		else if(b == 2){
			deleteMid(value);
		}
		else if(b == 3){
			deleteTail();
		}
	}
	
	struct data *curr = head;
//	printf("%d", head->a);
	
		while(curr != NULL){
			printf("%d, ", curr->a);
			curr = curr->next;
		}
			printf("\n\n");
	}while(a != 3);
	
	return 0;
}


