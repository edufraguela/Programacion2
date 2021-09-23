/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Fernando Seara Romera LOGIN 1: f.searar@udc.es
 * AUTHOR 2: Eduardo Pérez Fraguela LOGIN 2: eduardo.perez.fraguela@udc.es
 * GROUP: 4.1
 * DATE: 07 / 05 / 21
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "video_list.h"
#include "user_list.h"

#define MAX_BUFFER 255

char *getCategoryName(tUserCategory category) {
    /*
        -Tipo: Modificadora
        -Objetivo: Transformar la categoría del usuario de tUserCategory a String(char * en C)
        -Entrada: tUserCategory -> La categoría del usuario
        -Salida: char * -> La categoría del usuario en String
        -Precondición: -
        -Postcondición: -
    */
    switch (category) {
        case standard:
            return "standard";
        case premium:
            return "premium";
        default:
            break;
    }
}

void new(char *nickname, char *category, tUserList *userList) {
    /*
        -Tipo: Generadora
        -Objetivo: Insertar en la lista un usuario de categoría standard o premium
        -Entrada: char * -> nickname
                  char * -> categoría del usuario
		  tUserList -> la lista
        -Salida: -
        -Precondición: La lista ha sido inicializada
        -Postcondición: -
    */
    tUserItem userItem;
    if(strlen(nickname) <= NAME_LENGTH_LIMIT)
        strcpy(userItem.nickname, nickname);
    else {
        printf("+ Error: New not possible\n");
        return;
    }
    if(findItem(userItem.nickname, *userList) == NULL_USER) {   //No existe otro usuario con el nickname, por lo que insertamos
        if(!strcmp(category, "standard"))   userItem.userCategory = standard;
        else if(!strcmp(category, "premium"))   userItem.userCategory = premium;
        else {  //En caso de ser una categoría inválida
            printf("+ Error: New not possible\n");
            return;
        }
        userItem.totalPlayTime = 0;
        createEmptyListV(&userItem.videoList);
        if(insertItem(userItem, userList))
            printf("* New: nick %s category %s\n", userItem.nickname, getCategoryName(userItem.userCategory));
        else
            printf("+ Error: New not possible\n");
    } else  //Ya existe un usuario con el mismo nickname, no podemos insertar
        printf("+ Error: New not possible\n");
}

void add(char *nickname, char *video, tUserList *userList) {
    /*
        -Tipo: Generadora
        -Objetivo: Añadir un vídeo a la lista de vídeos de un usuario
        -Entrada: char * -> nickname del usuario
                  char * -> título del vídeo
                  tUserList -> La lista
        -Salida: -
        -Precondición: La lista ha sido inicializada
        -Postcondición: -
    */
    tUserPos userPos;
    if((userPos = findItem(nickname, *userList)) != NULL_USER) {    //Buscamos el usuario
        tUserItem userItem = getItem(userPos, *userList);
        tVideoItem videoItem;
        strcpy(videoItem.titleVideo, video);
        if(findItemV(videoItem.titleVideo, userItem.videoList) != NULL_VIDEO)   //Si ya tiene ese vídeo en su lista de videos,
            printf("+ Error: Add not possible\n");                      //no podemos insertarlo
        else {
            videoItem.playTime = 0;
            if(insertItemV(videoItem, NULL_VIDEO, &userItem.videoList)) { //Pasando como posición un NULL_VIDEO, insertamos al final
                printf("* Add: nick %s adds video %s\n", nickname, videoItem.titleVideo);
                updateItem(userItem, userPos, userList);    //Es necesario actualizar la lista de vídeos del usuario para
            }                                               //cargar el nuevo vídeo
            else
                printf("+ Error: Add not possible\n");
        }
    }
    else    //No existe ningún usuario con ese nickname
        printf("+ Error: Add not possible\n");
}

void printVideoList(tUserItem userItem) {
    /*
        -Tipo: Observadora
        -Objetivo: Imprime la lista de vídeos de un usuario
        -Entrada: tUserItem -> un usuario
        -Salida: -
        -Precondición: La lista ha sido inicializada
        -Postcondición: -
    */
    tVideoList videoList = userItem.videoList;
    if(isEmptyListV(videoList))
        printf("No videos\n");
    else {
        tVideoPos videoPos;
        tVideoItem videoItem;
        //Recorremos la lista de vídeos del usuario
        for(videoPos = firstV(videoList); videoPos != NULL_VIDEO; videoPos = nextV(videoPos, videoList)) {
            videoItem = getItemV(videoPos, videoList);
            printf("Video %s playtime %d\n", videoItem.titleVideo, videoItem.playTime);
        }
    }
}

