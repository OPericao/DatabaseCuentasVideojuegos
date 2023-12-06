#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define RESET_COLOR     "\x1b[0m"
#define VERDE           "\x1b[32m"
#define AZUL            "\x1b[34m"
#define AMARILLO        "\x1b[33m"
#define ROJO            "\x1b[31m"

struct DataBase{
    char id_lol[20];
    char nickname[20];
    char password[20];
    char elo[10];
    char lvl[5];
};

typedef struct Nodo *Pos;

struct Nodo{
    struct DataBase cuentas;
    struct Nodo *next;
};

typedef Pos List;


void inicializarListaVacia();
void createNode();
void addAccount();
void addAccountsFromFile();
void deleteAccount();
void editAccount();
void listAccount();


int main() {
    List *L = NULL;
    bool seguir = true;
    int opcion;

    addAccountsFromFile(&L);

    do {
        printf("Escolle unha opcion:\n"
               "1.Engadir conta\n"
               "2.Eliminar conta\n"
               "3.Modificar conta\n"
               "4.Listar contas\n"
               "5.Sair do menu\n"
               "Opcion: ");

        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                addAccount(&L);
                break;
            case 2:
                deleteAccount(&L);
                break;
            case 3:
                editAccount(&L);
                break;
            case 4:
                listAccount(&L);
                break;
            case 5:
                seguir = false;
                printf("\nSaindo da aplicacion, ata pronto :)");
                Pos t,q=*L;
                while(q!=NULL){
                    t=q->next;
                    free(q);
                    q=t;
                }
                L=NULL;

            default:
                printf(ROJO"\nError ao escoller a opcion, volva executar\n"RESET_COLOR);
                break;
        }
    } while (seguir);

    return 0;
}

void inicializarListaVacia(List *L){
    *L=NULL;
}

void createNode(Pos *q){
    *q=malloc(sizeof(struct Nodo));

    if (*q != NULL) {
        (*q)->next = NULL;
    } else {
        printf(ROJO"Erro: Memoria chea\n"RESET_COLOR);
    }
}

void addAccount(List *L){
    Pos q;

    createNode(&q);

    printf(AMARILLO"\nEnche os seguintes campos\n"RESET_COLOR);

    printf(AMARILLO"\nId do cliente: "RESET_COLOR);
    scanf("%19s", q->cuentas.id_lol); // Limitar la entrada a 19 caracteres para evitar desbordamiento

    // Limpiar el búfer de entrada
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf(AMARILLO"\nNome de invocador: "RESET_COLOR);
    fgets(q->cuentas.nickname, sizeof(q->cuentas.nickname), stdin);
    q->cuentas.nickname[strcspn(q->cuentas.nickname, "\n")] = '\0'; // Eliminar el salto de línea si está presente

    printf(AMARILLO"\nContrasinal: "RESET_COLOR);
    fgets(q->cuentas.password, sizeof(q->cuentas.password), stdin);
    q->cuentas.password[strcspn(q->cuentas.password, "\n")] = '\0'; // Eliminar el salto de línea si está presente

    printf(AMARILLO"\nNivel da conta: "RESET_COLOR);
    scanf("%4s", q->cuentas.lvl); // Limitar la entrada a 4 caracteres para evitar desbordamiento

    printf(AMARILLO"\nElo: "RESET_COLOR);
    scanf("%9s", q->cuentas.elo);

    printf(VERDE"\n\nConta engadida exitosamente\n"
            "------------------------------\n"
            AMARILLO"Id do cliente: " RESET_COLOR "%s\n"
            AMARILLO"Nome de invocador: " RESET_COLOR "%s\n"
            AMARILLO"Contrasinal: " RESET_COLOR "%s\n"
            AMARILLO"Nivel da conta: " RESET_COLOR "%s\n"
            AMARILLO"Elo: " RESET_COLOR "%s\n"
            VERDE"------------------------------\n\n"RESET_COLOR,
            q->cuentas.id_lol,
            q->cuentas.nickname,
            q->cuentas.password,
            q->cuentas.lvl,
            q->cuentas.elo);

    if (*L == NULL) {
        *L = q;  
    } else {
        Pos t = *L;
        while (t->next != NULL) {
            t = t->next;
        }
        t->next = q;
    }

    FILE *archivo = fopen("contrasinais.txt", "a");
    if (archivo != NULL) {
        fprintf(archivo, "%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\n",
                q->cuentas.id_lol,
                q->cuentas.nickname,
                q->cuentas.password,
                q->cuentas.lvl,
                q->cuentas.elo);
        fclose(archivo);
    } else {
        printf(ROJO"Error ao abrir o arquivo para escritura.\n"RESET_COLOR);
    }
}

void addAccountsFromFile(List *L) {
    FILE *archivo = fopen("contrasinais.txt", "r");
    if (archivo != NULL) {
        while (1) {
            Pos q;
            createNode(&q);
            if (fscanf(archivo, "%s %s %s %s %s",
                       q->cuentas.id_lol,
                       q->cuentas.nickname,
                       q->cuentas.password,
                       q->cuentas.lvl,
                       q->cuentas.elo) != 5) {
                free(q);
                break;
            }
            if (*L == NULL) {
                *L = q;
            } else {
                Pos t = *L;
                while (t->next != NULL) {
                    t = t->next;
                }
                t->next = q;
            }
        }
        fclose(archivo);
    }
}

void deleteAccount(List *L){
    printf(VERDE"\nConta %s eliminada exitosamente\n\n"RESET_COLOR, (*L)->cuentas.nickname);
}

void editAccount(List *L){
    //Pos q;
    printf(VERDE"\nConta %s modificada exitosamente\n\n"RESET_COLOR,(*L)->cuentas.nickname);
}

void listAccount(List *L) {
    Pos q;

    printf(AMARILLO"\nEsta e a tua Listaxe de contas\n"
       AMARILLO "------------------------------\n"
       AZUL "Id cliente\t\t\tNome Invocador\t\t\tContrasinal\t\t\tNivel\t\t\tElo\n\n");

    for (q = *L; q != NULL; q = q->next) {
        printf(VERDE "%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\n\n" RESET_COLOR,
               q->cuentas.id_lol,
               q->cuentas.nickname,
               q->cuentas.password,
               q->cuentas.lvl,
               q->cuentas.elo);
    }
}
