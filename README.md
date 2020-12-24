# Mini-compiler-pascal
c'est un mini compilateur du langage pascal avec le langage C. 
Il est divisé en 3 parties
Partie 1, Analyseur lexical:
  Dans cette partie, on essaie d'éliminer les espaces, les sauts de ligne, les tabulations et les commentaires. Et le reste du code, on le stocke dans une liste chainée qui contient le numéro de la ligne, la nom du symbole, le code du symbole et s'il existe un numéro, on le stocke comme numéro et ne pas une chaine de caractère. De plus, dans cette partie, on vérifie si les commentaires existent vraiemnt entre { * * } et si les numéros et les chaines de caractères de dépassent pas une taille précise.
Partie 2, analyseur syntaxique:
  Dans cette partie, on doit vérifier si le code suit vraiment la grammaire du langage pascal:
PROGRAM     ::= program ID ; BLOCK .
BLOCK       ::= CONSTS VARS INSTS
CONSTS      ::= const ID = NUM ; { ID = NUM ; } | e
VARS        ::= var ID { , ID } ; | e
INSTS       ::= begin INST { ; INST } end
INST        ::= INSTS | AFFEC | SI | TANTQUE | ECRIRE | LIRE | e
AFFEC       ::= ID := EXPR
SI          ::= if COND then INST
TANTQUE     ::= while COND do INST
ECRIRE      ::= write ( EXPR { , EXPR } )
LIRE        ::= read ( ID { , ID } )
COND        ::= EXPR RELOP EXPR
RELOP       ::= = | <> | < | > | <= | >=
EXPR        ::= TERM { ADDOP TERM }
ADDOP       ::= + | -
TERM        ::= FACT { MULOP FACT }
MULOP       ::= * | /
FACT        ::= ID | NUM | ( EXPR )
ID          ::= lettre {lettre | chiffre}
NUM         ::= chiffre {chiffre}
Chiffre     ::= 0|..|9
Lettre      ::= a|b|..|z|A|..|Z
Donc, on vérifie et si on trouve une erreur on l'affiche avec le numéro de ligne et on termine notre vérification. à la fin, toutes les erreurs seront affichées.
Partie 3, analyseur sémantique:
  Dans cette partie, on vérifie des régles, dans notre cas, on a vérifié les régles suivantes:
1. Toutes les déclarations dans CONSTS et VARS2.
2. PAS DE DOUBLE DECLARATIONS. 
3. Apres BEGIN, tous les symboles doivent être déjà déclarés.
4. Une constante ne peut changer de valeur dans le programme.
5. Le ID du programme ne peut être utilisé dans le programme
Dans les parties 2 et 3, on a travaillé avec la liste chainée qu'on a remplie dans la première partie. 
