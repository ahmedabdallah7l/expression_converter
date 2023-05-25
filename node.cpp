#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <iostream>
using namespace std;

node * creatTerm(float coef,int pow){
    node * n = (node *)malloc(sizeof(node));
    n->coef = coef;
    n->power= pow;
    n->next = nullptr;
    return n;
}
float powerX(float x , int p){
    float result = 1;
    for (int i = 0; i < p; ++i) {
        result *= x;
    }
    return result;
}

void insertSorted(node** head, node* n) {
    node* current = *head;
    if (*head == nullptr || n->power < current->power) {
        n->next = *head;
        *head = n;
        return;
    }

    while (current->next != nullptr && current->next->power < n->power) {
        current = current->next;
    }

    n->next = current->next;
    current->next = n;
}
node* getTail(node* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    return current;
}
int countNodes(node* head) {
    int count = 0;
    node* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

void deleteNode(node** head, node* toBeDeleted){
    if (*head == toBeDeleted) {
        *head = toBeDeleted->next;
        free(toBeDeleted);
        return;
    }

    node* current = *head;
    while (current != nullptr && current->next != toBeDeleted) {
        current = current->next;
    }

    if (current != nullptr) {
        current->next = toBeDeleted->next;
        free(toBeDeleted);
    }
}
float evaluatePolynomial(node* head, float x){
    if (head == nullptr){
        printf("can't evaluate an empty Polynomial\n");
    }
    float result = 0;
    node * p = head;
    while (p != nullptr){
        result += (p->coef) * powerX(x,p->power) ;
        p = p->next;
    }
    return result;
}


node * copyPolynomial(node * expr){
    node * copy = creatTerm(expr->coef,expr->power);
    node *p = expr->next;
    node *tmp = copy;
    while (p!= nullptr){
        tmp->next = creatTerm(p->coef,p->power);
        tmp = tmp->next;
        p = p->next;
    }
    return copy;

}

void freePolynomial(node* head){
    node* p ;
    while (head != nullptr) {
        p = head;
        head = head->next;
        free(p);
    }
}


int * getPowerInArray(node * head, int count){
    int * arr = (int *) malloc(sizeof(int)*count);
    int c = 0;
    node * p = head;
    while (p != nullptr){
        arr[c++] = p->power;
        p = p->next;
    }
    return arr;
}




vector<duplicate> findDuplicates(int *arr, int *arrCount) {
    vector<duplicate> duplicates;
    int size = *arrCount;
    sort(arr, arr + size);
    int count = 1;
    for (int i = 1; i < size; i++) {
        if (arr[i] == arr[i - 1]) {
            count++;
        } else {
            if (count > 1) {
                duplicate dup = {arr[i - 1], count};
                duplicates.push_back(dup);
            }
            count = 1;
        }
    }

    if (count > 1) {
        duplicate dup = {arr[size - 1], count};
        duplicates.push_back(dup);
    }

    int uniqueSize = distance(arr, std::unique(arr, arr + size));
    int* uniqueArr = (int *)malloc(sizeof(int)*uniqueSize);
    copy(arr, arr + uniqueSize, uniqueArr);
    arr = uniqueArr;
    *arrCount = uniqueSize;

    return duplicates;
}




node* sumTerms(node* head, vector<duplicate> dups) {
    if (dups.empty()) {
        return head;
    }

    node* newHead = nullptr;
    node* tmp = nullptr;
    node* tmp2 = nullptr;
    int num = 0;
    float coef = 0;

    for (const auto& dup : dups) {
        num = dup.number;
        coef = 0;
        for (int j = 0; j < dup.frequency; ++j) {
            tmp = head;
            while (tmp != nullptr) {
                if (tmp->power == num) {
                    coef += tmp->coef;
                    deleteNode(&head, tmp);
                    break;
                }
                tmp = tmp->next;
            }
        }
        if (newHead == nullptr) {
            newHead = creatTerm(coef, num);
            tmp2 = newHead;
        } else {
            tmp2->next = creatTerm(coef, num);
            tmp2 = tmp2->next;
        }
    }

    tmp = head;
    while (tmp != nullptr) {
        node* next = tmp->next;
        insertSorted(&newHead, tmp);
        tmp = next;
    }


    return newHead;
}
vector<duplicate> getDups(node * expression1){
    int * arr;
    int size ;
    size = countNodes(expression1);
    arr = getPowerInArray(expression1, size);
    vector<duplicate> dup = findDuplicates(arr, &size);
    return dup;
}

node * addPolynomials(node * exp1, node *exp2){
    node* copy1 = copyPolynomial(exp1);
    node* copy2 = copyPolynomial(exp2);
    node * tmp = copy1;
    while (tmp->next != nullptr) tmp = tmp->next;
    tmp->next = copy2;
    return copy1;
}
node * recMultiply(node *expr, node * term){
    if(term == nullptr){
    } else {
        node * tmp = expr;
        while (tmp != nullptr){
            tmp->coef *= term->coef;
            tmp->power += term->power;
            tmp = tmp->next;
        }
        recMultiply(expr, term->next);
    }
    return expr;
}