#include "libreriasYConstantes.c"

void inicializarListaVacia(List *L);
void createNode(Pos *q);
void addAccount(List *L,char nuevoNombre[]);
void addAccountsFromFile(List *L,char nuevoNombre[]);
void deleteAccount(List *L,char nuevoNombre[]);
void editAccount(List *L,char nuevoNombre[]);
void listAccount(List *L);