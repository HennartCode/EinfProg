  /*
Zur Abgabe einen branch `iprg-b08` erstellen und pushen, in dem als einzige Datei die `08ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 08ex_test.c -o 08ex_test.o -lm && ./08ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 08ex_test.c -o 08ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./08ex_test.o
*/

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* Ein Array zusammen mit seiner Länge. */
typedef struct ArrayWithLength_ {
    uint16_t *arr;
    size_t len;
} ArrayWithLength;

/*
Bei merge sort werden häufiger mal *zwei* vorsortierte Arrays kombiniert. Auf diesem Blatt
kombinieren wir effizient *beliebig viele* vorsortierte Arrays mit einem divide-and-conquer Algorithmus.
*/

/*
Aufgabe 1a:

Gegeben ein absteigend sortiertes Array, geben Sie ein absteigend sortiertes Array
mit den gleichen Elementen zurück.
Der Speicher für die Arrayelemente im Rückgabewert soll eigens mit malloc allokiert werden.

Tipp: Ja, es ist wirklich so banal wie es klingt. Das haben base-cases bei divide-and-conquer
Algorithmen häufig so an sich.
*/
ArrayWithLength base_case(ArrayWithLength arr) {
    ArrayWithLength ret;

    ret.arr = (uint16_t *) malloc(sizeof(uint16_t) * arr.len);
    for (int i = 0; i<arr.len; i++){
        ret.arr[i] = arr.arr[i];
    }
    ret.len = arr.len;

    return ret;
}

/*
Aufgabe 1b:

Gegeben zwei absteigend sortierte Arrays der Längen len1 und len2,
geben Sie ein absteigend sortiertes Array zurück,
welches die Elemente beider Eingabearrays enthält. Die Funktion soll in O(len1 + len2) laufen.
Der Speicher für die Arrayelemente im Rückgabewert soll eigens mit malloc allokiert werden.
*/
ArrayWithLength combine(ArrayWithLength arr1, ArrayWithLength arr2) {
    ArrayWithLength ret;

    ret.len = (arr1.len + arr2.len);
    ret.arr = (uint16_t *) malloc(sizeof(uint16_t) * ret.len);
 
    int a1 = 0;
    int a2 = 0;
    int i = 0;

    while ((a1 < arr1.len) && (a2 < arr2.len)){

        if (arr1.arr[a1] > arr2.arr[a2]){
            ret.arr[i] = arr1.arr[a1];
            a1++;
            i++;
        }
        else{
            ret.arr[i] = arr2.arr[a2];
            a2++;
            i++;
        }
    }
    while (a1 < arr1.len){
        ret.arr[i] = arr1.arr[a1];
        a1++;
        i++;    
    }
    while (a2 < arr2.len){
        ret.arr[i] = arr2.arr[a2];
        a2++;
        i++; 
    }

    return ret;
}

/*
Aufgabe 1c:

Gegeben ein nichtleeres Array `arrs` aus `count` vielen absteigend sortierten Arrays, geben Sie ein absteigend sortiertes Array
zurück, welches die Elemente aller Eingabearrays enthält. Ihre Lösung soll in O(n * log(count)) laufen, wobei `n` die
Gesamtzahl an Elementen in allen Arrays ist. Dazu müssen sie clever dive-and-conquern.

Der Speicher für die Arrayelemente im Rückgabewert soll eigens mit malloc allokiert werden.
*/



