#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main()
{

   int n;
    scanf("%d", &n);

    //this to make \n every round
    for(int i = 1; i<n*2; i++)
    {
        //here to fill line contents
        for(int j = 1; j<n*2; j++)
        {
            int x = i, y = j;  //know where we are
            if(x>n) x = n*2-x; // based on where we are(which round in vertical an horzontal loop)
                                //in the block calculate the value of x,y
            if(y>n) y = n*2-y;
            x = (x<y)? x:y;
            printf("%d ",n-x+1);
        }
        printf("\n");
    }
 return 0;
}
