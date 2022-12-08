// Blocked matrix multiplication is a technique in which you separate a matrix into different 'blocks' in which you calculate each block one at a time. 
#include <iostream>  
#include <omp.h> 
#include <time.h>
#include <stdlib.h>

using namespace std;

#define MatrixOrder 2048
#define FactorIntToDouble 1.1; 

double firstParaMatrix [MatrixOrder] [MatrixOrder] = {0.0};  
double secondParaMatrix [MatrixOrder] [MatrixOrder] = {0.0};
double matrixMultiResult [MatrixOrder] [MatrixOrder] = {0.0};

void matrixInit()
{
    for(int row = 0 ; row < MatrixOrder ; row++ ) {
        for(int col = 0 ; col < MatrixOrder ;col++){
            srand(row+col);
            firstParaMatrix [row] [col] = ( rand() % 10 ) * FactorIntToDouble;
            secondParaMatrix [row] [col] = ( rand() % 10 ) * FactorIntToDouble;
        }
    }
}

void smallMatrixMult (int upperOfRow , int bottomOfRow , 
                      int leftOfCol , int rightOfCol ,
                      int transLeft ,int transRight )
{
    int row=upperOfRow;
    int col=leftOfCol;
    int trans=transLeft;

    #pragma omp parallel for num_threads(16)
    for(int row = upperOfRow ; row <= bottomOfRow ; row++){
        for(int col = leftOfCol ; col < rightOfCol ; col++){
            for(int trans = transLeft ; trans <= transRight ; trans++){
                matrixMultiResult [row] [col] += firstParaMatrix [row] [trans] * secondParaMatrix [trans] [col] ;
            }
        }
    }
}

void matrixMulti(int upperOfRow , int bottomOfRow , 
                 int leftOfCol , int rightOfCol ,
                 int transLeft ,int transRight )
{
    if ( ( bottomOfRow - upperOfRow ) < 512 ) 
        smallMatrixMult ( upperOfRow , bottomOfRow , 
                          leftOfCol , rightOfCol , 
                          transLeft , transRight );·

    else
    {
        #pragma omp task
        {
            matrixMulti( upperOfRow , ( upperOfRow + bottomOfRow ) / 2 ,
                         leftOfCol , ( leftOfCol + rightOfCol ) / 2 ,
                         transLeft , ( transLeft + transRight ) / 2 );
            matrixMulti( upperOfRow , ( upperOfRow + bottomOfRow ) / 2 ,
                         leftOfCol , ( leftOfCol + rightOfCol ) / 2 ,
                         ( transLeft + transRight ) / 2 + 1 , transRight );
        }

        #pragma omp task
        {
            matrixMulti( upperOfRow , ( upperOfRow + bottomOfRow ) / 2 ,
                         ( leftOfCol + rightOfCol ) / 2 + 1 , rightOfCol ,
                         transLeft , ( transLeft + transRight ) / 2 );
            matrixMulti( upperOfRow , ( upperOfRow + bottomOfRow ) / 2 ,
                         ( leftOfCol + rightOfCol ) / 2 + 1 , rightOfCol ,
                         ( transLeft + transRight ) / 2 + 1 , transRight );
        }
        

        #pragma omp task
        {
            matrixMulti( ( upperOfRow + bottomOfRow ) / 2 + 1 , bottomOfRow ,
                         leftOfCol , ( leftOfCol + rightOfCol ) / 2 ,
                         transLeft , ( transLeft + transRight ) / 2 );
            matrixMulti( ( upperOfRow + bottomOfRow ) / 2 + 1 , bottomOfRow ,
                         leftOfCol , ( leftOfCol + rightOfCol ) / 2 ,
                         ( transLeft + transRight ) / 2 + 1 , transRight );
        }

        #pragma omp task
        {
            matrixMulti( ( upperOfRow + bottomOfRow ) / 2 + 1 , bottomOfRow ,
                         ( leftOfCol + rightOfCol ) / 2 + 1 , rightOfCol ,
                         transLeft , ( transLeft + transRight ) / 2 );
            matrixMulti( ( upperOfRow + bottomOfRow ) / 2 + 1 , bottomOfRow ,
                         ( leftOfCol + rightOfCol ) / 2 + 1 , rightOfCol ,
                         ( transLeft + transRight ) / 2 + 1 , transRight );
        }

        #pragma omp taskwait
    }
}

int main()  
{ 
    matrixInit();

    clock_t t1 = clock(); 

    matrixMulti( 0 , MatrixOrder - 1 , 0 , MatrixOrder -1 , 0 , MatrixOrder -1 );

    clock_t t2 = clock(); 
    cout<<"time: "<<t2-t1<<endl; 
    
    system("pause");

    return 0;  
}  