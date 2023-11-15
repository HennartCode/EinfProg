/*
Willkommen zum achten Aufgabenblatt vom Programmierkurs. Auf diesem Aufabenblatt geht es um Pointer und Arrays.

Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall 08ex_test.c -o 08ex_test.o -lm && ./08ex_test.o
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "turtlecanvas.h"

/*
Aufgabe 1a:
Lesen Sie das Headerfile `turtlecanvas.h`. Diese Funktion soll die Turtle `d` Schritte vorwärts machen lassen.
*/
void turtle_advance_by(TurtleCanvas *c, uint32_t d) {
    int i;
    for (i = 0; i<d; i++){
        turtle_advance(c);
    }
    
    return;
}

/*
Aufgabe 1b:
Füllen Sie die Turtlecanvas mit horizontalen, abwechselnd schwarzen und weißen Linien (die unterste Zeile soll
schwarz gefärbt werden). Die Turtle ist anfangs an Position (0, 0), ist nach rechts orientiert, und zeichnet schwarz.
*/
void turtle_stripes(TurtleCanvas *c) {
    int i;
    turtle_toggle_color(c);
    for (i = 0; i<turtle_canvas_height(c); i++){
        turtle_toggle_color(c);
        turtle_advance_by(c,turtle_canvas_width(c)-1);
        turtle_rotate_left(c);
        turtle_rotate_left(c);
        turtle_advance_by(c,turtle_canvas_width(c)-1);
        turtle_rotate_right(c);
        turtle_advance(c);
        turtle_rotate_right(c);
    }
    return;
}

/*
Aufgabe 1c:
Lesen Sie die Implementierungen der Turtlecanvas-Funktionen weiter unten in der "turtlecanvas.h".
Der Quellcode sollte vollständig verständlich und unüberraschend sein.
Hinweis: Diese Aufgabe wird nicht bewertet.
*/

/*
Aufgabe 2a:
Geben Sie einen Pointer auf das erste Vorkommen der größten Zahl im Eingabearray zurück.
*/
uint16_t *find_maximal_number(uint16_t numbers[], size_t numbers_len) {
    uint64_t i;
    uint16_t max_num = numbers[0];
    uint16_t *max_num_pointer = &numbers[0];
    for (i = 0; i<numbers_len; i++){
        if (numbers[i] > max_num){
           // printf("%d\n",numbers[i]);
            max_num = numbers[i];
            max_num_pointer = &numbers[i];
        }
    }
    return max_num_pointer;
}

/*
Aufgabe 2b:
Geben Sie (einen Pointer auf) das Teilarray zurück, welches ab dem ersten Vorkommen der größten Zahl im Eingabearray beginnt.
*/
uint16_t *find_subarray_starting_at_maximal_number(uint16_t numbers[], size_t numbers_len) {
    return find_maximal_number(numbers,numbers_len);
}

/*
Aufgabe 2c:
Geben Sie die größtmögliche Distanz zwischen zwei Zahlenwerten aus dem Array `numbers` zurück.
Beispiel: Im Array {1, 3, 7, 4} ist die größte Distanz die zwischen 1 und 7, und beträgt damit `6`.
*/
uint16_t find_maximum_distance(uint16_t numbers[], size_t numbers_len) {
    uint64_t i;
    uint16_t min_num = numbers[0];
    for (i = 0; i<numbers_len; i++){
        if (numbers[i] < min_num){
            min_num = numbers[i];
        }
    }
    uint16_t max_num = *find_maximal_number(numbers, numbers_len);

    return max_num - min_num;
}

/*
Aufgabe 2d:
Geben Sie die kleinstmögliche Distanz zwischen zwei Zahlenwerten aus dem Array `numbers` zurück.
Beispiel: Im Array {1, 3, 7, 4} ist die kleinste Distanz die zwischen 3 und 4, und beträgt damit `1`.
*/
uint16_t find_minimum_distance(uint16_t numbers[], size_t numbers_len) {
    uint64_t i;
    uint64_t s;

    uint16_t min_dist = abs(numbers[0] - numbers[1]);
    for (i = 0; i<numbers_len; i++){
        for (s = 0; s<numbers_len; s++){
            if (abs(numbers[i] -numbers[s]) < min_dist){
                if (i != s){    
                  min_dist = abs(numbers[i] - numbers[s]);
                }
            }
        }
    }
    return min_dist;
}

/*
Aufgabe 2e:
Schreiben Sie die ersten `numbers_len` Quadratzahlen aufsteigend in das gegebene Array `numbers`.
Hinweis: Wir starten bei `1`. Sollte numbers_len also `5` sein, sind die ersten 5 Quadratzahlen bis
einschließlich die von 5 gemeint: 1, 4, 9, 16, 25.
*/
void square_ascending(uint16_t numbers[], size_t numbers_len) {
    int i;
    for (i=1; i<=numbers_len; i++){
        numbers[i-1] = i*i;
    }
}

/*
Aufgabe 2f:
Füllen Sie das Array `out` mit den aufsteigend sortierten Zahlen aus dem `in` Array. Beide Arrays haben die Länge `len`.
Beispiel: Ist `in` {1, 4, 3, 7, 4}, so soll `out` am Ende {1, 3, 4, 4, 7} sein.
*/
void swap(uint16_t a, uint16_t b){
    uint16_t c = a;
    a = b;
    b = c;
}; 

//for debug
void printloop(uint16_t array[], size_t len){
    int loop;
    for(loop = 0; loop < len; loop++)
        printf("%d ", array[loop]);
      
    return;
}

void sort_ascending(uint16_t in[], uint16_t out[], size_t len) {
    bool unsorted = true;
    int i;
    uint16_t first;
    uint16_t second;
    for (i=0;i<len;i++){
        out[i] = in[i];
    }
    // printloop(in, len);
    // printf("\n");
    // printloop(out, len);


    while (unsorted){
        unsorted = false;
        for (i=0; i<len-1; i++){
            if (out[i] > out[i+1]){
                first = out[i];  
                second = out[i+1];
                out[i] = second;
                out[i+1] = first;
                unsorted = true;
            }
        }
    }
    return;
}
