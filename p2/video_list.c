/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Fernando Seara Romera LOGIN 1: f.searar@udc.es
 * AUTHOR 2: Eduardo Pérez Fraguela LOGIN 2: eduardo.perez.fraguela@udc.es
 * GROUP: 4.1
 * DATE: 07 / 05 / 21
 */


#include "types.h"
#include "video_list.h"

void createEmptyListV(tVideoList *L) {
    /*
        -Tipo: Modificadora
        -Objetivo: Inicializar la lista
        -Entrada: tVideoList -> La lista
        -Salida: -
        -Precondición: -
        -Postcondición: La lista queda inicializada y no contiene elementos
    */
    L->lastPos = NULL_VIDEO;
}

bool isEmptyListV(tVideoList L) {
    /*
        -Tipo: Observadora
        -Objetivo: Determinar si la lista está vacía
        -Entrada: tVideoList -> La lista
        -Salida: bool
        -Precondición: La lista ha sido inicializada
        -Postcondición: -
    */
    return L.lastPos == NULL_VIDEO;
}

tVideoPos firstV(tVideoList L) {
    /*
        -Tipo: Observadora
        -Objetivo: Devolver la posición del primer elemento de la lista
        -Entrada: tVideoList -> La lista
        -Salida: tVideoPos
        -Precondición: La lista ha sido inicializada y no está vacía
        -Postcondición: -
    */
    return 0;
}

tVideoPos lastV(tVideoList L) {
    /*
        -Tipo: Observadora
        -Objetivo: Devolver la posición del último elemento de la lista
        -Entrada: tVideoList -> La lista
        -Salida: tVideoPos
        -Precondición: La lista ha sido inicializada y no está vacía
        -Postcondición: -
    */
    return L.lastPos;
}

tVideoPos previousV(tVideoPos pos, tVideoList L) {
    /*
        -Tipo: Observadora
        -Objetivo: Devolver la posición en la lista del elemento anterior al de la posición indicada
        -Entrada: tVideoPos -> Una posición
                  tVideoList -> La lista
        -Salida: tVideoPos
        -Precondición: La lista ha sido inicializada y la posición es válida
        -Postcondición: -
    */
    if(pos == 0)
        return NULL_VIDEO;
    else
        return --pos;
}

tVideoPos nextV(tVideoPos pos, tVideoList L) {
    /*
        -Tipo: Observadora
        -Objetivo: Devolver la posición en la lista del elemento siguiente al de la posición indicada
        -Entrada: tVideoPos -> Una posición
                  tVideoList -> La lista
        -Salida: tVideoPos
        -Precondición: La lista ha sido inicializada y la posición es válida
        -Postcondición: -
    */
    if(pos == L.lastPos)
        return NULL_VIDEO;
    else
        return ++pos;
}

bool insertItemV(tVideoItem item, tVideoPos pos, tVideoList *L) {
    /*
        -Tipo: Generadora
        -Objetivo: Insertar un elemento en la lista antes de la posición indicada. Si la posición es NULL_VIDEO entonces se
        añade al final. Devuelve true si el elemento fue insertado; false en caso contrario
        -Entrada: tVideoItem -> Un item
                  tVideoPos -> Una posición
                  tVideoList -> La lista
        -Salida: bool
        -Precondición: La lista ha sido inicializada y la posición es válida o nula
        -Postcondición: Las posiciones de los elemento posteriores al insertado pueden haber variado
    */
    if(L->lastPos == MAX-1)
        return false;
    else {
        L->lastPos++;
        if(pos == NULL_VIDEO)
            L->data[L->lastPos] = item;
        else {
            tVideoPos aux;
            for(aux = L->lastPos; aux >= pos+1; aux--)
                L->data[aux] = L->data[aux-1];
            L->data[pos] = item;
        }
        return true;
    }
}

void deleteAtPositionV(tVideoPos pos, tVideoList *L) {
    /*
        -Tipo: Destructora
        -Objetivo: Eliminar de la lista el elemento que ocupa la posición indicada
        -Entrada: tVideoPos -> Una posición
                  tVideoList -> La lista
        -Salida: -
        -Precondición: La lista ha sido inicializada y la posición es válida
        -Postcondición: Las posiciones de los elementos posteriores al eliminado pueden haber variado
    */
    tVideoPos aux;
    L->lastPos--;
    for(aux = pos; aux <= L->lastPos; aux++)
        L->data[aux] = L->data[aux+1];
}

tVideoItem getItemV(tVideoPos pos, tVideoList L) {
    /*
       -Tipo: Observadora
       -Objetivo: Devolver el contenido del elemento de la lista que ocupa la posición indicada
       -Entrada: tVideoPos -> Una posición
                 tVideoList -> La lista
       -Salida: tVideoItem
       -Precondición: La lista ha sido inicializada y la posición es válida
       -Postcondición: -
   */
    return L.data[pos];
}

void updateItemV(tVideoItem item, tVideoPos pos, tVideoList *L) {
    /*
        -Tipo: Modificadora
        -Objetivo: Modificar el contenido del elemento situado en la posición indicada
        -Entrada: tVideoItem -> Un item
                  tVideoPos -> Una posición
                  tVideoList -> La lista
        -Salida: -
        -Precondición: La lista ha sido inicializada y la posición es válida
        -Postcondición: El orden de los elementos de la lista no se ve modificado
    */
    L->data[pos] = item;
}

tVideoPos findItemV(tTitleVideo titleVideo, tVideoList L) {
    /*
         -Tipo: Observadora
         -Objetivo: Devolver la posición del primer elemento de la lista cuyo título de vídeo se corresponda con
         el indicado
         -Entrada: tTitleVideo -> Un título de un vídeo
                   tVideoPos -> Una posición
                   tVideoList -> La lista
         -Salida: tVideoPos
         -Precondición: La lista ha sido inicializada
         -Postcondición: -
     */
    if(isEmptyListV(L))
        return NULL_VIDEO;
    else {
        tVideoPos aux;
        for(aux = 0; aux < L.lastPos && strcmp(L.data[aux].titleVideo, titleVideo) != 0; aux++);
        if(strcmp(L.data[aux].titleVideo, titleVideo) == 0)
            return aux;
        else
            return NULL_VIDEO;
    }
}
