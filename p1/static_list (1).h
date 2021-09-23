/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Fernando Seara Romera LOGIN 1: f.searar
 * AUTHOR 2: Eduardo Pérez Fraguela LOGIN 2: eduardo.perez.fraguela
 * GROUP: 4.1
 * DATE: 07 / 03 / 21
 */

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "types.h"

#include <stdbool.h>
#define LNULL -1
#define MAX 25

typedef int tPosL;
typedef struct tList{
    tItemL data[MAX];
    tPosL lastPos;
}tList;

void createEmptyList(tList *L);
bool isEmptyList(tList);
tPosL first(tList);
tPosL last(tList);
tPosL previous(tPosL, tList);
tPosL next(tPosL, tList);
bool insertItem(tItemL, tPosL, tList *L);
void deleteAtPosition(tPosL, tList *L);
tItemL getItem(tPosL, tList);
void updateItem(tItemL, tPosL, tList *L);
tPosL findItem(tNickname, tList);

#endif
