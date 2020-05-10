//gcc -Wall -fopenMP crypto.c -o crypto.o -lm
//./crypto.o


#include <stdio.h> 
#include <stdlib.h>
#include <math.h> 
#include <time.h>
#include <omp.h>

// A function to print all prime factors of a given number n 
void primeFactors(int n) 
{ 
    // Print the number of 2s that divide n 
    {
        while (n%2 == 0) 
        { 
            printf("%d ", 2); 
            n = n/2; 
        } 
      
        // n must be odd at this point.  So we can skip  
        // one element (Note i = i +2) 
        for (int i = 3; i <= sqrt(n); i = i+2) 
        { 
            // While i divides n, print i and divide n 
            while (n%i == 0) 
            { 
                printf("%d ", i); 
                n = n/i; 
            } 
        } 
      
        // This condition is to handle the case when n is a prime number greater than 2 
        if (n > 2){ 
            printf ("%d ", n);
        } 
    }
}

//having trouble writing the values of primeFactors into the file
//function writes to a file but not the values.
void writeToFile(int number){

    FILE *fp = fopen("Factors.txt", "w");

    if(fp != NULL){

        primeFactorS(number);
        fprintf(fp,"The prime factors for %d are:\n",number);
        fclose(fp);

    }else{
        printf("\nError:Could not open File.\n");
        exit(1);
    }

}

/* Driver program to test above function */
int main() 
{ 
    int number; 

    printf("Enter a number: ");
    scanf("%d,",&number);
    printf("The prime factors for %d are:\n",number);

    double begin = omp_get_wtime();

    #pragma omp parallel
    {  
        #pragma omp master
        primeFactors(number); 
    }

    printf("\n\nWriting the values into the file...\n");

    writeToFile(number);

    double end = omp_get_wtime();
    printf("\nExecution time was %f seconds.\n", end - begin);

    return 0; 
}
