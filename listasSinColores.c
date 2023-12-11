#include "listas.h"

void inicializarListaVacia(List *L){
    *L=NULL;
}

void createNode(Pos *q){
    *q=malloc(sizeof(struct Nodo));

    if (*q != NULL) {
        (*q)->next = NULL;
    } else {
        printf("Erro: Memoria chea\n");
    }
}

int crearDirectorio(const char *directorioPadre, const char *nombreDirectorio) {
    // Concatenamos la ruta completa
    char rutaCompleta[MAX_PATH];
    snprintf(rutaCompleta, sizeof(rutaCompleta), "%s\\%s", directorioPadre, nombreDirectorio);

    if (CreateDirectory(rutaCompleta, NULL) != 0) {
        printf("\nDirectorio creado exitosamente: ""%s\n", rutaCompleta);
        return 1; // Creado exitosamente
    } else{
        return 0; // Fallo al crearlo
    }
    // CODIGO POR SI SE QUIERE QUE EL USUARIO LE PUEDA DAR NOMBRE A SU DIRECTORIO

    /*else {
        DWORD error = GetLastError();
        if (error == _ALREADY_EXISTS) {
            printf("\nEl directorio ya existe: ""%s\n", rutaCompleta);
        } else {
            perror("\nError al crear el directorio\n");
        }
    }*/
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
        printf("\nIntroduce un nombre para el archivo: ");
        scanf("%255s", nuevoNombre); 
        while(getchar() != '\n');
    }else{
        obtenerArchivosEnDirectorio(ruta,nuevoNombre);
    }

    sprintf(ruta, "%s\\Database\\%s", docuPath,nuevoNombre);

    createNode(&q);

    printf("\nEnche os seguintes campos\n");

    printf("\nId do cliente: ");
    scanf("%20s", aux);
    strcpy(q->cuentas.id_lol, aux);
    memset(aux, 0, sizeof(aux));

    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nNome de invocador: ");
    scanf("%20s", aux);
    strcpy(q->cuentas.nickname, aux);
    memset(aux, 0, sizeof(aux));

    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nContrasinal: ");
    scanf("%20s", aux);
    strcpy(q->cuentas.password, aux);
    memset(aux, 0, sizeof(aux));

    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nNivel: ");
    scanf("%5s", auxLvl);
    strcpy(q->cuentas.lvl, auxLvl);
    memset(aux, 0, sizeof(auxLvl));

    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nElo: ");
    scanf("%10s", auxElo);
    strcpy(q->cuentas.elo, auxElo);
    memset(aux, 0, sizeof(auxElo));

    while ((c = getchar()) != '\n' && c != EOF);


    printf("\n\nConta engadida exitosamente en %s\n"
            "------------------------------------------------------------------------\n"
            "Id do cliente: "  "%s\n"
            "Nome de invocador: "  "%s\n"
            "Contrasinal: "  "%s\n"
            "Nivel da conta: "  "%s\n"
            "Elo: "  "%s\n"
            "------------------------------------------------------------------------\n\n",
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
        printf("Error ao abrir o arquivo para escritura.\n");
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

void deleteAccount(List *L,char nuevoNombre[]) {
    if (*L == NULL) {
        printf("\nNon hai contas para eliminar\n\n");
        return;
    }

    char ruta[256];
    
    char* docuPath = getenv("USERPROFILE");

    if (docuPath == NULL) {
        printf("Non se puido obter a ruta de Usuario\n");
        return;
    }

    sprintf(ruta, "%s\\Database\\%s", docuPath,nuevoNombre);

    char identificador[MAX_ID+1];
    printf("\nIntroduce o valor do campo polo cal desexas eliminar a conta: ");
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
        printf("\nNon se atopou a conta con campo %s\n\n", identificador);
        return;
    }

    if (prev == NULL) {
        *L = q->next;
    } else {
        prev->next = q->next;
    }

    printf("\nConta eliminada exitosamente:\n"
           "------------------------------\n"
           "Id do cliente: ""%s\n"
           "Nome de invocador: ""%s\n"
           "Contrasinal: ""%s\n"
           "Nivel da conta: ""%s\n"
           "Elo: ""%s\n"
           "------------------------------\n",
           q->cuentas.id_lol,
           q->cuentas.nickname,
           q->cuentas.password,
           q->cuentas.lvl,
           q->cuentas.elo);
    
    free(q);

    FILE *archivo = fopen(ruta, "w");
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
        printf("Error ao abrir o arquivo para escritura.\n");
    }
}

