#include "listas.c"

void manual();

int main() {
    List *L = NULL;
    bool seguir = true;
    int opcion;

    addAccountsFromFile(&L);

    do {
        printf(MSJ_SISTEMA"\nEscolle unha opcion:\n"
               DECORACION"====================\n"
               MENU"1. Engadir conta\n"
               "2. Eliminar conta\n"
               "3. Modificar conta\n"
               "4. Listar contas\n"
               "5. Consultar manuais\n"
               "6. Sair da aplicacion\n"
               DECORACION"====================\n"
               PETICION"Opcion: "RST);

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
                manual();
                break;
            case 6:
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
                printf(ERROR"\nError ao escoller a opcion, volva executar\n"RST);
                break;
        }
    } while (seguir);

    return 0;
}

void manual(){
    bool seguir = true;
    int opcion;

    do {
        printf(MSJ_SISTEMA"\nEscolle o manual dunha funcionalidade:\n"
               DECORACION"======================================\n"
               MENU"1.Engadir conta\n"
               "2.Eliminar conta\n"
               "3.Modificar conta\n"
               "4.Listar contas\n"
               "5.Sair do menu\n"
               DECORACION"======================================\n"
               PETICION"Opcion: "RST);

        scanf("%d", &opcion);

        

        switch (opcion) {
            case 1:
                printf(INFO"\nIntroduce a informacion que desexes en cada campo.\nSe te excedes do"
                        "numero maximo de caracteres que un campo pode soportar,\neste so almacenara caracteres"
                        "ata alcanzar o seu maximo.\nEstos maximos son:\n\n"
                        PETICION"Id cliente "DECORACION"-> "INFO"%d caracteres\n"
                        PETICION"Nome de invocador "DECORACION"-> "INFO"%d caracteres\n"
                        PETICION"Contrasinal "DECORACION"-> "INFO"%d caracteres\n"
                        PETICION"Nivel "DECORACION"-> "INFO"%d caracteres\n"
                        PETICION"Elo "DECORACION"-> "INFO"%d caracteres\n",MAX_ID,MAX_NICK,MAX_PW,MAX_LVL,MAX_ELO);
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
            default:
                printf(ERROR"\nError ao escoller a opcion, volva executar\n"RST);
                break;
        }
    } while (seguir);
}