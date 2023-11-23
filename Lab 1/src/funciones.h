//#ifndef __funciones_h__
//#define __funciones_h__


typedef enum code {OK,ERR_FILE_NOT_FOUND,ERR_FILE_NOT_PERM,IMPOSSIBLE_VALID_BOARD} code;





//Declaraciones de nuevas estructuras
typedef struct{
	
	char letrasCandy;
	int dureza;
	char poder;
} Candy;

typedef struct {
	
	int alto;
	int ancho;
	int dificultad;
	Candy **Matriz;	
	
} Board;

typedef struct {
	
	Board *tablero;
	
} Game;

typedef struct {
	
	//Dif
	//dif facil=3 tipos de dulces 		//Durezas= 3
	//dif medio =4 Tipos de dulces 		//Durezas=4
	//dif dificil =5 Tipos de dulces 	//Durezas=5
	int dificultad;
	int cantidadDulces;
	int cantidad0; 
	int cantidad1;
	int cantidad2;
	
	
} Params;

typedef struct Position{
	int posX;
	int posY;
	int ultimo; 
} Position;




//Declaracion de funciones
Board *createBoard(int N,int M,Params params,code *statusCode );
Position *checkCandies(Board *b,code *statusCode);
int checkDulces(Board *tablero);
int checkBoard(Board *b,code *statusCode);
int verificarFila(Board *tablero);
int verificarColumna(Board *tablero);
void fixFila(Board *tablero);
void fixColumna(Board *tablero);
void fixTablero(Board *tablero,code *statusCode);
void destruirTablero(Board *tablero);
void saveBoard(Board *b, int *id,code *statusCode);
Board *loadBoard(int id, code *statusCode);
void print(Board *b,code *statusCode);
int romperDurezas(Board *tablero,Position *pos, int ptj);
void actualizarTablero(Board *tablero,code *statusCode);
int contarDurezas(Board *tablero);
int play(Board *b,Position pOri,Position pDes, int *turnos,code *statusCode);
void displayMenu ();









//#endif