float getAverage(int users, int plays) {
    /*
        -Tipo: Generadora
        -Objetivo: Calcular la media de minutos reproducidos de un tipo de usuario
        -Entrada: int -> num de usuarios
                  int -> tiempo de reproducción
        -Salida: float -> La media del tiempo de reproducción de un tipo de usuario
        -Precondición: -
        -Postcondición: -
    */
    if(users == 0)
        return 0;
    else
        return  (float) (plays / users);
}

void printAverage(int stdUsers, int premUsers, int stdPlays, int premPlays) {
    /*
        -Tipo: Observadora
        -Objetivo: Imprime la media de minutos reproducidos por tipo de usuario, así como su número de usuarios
		   y su tiempo de reproducción en minutos
        -Entrada: int -> num de usuarios standard
                  int -> num de usuarios premium
		  int -> tiempo de reproducción de los usuarios standard
		  int -> tiempo de reproducción de los usuarios premium
        -Salida: -
        -Precondición: -
        -Postcondición: -
    */
    printf("Category  Users  TimePlay  Average\n");
    printf("Standard %6d %9d %8.2f\n", stdUsers, stdPlays, getAverage(stdUsers, stdPlays));
    printf("Premium  %6d %9d %8.2f\n", premUsers, premPlays, getAverage(premUsers, premPlays));
}

void stats(tUserList *userList) {
    /*
        -Tipo: Observadora
        -Objetivo: Imprimir la lista completa de usuarios y estadísticas de visualizaciones según el formato pedido
        -Entrada: tUserList -> La lista
        -Salida: -
        -Precondición: La lista ha sido inicializada
        -Postcondición: -
    */
    if(!isEmptyList(*userList)) {
        tUserItem userItem;
        tUserPos userPos;
        int stdUsers = 0;   //num de usuarios con categoría standard
        int premUsers = 0;  //num de usuarios con categoría premium
        int stdPlays = 0;   //tiempo de reproducción total de usuarios con categoría standard
        int premPlays = 0;  //tiempo de reproducción total de usuarios con categoría premium
        //Recorremos la lista de usuarios
        for(userPos = first(*userList); userPos != NULL_USER; userPos = next(userPos, *userList)) {
            userItem = getItem(userPos, *userList);
            printf("*Nick %s category %s totalplaytime %d\n", userItem.nickname,
                    getCategoryName(userItem.userCategory), userItem.totalPlayTime);

            printVideoList(userItem);
            if(userItem.userCategory == standard) {
                stdUsers++;
                stdPlays += userItem.totalPlayTime;
            } else {
                premUsers++;
                premPlays += userItem.totalPlayTime;
            }
        }
        printAverage(stdUsers, premUsers, stdPlays, premPlays);
    } else  //Si la lista de usuarios está vacía, imprimimos lo siguiente
        printf("+ Error: Stats not possible\n");
}

void deleteVideoList(tVideoList *videoList) {
    /*
        -Tipo: Destructora
        -Objetivo: Borrar la lista de vídeos de un usuario
        -Entrada:  tVideoList -> La lista
        -Salida: -
        -Precondición: La lista ha sido inicializada
        -Postcondición: -
    */
    tVideoPos pos = firstV(*videoList);
    while(!isEmptyListV(*videoList)) {
        deleteAtPositionV(pos, videoList);
        pos = nextV(pos, *videoList);
    }
}

void delete(char *nickname, tUserList *userList) {
    /*
        -Tipo: Destructora
        -Objetivo: Borrar un usuario de la lista, incluyendo su lista de vídeos
        -Entrada: char * -> nickname
                  tUserList -> La lista
        -Salida: -
        -Precondición: La lista ha sido inicializada
        -Postcondición: -
    */
    if(!isEmptyList(*userList)) {
        tUserPos pos;
        if((pos = findItem(nickname, *userList)) != NULL_USER) {  //Buscamos el usuario en la lista
            tUserItem item = getItem(pos, *userList);
            printf("* Delete: nick %s category %s totalplaytime %d\n", item.nickname,
                    getCategoryName(item.userCategory), item.totalPlayTime);
            deleteVideoList(&item.videoList);       //Borramos la lista de vídeos del usuario
            deleteAtPosition(pos, userList);        //Borramos al usuario de la lista
            return;
        }
    }
    printf("+ Error: Delete not possible\n");
}

