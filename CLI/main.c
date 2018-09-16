#include <stdio.h>
#include <stdlib.h>
#include "checkcopy.h"

int main(int argc,char *argv[]){
	char hasil[25];
	float result=test3("../pustaka2.c","../pustaka1.c", hasil);
	printf("%.2f\n",result);
}
