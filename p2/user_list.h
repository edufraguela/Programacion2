/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Fernando Seara Romera LOGIN 1: f.searar@udc.es
 * AUTHOR 2: Eduardo Pérez Fraguela LOGIN 2: eduardo.perez.fraguela@udc.es
 * GROUP: 4.1
 * DATE: 07 / 05 / 21
 */

#ifndef P2_USER_LIST_H
#define P2_USER_LIST_H

#include "types.h"
#include "video_list.h"
#define NULL_USER NULL

typedef struct tUserItem{
    tNickname nickname;
    tPlayTime totalPlayTime;
    tUserCategory userCategory;
    tVideoList videoList;
}tUserItem;
typedef struct tNode* tUserPos;

struct tNode{
    struct tUserItem data;
    tUserPos next;
};
typedef tUserPos tUserList;

void createEmptyList(tUserList *L);
bool isEmptyList(tUserList);
tUserPos first(tUserList);
tUserPos last(tUserList);
tUserPos previous(tUserPos, tUserList);
tUserPos next(tUserPos, tUserList);
bool insertItem(tUserItem, tUserList *L);
void deleteAtPosition(tUserPos, tUserList *L);
tUserItem getItem(tUserPos, tUserList);
void updateItem(tUserItem, tUserPos, tUserList *L);
tUserPos findItem(tNickname, tUserList);

#endif //P2_USER_LIST_H