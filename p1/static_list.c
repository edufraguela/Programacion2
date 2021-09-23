/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Fernando Seara Romera LOGIN 1: f.searar
 * AUTHOR 2: Eduardo Pérez Fraguela LOGIN 2: eduardo.perez.fraguela
 * GROUP: 4.1
 * DATE: 07 / 03 / 21
 */

#include "static_list.h"

#include <string.h>

void createEmptyList(tList *L) {
    /*
        -Tipo: Modificadora
        -Objetivo: Inicializar la lista
        -Entrada: tList -> La lista
        -Salida: -
        -Precondición: -
        -Postcondición: La lista queda inicializada y no contiene elementos
    */
    L->lastPos = LNULL;
}

bool isEmptyList(tList L) {
    /*
        -Tipo: Observadora
        -Objetivo: Determinar si la lista está vacía
        -Entrada: tList -> La lista
        -Salida: bool
        -Precondición: La lista ha sido inicializada
        -Postcondición: -
    */
    return L.lastPos == LNULL;
}

tPosL first(tList L) {
    /*
        -Tipo: Observadora
        -Objetivo: Devolver la posición del primer elemento de la lista
        -Entrada: tList -> La lista
        -Salida: tPosL
        -Precondición: La lista ha sido inicializada y no está vacía
        -Postcondición: -
    */
    return 0;
}

tPosL last(tList L) {
    /*
        -Tipo: Observadora
        -Objetivo: Devolver la posición del último elemento de la lista
        -Entrada: tList -> La lista
        -Salida: tPosL
        -Precondición: La lista ha sido inicializada y no está vacía
        -Postcondición: -
    */
    return L.lastPos;
}

tPosL next(tPosL p, tList L) {
    /*
        -Tipo: Observadora
        -Objetivo: Devolver la posición en la lista del elemento siguiente al de la posición indicada
        -Entrada: tPosL -> Una posición
                  tList -> La lista
        -Salida: tPosL
        -Precondición: La lista ha sido inicializada y la posición es válida
        -Postcondición: -
    */
    if(p == L.lastPos)
        return LNULL;
    else
        return ++p;
}

tPosL previous(tPosL p, tList L) {
    /*
        -Tipo: Observadora
        -Objetivo: Devolver la posición en la lista del elemento anterior al de la posición indicada
        -Entrada: tPosL -> Una posición
                  tList -> La lista
        -Salida: tPosL
        -Precondición: La lista ha sido inicializada y la posición es válida
        -Postcondición: -
    */
    if(p == 0)
        return LNULL;
    else
        return --p;
}

bool insertItem(tItemL item, tPosL p, tList *L) {
    /*
        -Tipo: Generadora
        -Objetivo: Insertar un elemento en la lista antes de la posición indicada. Si la posición es LNULL entonces se
        añade al final. Devuelve true si el elemento fue insertado; false en caso contrario
        -Entrada: tItemL -> Un item
                  tPosL -> Una posición
                  tList -> La lista
        -Salida: bool
        -Precondición: La lista ha sido inicializada y la posición es válida o nula
        -Postcondición: Las posiciones de los elemento posteriores al insertado pueden haber variado
    */
    if(L->lastPos == MAX-1)
        return false;
    else {
        L->lastPos++;
        if(p == LNULL)
            L->data[L->lastPos] = item;
        else {
            tPosL aux;
            for(aux = L->lastPos; aux >= p+1; aux--)
                L->data[aux] = L->data[aux-1];
            L->data[p] = item;
        }
        return true;
    }
}

void deleteAtPosition(tPosL p, tList *L) {
    /*
        -Tipo: Destructora
        -Objetivo: Eliminar de la lista el elemento que ocupa la posición indicada
        -Entrada: tPosL -> Una posición
                  tList -> La lista
        -Salida: -
        -Precondición: La lista ha sido inicializada y la posición es válida
        -Postcondición: Las posiciones de los elementos posteriores al eliminado pueden haber variado
    */
    tPosL i;
    L->lastPos--;
    for(i = p; i <= L->lastPos; i++) {
        L->data[i] = L->data[i+1];
    }
}

tItemL getItem(tPosL pos, tList L) {
    /*
       -Tipo: Observadora
       -Objetivo: Devolver el contenido del elemento de la lista que ocupa la posición indicada
       -Entrada: tPosL -> Una posición
                 tList -> La lista
       -Salida: tItemL
       -Precondición: La lista ha sido inicializada y la posición es válida
       -Postcondición: -
   */
    return L.data[pos];
}

void updateItem(tItemL item, tPosL pos, tList *L) {
    /*
        -Tipo: Modificadora
        -Objetivo: Modificar el contenido del elemento situado en la posición indicada
        -Entrada: tItemL -> Un item
                  tPosL -> Una posición
                  tList -> La lista
        -Salida: -
        -Precondición: La lista ha sido inicializada y la posición es válida
        -Postcondición: El orden de los elementos de la lista no se ve modificado
    */
    L->data[pos] = item;
}

tPosL findItem(tNickname nickname, tList L) {
    /*
         -Tipo: Observadora
         -Objetivo: Devolver la posición del primer elemento de la lista cuyo nickname de usuario se corresponda con
         el indicado
         -Entrada: tNickname -> Un nickname
                   tPosL -> Una posición
                   tList -> La lista
         -Salida: tPosL
         -Precondición: La lista ha sido inicializada
         -Postcondición: -
     */
    if(isEmptyList(L))
        return LNULL;
    else {
        tPosL pos;
        for(pos = 0; pos < L.lastPos && strcmp(L.data[pos].nickname, nickname) != 0; pos++);
        if(strcmp(L.data[pos].nickname, nickname) == 0)
            return pos;
        else return LNULL;
    }
}
