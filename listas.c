/*
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

int crearDirectorio(const char *directorioPadre, const char *nombreDirectorio) {
    // Concatenamos la ruta completa
    char rutaCompleta[MAX_PATH];
    snprintf(rutaCompleta, sizeof(rutaCompleta), "%s\\%s", directorioPadre, nombreDirectorio);

    if (CreateDirectory(rutaCompleta, NULL) != 0) {
        printf(COMPLETADO"\nDirectorio creado exitosamente: "INFO"%s\n"RST, rutaCompleta);
        return 1; // Creado exitosamente
    } else{
        return 0; // Fallo al crearlo
    }
    // CODIGO POR SI SE QUIERE QUE EL USUARIO LE PUEDA DAR NOMBRE A SU DIRECTORIO

    /*else {
        DWORD error = GetLastError();
        if (error == ERROR_ALREADY_EXISTS) {
            printf(ERROR"\nEl directorio ya existe: "INFO"%s\n"RST, rutaCompleta);
        } else {
            perror(ERROR"\nError al crear el directorio\n"RST);
        }
    }
}

int carpetaExiste(const char* directorio, const char* carpetaNombre) {
    DIR* dir = opendir(directorio);

    if (dir) {
        struct dirent* entrada;
        while ((entrada = readdir(dir)) != NULL) {
            if (entrada->d_type == DT_DIR && strcmp(entrada->d_name, carpetaNombre) == 0) {
                closedir(dir);
                return 1; // Carpeta encontrada
            }
        }
        closedir(dir);
    }

    return 0; // Carpeta no encontrada
}

int directorioEstaVacio(const char *ruta) {
    DIR *dir = opendir(ruta);

    if (dir == NULL) {
        perror("Error al abrir el directorio");
        exit(EXIT_FAILURE);
    }

    struct dirent *entrada;

    // Contador para contar el número de entradas en el directorio
    int contador = 0;

    // Lee todas las entradas en el directorio
    while ((entrada = readdir(dir)) != NULL) {
        // Ignora las entradas "." y ".."
        if (strcmp(entrada->d_name, ".") != 0 && strcmp(entrada->d_name, "..") != 0) {
            contador++;
        }
    }

    closedir(dir);

    // Si el contador es 0, el directorio está vacío
    return contador == 0;
}

void obtenerArchivosEnDirectorio(const char *ruta,char nuevoNombre[]) {
    DIR *dir = opendir(ruta);

    if (dir == NULL) {
        perror("Error al abrir el directorio");
        exit(EXIT_FAILURE);
    }

    //printf("Archivos en el directorio '%s':\n", ruta);

    struct dirent *entrada;
    
    // Lee todas las entradas en el directorio
    while ((entrada = readdir(dir)) != NULL) {
        // Ignora las entradas "." y ".."
        if (strcmp(entrada->d_name, ".") != 0 && strcmp(entrada->d_name, "..") != 0) {
            //printf("%s\n", entrada->d_name);
            strcpy(nuevoNombre,entrada->d_name);
        }
    }

    closedir(dir);
}

void addAccount(List *L,char nuevoNombre[]){
    Pos q;
    
    int c;

    char aux[MAX_ID+1];
    char auxLvl[MAX_LVL+1];
    char auxElo[MAX_ELO+1];

    char ruta[256];
    
    char* docuPath = getenv("USERPROFILE");

    if (docuPath == NULL) {
        printf("Non se puido obter a ruta de Usuario\n");
        return;
    }

    sprintf(ruta, "%s\\Database", docuPath); // C:\Users\lucas\Database

    if(directorioEstaVacio(ruta)){
        printf(PETICION"\nIntroduce un nombre para el archivo: "RST);
        scanf("%255s", nuevoNombre); 
        while(getchar() != '\n');
    }else{
        obtenerArchivosEnDirectorio(ruta,nuevoNombre);
    }

    sprintf(ruta, "%s\\Database\\%s", docuPath,nuevoNombre);

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


    printf(VERDE"\n\nConta engadida exitosamente en %s\n"
            DECORACION"------------------------------------------------------------------------\n"
            MSJ_SISTEMA"Id do cliente: " INFO "%s\n"
            MSJ_SISTEMA"Nome de invocador: " INFO "%s\n"
            MSJ_SISTEMA"Contrasinal: " INFO "%s\n"
            MSJ_SISTEMA"Nivel da conta: " INFO "%s\n"
            MSJ_SISTEMA"Elo: " INFO "%s\n"
            DECORACION"------------------------------------------------------------------------\n\n"RST,
            ruta,
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

    FILE *archivo = fopen(ruta, "a");
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

void addAccountsFromFile(List *L,char nuevoNombre[]) {

    char ruta[256];
    char* docuPath = getenv("USERPROFILE");

    if (docuPath == NULL) {
        printf("Non se puido obter a ruta do escritorio.\n");
        return;
    }

    sprintf(ruta,docuPath); 

    crearDirectorio(ruta,"Database");

    sprintf(ruta,"%s\\Database",ruta); 


    if(!directorioEstaVacio(ruta)){ // El directorio no esta vacio
        obtenerArchivosEnDirectorio(ruta,nuevoNombre);

        sprintf(ruta, "%s\\Database\\%s",docuPath,nuevoNombre);

        FILE *archivo = fopen(ruta, "r");
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
           DECORACION"------------------------------\n"
           MSJ_SISTEMA"Id do cliente: "INFO"%s\n"
           MSJ_SISTEMA"Nome de invocador: "INFO"%s\n"
           MSJ_SISTEMA"Contrasinal: "INFO"%s\n"
           MSJ_SISTEMA"Nivel da conta: "INFO"%s\n"
           MSJ_SISTEMA"Elo: "INFO"%s\n"RST
           DECORACION"------------------------------\n",
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
       AZUL"Id cliente\t\tNome Invocador\t\tContrasinal\t\tNivel\t\tElo\n\n");

    for (q = *L; q != NULL; q = q->next) {
        printf(INFO "%-20s\t%-20s\t%-20s\t%-10s\t%-10s\n\n" RST,
               q->cuentas.id_lol,
               q->cuentas.nickname,
               q->cuentas.password,
               q->cuentas.lvl,
               q->cuentas.elo);
    }
}
*/