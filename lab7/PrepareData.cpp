#include <stdlib.h>
#include <math.h>

float FunctionData[100][3];
int   NoPoints;

void PrepareData(int fun)
{
    int i;
    float x,y;
    srand(376257);

    switch (fun)
    {
        case 0: NoPoints=5;
            FunctionData[0][0]=-1.0;	FunctionData[0][1]= 1.0;	FunctionData[0][2]= 0.0;
	        FunctionData[1][0]= 1.0;	FunctionData[1][1]= 1.0;	FunctionData[1][2]=25.0;
	        FunctionData[2][0]= 1.0;	FunctionData[2][1]=-1.0;	FunctionData[2][2]= 5.0;
	        FunctionData[3][0]=-1.0;	FunctionData[3][1]=-1.0;	FunctionData[3][2]=25.0;
	        FunctionData[4][0]= 0.0;	FunctionData[4][1]= 0.0;	FunctionData[4][2]=15.0;
	        break;
        case 1: NoPoints=20;
            for (i=0; i<NoPoints; i++)
            {
                x=4.8*(float(rand())/RAND_MAX)-2.4;
                y=4.8*(float(rand())/RAND_MAX)-2.4;
                FunctionData[i][0]=x;
                FunctionData[i][1]=y;
                FunctionData[i][2]=200*(float(rand())/RAND_MAX);
            }
            break;
        case 2: NoPoints=100;
            for (i=0; i<NoPoints; i++)
            {
                x=4.8*(float(rand())/RAND_MAX)-2.4;
                y=4.8*(float(rand())/RAND_MAX)-2.4;
                FunctionData[i][0]=x;
                FunctionData[i][1]=y;
                FunctionData[i][2]=x*(2*x-7)*(2*y+1)+2*y;
            }
            break;
        case 3: NoPoints=10;
            for (i=0; i<NoPoints; i++)
            {
                x=4.8*(float(rand())/RAND_MAX)-2.4;
                y=4.8*(float(rand())/RAND_MAX)-2.4;
                FunctionData[i][0]=x;
                FunctionData[i][1]=y;
                FunctionData[i][2]=x*sinf(2*y);
            }
            break;
        case 4: NoPoints=100;
            for (i=0; i<NoPoints; i++)
            {
                x=2*(float(rand())/RAND_MAX)-1;
                y=2*(float(rand())/RAND_MAX)-1;
                FunctionData[i][0]=x;
                FunctionData[i][1]=y;
                FunctionData[i][2]=sinf(8*(x*x+y*y));
            }
            break;
    }
}

float Shepard(float terrain[100][3], float x, float y) {
    float xk = terrain[0][0], yk = terrain[0][1], wk = 0;
    float sumUpper = 0, sumLower = 0;
    for (int i = 0; i < NoPoints; i++)
    {
        xk = terrain[i][0];
        yk = terrain[i][1];
        wk = 1.0 / fabs((x - xk) * (x - xk) + (y - yk) * (y - yk));
        sumUpper += wk * terrain[i][2];
        sumLower += wk;
    }
    return sumUpper / sumLower;
}