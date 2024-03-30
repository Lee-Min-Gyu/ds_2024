#ifndef LINKEDLISTBASIC_H
#define LINKEDLISTBASIC_H

#include <stdio.h>
#include <stdlib.h>
#include "ListNode.h"

typedef struct {
    struct ListNode* __head;
    struct ListNode* __tail;
    int __numItems;
} LinkedListBasic;

LinkedListBasic* LinkedListBasic_create() {
    LinkedListBasic* list = (LinkedListBasic*)malloc(sizeof(LinkedListBasic));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    list->__head = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (list->__head == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    list->__head->item = -1; // dummy
    list->__head->next = NULL;
    list->__tail = list->__head;
    list->__numItems = 0;
    return list;
}

void LinkedListBasic_insert(LinkedListBasic* list, int i, int newItem) {
    if (0 <= i && i <= list->__numItems) {
        struct ListNode* prev = list->__head;
        for (int index = 0; index < i; index++) {
            prev = prev->next;
        }
        struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        if (newNode == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        newNode->item = newItem;
        newNode->next = prev->next;
        prev->next = newNode;
        if (newNode->next == NULL) {
            list->__tail = newNode;
        }
        list->__numItems++;
    } else {
        printf("index %d : out of bound in insert()\n", i);
    }
}

void LinkedListBasic_append(LinkedListBasic* list, int newItem) {
    list->__tail->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (list->__tail->next == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    list->__tail = list->__tail->next;
    list->__tail->item = newItem;
    list->__tail->next = NULL;
    list->__numItems++;
}

int LinkedListBasic_pop(LinkedListBasic* list, int i) {
    if (list->__numItems == 0) {
        return -1; // 리스트가 비어있는 경우
    } else if (0 <= i && i < list->__numItems) {
        struct ListNode* prev;
        struct ListNode* curr;
        if (i == 0) {
            prev = list->__head;
        } else {
            prev = list->__head;
            for (int index = 0; index < i; index++) {
                prev = prev->next;
            }
        }
        curr = prev->next;
        int retItem = curr->item;
        prev->next = curr->next;
        if (curr == list->__tail) {
            list->__tail = prev;
        }
        free(curr);
        list->__numItems--;
        return retItem;
    } else {
        return -1; // 인덱스가 올바르지 않은 경우
    }
}

int LinkedListBasic_remove(LinkedListBasic* list, int x) {
    struct ListNode* prev = list->__head;
    struct ListNode* curr = prev->next;
    while (curr != NULL) {
        if (curr->item == x) {
            prev->next = curr->next;
            if (curr == list->__tail) {
                list->__tail = prev;
            }
            free(curr);
            list->__numItems--;
            return x;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    return -1;
}

int LinkedListBasic_get(LinkedListBasic* list, int i) {
    if (0 <= i && i < list->__numItems) {
        struct ListNode* curr = list->__head->next;
        for (int index = 0; index < i; index++) {
            curr = curr->next;
        }
        return curr->item;
    } else {
        return -1;
    }
}

int LinkedListBasic_index(LinkedListBasic* list, int x) {
    struct ListNode* curr = list->__head->next;
    int index = 0;
    while (curr != NULL) {
        if (curr->item == x) {
            return index;
        } else {
            curr = curr->next;
            index++;
        }
    }
    return -2;
}

int LinkedListBasic_isEmpty(LinkedListBasic* list) {
    return list->__numItems == 0;
}

int LinkedListBasic_size(LinkedListBasic* list) {
    return list->__numItems;
}

void LinkedListBasic_clear(LinkedListBasic* list) {
    struct ListNode* curr = list->__head->next;
    while (curr != NULL) {
        struct ListNode* temp = curr;
        curr = curr->next;
        free(temp);
    }
    list->__head->next = NULL;
    list->__tail = list->__head;
    list->__numItems = 0;
}

int LinkedListBasic_count(LinkedListBasic* list, int x) {
    int cnt = 0;
    struct ListNode* curr = list->__head->next;
    while (curr != NULL) {
        if (curr->item == x) {
            cnt++;
        }
        curr = curr->next;
    }
    return cnt;
}

void LinkedListBasic_extend(LinkedListBasic* list, LinkedListBasic* a) {
    for (int index = 0; index < LinkedListBasic_size(a); index++) {
        LinkedListBasic_append(list, LinkedListBasic_get(a, index));
    }
}

LinkedListBasic* LinkedListBasic_copy(LinkedListBasic* list) {
    LinkedListBasic* a = LinkedListBasic_create();
    for (int index = 0; index < list->__numItems; index++) {
        LinkedListBasic_append(a, LinkedListBasic_get(list, index));
    }
    return a;
}

void LinkedListBasic_reverse(LinkedListBasic* list) {
    LinkedListBasic* a = LinkedListBasic_create();
    for (int index = 0; index < list->__numItems; index++) {
        LinkedListBasic_insert(a, 0, LinkedListBasic_get(list, index));
    }
    LinkedListBasic_clear(list);
    for (int index = 0; index < LinkedListBasic_size(a); index++) {
        LinkedListBasic_append(list, LinkedListBasic_get(a, index));
    }
    free(a);
}



#endif
