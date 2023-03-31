#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main2()
{

//Declartion
int v,w;
float x,y;

//Get User inputs
scanf("%d %d %f %f" ,&v,&w,&x,&y);

//calculation
    v = v+w;
    w = v-(2*w);
    x = x+y;
    y = x-(2*y);

//print results
printf("%d %d \n%2.1f %2.1f",v,w, x, y);

    return 0;
}
