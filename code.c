#include "header.h"

const char* keyword_token_list[]={"PROGRAM", "CONST", "VAR", "BEGIN", "END", "IF", "THEN", "WHILE", "DO", "READ", "WRITE"};
const char* special_token_list[]={"PV", "PT", "PLUS", "MOINS", "MULT", "DIV", "VIR", "AFF", "INF", "INFEG", "SUP", "SUPEG", "DIFF", "PO", "PF", "EG"};

const char* special_symbols_list[]={";", ".", "+", "-", "*", "/", "," , ":=", "<", "<=",  ">", ">=", "<>", "(", ")", "="};

int lolo = 1;
int lex = 0;
int syn = 0;
int sem = 0;
// functions
// ########################################Lexical####################################################################
void SymboleSuiv(){
	
	memset(token_cour.code, '\0', codeTaille);
    memset(token_cour.nom, '\0', nomTaille);
    //ignore anything that doesn't belong to the tokens lists
    Separateur();
    token_cour.line = lolo;
    if( car_cour == EOF ){
    	strcpy(token_cour.code, "EOF");
    }
    else if ( lire_mot() ){}
    else if ( lire_nombre() ){}
    else if ( lire_car() ) {}
    else{Erreur("Invalid");}
}

char CarSuiv(){
	return car_cour = fgetc(fichier);
}

void Erreur(char *erreur){
	lex = 1;
	int er = lolo;
	er++;
	printf("line %d %s\n", er, erreur);
}

void Separateur(){
	//ignore blank space, newline, tabulation
	while((car_cour == ' ') || (car_cour =='\n') || (car_cour == '\t') || (car_cour == '{')){
		//number of lines
		if( car_cour == '\n'){
			lolo++;
		}
		CarSuiv();
		//ignore comments
		if( car_cour == '{'){
			CarSuiv();
            if(car_cour == '*'){
                while(1){
                	CarSuiv();
                	if(car_cour == '*'){
                		CarSuiv();
                		break;
                	}
                }
            }
            else 
                Erreur("Error in comment, open brace");
            if(car_cour != '}')
                Erreur("Error in comment, close brace");
            CarSuiv();
        }
	}
}

bool lire_mot(){
	if( isalpha(car_cour) == 0)
		return FALSE;
	char mot[MAXCHAR];
	int countM = 0, countL = 0, comp = 0;
	mot[0] = toupper(car_cour);

	do{
		countM++;
	}while(countM<MAXCHAR && (isalnum(mot[countM] = car_cour = toupper(CarSuiv()))|| mot[countM] == '_' ));

	if( countM >= MAXCHAR )
		Erreur("Number of characters exceed");
	mot[countM] = '\0';
	while( (comp = strcmp(mot, keyword_token_list[countL++])) !=0 && countL < NUMKEYWORDTOKEN );
	if( comp == 0){
		strcpy(token_cour.code, keyword_token_list[countL-1]);
		strcpy(token_cour.nom, mot);
	}
	else{
		strcpy(token_cour.code, "ID");
		strcpy(token_cour.nom, mot);
	}
	return TRUE;
}

bool lire_nombre(){
	if (isdigit(car_cour) == 0)
		return FALSE;
	char num[MAXNUM];
	int count = 0;
	num[0] = car_cour;
	do{
		count++;
	}while(count<MAXNUM && isdigit(num[count] = car_cour = CarSuiv()));
	if( count >= MAXNUM)
		Erreur("Number of digits exceed");
	num[count] = '\0';
	strcpy(token_cour.code, "NUM");
	strcpy(token_cour.nom, num);
	car_cour = CarSuiv();
	return TRUE;
}

