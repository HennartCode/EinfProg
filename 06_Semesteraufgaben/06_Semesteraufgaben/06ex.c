/*
Zur Abgabe einen branch `iprg-b06` erstellen und pushen, in dem als einzige Datei die `06ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 06ex_test.c -o 06ex_test.o -lm && ./06ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 06ex_test.c -o 06ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./06ex_test.o
*/

#include "array_visualizer.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Aufgabe 1:
Machen Sie sich in dieser Aufgabe mit dem `Visualizer` (siehe array_visualizer.h) vertraut.
Nutzen Sie die `visualizer_append_array` Funktion damit die Tests durchlaufen.

Tipp 1: Die erste Zeile im erzeugten Bild stellt das Eingabearray dar.
*/
void rotateArray(uint8_t arr[], int size) {
    if (size <= 1) {
        return;  
    }
    uint8_t temp = arr[0];  

    for (int i = 0; i < size-1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[size - 1] = temp;  
}

void warmup(Visualizer *v, uint8_t *arr, size_t len) {

    for (int i = 0; i < len; i++){
        visualizer_append_array(v,arr);
        rotateArray(arr,len);
    }

    
}

/*
Aufgabe 2:
Bringen Sie die Tests zum durchlaufen.

Tipp 1: Die erste Zeile im erzeugten Bild stellt das Eingabearray dar.
Tipp 2: Es handelt sich um eine Abwandlung von iterativem Mergesort.
Tipp 3: `len` ist immer eine Dreierpotenz, damit Sie sich nicht mit Rundungsdetails herumschlagen brauchen.
*/
void printvars(uint8_t l,uint8_t m,uint8_t r,uint8_t i){
    printf("Left: %d\n",l);
    printf("mid: %d\n",m);
    printf("right: %d\n",r);
    printf("i: %d\n",i);
    // printf("inserted: %d\n",var);
    printf("\n");
}


void merge(uint8_t *arr,uint8_t left,uint8_t mid,uint8_t right,uint8_t len){
uint8_t l_stop,m_stop,r_stop;
uint8_t l,m,r,i;
uint8_t* out = malloc(len*sizeof(uint8_t)*len);

i = 0;
l = 0;
m = left;
r = left+mid;
l_stop = left;
m_stop = left+mid;
r_stop = left+mid+right;
printvars(l,m,r,i);
while (l<l_stop && m<m_stop && r<r_stop){               //wenn alle noch voll sind
    if ((arr[l] <= arr[m]) && (arr[l] <= arr[r])){
        out[i] = arr[l];
        i++;
        l++;
    }
    if ((arr[m] <= arr[r]) && (arr[m] <= arr[l])){
        out[i] = arr[m];
        i++;
        m++;
    }
    if ((arr[r] <= arr[m]) && (arr[r] <= arr[l])){
        out[i] = arr[r];
        i++;
        r++;
    }
printvars(l,m,r,i);
}

while (l<l_stop&&m<m_stop){                            //wenn l m noch voll sind
    if (arr[l] < arr[m]){
        out[i] = arr[l];
        i++;
        l++;

    }
    else{
        out[i] = arr[m];
        i++;
        m++;
    }
printvars(l,m,r,i);
}

while (l<l_stop&&r<r_stop){                             // wenn l r noch voll sind
    if (arr[l] < arr[r]){
        out[i] = arr[l];
        i++;
        l++;
    }
    else{
        out[i] = arr[r];
        i++;
        r++;
    }
printvars(l,m,r,i);
}
while (r<r_stop&&m<m_stop){                             //wenn r m noch voll sind
    if (arr[r] < arr[m]){
        out[i] = arr[r];
        i++;
        r++;
    }
    else{
        out[i] = arr[m];
        i++;
        m++;
    }
printvars(l,m,r,i);
}

while (l<l_stop){                                       //wenn einer noch voll ist
    out[i] = arr[l];
    i++;
    l++;
printvars(l,m,r,i);
}
while (m<m_stop){
    out[i] = arr[m];
    i++;
    m++;
printvars(l,m,r,i);
}
while (r<r_stop){
    out[i] = arr[r];
    i++;
    r++;
printvars(l,m,r,i);
}

for (int j = 0; j < len; j++){
    arr[j] = out[j];
}
free(out);
}


void sort_it(Visualizer *v, uint8_t *arr, size_t len){
    uint8_t step = 3;
    uint8_t i = 0;
    while (step <= len)
    {
        visualizer_append_array(v,arr);
        merge(arr + (i*step),step/3,step/3,step/3,step);
        i++;
        if (step * i >= len){
            step *= 3;
            i = 0;
        }
    }
    visualizer_append_array(v,arr);
    
}

// void sort_it(Visualizer *v, uint8_t *arr, size_t len) {
//     if (len > 1){
//         sort_it(v,arr,len/3);
//     }
//     uint8_t l,m,r = len/3;
//     merge(arr,l,m,r,len);
// }




// int main(int argc, char const *argv[])
// {
//     uint8_t A[3] = {42,1,7};
//     merge(A,1,1,1,3);
//     for (int i = 0; i < 3; i++)
//     {
//        ( printf("%d ",A[i]));
//     }


    
//     return 0;
// }

