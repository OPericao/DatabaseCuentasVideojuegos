//#include "listas.c"
#include "listasSinColores.c"

void manual();

int main() {
    List *L = NULL;
    bool seguir = true;
    int opcion;
    char nuevoNombre[256];
    

    addAccountsFromFile(&L, nuevoNombre);

    do {
        printf("\nEscolle unha opcion:\n"
               "====================\n"
               "1. Engadir conta\n"
               "2. Eliminar conta\n"
               "3. Modificar conta\n"
               "4. Listar contas\n"
               "5. Consultar manuais\n"
               "6. Sair da aplicacion\n"
               "====================\n"
               "Opcion: ");

        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                addAccount(&L,nuevoNombre);
                break;
            case 2:
                deleteAccount(&L,nuevoNombre);
                break;
            case 3:
                editAccount(&L,nuevoNombre);
                break;
            case 4:
                listAccount(&L);
                break;
            case 5:
                manual();
                break;
            case 6:
                printf("\nSaindo da aplicacion, ata pronto :)");
                Pos t,q=*L;
                while(q!=NULL){
                    t=q->next;
                    free(q);
                    q=t;
                }
                L=NULL;
                seguir = false;
                break;
            default:
                printf("\nError ao escoller a opcion, volva executar\n");
                break;
        }
    } while (seguir);

    return 0;
}

void manual(){
    bool seguir = true;
    int opcion;

    do {
        printf("\nEscolle o manual dunha funcionalidade:\n"
               "======================================\n"
               "1.Engadir conta\n"
               "2.Eliminar conta\n"
               "3.Modificar conta\n"
               "4.Listar contas\n"
               "5.Sair do menu\n"
               "======================================\n"
               "Opcion: ");

        scanf("%d", &opcion);        

        switch (opcion) {
            case 1:
                printf("\nIntroduce a informacion que desexes en cada campo.\nSe te excedes do"
                        "numero maximo de caracteres que un campo pode soportar,\neste so almacenara caracteres"
                        "ata alcanzar o seu maximo.\nEstos maximos son:\n\n"
                        "Id cliente -> %d caracteres\n"
                        "Nome de invocador -> %d caracteres\n"
                        "Contrasinal -> %d caracteres\n"
                        "Nivel -> %d caracteres\n"
                        "Elo -> %d caracteres\n",MAX_ID,MAX_NICK,MAX_PW,MAX_LVL,MAX_ELO);
                break;
            case 2:
                
                break;
            case 3:
                
                break;
            case 4:
                
                break;
            case 5:
                seguir = false;
                printf("\nSaindo do manual\n");
                break;
            default:
                printf("\nError ao escoller a opcion, volva executar\n");
                break;
        }
    } while (seguir);
}