bool lire_car(){
	int count = 0, comp = 0;
    char spec[3];
    memset(spec,'\0',sizeof(spec));

    spec[0] = car_cour;
    if((spec[1] = car_cour = CarSuiv()) != '=')
        spec[1] =  '\0';
    else
        CarSuiv();
     
    while( (comp = strcmp(spec, special_symbols_list[count++]) != 0) && count < NUMSPECIALTOKEN);

    if(comp != 0)
        return FALSE;

    strcpy(token_cour.code, special_token_list[count-1]); 
    strcpy(token_cour.nom, spec);

    return TRUE;
}
// ########################################Syntaxique####################################################################
//to import token
 chaineToken* importToken(int nligne, char *nom, char *code){
 	char num[MAXNUM];
	int count = 0;
	chaineToken *p=Malloc(chaineToken);
	p->numLigne = nligne;
	strcpy(p->nomToken,nom);
	strcpy(p->codeToken,code);
	if (isdigit(nom[0]) != 0){
		num[0] = car_cour;
		do{
			num[count] = nom[count];
			count++;
		}while(nom[count] != '\0');

		p->ifNum = atoi(num);
	}
	strcpy(token_cour.code, "NUM");
	strcpy(token_cour.nom, num);
	return p;
}
//insert the imported token at the end of the list
listeSequence insererSequence(chaineToken *seq,listeSequence liste){
	noeud *nouveau=Malloc(noeud);
	nouveau->infos=seq;
	noeud *p;
	if(!liste){
		liste=nouveau;
		nouveau->suivant=NULL;
		return liste;
	}
	p=liste;
	while(p->suivant){
		p=p->suivant;
	}
	p->suivant=nouveau;
	nouveau->suivant=NULL;
	return liste;
}

int ch = 0;
static char *current;
void afficherSequences(listeSequence liste){
	int stop = 0;
	listeSequence li;
	li = liste;
	while(li != NULL){
		printf("%d\t%s\t : %s  %d\n",li->infos->numLigne,li->infos->nomToken,li->infos->codeToken, li->infos->ifNum);
		li=li->suivant;
	}
	return;
}
int pp = 0;

bool verifyToken(char *code){
	if(strcmp(L->infos->codeToken, code) == 0){
		L=L->suivant;
		return TRUE;
	}
	return FALSE;
}

void SyntaxError(char *err){
	syn = 1;
    printf("line : %d Syntax Error : %s\n",L->infos->numLigne, err);
}

void Program(){
    verifyToken("PROGRAM");
    if(!verifyToken("ID"))
    	SyntaxError("ID_PROGRAM");
    if(!verifyToken("PV"))
    	SyntaxError("A ';' is forgotten");
    Block();
    verifyToken("PT");

}

void Block(){
	if (verifyToken("CONST"))
	{
		Consts();
	}
	else if (verifyToken("VAR"))
	{
		Vars();
	}
	else
		Insts();
	
}

void Consts(){
    verifyToken("ID");
    do{
        if(!verifyToken("EG"))
        	SyntaxError("A '=' is forgotten ");
        if(!verifyToken("NUM"))
        	SyntaxError("A number is forgotten  ");
        if(!verifyToken("PV"))
        	SyntaxError("A ';' is forgotten  ");
    }while(verifyToken("ID"));
    Block();
}

void Vars(){
    do{
        if(!verifyToken("ID"))
        	SyntaxError("Variable");
    }while(verifyToken("VIR"));
    if(!verifyToken("PV"))
    	SyntaxError("A ';' is forgotten ");
    Block();
}

void Insts(){
    verifyToken("BEGIN");

    while (Inst())  
        if(!verifyToken("PV"))
        	SyntaxError(" A ';' is forgotten ");

    if(!verifyToken("END"))
    	SyntaxError("END");
}

bool Inst(){
	if (verifyToken("BEGIN"))
	{
		Insts();
		return TRUE;
	}
	else if (verifyToken("ID"))
	{
		Affec();
		return TRUE;
	}
	else if (verifyToken("IF"))
	{
		Si();
		return TRUE;
	}else if (verifyToken("WHILE"))
	{
		Tantque();
		return TRUE;
	}else if (verifyToken("WRITE"))
	{
		Ecrire();
		return TRUE;
	}else if (verifyToken("READ"))
	{
		Lire();
		return TRUE;
	}
	else{
		return FALSE;
	}

}

