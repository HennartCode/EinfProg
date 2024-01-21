/*
Zur Abgabe einen branch `iprg-b07` erstellen und pushen, in dem als einzige Datei die `07ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 07ex_test.c -o 07ex_test.o -lm && ./07ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 07ex_test.c -o 07ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./07ex_test.o
*/

#include "sphinx.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Aufgabe 1:

Da spaziert man entspannt durch Theben, und plötzlich kommt eine Sphinx angeflogen
und spricht: "Ich habe mir ein Array mit n absteigend sortierten Zahlen überlegt (Zahlen
können mehrfach vorkommen). Du darfst mich nach dem Wert an 1 + log2(n) (aufgerundet) vielen
Positionen fragen. Und wenn du mir danach nicht sagen kannst, ob das Array die Zahl 12345
enthält, dann fresse ich dich.".

Geben Sie zurück, ob das Array der Sphinx die Zahl 12345 enthält. Um den Wert an Position `i`
zu erfragen, rufen Sie `sphinx_ask(s, i)` auf. Aber Achtung: Wenn Sie diese Funktion mehr als
1 + log2(n) (aufgerundet) mal aufrufen, stürzt das Programm fehlerhaft ab.
*/
void print_debug(int s,int e,int mid,uint16_t val,int n){
    printf("\nStart: %d ",s);
    printf("\nend: %d ",e);
    printf("\nmid: %d ",mid);
    printf("\nval: %d ",val);
    printf("\nn: %d",n);
    printf("\n");
}

bool descending_sphinx(Sphinx *s, size_t n) {
    int start = 0;
    int end = n-1;
    print_debug(start,end,0,0,n);
    if (n == 0){
        return false;
    }

    if (end == start)
    {
        uint16_t midval = sphinx_ask(s,0);
        if (midval == 12345){
            return true;
        }
        else{
            return false;
        }
    }
    if (sphinx_ask(s,0) == 12345){
        return true;
    }


    while ((end - start) > 1){
        int mid = (start+end+1)/2;
        uint16_t midval = sphinx_ask(s,mid);
        print_debug(start,end,mid,midval,n);
        if (midval == 12345){
            return true;
        }
        if (12345 > midval){
            end = mid;
        }
        else if (12345 < midval){
            start = mid;
        }
        printf("\n %d",start);
        printf("\n %d",end);

    }
    if ((end==n-1) && sphinx_ask(s,n-1) == 12345){
        return true;
    }
    return false;
}
