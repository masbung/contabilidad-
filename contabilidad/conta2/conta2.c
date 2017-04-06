#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>

//contraseña

char password [10], l=' ';
char str [10], m=' ';

int lenght (char *s){
    char *start = s;
    while (*s) s++;
    return s - start;
}

void trim(char *s){
    while (*s) s++; 
    while(*s == ' ' || *s == '\0' || *s == '\n') s--;
    *(s+1) = '\0';
}

int compare(char *s, char*t){
    while (*s != '\0' && *t != '\0' && *s - *t == 0){
        s++;
        t++;
    } return *s - *t;
}

int new_password(){
    int i=0;
    printf("\n Digita una contrasena [maximo 10 letras o numeros]: ");
    while (i<=9){
    password[i]=getch();
    l=password[i];
    if(l==13) break;
    else printf("*");
    i++;
    }
    password[i]='\0';
    i=0;
    FILE *pFile;
    pFile = fopen("password.txt" , "w");
    fprintf (pFile,"%s",password);
    fclose (pFile);
    return 0;
}

int old_password (){

    int i=0;
    printf("Contrasena?");
    while (i<=9){
        str[i]=getch();
        m=str[i];
        if(m==13) break;
        else printf("*");
        i++;
    }
    str[i]='\0';
    i=0;
    trim(str);
    compare (str, password);
    return 0;
}

//contabilidad

struct struct_cuenta {
        int id;
        char account_name [25];
        int balance;
        struct struct_cuenta *next;
        struct struct_cuenta *previous;
    }; typedef struct struct_cuenta CUENTA;

void print (CUENTA *cuenta) {
    printf("%d\t", cuenta->id);
    printf("%s\t", cuenta->account_name);
    printf("(%d)\n", cuenta->balance);
} 

/*void log (CUENTA *current) { // Log funcionando

    FILE *pFile;
    pFile = fopen("logs.txt" , "w");
    while(current != NULL) {
        fprintf(pFile,"%d\t", current->id);
        fprintf(pFile,"%s\t", current->account_name);
        fprintf(pFile,"%d\n", current->balance);
        current = current->next;
    } 
    fclose (pFile);           
}*/

void log2 (CUENTA *current) {

    time_t rawtime;
    struct tm * timeinfo;

    FILE *pFile;
    pFile = fopen("logs.txt" , "w");
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    fprintf (pFile,asctime (timeinfo) );
    //do{
        fprintf(pFile,"Cuenta de retiro: ");
        fprintf(pFile,"%d\t", current->id);
        fprintf(pFile,"%s\t", current->account_name);
        fprintf(pFile,"%d\t", current->balance);
        //fprintf(pFile,"Cantidad del movimiento %d",*pqty);
        current = current->next;
        fprintf(pFile,"Cuenta de deposito: ");
        fprintf(pFile,"%d\t", current->id);
        fprintf(pFile,"%s\t", current->account_name);
        fprintf(pFile,"%d\n", current->balance);
    //}while(1=1)
    fclose (pFile);           
}

void add_account(CUENTA* current) {
    while(current->next != NULL){
        current = current->next;
    }
        printf("Dame el id de la cuenta: ");
        scanf("%d", &current->id );
        printf("Dame el nombre de la cuenta: ");
        scanf("%s", current->account_name);
        printf("Dame el balance de la cuenta: ");
        scanf("%d", &current->balance );
        
        current->next = malloc(sizeof(CUENTA));    
        current->next->next = NULL;
}

void print_all(CUENTA *current) {
    printf("No.\tCuenta\tBalance\n");
    while(current != NULL) {
        print(current);
        current = current->next;
    }
}

void save_all(CUENTA *current) {
    FILE *pFile;
    pFile = fopen("accounts.txt" , "w");
    while(current != NULL) {
        fprintf(pFile,"%d\t", current->id);
        fprintf(pFile,"%s\t", current->account_name);
        fprintf(pFile,"%d\n", current->balance);
        current = current->next;
    } 
    fclose (pFile);           
}

void load_all(CUENTA *current) {

    FILE *pFile;
    pFile = fopen("accounts.txt" , "r");
    do{
        fscanf(pFile,"%d\t%s\t%d\n", &current->id, current->account_name, &current->balance);
        current->next = malloc(sizeof(CUENTA));
        current = current->next;
        current->next = NULL;
    }while(feof(pFile));
    fclose (pFile);
} 
    

void make_move(CUENTA *current){ 
    
    char response[] = "no";
    int source,dest;
    int updated = 0;

    int qty;
    /*int *pqty; //Declare a pointer with *
    pqty = &qty;*/

    printf("Quieres imrpimir todas las cuentas? s/n\n");
    scanf("%s", response);
    if (response[0] == 's'){
    print_all(current);}
    //else{
    printf("Elige el numero de cuenta de retiro: ");
    scanf("%d",&source);
    printf("Elige el numero de cuenta de deposito: ");
    scanf("%d",&dest);
    printf("Elige la cantidad a mover: ");
    scanf("%d",&qty);
    
        do {
            if (current->id == source){
                current->balance = current->balance - qty;
                log2(current); //AQUI IMPRIME LAS DOS CUENTAS ANTES DE MOVIMIENTOS
            }
            if (current->id == dest){
                current->balance = current->balance + qty;
            }
            //log(current); Solo, imprime el resultado unicamente
            updated++;
            current = current->next;
            //log(current); Solo, no
        }while (updated < 3 && current->next !=NULL);
    //}
}
        

int main() {

    CUENTA* head = NULL;
    head = malloc(sizeof(CUENTA));
    head->next = NULL;
    CUENTA* current = NULL;
    current = head;

    char response[] = "no";
    int menu_option;

    char c;

    FILE * fPointer;
    fPointer = fopen ("password.txt","r");
    if (fPointer != NULL){
        do{
            c = fgetc(fPointer);
            if (c != EOF && c != ' ' && c != '\n'){
                fclose(fPointer);
            //pasword_pass-begin HACER MENU
                FILE * fPointer;
                fPointer = fopen ("password.txt", "r");
                while (!feof(fPointer)){
                fgets (password, 10, fPointer);
                }
                old_password ();
                if (compare(str,password) == 0){
                    printf("\nAccesso permitido\n\n");
            
                    do {
                    printf("Que funcion quieres hacer?\n 1. Listar cuentas \n 2. Agregar cuentas \n 3. Realizar un movimiento \n 4. Salir del programa \n 5. Guardar \n 6. Cargar\n");
                    scanf("%d",&menu_option);    
                    switch (menu_option) {
                        case 1:                          
                            print_all(current);            
                            break; 
                        case 2:
                            do {                
                                add_account(current);        
                                printf("Quieres agregar otra (s/n)");
                                scanf("%s", response);
                                if (response[0] == 's') {
                                }
                            } while (response[0] == 's');                   
                            break;
                        case 3:
                            make_move(current);                    
                            break;   
                        case 4:
                            printf("Gracias...\n");
                            getchar();
                            exit(0);        
                            break;
                        case 5: 
                            save_all(current);
                            break;
                        case 6: 
                            load_all(current);
                            break;
                        default:
                            printf("No encontrado");
                    }    
        
                } while (menu_option != 4);
                }

                else
                printf("Accesso denegado\n");
                fclose(fPointer);
                return 0;
                }
            //password_pass-ends 
            else{
            new_password();
            }
        }while(1>2);
    }
}


    