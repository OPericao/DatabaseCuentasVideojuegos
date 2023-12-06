#include "listas.h"

void inicializarListaVacia(List *L){
    *L=NULL;
}

void createNode(Pos *q){
    *q=malloc(sizeof(struct Nodo));

    if (*q != NULL) {
        (*q)->next = NULL;
    } else {
        printf(ERROR"Erro: Memoria chea\n"RST);
    }
}

void addAccount(List *L){
    Pos q;
    
    int c;

    char aux[MAX_ID+1];
    char auxLvl[MAX_LVL+1];
    char auxElo[MAX_ELO+1];

    createNode(&q);

    printf(MSJ_SISTEMA"\nEnche os seguintes campos\n"RST);

    printf(PETICION"\nId do cliente: "RST);
    scanf("%20s", aux);
    strcpy(q->cuentas.id_lol, aux);
    memset(aux, 0, sizeof(aux));

    while ((c = getchar()) != '\n' && c != EOF);

    printf(PETICION"\nNome de invocador: "RST);
    scanf("%20s", aux);
    strcpy(q->cuentas.nickname, aux);
    memset(aux, 0, sizeof(aux));

    while ((c = getchar()) != '\n' && c != EOF);

    printf(PETICION"\nContrasinal: "RST);
    scanf("%20s", aux);
    strcpy(q->cuentas.password, aux);
    memset(aux, 0, sizeof(aux));

    while ((c = getchar()) != '\n' && c != EOF);

    printf(PETICION"\nNivel: "RST);
    scanf("%5s", auxLvl);
    strcpy(q->cuentas.lvl, auxLvl);
    memset(aux, 0, sizeof(auxLvl));

    while ((c = getchar()) != '\n' && c != EOF);

    printf(PETICION"\nElo: "RST);
    scanf("%10s", auxElo);
    strcpy(q->cuentas.elo, auxElo);
    memset(aux, 0, sizeof(auxElo));

    while ((c = getchar()) != '\n' && c != EOF);


    printf(VERDE"\n\nConta engadida exitosamente\n"
            DECORACION"------------------------------\n"
            MSJ_SISTEMA"Id do cliente: " INFO "%s\n"
            MSJ_SISTEMA"Nome de invocador: " INFO "%s\n"
            MSJ_SISTEMA"Contrasinal: " INFO "%s\n"
            MSJ_SISTEMA"Nivel da conta: " INFO "%s\n"
            MSJ_SISTEMA"Elo: " INFO "%s\n"
            DECORACION"------------------------------\n\n"RST,
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
        printf(ERROR"Error ao abrir o arquivo para escritura.\n"RST);
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

void deleteAccount(List *L) {
    if (*L == NULL) {
        printf(ERROR"\nNon hai contas para eliminar\n\n"RST);
        return;
    }

    char identificador[MAX_ID+1];
    printf(PETICION"\nIntroduce o valor do campo polo cal desexas eliminar a conta: "RST);
    scanf("%20s", identificador);

    Pos q = *L;
    Pos prev = NULL;

    while (q != NULL && strcmp(q->cuentas.id_lol, identificador) != 0 &&
           strcmp(q->cuentas.nickname, identificador) != 0 &&
           strcmp(q->cuentas.password, identificador) != 0 &&
           strcmp(q->cuentas.lvl, identificador) != 0 &&
           strcmp(q->cuentas.elo, identificador) != 0) {
        prev = q;
        q = q->next;
    }

    if (q == NULL) {
        printf(ERROR"\nNon se atopou a conta con campo %s\n\n"RST, identificador);
        return;
    }

    if (prev == NULL) {
        *L = q->next;
    } else {
        prev->next = q->next;
    }

    printf(VERDE"\nConta eliminada exitosamente:\n"
           MSJ_SISTEMA"Id do cliente: "INFO"%s\n"
           MSJ_SISTEMA"Nome de invocador: "INFO"%s\n"
           MSJ_SISTEMA"Contrasinal: "INFO"%s\n"
           MSJ_SISTEMA"Nivel da conta: "INFO"%s\n"
           MSJ_SISTEMA"Elo: "INFO"%s\n\n"RST,
           q->cuentas.id_lol,
           q->cuentas.nickname,
           q->cuentas.password,
           q->cuentas.lvl,
           q->cuentas.elo);
    
    free(q);

    FILE *archivo = fopen("contrasinais.txt", "w");
    if (archivo != NULL) {
        Pos t = *L;
        while (t != NULL) {
            fprintf(archivo, "%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\n",
                    t->cuentas.id_lol,
                    t->cuentas.nickname,
                    t->cuentas.password,
                    t->cuentas.lvl,
                    t->cuentas.elo);
            t = t->next;
        }
        fclose(archivo);
    } else {
        printf(ERROR"Error ao abrir o arquivo para escritura.\n"RST);
    }
}

void editAccount(List *L) {  

    if (*L == NULL) {
        printf(ERROR"\nNon hai contas para modificar\n\n"RST);
        return;
    }

    int c;
    int opcion;

    bool seguir=true;

    char identificador[MAX_ID+1];
    char aux[MAX_ID+1];
    char auxLvl[MAX_LVL+1];
    char auxElo[MAX_ELO+1];

    printf(PETICION"\nIntroduce o valor do campo polo cal desexas modificar a conta: "RST);
    scanf("%20s", identificador);

    Pos q = *L;
    Pos prev = NULL;

    while (q != NULL && strcmp(q->cuentas.id_lol, identificador) != 0 &&
           strcmp(q->cuentas.nickname, identificador) != 0) {
        prev = q;
        q = q->next;
    }

    if (q == NULL) {
        printf(ERROR"\nNon se atopou a conta con campo %s\n\n"RST, identificador);
        return;
    }

    do{
        printf(MSJ_SISTEMA"\nEscolle unha opcion:\n"
            DECORACION"====================\n"
            MENU"1. Modificar Id do cliente\n"
            "2. Modificar Nome de invocador\n"
            "3. Modificar Contrasinal\n"
            "4. Modificar Nivel da conta\n"
            "5. Modificar Elo\n"
            "6. Cancelar Operacion\n"
            DECORACION"====================\n"
            PETICION"Opcion: "RST);

        scanf("%d", &opcion);

        switch(opcion){
            case 1:
                printf(PETICION"\nId do cliente novo (antes %s): "RST, q->cuentas.id_lol);
               scanf("%20s", aux);
               strcpy(q->cuentas.id_lol, aux);
                memset(aux, 0, sizeof(aux));

                while ((c = getchar()) != '\n' && c != EOF);
            
                printf(MSJ_SISTEMA"\nId do cliente modificado correctamente a "INFO"%s\n",q->cuentas.id_lol);
                break;
            case 2:
                while ((c = getchar()) != '\n' && c != EOF);
               printf(PETICION"\nNome de invocador novo (antes %s): "RST, q->cuentas.nickname);
                fgets(q->cuentas.nickname, sizeof(q->cuentas.nickname), stdin);
                q->cuentas.nickname[strcspn(q->cuentas.nickname, "\n")] = '\0';
                printf(MSJ_SISTEMA"\nNome de invocador modificado correctamente a "INFO"%s\n",q->cuentas.nickname);
                break;
            case 3:
                while ((c = getchar()) != '\n' && c != EOF);
                printf(PETICION"\nContrasinal novo (antes %s): "RST, q->cuentas.password);
                fgets(q->cuentas.password, sizeof(q->cuentas.password), stdin);
                q->cuentas.password[strcspn(q->cuentas.password, "\n")] = '\0';
                printf(MSJ_SISTEMA"\nContrasinal modificado correctamente a " INFO"%s\n",q->cuentas.password);
                break;
            case 4:
                while ((c = getchar()) != '\n' && c != EOF);
                printf(PETICION"\nNivel da conta novo (antes %s): "RST, q->cuentas.lvl);
                scanf("%5s", q->cuentas.lvl);
                printf(MSJ_SISTEMA"\nNivel da conta modificado correctamente a "INFO"%s\n",q->cuentas.lvl);
                break;
            case 5:
                while ((c = getchar()) != '\n' && c != EOF);
                printf(PETICION"\nElo novo (antes %s): "RST, q->cuentas.elo);
                scanf("%10s", q->cuentas.elo);
                printf(MSJ_SISTEMA"\nElo da conta modificado correctamente a "INFO"%s\n",q->cuentas.elo);
                break;
            case 6:
                printf(MSJ_SISTEMA"\nOperacion cancelada\n"RST);
                
                seguir=false;
                break;
            default:
                printf(ERROR"\nOpcion non valida, introduza algun dos numeros no menu\n"RST);

                break;
        }
    }while(seguir);


    FILE *archivo = fopen("contrasinais.txt", "w");
    if (archivo != NULL) {
        Pos t = *L;
        while (t != NULL) {
            fprintf(archivo, "%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\n",
                    t->cuentas.id_lol,
                    t->cuentas.nickname,
                    t->cuentas.password,
                    t->cuentas.lvl,
                    t->cuentas.elo);
            t = t->next;
        }
        fclose(archivo);
    } else {
        printf(ERROR"Error ao abrir o arquivo para escritura.\n"RST);
    }
}

void listAccount(List *L) {
    Pos q;

    printf(MSJ_SISTEMA"\nEsta e a tua Listaxe de contas\n"
       DECORACION"------------------------------\n"
       AZUL"Id cliente\t\t\tNome Invocador\t\t\tContrasinal\t\t\tNivel\t\t\tElo\n\n");

    for (q = *L; q != NULL; q = q->next) {
        printf(INFO "%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\n\n\n" RST,
               q->cuentas.id_lol,
               q->cuentas.nickname,
               q->cuentas.password,
               q->cuentas.lvl,
               q->cuentas.elo);
    }
}