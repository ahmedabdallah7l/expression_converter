//
// Created by pc on 5/12/2023.
//

#ifndef POLYNOMIALEXPRESSIONS_MAIN_H
#define POLYNOMIALEXPRESSIONS_MAIN_H
#include <iostream>
#include <vector>
using namespace std;

struct node {
    float coef;
    int power;
    node* next;
};
struct duplicate {
    int number;
    int frequency;
};

node* getTerm();
node * creatTerm(float coef,int pow);
node * copyPolynomial(node * exp);
node * addPolynomials(node * exp1, node *exp2);
node * recMultiply(node *expr, node * term);
float evaluatePolynomial(node* head, float x);
float powerX(float x , int p);
void freePolynomial(node* head);
void printPolynomial(node* head);
bool validate2(string input);
int getChoise();
int getChoise2();
void cheakEval(node * expr, string type,float x);

void deleteNode(node** head, node* toBeDeleted);
vector<duplicate> findDuplicates(int *arr, int *arrCount);
vector<duplicate> getDups(node * expression1);
node * sumTerms(node * head, vector<duplicate> dups);
void insertSorted(node** head, node* n);
int * getPowerInArray(node * head, int count);
int countNodes(node* head);

#endif //POLYNOMIALEXPRESSIONS_MAIN_H
