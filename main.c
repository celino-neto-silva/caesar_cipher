#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void clean_screen() {
    printf("\033[2J\033[H");
}
//1º Habilitado a leitura de um numero indeterminado de caracteress
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream) {
    if (lineptr == NULL || n == NULL || stream == NULL) return -1;

    size_t pos = 0;
    int c;

    if (*lineptr == NULL) {
        *n = 128;                    
        *lineptr = malloc(*n);
        if (*lineptr == NULL) return -1;
    }

    while ((c = fgetc(stream)) != EOF) {
        if (pos + 1 >= *n) {         
            size_t new_size = *n * 2;
            char *new_ptr = realloc(*lineptr, new_size);
            if (!new_ptr) return -1;
            *n = new_size;
            *lineptr = new_ptr;
        }

        (*lineptr)[pos++] = (char)c;

        if (c == '\n') break;         
    }

    if (pos == 0 && c == EOF) return -1;

    (*lineptr)[pos] = '\0';
    return (ssize_t)pos;
}

char get_option(){
    char* line = NULL;
    size_t size = 0;

    ssize_t len = my_getline(&line, &size, stdin);

    if (len != 2)
    {
        return '0';
    }
    else{
        return line[0];
    }
}

void menu(){
    printf("---------------------------\n");
    printf("[1] - Ler manual\n");
    printf("[2] - Play\n");
    printf("[3] - Exit\n");
    printf("---------------------------\n");
}

void english_manual(){
    printf("-------- WELCOME THE CAESAR's KEY --------\n");
    printf("Now will explain you how to use the application!\n");
    printf("1 - In the main menu choose the option play\n");
    printf("2 - Insert a numeric key between 1 and 9\n");
    printf("3 - Insert a text than you want make encryptied\n");
    printf("4 - You will see the result of the test\n");
}

void portuguese_manual(){
    printf("-------- BEM-VINDO A CHAVE DE CESAR --------\n");
    printf("Agora vou explicar como usar o aplicativo!\n");
    printf("1 - No menu principal escolha a opcao play!\n");
    printf("2 - Insira uma chave numerica entre 1 e 9\n");
    printf("3 - Insira o texto que queres encriptar\n");
    printf("4 - Veja o resultado do teste\n");
}

void languages(){
    printf("----------------------\n");
    printf("1 - Portuguese\n");
    printf("2 - English\n");
}

int question_language(){
    char option;
    while(1){
        languages();

        printf("->Choose your option: ");
        option = get_option();

        switch(option){
            case '1':
                clean_screen();
                return 0;
            case '2':
                clean_screen();
                return 1;
            default:
                clean_screen();
        }
    }
}

void manual_reading(){
    char option;
    int flag = 1;
    int lang = question_language();
    
    while(flag == 1){
        if(lang == 1){
            english_manual();
        }
        else{
            portuguese_manual();
        }
        
        printf("->De volta ao menu? (y / N): \n");
        option = get_option();
        
        switch(option){
            case 'y':
                clean_screen();
                flag = 0;
            case 'N':
                clean_screen();
            default:
                clean_screen();
        }
    }
}

int get_key(){
    char key_char;
    char option;

    while (1)
    {
        printf("->Insira uma chave para criptografia entre (1 e 9): \n");
        key_char = get_option();
        
        if (key_char > 48 && key_char < 58)
        {
            return key_char - '0';
        }
        else
        {
            printf("->Continuar? (y / N): \n");
            option = get_option();
            
            switch(option){
                case 'y':
                    clean_screen();
                    break;
                case 'N':
                    clean_screen();
                    return 0;
                default:
                    clean_screen();
            }
        }
    }   
}

void get_text(int key){
    int flag = 0;
    while(flag == 0)
    {    
        char *line = NULL;
        size_t size = 0;

        printf("Escreva sua mensagem para criptografar: ");

        ssize_t len = my_getline(&line, &size, stdin);

        if (len != -1) {
            printf("O que foi escrito: %s", line);
            clean_screen();
            ciphering(line, key);
            flag = 1;
        }

        free(line);
    }
}

void caesar_workflow(){
    int key = 0;
    key = get_key();
       
    if(key > 0){
        get_text(key);
    }
    else{
        clean_screen();
    }
}

void ciphering(char *line, int key){
    char option;
    int flag = 1;
    int size_text = strlen(line);
    char cipher_text[size_text];

    for(int i = 0; i < size_text; i++){
        if(line[i] + key > 255){
            cipher_text[i] = (33 + key)-1;
        }
        else{
            cipher_text[i] = line[i] + key;
        }
    }
    
    cipher_text[size_text] = '\0';

    printf("->Chave inserida: %d\n", key);
    printf("->Texto inserido: %s\n", line);
    printf("->Texto cifrado: %s\n", cipher_text);

    while(flag == 1){
        printf("->Continuar? (y / N): \n");
        option = get_option();

        switch(option){
            case 'y':
                clean_screen();
                caesar_workflow();
            case 'N':
                clean_screen();
                flag = 0;
            default:
                clean_screen();                
        }     
    }
}

//49 - 57 = 1 a 9

int main(void) {
    char option;

    while(1){
        menu();
        printf("\n->Escolha uma opcao: \n");
        option = get_option();

        switch(option){
            case '1':
                clean_screen();
                manual_reading();
                break;
            case '2':
                clean_screen();
                caesar_workflow();
                break;
            case '3':
                clean_screen();
                printf("See you soon!\n");
                exit(0);
            default:
                clean_screen();    
                printf("Try Again!\n");
        }
    }    
    return 0;
}