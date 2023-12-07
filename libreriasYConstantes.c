#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include <ctype.h>
#include <limits.h>

#include <windows.h>

#include "colores.c"

#define MAX_ID      20
#define MAX_NICK    20
#define MAX_PW      20
#define MAX_LVL     5
#define MAX_ELO     10

struct DataBase{
    char id_lol[MAX_ID+1];
    char nickname[MAX_NICK+1];
    char password[MAX_PW+1];
    char lvl[MAX_LVL+1];
    char elo[MAX_ELO+1];
};

typedef struct Nodo *Pos;

struct Nodo{
    struct DataBase cuentas;
    struct Nodo *next;
};

typedef Pos List;