void Affec(){
    if(!verifyToken("AFF"))
    	SyntaxError("Affectation.");
    Expr();
}

void Si(){
    Cond();
    if(!verifyToken("THEN"))
    	SyntaxError("THEN");
    Inst();
}

void Tantque(){
    Cond();
    if(!verifyToken("DO")){
    	SyntaxError("DO");
    	return;
    }
    Inst();
}

void Ecrire(){
    if(!verifyToken("PO"))
    	SyntaxError("An open brace is forgotten ");
    
    while(!verifyToken("PF")){
        Expr();
        verifyToken("VIR");
    }
}

void Lire(){
	int tt = 0;
    if(!verifyToken("PO"))
    	SyntaxError("An open brace is forgotten ");
    while(!verifyToken("PF")){
    	if(tt == 1){
    		SyntaxError("A close brace is forgotten ");
        	break;
    	}
        verifyToken("ID");
        if((!verifyToken("VIR"))){
        	tt = 1;
        	
        }
    }
}

void Cond(){
    Expr();
    if (verifyToken("EG"))
	{
	}
	else if (verifyToken("PLUS"))
	{
	}
	else if (verifyToken("MOINS"))
	{
	}else if (verifyToken("MULT"))
	{
	}else if (verifyToken("DIV"))
	{
	}else if (verifyToken("INF"))
	{
	}
	else if (verifyToken("INFEG"))
	{
	}else if (verifyToken("SUP"))
	{
	}else if (verifyToken("SUPEG"))
	{
	}
	else{
		if(pp==1)
			return;
	}

    Expr();
}

bool Expr(){
    Term();
    while(1){
    	if(!AddOp()){
    		return FALSE;
    		break;
    	}

    	Term();
    }
    return TRUE;       
}

bool AddOp(){
	if (verifyToken("PLUS")){
		return TRUE;
	}
	else if (verifyToken("MOINS"))
	{
		return TRUE;
	}
	else{
		//SyntaxError(3);
		return FALSE;
	}
}

void Term(){
	Fact();
	while(1){
    	if(!MulOp()){
    		break;
    	}
    	Fact();
    }        
}

bool MulOp(){
	if (verifyToken("MULT"))
	{
		return TRUE;
	}
	else if (verifyToken("DIV"))
	{
		return TRUE;
	}
	else{
		//SyntaxError(4);
		return FALSE;
	}
}

void Fact(){
	pp=0;
	if(verifyToken("ID")){
	}
	else if (verifyToken("NUM"))
	{
	}
	else if (verifyToken("PO"))
	{
		Expr();
		if(!verifyToken("PF"))
			SyntaxError("A close brace is forgotten ");
	}
	else{
		pp=1;
		SyntaxError("FACT");
	}
}
// ########################################Semantique####################################################################
void programS(listeSequence list){
	declarer(list);  
    doubleDeclar(list);
    constChange(list);
    if((lex == 0) && (syn == 0) && (sem == 0)){
    	printf("\033[0;35m");
    	printf("\nCongratulations, successful compilation.\n");
    	printf("\033[0;35m");
    }
}
void declarer(listeSequence liste){
	int ccheck = 0;
	listeSequence li, lis;
	li=liste;
	lis=liste;
	while(strcmp(li->infos->nomToken, "BEGIN") != 0){
		li=li->suivant;
	}
	while(li!=NULL){
		if(strcmp(li->infos->codeToken, "ID") == 0){
			while(strcmp(lis->infos->nomToken, "BEGIN") != 0){
				if(strcmp(li->infos->nomToken, lis->infos->nomToken) == 0){
					ccheck = 1;
					break;
				}
				lis=lis->suivant;
			}
			if(ccheck == 0)
				erreurDeclar(li->infos->numLigne, li->infos->nomToken);
		}
		lis = liste;
		ccheck = 0;
		li=li->suivant;
	}
	return;
}

