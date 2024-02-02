/*
Zur Abgabe einen branch `iprg-b09` erstellen und pushen, in dem als einzige Datei die `09ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 09ex_test.c -o 09ex_test.o -lm && ./09ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 09ex_test.c -o 09ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./09ex_test.o
*/

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "tree.h"
#include "array.h"

/*
Aufgabe 1:

Gegeben ein Array `arr`, geben Sie zurück, ob der zugehörige linksvollständige Binärbaum
die max-heap Eigenschaft erfüllt.
*/
bool is_max_heap(Array arr) {
    size_t lci;
    size_t rci;
    for (size_t i = 0; i<arr.len; i++){
        lci = ((i+1)*2)-1;
        rci = (i+1)*2;
        if (lci < arr.len && arr.arr[lci] > arr.arr[i]){
            return false;
        }
        if (rci < arr.len && arr.arr[rci] > arr.arr[i]){
            return false;
        }
    }
    return true;
}

/*
Aufgabe 2:

Gegeben ein linksvollständiger Binärbaum, tragen Sie im Array `arr` dessen Arrayrepräsentation ein.

Tipp 1: Wie so häufig bei Bäumen, bietet sich hier eine rekursive Lösung an.
Tipp 2: Diese Funktion selbst ist allerdings nur so mäßig gut für rekursive Aufrufe geeignet, eventuell sollten Sie sich eine (rekursive) Hilfsfunktion schreiben.
Tipp 3: Die Position eines Knotens im Array lässt sich relativ leicht bestimmen, wenn man die Position vom Elternknoten weiß, und, ob es sich um ein linkes oder ein rechtes Kind handelt.
Tipp 4: Ja, das sind also sinnvolle Argumente für die Hilfsfunktion.
Tipp 5: Regelmäßig zähneputzen und genug bewegen.
*/


size_t heap_size(TreeNode *t){
    if (t == NULL){
        return 0;
    }
    return 1 + heap_size(t->left) + heap_size(t->right);
}

void recursive_array(TreeNode *t, Array arr, size_t ix){
    if(t == NULL){
        return;
    }
    arr.arr[ix] = t->item;      //erst Parent reinschreiben
    recursive_array(t->left, arr, ((ix+1)*2)-1); //dann linkes Kind
    recursive_array(t->right, arr, (ix+1)*2); //dann rechtes Kind
}

void tree_to_array(TreeNode *t, Array arr) {
    recursive_array(t, arr, 0);
}
