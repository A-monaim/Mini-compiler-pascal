#include "header.h"


int main(){
	int x =0;
    listeSequence list;
    list = NULL;
    fichier = fopen("fich1.pascal", "r");
    CarSuiv();
    SymboleSuiv();
    do{
        L=insererSequence(importToken(token_cour.line, token_cour.nom,token_cour.code),L);
        SymboleSuiv();
    }while(strcmp(token_cour.code,"EOF"));
    list = L;
    printf("\033[0;31m");
    printf("\n#############Test Syntaxique#############\n");
    printf("\033[0;31m");
    Program();
    printf("\033[0;33m");
    printf("\n#############Test Sémantique#############\n");
    printf("\033[0;33m");
    programS(list);
    return 1;
} 