void doubleDeclar(listeSequence liste){
	int count = 0;
	listeSequence li1, li2;
	li1 = liste;
	li2 = liste;
	li1 = li1->suivant;
	for(int k =0; k<2; k++)
		li2=li2->suivant;
	while(strcmp(li2->infos->nomToken, "END") != 0){
		if(strcmp(li1->infos->nomToken, li2->infos->nomToken) == 0){
			sem = 1;
			printf("line: %d SEMANTIC ERROR: %s is the name of the program, can't be used.\n",li2->infos->numLigne, li2->infos->nomToken );
			break;
		}
		li2=li2->suivant;
	}
	li1 = liste;
	li2 = liste;
	while(strcmp(li2->infos->nomToken, "BEGIN") != 0){
		if(strcmp(li2->infos->codeToken, "ID") == 0){
			while(strcmp(li1->infos->nomToken, "BEGIN") != 0){
				if(strcmp(li1->infos->nomToken, li2->infos->nomToken) == 0){
					count++;
				}
				li1=li1->suivant;
			}
			if(count>1){
				erreurDoubleDeclar(li2->infos->numLigne, li2->infos->nomToken);
			}
			li1 = liste;
			count = 0;
		}
		li2=li2->suivant;
	}
}

void constChange(listeSequence liste){
	listeSequence li1, li2;
	li1 = liste;
	li2 = liste;
	int sortir = 0, pf = 0;
	while(strcmp(li1->infos->nomToken, "BEGIN") != 0)
		li1=li1->suivant;
	while(strcmp(li2->infos->nomToken, "BEGIN") != 0){
		if(strcmp(li2->infos->nomToken, "CONST") == 0){
			li2 = li2->suivant;
			while(strcmp(li2->infos->codeToken, "PV") != 0){
				while(strcmp(li1->infos->codeToken, "END")!=0){
					if ((strcmp(li1->infos->nomToken, li2->infos->nomToken) == 0) && (strcmp(li1->infos->codeToken, "ID") == 0))
					{
						li1 = li1->suivant;
						if(strcmp(li1->infos->nomToken, ":=") == 0 ){
							sem = 1;
							printf("line : %d SEMANTIC ERROR: %s is a constant, can't be changed\n",li1->infos->numLigne ,li2->infos->nomToken);
						}
						else if(strcmp(li1->infos->nomToken, "=") == 0 ){
							sem = 1;
							printf("line : %d SEMANTIC ERROR: %s is a constant, can't be changed\n",li1->infos->numLigne ,li2->infos->nomToken);
						}
					}
					else if (strcmp(li1->infos->codeToken, "READ") == 0)
					{
						li1 = li1->suivant;
						if (strcmp(li1->infos->codeToken, "PO") == 0)
						{
							while(strcmp(li1->infos->codeToken, "PF") != 0){
								if(strcmp(li1->infos->codeToken, "ID") != 0){
									li1 = li1->suivant;
									if(strcmp(li1->infos->codeToken, "PF") == 0){
										pf = 1;
										break;
									}
								}
								if(strcmp(li1->infos->codeToken, "ID") == 0)
									pf = 0;
								if ((strcmp(li1->infos->nomToken, li2->infos->nomToken) == 0) && (strcmp(li1->infos->codeToken, "ID") == 0))
								{
									sem = 1;
									printf("line : %d SEMANTIC ERROR: %s is a constant, can't be changed\n", li1->infos->numLigne, li1->infos->nomToken);
									sortir = 1;
									break;
								}
								li1 = li1->suivant;
							}
						}
					}
					li1 = li1->suivant;
				}
				if(sortir == 1)
					break;
				li1 = liste;
				while(strcmp(li1->infos->nomToken, "BEGIN") != 0){
					li1=li1->suivant;
				}
				li2 = li2->suivant;
			}
		}
		li2 = li2->suivant;
	}
}

void erreurDeclar(int ll, char *varr){
	sem = 1;
	printf("line %d SEMANTIC ERROR: %s not declared\n",ll, varr );
}

void erreurDoubleDeclar(int l, char *varr){
	sem = 1;
	printf("line %d SEMANTIC ERROR: %s is already declared \n", l, varr);
}
// ############################################################################################################