void play(char *nickname, char *title, char *playTime, tUserList *userList) {
    /*
        -Tipo: Modificadora
        -Objetivo: Incrementar el tiempo de reproducción de un usuario de la lista
        -Entrada: char * -> nickname
                  char * -> título del vídeo
                  char * -> minutos de reproducción a sumar
                  tUserList -> La lista
        -Salida: -
        -Precondición: La lista ha sido inicializada
        -Postcondición: -
    */
    int minutos = atoi(playTime);     //Convertir string a int
    if(!isEmptyList(*userList)) {
        tUserPos pos;
        if((pos = findItem(nickname, *userList)) != NULL_USER) {   //Buscamos el nick en la lista
            tUserItem item = getItem(pos, *userList);
            tVideoPos auxPos;
            if((auxPos = findItemV(title, item.videoList)) != NULL_VIDEO) {  //Buscamos el vídeo en la lista de vídeos del usuario
                tVideoItem auxItem = getItemV(auxPos, item.videoList);
                auxItem.playTime += minutos;    //Sumamos minutos en el tiempo de reproducción del vídeo
                updateItemV(auxItem, auxPos, &item.videoList);
                item.totalPlayTime += minutos;  //Sumamos minutos en el tiempo de reproducción total del usuario
                updateItem(item, pos, userList);
                printf("* Play: nick %s plays video %s playtime %d totalplaytime %d\n", nickname, title,
                                auxItem.playTime, item.totalPlayTime);
                return;
            }
        }
    }
    //En caso de error, se imprime lo siguiente
    printf("+ Error: Play not possible\n");
}

void removeC(char *param1, tUserList *userList) {
    /*
        -Tipo: Destructora
        -Objetivo: Borrar de la lista los usuarios standard que excedieron el tiempo máximo de reproducción,
                   borrando también su lista de vídeos
        -Entrada: char * -> tiempo de reproducción máximo
                  tUserList -> La lista
        -Salida: -
        -Precondición: La lista ha sido inicializada
        -Postcondición: -
    */
    int maxTime = atoi(param1);
    int cnt = 0;    //Número de usuarios a borrar, el cuál se actualiza en el bucle
    tUserItem item;
    if(!isEmptyList(*userList)) {
        //Recorremos la lista de usuarios buscando usuarios con categoría standard y con más minutos de los permitidos
        tUserPos aux;
        tUserPos i = first(*userList);
        while(i != NULL_USER) {
            aux = i;
            item = getItem(i, *userList);
            if (item.userCategory == standard && item.totalPlayTime > maxTime) {
                printf("Removing nick %s totalplaytime %d\n", item.nickname, item.totalPlayTime);
                //Borramos la lista de vídeos del usuario
                deleteVideoList(&item.videoList);
                if(i == first(*userList)) {         //En caso de estar al principio de la lista el usuario
                    deleteAtPosition(i, userList);
                    i = first(*userList);
                } else if(i == next(first(*userList), *userList)) {     //En caso de estar en la segunda posición
                    deleteAtPosition(i, userList);
                    i = next(first(*userList), *userList);
                } else {        //En cualquier otro caso
                    aux = previous(previous(i, *userList), *userList);
                    deleteAtPosition(i, userList);
                    i = next(next(aux, *userList), *userList);
                }
                cnt++;
                continue;
            }
            i = next(aux, *userList);
        }
    }
    if(cnt == 0)    //En caso de no haber encontrado ningún usuario a borrar:
        printf("+ Error: Remove not possible\n");
}

void printAsterisks() {
    /*
        -Tipo: Observadora
        -Objetivo: Imprimir una cadena de 20 asteriscos
        -Entrada: -
        -Salida: -
        -Precondición: -
        -Postcondición: -
    */
    printf("********************\n");
}

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, tUserList *userList) {

    switch(command) {
        case 'N': {
            printAsterisks();
            printf("%s %c: nick %s category %s\n", commandNumber, command, param1, param2);
            new(param1, param2, userList);
            break;
        }
        case 'A': {
            printAsterisks();
            printf("%s %c: nick %s video %s\n", commandNumber, command, param1, param2);
            add(param1, param2, userList);
            break;
        }
        case 'S': {
            printAsterisks();
            printf("%s %c\n", commandNumber, command);
            stats(userList);
            break;
        }
        case 'D': {
            printAsterisks();
            printf("%s %c: nick %s\n", commandNumber, command, param1);
            delete(param1, userList);
            break;
        }
        case 'P': {
            printAsterisks();
            printf("%s %c: nick %s video %s minutes %s\n", commandNumber, command, param1, param2, param3);
            play(param1, param2, param3, userList);
            break;
        }
        case 'R': {
            printAsterisks();
            printf("%s %c: maxtime %s\n", commandNumber, command, param1);
            removeC(param1, userList);
            break;
        }
        default: {
            break;
        }
    }
}

void readTasks(char *filename) {
    FILE *df;
    char *commandNumber, *command, *param1, *param2, *param3;
    tUserList userList;
    df = fopen(filename, "rb");
    if (df != NULL) {
        createEmptyList(&userList);
        const char delimiters[] = " \n\r";
        char buffer[MAX_BUFFER];
        while (fgets(buffer, MAX_BUFFER, df)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            processCommand(commandNumber, command[0], param1, param2, param3, &userList);
        }
        fclose(df);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {

    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name);

    return 0;
}
