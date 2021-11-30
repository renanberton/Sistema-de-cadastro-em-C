#pragma once
#ifndef funcUtils
#define funcUtils

char *concat(char *text, char *text2);
int isChar(char *c);
void loguin();
int isDigit(char *c);
int calcIdade(char dataNasc[8], int anoAtual);
int isValidEmail(char *email);
void grupoDeRisco(char *cep, char ano_nasc[8], int comorbidade);
void login();
void menu();
void cadastro();
void excluir();
void alterar();
void consulta();
int checkFileExist(char *filename, char *folder);
int checkFolderExist(char *dirname);
void createFile(char *filename, char *content, char *type, char *folder);
void *incTextInFile(char *filename, char *text, char *folder);
char *readFile(char *file, char *folder);

#endif // funcUtils
