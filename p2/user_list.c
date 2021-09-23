/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Fernando Seara Romera LOGIN 1: f.searar@udc.es
 * AUTHOR 2: Eduardo Pérez Fraguela LOGIN 2: eduardo.perez.fraguela@udc.es
 * GROUP: 4.1
 * DATE: 07 / 05 / 21
 */


#include "types.h"
#include "user_list.h"

bool createNode(tUserPos *pos) {
    /*
        -Tipo: Generadora
        -Objetivo: Crear un nodo
        -Entrada: tUserPos -> Posición de la lista donde hay que crearlo
        -Salida: bool -> Indicando si se creó o no
        -Precondición: -
        -Postcondición: -
    */
    *pos = malloc(sizeof(struct tNode));
    return *pos != NULL_USER;
}

void createEmptyList(tUserList *L) {
    /*
        -Tipo: Modificadora
        -Objetivo: Inicializar la lista
        -Entrada: tUserList -> La lista
        -Salida: -
        -Precondición: -
        -Postcondición: La lista queda inicializada y no contiene elementos
    */
    *L = NULL_USER;
}

bool isEmptyList(tUserList L) {
    /*
        -Tipo: Observadora
        -Objetivo: Determinar si la lista está vacía
        -Entrada: tUserList -> La lista
        -Salida: bool
        -Precondición: La lista ha sido inicializada
        -Postcondición: -
    */
    return L == NULL_USER;
}

tUserPos first(tUserList L) {
    /*
        -Tipo: Observadora
        -Objetivo: Devolver la posición del primer elemento de la lista
        -Entrada: tUserList -> La lista
        -Salida: tUserPos
        -Precondición: La lista ha sido inicializada y no está vacía
        -Postcondición: -
    */
    return L;
}

tUserPos last(tUserList L) {
    /*
        -Tipo: Observadora
        -Objetivo: Devolver la posición del último elemento de la lista
        -Entrada: tUserList -> La lista
        -Salida: tUserPos
        -Precondición: La lista ha sido inicializada y no está vacía
        -Postcondición: -
    */
    tUserPos aux;
    for(aux = L; aux->next != NULL_USER; aux = aux->next);
    return aux;
}

tUserPos previous(tUserPos pos, tUserList L) {
    /*
        -Tipo: Observadora
        -Objetivo: Devolver la posición en la lista del elemento anterior al de la posición indicada
        -Entrada: tUserPos -> Una posición
                  tUserList -> La lista
        -Salida: tUserPos
        -Precondición: La lista ha sido inicializada y la posición es válida
        -Postcondición: -
    */
    tUserPos aux;
    if(pos == L)
        aux = NULL_USER;
    else
        for(aux = L; aux->next != pos; aux = aux->next);
    return aux;
}

tUserPos next(tUserPos pos, tUserList L) {
    /*
        -Tipo: Observadora
        -Objetivo: Devolver la posición en la lista del elemento siguiente al de la posición indicada
        -Entrada: tUserPos -> Una posición
                  tUserList -> La lista
        -Salida: tUserPos
        -Precondición: La lista ha sido inicializada y la posición es válida
        -Postcondición: -
    */
    return pos->next;
}

tUserPos findPosition(tUserItem item, tUserList L) {
    /*
        -Tipo: Observadora
        -Objetivo: Devolver la posición encontrada en la lista
        -Entrada: tUserItem -> Un item
                  tUserList -> La lista
        -Salida: tUserPos
        -Precondición: La lista ha sido inicializada y la posición es válida
        -Postcondición: -
    */
    tUserPos aux;
    aux = L;
    while((aux->next != NULL_USER) && strcmp(aux->next->data.nickname, item.nickname) < 0)
        aux = aux->next;
    return aux;
}

bool insertItem(tUserItem item, tUserList *L) {
    /*
        -Tipo: Generadora
        -Objetivo: Insertar un elemento en la lista antes de la posición indicada. Si la posición es NULL_USER entonces se
        añade al final. Devuelve true si el elemento fue insertado; false en caso contrario
        -Entrada: tUserItem -> Un item
                  tUserPos -> Una posición
                  tUserList -> La lista
        -Salida: bool
        -Precondición: La lista ha sido inicializada y la posición es válida o nula
        -Postcondición: Las posiciones de los elemento posteriores al insertado pueden haber variado
    */
    tUserPos p, q;
    if(!createNode(&q))
        return false;
    else {
        q->data = item;
        q->next = NULL_USER;
        if (*L == NULL_USER)
            *L = q;
        else {
            if (strcmp(item.nickname, (*L)->data.nickname) < 0) {
                q->next = *L;
                *L = q;
            }
            else {
                p = findPosition(item, *L);
                q->next = p->next;
                p->next = q;
            }
        }
        return true;
    }
}

void deleteAtPosition(tUserPos pos, tUserList *L) {
    /*
        -Tipo: Destructora
        -Objetivo: Eliminar de la lista el elemento que ocupa la posición indicada
        -Entrada: tUserPos -> Una posición
                  tUserList -> La lista
        -Salida: -
        -Precondición: La lista ha sido inicializada y la posición es válida
        -Postcondición: Las posiciones de los elementos posteriores al eliminado pueden haber variado
    */
    tUserPos aux;
    if(pos == *L){
        *L = (*L)->next;
    } else if(pos->next == NULL_USER){
        for(aux = *L; aux->next != pos; aux = aux->next);
        aux->next = NULL_USER;
    } else{
        aux = pos->next;
        pos->data = aux->data;
        pos->next = aux->next;
        pos = aux;
    }
    free(pos);
}

tUserItem getItem(tUserPos pos, tUserList L) {
    /*
        -Tipo: Observadora
        -Objetivo: Devolver el contenido del elemento de la lista que ocupa la posición indicada
        -Entrada: tUserPos -> Una posición
                  tUserList -> La lista
        -Salida: tUserItem
        -Precondición: La lista ha sido inicializada y la posición es válida
        -Postcondición: -
    */
    return pos->data;
}

void updateItem(tUserItem item, tUserPos pos, tUserList *L) {
    /*
        -Tipo: Modificadora
        -Objetivo: Modificar el contenido del elemento situado en la posición indicada
        -Entrada: tUserItem -> Un item
                  tUserPos -> Una posición
                  tUserList -> La lista
        -Salida: -
        -Precondición: La lista ha sido inicializada y la posición es válida
        -Postcondición: El orden de los elementos de la lista no se ve modificado
    */
    pos->data = item;
}

tUserPos findItem(tNickname nickname, tUserList L) {
    /*
        -Tipo: Observadora
        -Objetivo: Devolver la posición del primer elemento de la lista cuyo nickname de usuario se corresponda con
        el indicado
        -Entrada: tNickname -> Un nickname
                  tUserPos -> Una posición
                  tUserList -> La lista
        -Salida: tPosL
        -Precondición: La lista ha sido inicializada
        -Postcondición: -
    */
    tUserPos aux;
    if(isEmptyList(L))
        return NULL_USER;
    else {
        for (aux = L; (aux != NULL_USER) && strcmp(aux->data.nickname, nickname) < 0; aux = aux->next);
        if(aux != NULL_USER && strcmp(aux->data.nickname, nickname) == 0)
            return aux;
        else
            return NULL_USER;
    }
}

