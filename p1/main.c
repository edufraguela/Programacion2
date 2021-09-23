/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Fernando Seara Romera LOGIN 1: f.searar
 * AUTHOR 2: Eduardo Pérez Fraguela LOGIN 2: eduardo.perez.fraguela
 * GROUP: 4.1
 * DATE: 07 / 03 / 21
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef STATIC_LIST
#include "static_list.h"
#endif
#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef TEST_LIST
#include "list/list.h"
#endif

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

void new(char *nickname, char *category, tList *L) {
    /*
        -Tipo: Generadora
        -Objetivo: Insertar en la lista un usuario de categoría standard o premium
        -Entrada: char * -> nickname
                  char * -> categoría del usuario
        -Salida: -
        -Precondición: La lista ha sido inicializada
        -Postcondición: -
    */
    tItemL item;
    if(strlen(nickname) <= NAME_LENGTH_LIMIT)
        strcpy(item.nickname, nickname);    //copiamos el nombre del usuario en el struct tItemL
    else
        printf("+ Error: New not possible\n");
    if(findItem(nickname, *L) == LNULL) {
        if (!strcmp(category, "standard")) item.userCategory = standard;
        else if (!strcmp(category, "premium")) item.userCategory = premium;
        else {  //En caso de pasar una categoría inválida
            printf("+ Error: New not possible\n");
            return;
        }
        item.numPlay = 0;   //Inicializamos el número de reproducciones a 0
        if (insertItem(item, LNULL, L))
            printf("* New: nick %s category %s\n", item.nickname, getCategoryName(item.userCategory));
        else
            printf("+ Error: New not possible\n");
    } else {    //Hemos encontrado un usuario cn el mismo nickname, por lo que no podemos añadirlo de nuevo
        printf("+ Error: New not possible\n");
    }
}

float getAverage(int plays, int users) {
    /*
        -Tipo: Generadora
        -Objetivo: Calcular la media de visitas por usuario
        -Entrada: int -> num de visitas
                  int -> num de usuarios
        -Salida: float -> La media de visitas
        -Precondición: -
        -Postcondición: -
    */
    if(users == 0)
        return 0;
    else
        return  (float) (plays / users);
}

void delete(char *nickname, tList *L) {
    /*
        -Tipo: Destructora
        -Objetivo: Borrar un usuario de la lista
        -Entrada: char * -> nickname
                  tList -> La lista
        -Salida: -
        -Precondición: La lista ha sido inicializada
        -Postcondición: -
    */
    tPosL pos;
    if((pos = findItem(nickname, *L)) != LNULL) {
        tItemL item = getItem(pos, *L);
        printf("* Delete: nick %s category %s numplays %d\n", item.nickname, getCategoryName(item.userCategory), item.numPlay);
        deleteAtPosition(pos, L);
    } else  //Si no encontramos el usuario, significa que no existe
        printf("+ Error: Delete not possible\n");
}

void play(char *nickname, char *video, tList *L) {
    /*
        -Tipo: Modificadora
        -Objetivo: Incrementar en 1 el número de visitas de un usuario de la lista
        -Entrada: char * -> nickname
                  char * -> video
                  tList -> La lista
        -Salida: -
        -Precondición: La lista ha sido inicializada
        -Postcondición: -
    */
    tPosL pos;
    if(strlen(video) > NAME_LENGTH_LIMIT) { //En caso de que el título supere la longitud máxima, no se contabilizará la
                                            // visita ya que es un vídeo inválido
        printf("+ Error: Play not possible\n");
        return;
    }
    if((pos = findItem(nickname, *L)) != LNULL) {
        tItemL item = getItem(pos, *L);
        item.numPlay += 1;
        updateItem(item, pos, L);
        printf("* Play: nick %s plays video %s numplays %d\n", item.nickname, video, item.numPlay);
    } else
        printf("+ Error: Play not possible\n");
}

void stats(tList *L) {
    /*
        -Tipo: Observadora
        -Objetivo: Imprimir la lista completa de usuarios y estadísticas de visualizaciones según el formato pedido
        -Entrada: tList -> La lista
        -Salida: -
        -Precondición: La lista ha sido inicializada
        -Postcondición: -
    */
    tPosL pos;
    if(!isEmptyList(*L)) {
        tItemL item;
        int stdUsers = 0;   //num de usuarios con categoría standard
        int premUsers = 0;  //num de usuarios con categoría premium
        int stdPlays = 0;   //num de reproducciones totales de usuarios con categoría standard
        int premPlays = 0;  //num de reproducciones totales de usuarios con categoría premium
        for(pos = first(*L); pos != LNULL; pos = next(pos, *L)) {
            item = getItem(pos, *L);
            //Imprimimos información sobre cada usuario de la lista
            printf("Nick %s category %s numplays %d\n", item.nickname, getCategoryName(item.userCategory), item.numPlay);
            if(item.userCategory == standard) {
                stdUsers++;
                stdPlays += item.numPlay;
            } else {
                premUsers++;
                premPlays += item.numPlay;
            }
        }
        //Imprimimos las estadísticas con el formato pedido
        printf("Category   Users  Plays  Average\n");
        printf("Standard    %d     %d     %.2f\n", stdUsers, stdPlays, getAverage(stdPlays, stdUsers));
        printf("Premium     %d     %d     %.2f\n", premUsers, premPlays, getAverage(premPlays, premUsers));
    }
    else    //En caso de que la lista esté vacía
        printf("+ Error: Stats not possible");
}

void processCommand(char *commandNumber, char command, char *param1, char *param2, tList *L) {

    switch(command) {
        case 'N': {
            printf("********************\n");
            printf("%s %c: nick %s category %s\n", commandNumber, command, param1, param2);
            new(param1, param2, L);
            break;
        }
        case 'D': {
            printf("********************\n");
            printf("%s %c: nick %s\n", commandNumber, command, param1);
            delete(param1, L);
            break;
        }
        case 'P': {
            printf("********************\n");
            printf("%s %c: nick %s video %s\n", commandNumber, command, param1, param2);
            play(param1, param2, L);
            break;
        }
        case 'S': {
            printf("********************\n");
            printf("%s %c\n", commandNumber, command);
            stats(L);
            break;
        }
        default: {
            break;
        }
    }
}


void readTasks(char *filename) {
    FILE *df;
    char *commandNumber, *command, *param1, *param2;
    tList L;

    df = fopen(filename, "rb");
    if (df != NULL) {
        createEmptyList(&L);
        const char delimiters[] = " \n\r";
        char buffer[MAX_BUFFER];
        while (fgets(buffer, MAX_BUFFER, df)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            processCommand(commandNumber, command[0], param1, param2, &L);
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






