#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
void main(){
    FILE *file=fopen("SE.txt","w");
    fprintf(file,"%s","abc");
    printf("Success");
    getch();
}