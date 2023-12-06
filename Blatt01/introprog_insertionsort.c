#include <stdio.h>
#include <stdlib.h>
#include "arrayio.h"

int MAX_LAENGE = 1000;

void swap(int* a, int* b){
    int atemp = 0;
    atemp = *a;
    *a = *b;
    *b = atemp;

}

void insertion_sort(int array[], int len) {
    /*
     * Hier Insertionsort implementieren!
     * Diese Funktion soll das Eingabearray nach dem
     * Insertionsort-Verfahren sortieren.
     * Hinweis: Verwende die "in place"-Variante! D.h. der
     * Sortiervorgang soll auf dem originalen Array stattfinden und
     * kein zweites verwendet werden.
     */


    int i;
    for (i=0;i<(len-1);i++){
        int ii = i;
        while (ii >= 0 && array[ii]>array[ii+1])
        {
            swap(&array[ii],&array[ii+1]);
            ii--;
        }
    }


    
}

int main(int argc, char *argv[]) {

    if (argc < 2){
        printf("Aufruf: %s <Dateiname>\n", argv[0]);
        printf("Beispiel: %s zahlen.txt\n", argv[0]);
        exit(1);
    }

    char *filename = argv[1];

    int array[MAX_LAENGE];
    int len = read_array_from_file(array, MAX_LAENGE, filename);

    printf("Unsortiertes Array:");
    print_array(array, len);

    /* Aufruf Insertionsort */
    insertion_sort(array,len);

    printf("Sortiertes Array:");
    print_array(array, len);

    return 0;
}


//clang -std=c11 -Wall introprog_insertionsort.c arrayio.c \-o introprog_insertionsort
//  ./introprog_insertionsort zahlen_insertionsort.txt