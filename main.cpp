#include "main.h"
#include <stdio.h>
#include <iostream>
using namespace std;



int main(){

    node * expression1 = nullptr;
    node * expression2 = nullptr;
    node * summation = nullptr;
    node * product = nullptr;
    node * term = nullptr;
    int choice;
    printf("\nMENU\n");
    while (1) {
        choice = getChoise();

        switch (choice) {
            case 1:
                term = getTerm();
                insertSorted(&expression1, term);
                break;
            case 2:
                term = getTerm();
                insertSorted(&expression2, term);
                break;
            case 3:
                printf("\nA(x) = ");
                expression1 = sumTerms(expression1, getDups(expression1));
                printPolynomial(expression1);
                break;
            case 4:
                printf("\nB(x) = ");
                expression2 = sumTerms(expression2, getDups(expression2));
                printPolynomial(expression2);
                break;
            case 5:
                int c;
                float x;
                c = getChoise2();
                x = 0;
                printf("Enter the value of x: ");

                scanf("%f",&x);
                fflush(stdin);
                switch (c) {
                    case 1:
                        cheakEval(expression1, "A", x);
                        break;
                    case 2:
                        cheakEval(expression2, "B", x);
                        break;
                    case 3:
                        cheakEval(summation, "summation", x);
                        break;
                    case 4:
                        cheakEval(product, "product", x);
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");

                }
                break;
            case 6:
                if (expression2 == nullptr || expression1 == nullptr){
                    printf("can't do summation\n");
                } else{
                    printf("A(x) + B(x) = ");
                    summation = addPolynomials(expression1,expression2);
                    summation = sumTerms(summation, getDups(summation));
                    printPolynomial(summation);
                }
                break;
            case 7:
                if (expression2 == nullptr || expression1 == nullptr){
                    printf("can't do multiplication\n");
                } else if (countNodes(expression1) > countNodes(expression2)){
                    product = recMultiply(copyPolynomial(expression1), copyPolynomial(expression2));
                } else{
                    product = recMultiply(copyPolynomial(expression2), copyPolynomial(expression1));
                }
                product = sumTerms(product, getDups(product));
                printf("A(x) * B(x) = ");
                printPolynomial(product);
                break;
            case 8:
                printf("\n1. free A(x)\n");
                printf("2. free B(x)\n");
                printf("3. free summation(x)\n");
                printf("4. free product(x)\n Enter choice :");
                int ch;
                scanf("%d",&c);
                fflush(stdin);
                switch (c) {
                    case 1:
                        freePolynomial(expression1);
                        printf("\n DONE \n");
                        break;
                    case 2:
                        freePolynomial(expression2);
                        printf("\n DONE \n");
                        break;
                    case 3:
                        freePolynomial(summation);
                        printf("\n DONE \n");
                        break;
                    case 4:
                        freePolynomial(product);\
                        printf("\n DONE \n");
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
                break;
            case 9:
                printf("\nGoodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}