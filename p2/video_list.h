/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Fernando Seara Romera LOGIN 1: f.searar@udc.es
 * AUTHOR 2: Eduardo Pérez Fraguela LOGIN 2: eduardo.perez.fraguela@udc.es
 * GROUP: 4.1
 * DATE: 07 / 05 / 21
 */

#ifndef P2_VIDEO_LIST_H
#define P2_VIDEO_LIST_H

#include "types.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define NULL_VIDEO -1
#define MAX 25

typedef int tVideoPos;
typedef struct tVideoItem {
    tTitleVideo titleVideo;
    tPlayTime playTime;
} tVideoItem;
typedef struct tVideoList {
    tVideoItem data[MAX];
    tVideoPos lastPos;
} tVideoList;

void createEmptyListV(tVideoList *L);
bool isEmptyListV(tVideoList);
tVideoPos firstV(tVideoList);
tVideoPos lastV(tVideoList);
tVideoPos previousV(tVideoPos, tVideoList);
tVideoPos nextV(tVideoPos, tVideoList);
bool insertItemV(tVideoItem, tVideoPos, tVideoList *L);
void deleteAtPositionV(tVideoPos, tVideoList *L);
tVideoItem getItemV(tVideoPos, tVideoList);
void updateItemV(tVideoItem, tVideoPos, tVideoList *L);
tVideoPos findItemV(tTitleVideo, tVideoList);

#endif //P2_VIDEO_LIST_H

