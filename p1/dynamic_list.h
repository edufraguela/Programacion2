/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Fernando Seara Romera LOGIN 1: f.searar
 * AUTHOR 2: Eduardo Pérez Fraguela LOGIN 2: eduardo.perez.fraguela
 * GROUP: 4.1
 * DATE: 07 / 03 / 21
 */

#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

#include "types.h"
#include <stdbool.h>
#include <stdlib.h>
#define LNULL NULL

typedef struct tNode* tPosL;
struct tNode{
    tItemL data;
    tPosL next;
};
typedef tPosL tList;

bool createNode(tPosL *p);
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
