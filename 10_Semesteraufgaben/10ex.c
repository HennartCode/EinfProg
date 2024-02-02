/*
Zur Abgabe einen branch `iprg-b10` erstellen und pushen, in dem als einzige Datei die `10ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 10ex_test.c -o 10ex_test.o -lm && ./10ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 10ex_test.c -o 10ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./10ex_test.o
*/

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "tree.h"
#include "array.h"

/*
Aufgabe 1:

Implementieren Sie min-heapify auf Bäumen: gegeben ein nichtleerer, linksvollständiger Baum `t`, dessen
Kinder der Wurzel die min-heap Eigenschaft erfüllen, lassen Sie den Wert in der Wurzel so lange
"hinuntersinken", bis `t` die min-heap Eigenschaft erfüllt.

Da "hinuntersinken" nicht gerade präzise formuliert ist, müssen Sie unter Umständen Ihre Implementierung
an die Testfälle anpassen. Aber wenn Sie der Intuition der Vorlesungsfolien folgen, sollte das keine Probleme bereiten.

Werte kommen in `t` niemals mehrfach vor.
*/
void heap_swap(TreeNode *a, TreeNode *b) {
    int tmp = a->item;
    a->item = b->item;
    b->item = tmp;
}

void heapify_tree(TreeNode *t) {
    if (t->left == NULL && t->right == NULL) {
        return;
    }
    if (t->left != NULL && t->right != NULL) {   //wenn beide Kinder existieren
        if (t->left->item < t->right->item) {  //wenn das linke Kind kleiner ist als das rechte
            if (t->left->item < t->item) {      //wenn das linke Kind kleiner ist als der Vater
                heap_swap(t, t->left);
                heapify_tree(t->left);
            }
        } else {                            //wenn das rechte Kind kleiner ist als das linke                    
            if (t->right->item < t->item) {     //wenn das rechte Kind kleiner ist als der Vater
                heap_swap(t, t->right);
                heapify_tree(t->right);
            }
        }
    } else if (t->left != NULL) {           //wenn nur das linke Kind existiert
        if (t->left->item < t->item) {          //wenn das linke Kind kleiner ist als der Vater
            heap_swap(t, t->left);
            heapify_tree(t->left);
        }
    } else {                            //wenn nur das rechte Kind existiert
        if (t->right->item < t->item) {     //wenn nur das rechte Kind existiert
            heap_swap(t, t->right);
            heapify_tree(t->right);
        }
    }

}

/*
Aufgabe 2:

Implementieren Sie min-heapify auf Arrays: gegeben ein nichtleeres Array und eine Position `i` innerhalb des Arrays,
sodass die Kinder vom Knoten der zum Element an Position `i` gehört min-heaps sind, lassen Sie den Wert an Position `i`
solange hinuntersinken, wie nötig, um die min-heap Eigenschaft für den Teilbaum ab Position `i` wiederherzustellen.

Oder knapper: Implementieren Sie den heapify Algorithmus aus der Vorlesung, aber für min-heaps.

Werte kommen im Array niemals mehrfach vor.
*/

void heap_swap_arr(Array arr, size_t a, size_t b) {
    int tmp = arr.arr[a];
    arr.arr[a] = arr.arr[b];
    arr.arr[b] = tmp;

}
void heapify_array(Array arr, size_t i) {

    size_t lci = ((i+1)*2)-1;
    size_t rci = (i+1)*2;

    // printf("\n\nHEHEAKHE%d",arr.arr[i]);

    if (i >= arr.len) {         //wenn root nicht existiert
        return;
    }
    if ((lci < arr.len) && (rci < arr.len)){   //wenn beide Kinder existieren
        if((arr.arr[lci] >= arr.arr[i]) && arr.arr[rci] < arr.arr[i]){          //wenn rechts kleiner als root und links nicht kleiner
            heap_swap_arr(arr, rci, i);           //swap mit rechts
            return heapify_array(arr, rci);
        }
        if((arr.arr[rci] >= arr.arr[i]) && (arr.arr[lci] < arr.arr[i])){      //wenn links kleiner als root und rechts nicht kleiner
            heap_swap_arr(arr,lci,i);               //swap links
            return heapify_array(arr, lci);
        }
        if(arr.arr[lci] <= arr.arr[i] && arr.arr[rci] <= arr.arr[i]){         //wenn beiode kleiner als root
            if(arr.arr[lci] <= arr.arr[rci]){         //wenn links kleiner gleich rechts
                heap_swap_arr(arr,lci,i);               //swap links mit root
                return heapify_array(arr, lci);
            }
            else{
                heap_swap_arr(arr,rci,i);             //wenn rechts kliener gleich links: swap rechts mit root
                return heapify_array(arr, rci);       //an stelle von rechtem Kind wiederholen
            }
        }
    }
    if(lci < arr.len && rci >= arr.len){      //wenn nur linkes Kind existiert
        if(arr.arr[lci] < arr.arr[i]){          //wenn links kliener als root
            heap_swap_arr(arr,lci,i);       //swap links
            return heapify_array(arr, lci);
        }
    }
    else{                   //wenn kein Kind existiert
        return;
    }

}


// int main(int argc, char const *argv[])
// {
//     Array test;
//     uint16_t* ar = malloc(sizeof(uint16_t)*3);
//     ar[0] = 8;
//     ar[1] = 3;
//     ar[2] = 6;
//     test.arr = ar;
//     test.len = 3;

//     heapify_array(test,0);

//     for(int i = 0; i<3; i++){
//         printf("\n%d",test.arr[i]);
//     }

//     free(ar);

//     return 0;
// }