ArrayWithLength merge_k(ArrayWithLength *arrs, size_t count) {
    if(count == 1){

        ArrayWithLength combined = base_case(arrs[0]);

        return combined;
    }

    if(count >= 2){
        ArrayWithLength* b_ptr = NULL;
        ArrayWithLength* a_ptr = NULL;
        if(count%2 == 1){
            a_ptr = (ArrayWithLength*)malloc(sizeof(ArrayWithLength)*(count-1));
            size_t a_count = count-1;
            for(size_t i = 0;i<(a_count);i++){
                a_ptr[i].arr = arrs[i].arr;
                a_ptr[i].len = arrs[i].len;
            }
            b_ptr = (ArrayWithLength*)malloc(sizeof(ArrayWithLength));
            size_t b_count = 1;
            //printf("\nCount: %ld a coubnt:%ld  b count:%ld",count,a_count,b_count);
            b_ptr[0].arr = arrs[a_count].arr;
            b_ptr[0].len = arrs[a_count].len;
            
            ArrayWithLength a = merge_k(a_ptr,a_count);
            ArrayWithLength b = merge_k(b_ptr,b_count);
            ArrayWithLength combined = combine(a,b);

            if(a.arr != NULL){
                free(a.arr);
                a.arr = NULL;
            }
            if(a_ptr != NULL){
                free(a_ptr);
            }
            if(b_ptr != NULL){
                free(b_ptr);
            }
            a_ptr = NULL;
            b_ptr = NULL;
            return combined;
        }
        else if((count > 2) && (count%2 == 0)){
            a_ptr = (ArrayWithLength*)malloc(sizeof(ArrayWithLength)*(count/2));
            b_ptr = (ArrayWithLength*)malloc(sizeof(ArrayWithLength)*(count/2));
            for(size_t i = 0; i<count;i++){
                if(i<(count/2)){
                    a_ptr[i%(count/2)].arr = arrs[i].arr;
                    a_ptr[i%(count/2)].len = arrs[i].len;
                }else{ 
                    b_ptr[i%(count/2)].arr = arrs[i].arr;
                    b_ptr[i%(count/2)].len = arrs[i].len;
                }
            }
            size_t a_count = count/2;
            size_t b_count = count/2;
            //printf("\nCount: %ld a coubnt:%ld  b count:%ld",count,a_count,b_count);

            ArrayWithLength a = merge_k(a_ptr,a_count);
            ArrayWithLength b = merge_k(b_ptr,b_count);

            ArrayWithLength combined = combine(a,b);

    	    if(a.arr != NULL){
    	        free(a.arr);
    	        a.arr = NULL;
    	    }
    	    if(b.arr != NULL){
    	        free(b.arr);
    	        b.arr = NULL;
    	    }
            if(a_ptr != NULL){
                free(a_ptr);
            }
            if(b_ptr != NULL){
                free(b_ptr);
            }

            b.arr = NULL;
            a.arr = NULL;
            a_ptr = NULL;
            b_ptr = NULL;

            return combined;
        }
        else {
            //printf("\n\nTWO\n\n");
            ArrayWithLength a = arrs[0];
            ArrayWithLength b = arrs[1];
            ArrayWithLength combined = combine(a,b);    

            return combined;
        }

    }
    else{
        printf("ERROR");
        return arrs[0];
    }
}











    // // printf("\ncount %ld",count);
    // // printf("\nnewlen %d",totallen);


    // size_t newcount = count;
    // while (count > 1){

    //     int r = 0;
    //     ArrayWithLength newarr;
    //     for (i=0; i<(count-1); i+=2){
    //         newarrs[r] = combine(input[i],input[i+1]);
    //         r++;
    //         newcount--;
    //     }
    //     if (count%2 == 1){  
    //         newarrs[r] = input[count];
    //     }

    //     count = newcount;
    //     free(input->arr);                                                                           //input:   x,x,x,x,x,x,x -> NULL
    //     ArrayWithLength* input = (ArrayWithLength*)malloc(sizeof(ArrayWithLength)*count);       //newarrs: x,x,x,x,0,0,0 
    //     for (i = 0; i<count; i++){                                                              //input:   NULL          -> x,x,x,x
    //         input[i] = newarrs[i];
    //     }
    //     free(newarrs->arr);
    //     ArrayWithLength* newarrs = (ArrayWithLength*)calloc(count,sizeof(ArrayWithLength));     //newarrs: x,x,x,x,0,0,0 -> 0,0,0,0
    
    // }

    // ret = newarrs[0];

    //return ret;
//}







// printf("\n\n\n");

// int totallen = 0;
// for (int i = 0; i<count;i++){                                                       //find cumulative Array length sum
//     totallen += arrs[i].len;
// }

// ArrayWithLength ret;
// if (totallen == 0){
//     ret.arr = NULL;
// }else{
//     ret.arr = (uint16_t*)calloc(totallen,sizeof(uint16_t));                       //assign memory for result Array
// }
// ret.len = totallen;    

// int r = 0;                                                                      //copy all arrs into ret
// for(int i = 0; i<count; i++){
//     for(int j = 0; j<arrs[i].len; j++){
//         ret.arr[r] = arrs[i].arr[j];
//         r++;
//     }
// }

// ArrayWithLength lenlist;                                                       //make lenlist
// lenlist.arr = (uint16_t*)malloc(sizeof(uint16_t)*count);
// lenlist.len = count;

// for(int i = 0;i<count;i++){
//     lenlist.arr[i] = (arrs+i)->len;
// }

// for(int i = 0;i<lenlist.len;i++){
//     printf("\nind %d: %d",i,lenlist.arr[i]);
// }                                                                               //..

// int arrstocombine = count;
// int i = 0;
// int ai = 0;
// int bi = lenlist.arr[0];
// ArrayWithLength a,b;
// while(arrstocombine > 1){
//     a.len = lenlist.arr[ai];
//     b.len = lenlist.arr[bi];
//     ArrayWithLength combined = combine(ret.arr[ai],ret.arr[bi]);
// }

// free(lenlist.arr);
// return ret;

// }











    // int ind = 0;
    // while (count > 1){
    //     ArrayWithLength new;
    //     for(int i=0; (i+2)<=count;i+=2){

    //         new = combine(arrs[i], arrs[i+1]);
    //         int stop = (ind+new.len);
    //         while (ind < stop){
    //             ret.arr[ind] = new.arr[ind];
                
    //         }

    //         count -= 1;
    //     }
    // if (count == 1){
    //     ret = base_case(arrs[0]);
    // }

    // }
    






// int main(int argc, char const *argv[])
// {
//     ArrayWithLength ar1,ar2;
    
//     ar1.arr = (uint16_t*) malloc(sizeof(uint16_t)*3);
//     ar2.arr = (uint16_t*) malloc(sizeof(uint16_t)*1);
//     ar1.len = 3;
//     ar2.len = 1;
//     ar1.arr[0] = 1;
//     ar1.arr[1] = 2;
//     ar1.arr[2] = 3;
//     ar2.arr[0] = 1;
//     //ar2.arr[1] = 2;
//     //ar2.arr[2] = 3;

//     ArrayWithLength comb = combine(ar1,ar2);

//     for (int i = 0; i<comb.len;i++){
//         printf("\n %d ",comb.arr[i]);
//     }
//     return 0;
// }

//cc -std=c11 -g -Wall -Werror 08ex.c -o 08ex_test.o -lm && ./08ex_test.o
