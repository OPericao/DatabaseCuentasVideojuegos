#include "libreriasYConstantes.c"

void inicializarListaVacia(List *L);
void createNode(Pos *q);
void addAccount(List *L,char nuevoNombre[]);
void addAccountsFromFile(List *L,char nuevoNombre[]);
void deleteAccount(List *L);
void editAccount(List *L);
void listAccount(List *L);