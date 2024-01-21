/*
Zur Abgabe einen branch `iprg-b05` erstellen und pushen, in dem als einzige Datei die `05ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 05ex_test.c -o 05ex_test.o -lm && ./05ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 05ex_test.c -o 05ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./05ex_test.o
*/

#include "search_tree.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Aufgabe 1:

Fügen Sie den Wert `x` als Blatt so in den nicht-leeren Suchbaum `t` ein, dass `t` hinterher
wieder ein Suchbaum ist. Falls `x` bereits in `t` vorkam, soll `t` stattdessen
unverändert bleiben.
Geben Sie zurück, ob der Baum modifiziert wurde.

Nutzen Sie `malloc`, um das neue Blatt zu erstellen. Der Testrunner wird das Blatt wieder `free`n,
darum brauchen Sie sich nicht zu kümmern.
*/

bool search_tree_insert(TreeNode *t, uint16_t x) {

    if (x == t->item){
        return false;
    }
    if (x < t->item){
        if (t->left == NULL){
            TreeNode* newpage = malloc(sizeof(TreeNode));
            newpage->left = NULL;
            newpage->right = NULL;
            newpage->item = x;
            t->left = newpage;
            return true;
        }else{
            return search_tree_insert(t->left, x);
        }
    }
    if (x > t->item){
        if (t->right == NULL){
            TreeNode* newpage = malloc(sizeof(TreeNode));
            newpage->left = NULL;
            newpage->right = NULL;
            newpage->item = x;
            t->right = newpage;
            return true;
        }else{
            return search_tree_insert(t->right, x);
        }
    }
    else{
        return false;
    }
}



/*
Aufgabe 2:
Geben Sie die kleinste Zahl im Suchbaum `t` zurück, welche echt größer als `x` ist.
Falls keine solche Zahl existiert, geben Sie stattdessen `x` zurück. Die Laufzeit Ihrer Lösung soll
proportional zur Höhe des Baumes sein, aber unabhängig von der Gesamtzahl an Knoten. 
*/
uint16_t search_tree_get_greater_than(TreeNode *t, uint16_t x) {

    int res = x;
    TreeNode* next_t = t; 


    while(true){
        if (next_t==NULL){
            return res;
        }
        if(next_t->item > x){
            res = next_t->item;
            if (t->left != NULL){
                next_t = next_t->left;
            }
            else{
                return res;
            }
        }

        else if(next_t->item <= x){
            if (next_t->right != NULL){
                next_t = next_t->right;
            }else{
                return res;
            }
        }

        else {
            return res;
        }
    }
}