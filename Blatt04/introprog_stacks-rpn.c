#include <stdlib.h>
#include <string.h>
#include <math.h>  // definiert den speziellen Wert NaN für floats
#include "introprog_stacks-rpn.h"
#include "introprog_input_stacks-rpn.h"
#include <stdio.h>

/* 
 * Füge Element am Anfang des Stacks ein
 *
 * char* - Ein Pointer auf den Stack.
 * float - Zahl, die als neues Element auf den Stack gelegt
 *         werden soll.
 */
void stack_push(stack* workstack, float workfloat)
{
    //printf("%f",workstack->top->value);

    stack_element* second_layer = workstack->top;
    stack_element* new_top = (stack_element*)malloc(sizeof(stack_element));
    new_top->value = workfloat;
    new_top->next = second_layer;
    workstack->top = new_top;
    
}

/* 
 * Nehme das letzte eingefügte Element vom Anfang des Stacks
 * Gebe NaN zurück, wenn keine Element vorhanden ist.
 *
 * stack* - Ein Pointer auf den Stack
 *
 * Gebe die im Element enthaltenen Zahl zurück
 */
float stack_pop(stack* workstack)
{   
    if (workstack->top == NULL){
        return NAN;
    }
    stack_element* top = workstack->top;
    workstack->top = top->next;
    float value = top->value;
    free(top);
    return value;
}

/*
 * Führt abhängig von dem Token eine entsprechende Operation auf
 * dem Stack aus.  Wenn es sich bei dem Token um
 *  -> eine Zahl handelt, dann konvertiere die Zahl mithilfe von
 *     atof() zu einem float und lege sie auf den Stack.
 *  -> einen Operator handelt, dann nehme zwei Zahlen vom Stack,
 *     führe die Operation aus und lege das Resultat auf den Stack.
 *  -> eine nichterkennbare Zeichenkette handelt, dann tue nichts.
 *
 * stack*  - Ein Pointer auf den Stack
 * char*  - Eine Zeichenkette
 */
void process(stack* calc_stack, char* input)
{
    /* HIER implementieren */
    if (is_number(input))
    {
        stack_push(calc_stack, atof(input));
    }
    if (is_add(input))
    {
        float a = stack_pop(calc_stack);
        float b = stack_pop(calc_stack);
        stack_push(calc_stack,a + b);
    }
    if (is_sub(input))
    {
        float a = stack_pop(calc_stack);
        float b = stack_pop(calc_stack);
        stack_push(calc_stack,b - a);
    }
    if (is_mult(input))
    {
        float a = stack_pop(calc_stack);
        float b = stack_pop(calc_stack);
        stack_push(calc_stack,a * b);
    }
    return;
    /* Du kannst zur Erkennung der Token folgende Hilfsfunktionen
     * benutzen:
     *
     * Funktion          Rückgabewert von 1 bedeutet
     * ---------------------------------------------
     * is_add(token)     Token ist ein Pluszeichen
     * is_sub(token)     Token ist ein Minuszeichen
     * is_mult(token)    Token ist ein Multiplikationszeichen
     * is_number(token)  Token ist eine Zahl
     */
}

/* 
 * Erstelle einen Stack mit dynamischem Speicher.
 * Initialisiere die enthaltenen Variablen.
 *
 * Gebe einen Pointer auf den Stack zurück.
 */
stack* stack_erstellen() {
    stack* outstack = (stack*)malloc(sizeof(stack));
    outstack->top = NULL;
    return outstack;
}

// clang -std=c11 -Wall stacks-rpn.c introprog_stacks-rpn.c \introprog_input_stacks-rpn.c -o introprog_stacks-rpn
// ./ introprog_stacks-rpn