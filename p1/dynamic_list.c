/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Fernando Seara Romera LOGIN 1: f.searar
 * AUTHOR 2: Eduardo Pérez Fraguela LOGIN 2: eduardo.perez.fraguela
 * GROUP: 4.1
 * DATE: 07 / 03 / 21
 */

#include "dynamic_list.h"

#include <string.h>

bool createNode(tPosL *p) {
    /*
        -Tipo: Generadora
        -Objetivo: Crear un nodo
        -Entrada: tPosL -> Posición de la lista donde hay que crearlo
        -Salida: bool -> Indicando si se creó o no
        -Precondición: -
        -Postcondición: -
    */
    *p = malloc(sizeof(struct tNode));
    return *p != LNULL;
}

void createEmptyList(tList *L) {
    /*
        -Tipo: Modificadora
        -Objetivo: Inicializar la lista
        -Entrada: tList -> La lista
        -Salida: -
        -Precondición: -
        -Postcondición: La lista queda inicializada y no contiene elementos
    */
    *L = LNULL;
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
    return L == LNULL;
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
    return L;
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
    tPosL q;
    for (q = L; q->next != LNULL; q = q->next);
    return q;
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
    return p->next;
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
    tPosL q;
    if (p == L)
        q = LNULL;
    else
        for (q = L; q->next != p; q = q->next);
    return q;
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
    tPosL q, r;
    if (!createNode(&q))
        return false;
    else {
        q->data = item;
        q->next = LNULL;
        if (*L == LNULL)
            *L = q;
        else if (p == LNULL) {
            for (r = *L; r->next != LNULL; r = r->next);
            r->next = q;
        } else if (p == *L) {
            q->next = p;
            *L = q;
        } else {
            q->next = p->next;
            p->next = q;
            q->data = p->data;
            p->data = item;
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
    tPosL q;
    if(p == *L){
        *L = (*L)->next;
    } else if(p->next == LNULL){
        for(q = *L; q->next != p; q = q->next);
        q->next = LNULL;
    } else{
        q = p->next;
        p->data = q->data;
        p->next = q->next;
        p = q;
    }
    free(p);
}

tItemL getItem(tPosL p, tList L) {
    /*
        -Tipo: Observadora
        -Objetivo: Devolver el contenido del elemento de la lista que ocupa la posición indicada
        -Entrada: tPosL -> Una posición
                  tList -> La lista
        -Salida: tItemL
        -Precondición: La lista ha sido inicializada y la posición es válida
        -Postcondición: -
    */
    return p->data;
}

void updateItem(tItemL item, tPosL p, tList *L) {
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
    p->data = item;
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
    tPosL p;
    for(p = L; (p != LNULL) && (strcmp((*p).data.nickname, nickname) != 0); p = (*p).next);
    return p;
}