void editAccount(List *L,char nuevoNombre[]) {  

    if (*L == NULL) {
        printf("\nNon hai contas para modificar\n\n");
        return;
    }

    int c;
    int opcion;

    bool seguir=true;

    char identificador[MAX_ID+1];
    char aux[MAX_ID+1];
    char auxLvl[MAX_LVL+1];
    char auxElo[MAX_ELO+1];

    char ruta[256];
    
    char* docuPath = getenv("USERPROFILE");

    if (docuPath == NULL) {
        printf("Non se puido obter a ruta de Usuario\n");
        return;
    }

    sprintf(ruta, "%s\\Database\\%s", docuPath,nuevoNombre);

    printf("\nIntroduce o valor do campo polo cal desexas modificar a conta: ");
    scanf("%20s", identificador);

    Pos q = *L;
    Pos prev = NULL;

    while (q != NULL && strcmp(q->cuentas.id_lol, identificador) != 0 &&
           strcmp(q->cuentas.nickname, identificador) != 0) {
        prev = q;
        q = q->next;
    }

    if (q == NULL) {
        printf("\nNon se atopou a conta con campo %s\n\n", identificador);
        return;
    }

    do{
        printf("\nEscolle unha opcion:\n"
            "====================\n"
            "1. Modificar Id do cliente\n"
            "2. Modificar Nome de invocador\n"
            "3. Modificar Contrasinal\n"
            "4. Modificar Nivel da conta\n"
            "5. Modificar Elo\n"
            "6. Cancelar Operacion\n"
            "====================\n"
            "Opcion: ");

        scanf("%d", &opcion);

        switch(opcion){
            case 1:
                printf("\nId do cliente novo (antes %s): ", q->cuentas.id_lol);
               scanf("%20s", aux);
               strcpy(q->cuentas.id_lol, aux);
                memset(aux, 0, sizeof(aux));

                while ((c = getchar()) != '\n' && c != EOF);
            
                printf("\nId do cliente modificado correctamente a ""%s\n",q->cuentas.id_lol);
                break;
            case 2:
                while ((c = getchar()) != '\n' && c != EOF);
               printf("\nNome de invocador novo (antes %s): ", q->cuentas.nickname);
                fgets(q->cuentas.nickname, sizeof(q->cuentas.nickname), stdin);
                q->cuentas.nickname[strcspn(q->cuentas.nickname, "\n")] = '\0';
                printf("\nNome de invocador modificado correctamente a ""%s\n",q->cuentas.nickname);
                break;
            case 3:
                while ((c = getchar()) != '\n' && c != EOF);
                printf("\nContrasinal novo (antes %s): ", q->cuentas.password);
                fgets(q->cuentas.password, sizeof(q->cuentas.password), stdin);
                q->cuentas.password[strcspn(q->cuentas.password, "\n")] = '\0';
                printf("\nContrasinal modificado correctamente a " "%s\n",q->cuentas.password);
                break;
            case 4:
                while ((c = getchar()) != '\n' && c != EOF);
                printf("\nNivel da conta novo (antes %s): ", q->cuentas.lvl);
                scanf("%5s", q->cuentas.lvl);
                printf("\nNivel da conta modificado correctamente a ""%s\n",q->cuentas.lvl);
                break;
            case 5:
                while ((c = getchar()) != '\n' && c != EOF);
                printf("\nElo novo (antes %s): ", q->cuentas.elo);
                scanf("%10s", q->cuentas.elo);
                printf("\nElo da conta modificado correctamente a ""%s\n",q->cuentas.elo);
                break;
            case 6:
                printf("\nOperacion cancelada\n");
                
                seguir=false;
                break;
            default:
                printf("\nOpcion non valida, introduza algun dos numeros no menu\n");

                break;
        }
    }while(seguir);


    FILE *archivo = fopen(ruta, "w");
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
        printf("Error ao abrir o arquivo para escritura.\n");
    }
}

void listAccount(List *L) {
    Pos q;

    printf("\nEsta e a tua Listaxe de contas\n"
       "------------------------------\n"
       "Id cliente\t\tNome Invocador\t\tContrasinal\t\tNivel\t\tElo\n\n");

    for (q = *L; q != NULL; q = q->next) {
        printf( "%-20s\t%-20s\t%-20s\t%-10s\t%-10s\n\n" ,
               q->cuentas.id_lol,
               q->cuentas.nickname,
               q->cuentas.password,
               q->cuentas.lvl,
               q->cuentas.elo);
    }
}
