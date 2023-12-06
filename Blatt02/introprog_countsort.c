#include <stdio.h>
#include <string.h>
#include "introprog_countsort.h"
#include "arrayio.h"

/* Ab hier Funktion count_sort_calculate_counts implementieren */
void count_sort_calculate_counts(int input_array[], int len, int count_array[])
{   
    int i;
    for (i=0;i<len;i++){
        count_array[input_array[i]]++;
    }
    // for (i=1;i<MAX_VALUE;i++){
    //     count_array[i] += count_array[i-1];
    // }
    return;
}
/* Ab hier Funktion count_sort_write_output_array implementieren */
void count_sort_write_output_array(int output_array[], int count_array[], SortDirection order){
    int j,i;
    int k = 0;
    if (order == ASCENDING || order == NOTDEFINED){
        for (j=0;j<=MAX_VALUE;j++){
            for(i=0;i<count_array[j];i++){
                output_array[k] = j;
                k++;
            }
        }
    }


    if (order == DESCENDING){
        for (j=MAX_VALUE;j>=0;j--){
            for(i=0;i<count_array[j];i++){
                output_array[k] = j;
                k++;
            }
        }
    }
    
    return;
}
/* Ab hier Funktion extract_order_direction implementieren */
SortDirection extract_order_direction(char *order){
    if(!strcmp(order,"asc")){
        return ASCENDING;
    }else if (!strcmp(order,"desc")){
        return DESCENDING;
    }else{
        return NOTDEFINED;
    }
    
    
}
/* Ab hier Funktion count_sort implementieren und entsprechende Funktionsaufrufe einfügen */
void count_sort(int input_array[], int len, int output_array[], SortDirection order){
    int count_array[MAX_VALUE+1];                                       //setup count_array
    memset(count_array,0,(MAX_VALUE+1)*sizeof(int));



    count_sort_calculate_counts(input_array, len, count_array);         // statistic

    printf("COUNTS:");
    print_array(count_array,MAX_VALUE+1);
    printf("\n\n");

    count_sort_write_output_array(output_array,count_array,order);   //out
}


int main(int argc, char *argv[]) {
    if (argc < 3){
        printf("Aufruf: %s <Dateiname> asc|desc\n", argv[0]);
        printf("Beispiel: %s zahlen.txt asc\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];

    /*
     * Hier die Sortierrichtung einlesen und einer Variablen
     * des Datentypes SortDirection (siehe h-Datei) verwenden.
     * 
     * Beenden des Programmes mit derselben Ausgabe der Hilfe 
     * (siehe Anfang main-Funktion)
     * 
     * Implementieren Sie zur Umwandlung die Funktion 
     * extract_order_direction und verwenden Sie, wenn kein 
     * gültiger Parameter gefunden wurde, NOTDEFINED.
     * 
     * Hinweis: Die extract_order_direction soll auch mit dieser
     * SortDirection auch ein Standardverhalten implementieren, 
     * die nicht mit einem Fehler terminiert.
     * 
     * Das Hauptprogramm main hingegen, darf auf unkorrekte Eingaben
     * reagieren und auch entsprechend Ausgaben erzeugen oder mit Fehler
     * beenden.
     */

    int input_array[MAX_LAENGE];
    int len = read_array_from_file(input_array, MAX_LAENGE, filename);

    printf("Unsortiertes Array:");
    print_array(input_array, len);
    /*
     * Hier count_sort aufrufen und alle nötigen Deklarationen einfügen!
     */
    printf("\nMAX_VALUE: %i\n",MAX_VALUE);

    int output_array[len];                                              // setup ouput array
    SortDirection sort_dir = extract_order_direction(argv[2]);          // load SortDir

    count_sort(input_array,len,output_array,sort_dir);

    printf("Sortiertes Array:");

    /* Folgende Zeile einkommentieren, um das Array auszugeben! */
    print_array(output_array, len);

    return 0;
}



//clang -std=c11 -Wall introprog_countsort.c arrayio.c \-o introprog_countsort
//  ./introprog_countsort zahlen_countsort.txt