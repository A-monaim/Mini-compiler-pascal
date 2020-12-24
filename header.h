#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>
#include <ctype.h>

#define Malloc(type) (type*)malloc(sizeof(type))

#define TRUE    1
#define FALSE   0

#define NUMKEYWORDTOKEN 11
#define NUMSPECIALTOKEN 16

typedef enum 
{
	PROGRAM, CONST, VAR, BEGIN, END, IF, THEN, WHILE, DO, READ, WRITE
} keyword_token;
typedef enum 
{
	PV, PT, PLUS, MOINS, MULT, DIV, VIR, AFF, INF, INFEG, SUP, SUPEG, DIFF, PO, PF, EG
} special_token;


FILE* fichier ;

#define codeTaille    20
#define nomTaille     20


typedef struct{
	int line;
    char code[codeTaille];
    char nom[nomTaille];
} Token;
//Structure to store tokens
typedef struct {
	int numLigne;
	char nomToken[nomTaille]; 
	char codeToken[codeTaille]; 
	int ifNum;
}chaineToken;

typedef struct _noeud {
	chaineToken *infos;
	struct _noeud *suivant;
}noeud;

typedef noeud *listeSequence;

listeSequence L;


#define MAXNUM 	 11
#define MAXCHAR  20

char car_cour;
Token token_cour;

// Fonctions
// ############################################Lexical################################################################
extern void SymboleSuiv();
extern char CarSuiv();
extern void Erreur();
extern void Separateur();
extern bool lire_mot();
extern bool lire_nombre();
extern bool lire_car();
// ############################################Syntaxique################################################################
extern chaineToken* importToken(int nligne, char *nom, char *code);
extern listeSequence insererSequence(chaineToken *seq,listeSequence liste);
extern void afficherSequences(listeSequence list);
bool verifyToken(char *code);
void Program();
void Block();
void Consts();
void Vars();
void Insts();
bool Inst();
void Affec();
void Si();
void Tantque();
void Ecrire();
void Lire();
void Cond();
void Relop();
bool Expr();
bool AddOp();
void Term();
bool MulOp();
void Fact();
void ID();
void Num();
void Chiffre();
void Lettre();
// ############################################Semantique################################################################
void programS(listeSequence list);
void declarer(listeSequence liste);
void erreurDeclar(int ll, char *varr);
void doubleDeclar(listeSequence liste);
void erreurDoubleDeclar(int l, char *varr);
void constChange(listeSequence liste);
// ############################################################################################################

#endif