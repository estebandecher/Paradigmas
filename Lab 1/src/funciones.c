#include <funciones.h>
//Importacion de librerias
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char TiposCandys[32]={'A','B','C','D','E'};

//Fucion que crea el tablero de dulces 
Board *createBoard(int N,int M,Params params,code *statusCode ){
	
	
	
	//Pedir memoria para un tablero 				
	Board *tablero = (Board*)malloc(sizeof(Board));
	tablero->alto=M;
	tablero->ancho=N;
	//printf("El alto es: %d\n",tablero->alto );
	//printf("El ancho es: %d \n",tablero->ancho );

	Candy **Matriz=(Candy **)malloc(M*sizeof(Candy*));
	//Verificar si se logro asignar memoria a la matriz 	
	if (Matriz == NULL){
		
		printf("\nNo hay memoria\n");
		return NULL;
	}
	
	
	int i;
	int j;
	
	for(i=0;i<M;i++){
		
		Matriz[i]=(Candy*)malloc(N*sizeof(Candy));

		if (Matriz[i] == NULL){
		
			printf("\nNo hay memoria\n");
		}
		
	}



	//se asigna la matriz creada a tablero	
	tablero->Matriz=Matriz;
	//se asigna la dificultad al tablero
	tablero->dificultad=params.dificultad;



	//Se Agregan los duces segun dificultad
	for(i=0;i<M;i++){
		
		for (j=0;j<N;j++){
			//rand() Dif 
			int r =rand() %  params.dificultad;
			tablero->Matriz[i][j].letrasCandy=TiposCandys[r];
			tablero->Matriz[i][j].dureza=0;
			tablero->Matriz[i][j].poder='.';
			
		}
		
	}
	//Se agregan las durezas
	i=0;
	int ranX,ranY;
	while (i<tablero->dificultad){
		ranX=rand() %  tablero->ancho;
		ranY=rand() %  tablero->alto;
		tablero->Matriz[ranY][ranX].dureza=tablero->dificultad-2;
		tablero->Matriz[ranY][ranX].letrasCandy='X';
		i++;
	}
	//Se agregan poderes especiales	
	i=0;
	int ranP;
	while (i<tablero->dificultad){
		ranX=rand() %  tablero->ancho;
		ranY=rand() %  tablero->alto;
		ranP=rand() %  2;
		if (ranP==0){
			tablero->Matriz[ranY][ranX].poder='!';
		}
		else if (ranP==1){
			tablero->Matriz[ranY][ranX].poder='~';
		}
		i++;
	}



	
	fixTablero(tablero,statusCode);
	return tablero;	
}




//Funcion que rotorna un arreglo de posiciones de un grupo de 3 o mas dulces 
Position *checkCandies(Board *b,code *statusCode){
	
	
	Position *pos=(Position*)malloc(sizeof(Position));

	char letra;
	char nuevaLetra;
	int i,j;
	letra='Z';
	int trio=1;
	
	int r;
	int N,M;
	M=b->alto;
	N=b->ancho;
	//printf("\nEl alto es: %d ",tablero->alto);
	//printf("\nEl ancho es: %d ",tablero->ancho);
	//contador de pos
	int p;
	
	
	
	//Buscando en Fila
	for(i=0;i<M;i++){
		
		for (j=0;j<N;j++){
		
	
			if (b->Matriz[i][j].letrasCandy == letra){
				pos[p].posX=j;
				pos[p].posY=i;
				p=p+1;
				trio=trio+1;		
			}
			else if (b->Matriz[i][j].letrasCandy != letra){
				//Si ya son tres o + dulces => se retorna el arreglo de posiciones
				if (trio >= 3){
					pos[p-1].ultimo=1;
					return pos;
				}
				
				trio=1;
				p=0;
				pos[p].posX=j;
				pos[p].posY=i;
				letra=b->Matriz[i][j].letrasCandy;
				p=p+1;
				
			}
			//si son mas de 3 ducles y ya se llego al final de la Fila
			if (trio >=3 && j == N-1){
				pos[p-1].ultimo=1;
				return pos;
			}
			

		}//for j
		//se para a buscar en la siguiente fila
		trio=1;
		letra='N';
		p=0;
		
		
	}//for i
	


	trio=1;
	p=0;
	letra='N';
	//Buscando en Columna
	for(i=0;i<N;i++){
		
		for (j=0;j<M;j++){
			 
	
			if (b->Matriz[j][i].letrasCandy == letra){
				pos[p].posX=i;
				pos[p].posY=j;
				p=p+1;
				trio=trio+1;		
			}
			else if (b->Matriz[j][i].letrasCandy != letra){
				//Si ya son tres o + dulces => se retorna el arreglo de posiciones
				if (trio >= 3){
					pos[p-1].ultimo=1;
					return pos;	
				}
				
				trio=1;
				p=0;
				pos[p].posX=i;
				pos[p].posY=j;
				letra=b->Matriz[j][i].letrasCandy;
				p=p+1;
				
			}
			//si son mas de 3 ducles y ya se llego al final de la Columna 
			if (trio >= 3 && j == M-1){
				pos[p-1].ultimo=1;
				return pos;
			}
			

		}//for j
		//se para a buscar en la siguiente columna
		trio=1;
		letra='N';
		p=0;
		
	}//for i
	
	
	
	return NULL;
}

	


//Verifiar si existen dulces que no esten dentro de la dificultad /retorna un 1 en caso que NO haya dulces no adecuados 
int checkDulces(Board *tablero){
	
	int i,j;
	char dulceTipo;
	int d;
	
	int N,M;
	M=tablero->alto;
	N=tablero->ancho;
	
	for (i=0;i<M;i++){
		
		for (j=0;j<N;j++){
			
			d=(tablero->dificultad);
			while (d < 5){
				
				if (tablero->Matriz[i][j].letrasCandy == TiposCandys[d]){
					return 0;
				}
				
				d++;	
			}
				
		}//for fuera
		
		
	}//for fuera
	
	return 1;
}




//Funcion que retorna un 1 si el tablero ingresado es valido 
int checkBoard(Board *b,code *statusCode){
	
	//Ver si hay dulces invalidos tiposDulce[tablero->dificultad] 

	//Ver si hay X dureza menor a 1

	//Ver si hay 


	//Se verifica si hay un grupo de al menos 3 dulces iguales
	if (verificarFila(b) == 0){
		return 0;
	}
	else if (verificarColumna(b) == 0){
		return 0;
	}
		
		

	return 1;
}





//funcion que retorne un 0 en caso que se encuentre un grupo con mas de 3 dulces iguales en alguna Fila
int verificarFila(Board *tablero){
	
	char letra;
	char nuevaLetra;
	int i,j;
	letra='Z';
	int trio=1;
	
	int r;
	int N,M;

	M=tablero->alto;
	N=tablero->ancho;
	
	for(i=0;i<M;i++){
		
		
		
		for (j=0;j<N;j++){
	
			
			if (tablero->Matriz[i][j].letrasCandy == letra){
				trio=trio+1;		
			}
			else if (tablero->Matriz[i][j].letrasCandy != letra){
				trio=1;
				letra=tablero->Matriz[i][j].letrasCandy;
				
			}
			
			//si se encontraron 3 trios, se debe cambiar esta ultima letra 	
			if (trio==3){	
				//
				return 0;
			
			}
			

		}//for j
		//se para a buscar en la siguiente fila
		letra=='N';
		trio=1;

		
		
	}//for i
	
	
	return 1;
}





//funcion que retorne un 0 en caso que se encuentre un grupo con mas de 3 dulces iguales en alguna Columna
int verificarColumna(Board *tablero){
	
	char letra;
	char nuevaLetra;
	int i,j;
	letra='N';
	int trio=1;
	
	int r;

	int N,M;
	M=tablero->alto;
	N=tablero->ancho;
		
	for(i=0;i<N;i++){
		
		for (j=0;j<M;j++){
	
			
			if (tablero->Matriz[j][i].letrasCandy == letra){
				trio=trio+1;		
			}
			else if (tablero->Matriz[j][i].letrasCandy != letra){
				trio=1;
				letra=tablero->Matriz[j][i].letrasCandy;
				
			}
			
			//si se encontraron 3 trios, se debe cambiar esta ultima letra 	
			if (trio==3){
				
				//se debe cabiar el %n, ya que depende de la dificultad
				return 0;
			}
			

		}//for j
		//se para a buscar en la siguiente columna
		trio=1;
		
		
	}//for i
	return 1;
	
}




//funcion que arregla el tablero en caso de encontrar mas de 3 dulces iguales en alguna fila
void fixFila(Board *tablero){
	
	char letra;
	char nuevaLetra;
	int i,j;
	letra='Z';
	int trio=1;
	
	int r;
	int N,M;
	M=tablero->alto;
	N=tablero->ancho;
	
	
	
	
	for(i=0;i<M;i++){
		
		
		
		for (j=0;j<N;j++){
	
			//printf("\nEn tablero: %c -> Con a Buscar %c",tablero->Matriz[i][j].letrasCandy ,letra);
			if (tablero->Matriz[i][j].letrasCandy == letra){
				//printf("Igual");
				trio=trio+1;		
			}
			else if (tablero->Matriz[i][j].letrasCandy != letra){
				trio=1;
				letra=tablero->Matriz[i][j].letrasCandy;
				
			}
			
			//si se encontraron 3 trios, se debe cambiar esta ultima letra 	
			if (trio==3){
				//printf("Entra");
				//se debe cabiar el %n, ya que depende de la dificultad
				r= rand()%tablero->dificultad; 
				nuevaLetra=TiposCandys[r];
				while (nuevaLetra == letra){
					r=rand()%3; 
					nuevaLetra=TiposCandys[r];
				}
				
				tablero->Matriz[i][j].letrasCandy=nuevaLetra;
				letra=nuevaLetra;
				trio=1;
			}
			

		}//for j
		//se para a buscar en la siguiente fila
		trio=1;
		
		
	}//for i
}





//funcion que arregla el tablero si hay mas de 3 dulces iguale en alguna columna
void fixColumna(Board *tablero){
	
		
	char letra;
	char nuevaLetra;
	int i,j;
	letra='N';
	int trio=1;
	
	int r;

	int N,M;
	M=tablero->alto;
	N=tablero->ancho;
		
	for(i=0;i<N;i++){
		
		
		
		for (j=0;j<M;j++){
	
			
			if (tablero->Matriz[j][i].letrasCandy == letra){
				trio=trio+1;		
			}
			else if (tablero->Matriz[j][i].letrasCandy != letra){
				trio=1;
				letra=tablero->Matriz[j][i].letrasCandy;
				
			}
			
			//si se encontraron 3 trios, se debe cambiar esta ultima letra 	
			if (trio==3){
				
				//se debe cabiar el %n, ya que depende de la dificultad
				r= rand()%3; 
				nuevaLetra=TiposCandys[r];
				while (nuevaLetra == letra){
					r=rand()% tablero->dificultad; 
					nuevaLetra=TiposCandys[r];
				}
				
				tablero->Matriz[j][i].letrasCandy=nuevaLetra;
				letra=nuevaLetra;
				trio=1;
			}
			

		}//for j
		//se para a buscar en la siguiente columna
		trio=1;
		
		
	}//for i	
} 





//Funcion que "arregla" el tablero en caso de encontar algun trio en el tablero  
void fixTablero(Board *tablero,code *statusCode){
	
	int check;
	
	check=checkBoard(tablero,statusCode);
	
	while (check == 0){
		
		fixFila(tablero);
		fixColumna(tablero);
		
		check=checkBoard(tablero,statusCode);
	}	
}




//Funcion que libera la memoria solicitada para crear el tablero 
void destruirTablero(Board *tablero){
	
	int i;
	
	for(i=0;i<tablero->alto;i++){
		
		free(tablero->Matriz[i]);
		
	}
	
	free(tablero->Matriz);
	free(tablero);
	
}





//Funcion que imprime el tablero 
void saveBoard(Board *b, int *id,code *statusCode){
	
	
	int i,j,n,m;
	int largo;
	m=b->alto;
	n=b->ancho;
	time_t tiempo;
	char fecha[80];
	char numero[80];
	char letra;
  	struct tm *tmPtr;
	tiempo = time(NULL);
  	tmPtr = localtime(&tiempo);
  	strftime( numero, 80, "%H%M%S", tmPtr );
  	strftime( fecha, 80, "Tablero grabado el dia: %A %B de %Y a las %H:%M:%S", tmPtr);
	largo=strlen(numero);
	numero[largo]='.';numero[largo+1]='t';numero[largo+2]='x'; numero[largo+3]='t';numero[largo+4]='\0';
	
	FILE *archivoSalida;
	archivoSalida = fopen(numero,"w");
	

	numero[largo]='\0'; 
	fprintf(archivoSalida, "%s", numero);
	fprintf(archivoSalida,"%s","\n");
	//Se imprime dato de alto
	fprintf(archivoSalida,"%d ",b->alto);
	//Se imprime dato de alto
	fprintf(archivoSalida, "%d",b->ancho);
	fprintf(archivoSalida,"%s","\n");
	//Se imprime la fecha
	fprintf(archivoSalida, "%s",fecha);
	fprintf(archivoSalida,"%s","\n");


	//Se tranforma "numero" a un entero para ser almacenado como id

	*id=atoi(numero);


	//Se imprime todo el tablero	
	for(i=0;i<m;i++){
		
		for (j=0;j<n;j++){
			
			fprintf(archivoSalida,"%c",b->Matriz[i][j].letrasCandy);
			fprintf(archivoSalida,"%d",b->Matriz[i][j].dureza);
			fprintf(archivoSalida,"%c",b->Matriz[i][j].poder);
			fprintf(archivoSalida,"%c",' ');
		}
		fprintf(archivoSalida,"%s","\n");
	}

	
	fclose(archivoSalida);
}







//Funcion que carga un tablero desde un archivo de texto
Board *loadBoard(int id, code *statusCode){
	


	int largo;
	char idBuscar[20];
	//idBuscar=spin();
	sprintf(idBuscar,"%d",id);
	largo=strlen(idBuscar);
	idBuscar[largo]='.';idBuscar[largo+1]='t';idBuscar[largo+2]='x';idBuscar[largo+3]='t';idBuscar[largo+4]='\0';
	

	//Se debe buscar el archivo con el nombre de: idBuscar en modo r
	FILE *archivoLectura;
	archivoLectura=fopen(idBuscar,"r");
	


	if (archivoLectura == NULL){
		printf("No se encontro el archivo con el nombre: %s\n\n",idBuscar);
		//modificar el status 
		fclose(archivoLectura);
		return NULL;
	}

	else if (archivoLectura != NULL){
		printf("Se encontro el archivo con el nombre: %s\n\n",idBuscar);
	}



	
	//si se encuentra el archivo
	char fecha[80];
	int idNumber;
	char aux[1];
	char algo[4];
	int M,N;
	char letra;
	int dureza; 
	char poder;
	char dulce[3];

	// Se lee el id encontrado en el archivo, el cual debe calzar con el nombre del archivo
	fscanf(archivoLectura,"%d",&idNumber);
	if (idNumber != id){
		printf("El nombre del archivo de entrada no corresponde al mismo id del tablero\n");
		fclose(archivoLectura);
		return NULL;
	}


	//Pedir memoria para un tablero 	
	Board *tablero = (Board*)malloc(sizeof(Board));


	//Se lee el alto del tablero
	fscanf(archivoLectura,"%s",algo);
	tablero->alto=atoi(algo);
	printf("El alto del tablero es: %d\n",(tablero->alto));
	//Se lee el ancho del tablero
	fscanf(archivoLectura,"%s",algo);
	tablero->ancho=atoi(algo);
	printf("El ancho del tablero es: %d\n",(tablero->ancho));
	//Se lee el salto de linea 
	aux[0]=fgetc(archivoLectura);
	//Se lee la fecha de cuando se guardo el tablero y se creo el archivo de texto
	fgets(fecha,80,archivoLectura);
	printf("%s\n", fecha);

	M=tablero->alto;
	N=tablero->ancho;

	Candy **Matriz=(Candy **)malloc(M*sizeof(Candy*));
	//Verificar si se logro asignar memoria a la matriz 
	
	if (Matriz == NULL){
		
		printf("No hay memoria");
	}
	
	
	int i;
	int j;
	for(i=0;i<M;i++){
		
		Matriz[i]=(Candy*)malloc(N*sizeof(Candy));
		
	}
		


	tablero->Matriz=Matriz;




	
	for(i=0;i<M;i++){
		
		for (j=0;j<N;j++){
			
			letra=getc(archivoLectura);
			//printf("La primera letra leida es: %c\n",letra);
			tablero->Matriz[i][j].letrasCandy=letra;

			aux[0]=getc(archivoLectura);
			dureza = atoi(aux);
			//printf("La dureza es: %d\n",dureza);
			tablero->Matriz[i][j].dureza=dureza;

			poder=getc(archivoLectura);
			//printf("El poder del dulce es: %c\n",poder);
			tablero->Matriz[i][j].poder=poder;


			aux[0]=fgetc(archivoLectura);
			if (aux[0]==' '){
				//printf("\nESPACIO\n");
			}	


		}

		aux[0]=fgetc(archivoLectura);
		if (aux[0]=='\n'){
				//printf("\nSALTO\n");
		}

	}
			
	
	

	printf("\n");
	fclose(archivoLectura);
	return tablero;
}






//funcion que imprime el tablero en pantalla
void print(Board *b,code *statusCode){
	
	printf("\n");
	int M,N;
	M=b->alto;
	N=b->ancho;
	int i,j;	


	//Se imprime encabezado
	printf("\t ");
	for (j=0;j<N;j++){
		printf("%d    ",j);
	}
	printf("\n\n");




	//Se imprime todo el tablero
	for(i=0;i<M;i++){
		printf("%d]\t",i);
		for (j=0;j<N;j++){
			
			printf("%c",b->Matriz[i][j].letrasCandy);
			printf("%d",b->Matriz[i][j].dureza);
			printf("%c  ",b->Matriz[i][j].poder);
		}
		printf("\n");
	}
	printf("\n");
}






//Funcion que Rompe las durezas de los dulces que alrededor de la explosion y ejecuta los poderes de cada tipo de dulce 
int romperDurezas(Board *tablero,Position *pos, int ptj){



	int p=0;
	int maxX,minX;
	int maxY,minY;


	if (pos != NULL){

			maxX=pos[0].posX;
			minX=pos[0].posX;
			maxY=pos[0].posY;
			minY=pos[0].posY;

				do{

				printf("\nLa pos X es: %d",pos[p].posX);
				printf("\nLa pos Y es: %d",pos[p].posY);
				printf("\n");


				if (pos[p].posX > maxX){
					maxX=pos[p].posX;

				}
				if (pos[p].posX < minX){
					minX=pos[p].posX;
				}
				if (pos[p].posY > maxY){
					maxY=pos[p].posY;
				}
				if(pos[p].posY < minY){
					minY=pos[p].posY;
				}

				tablero->Matriz[pos[p].posY][pos[p].posX].dureza = (tablero->Matriz[pos[p].posY][pos[p].posX].dureza)-1;


				p++;
				}
				while (pos[p-1].ultimo != 1); 

	}
	if (pos == NULL){
		//printf("\nTablero Sin Grupos de 3 o mas \n");
	}

	printf("El numero de dulces es: %d\n",p);
	ptj=ptj+p;

	
	//-----------------------------------------------------------------------------------------------------------------------------------------
	//.........................................................Disminuir durezas................................................................





	//*******************************************************************************************************************************************
	
	
	//Dulces especiales
	p=0;

			if (pos != NULL){
		

				do{

					if (tablero->Matriz[pos[p].posY][pos[p].posX].poder == '!'){

						//Disminuir dureza en columna
						int i;
						for (i=0; i < tablero->alto ;i++){
							tablero->Matriz[i][pos[p].posX].dureza = (tablero->Matriz[i][pos[p].posX].dureza)-1;
							ptj=ptj+2;
						}
					}



					if (tablero->Matriz[pos[p].posY][pos[p].posX].poder == '~'){
						//Disminuir dureza en fila
						int i;
						for (i=0; i < tablero->ancho ;i++){
							tablero->Matriz[pos[p].posY][i].dureza = (tablero->Matriz[pos[p].posY][i].dureza)-1;
							ptj=ptj+2;
						}
					}
		
				p++;
				}
				while (pos[p-1].ultimo != 1); 

	}
	if (pos == NULL){
		//printf("\nTablero Sin Grupos de 3 o mas \n");
	}


	//*******************************************************************************************************************************************
	//Dulces normales 




	//Vertical

	if(maxX == minX){
		
		//printf("\nMaxX es: %d",maxX);
		//printf("\nMixX es: %d",minX);
		
		//Eliminar izquierda
		if (minX>0 && minY-1 >= 0 && maxY+1 < tablero->alto){

				
			int i=minY-1;
			while(i <= maxY+1){

				tablero->Matriz[i][minX-1].dureza=(tablero->Matriz[i][minX-1].dureza)-1;
				ptj=ptj+1;
				i++;
			} 
			
		}
		else if (minX>0 && minY >= 0 && maxY+1 < tablero->alto){

			
			
			int i=minY;
			while(i <= maxY+1){

				tablero->Matriz[i][minX-1].dureza=(tablero->Matriz[i][minX-1].dureza)-1;
				ptj=ptj+1;
				i++;
			} 
			
		}
		else if (minX>0 && minY-1 >= 0 && maxY < tablero->alto){

		
			int i=minY-1;
			while(i <= maxY){
				
				//printf("%s\n", );
				tablero->Matriz[i][minX-1].dureza=(tablero->Matriz[i][minX-1].dureza)-1;
				ptj=ptj+1;
				i++;
			} 
			
		}
		else if (minX>0 && minY >= 0 && maxY < tablero->alto){

			int i=minY;
			while(i <= maxY){
			
				tablero->Matriz[i][minX-1].dureza=(tablero->Matriz[i][minX-1].dureza)-1;
				ptj=ptj+1;
				i++;
			} 
			
		}

	

		//Eliminar derecha 
		if (maxX+1 < tablero->ancho && minY-1 >= 0 && maxY+1 < tablero->alto){

			
			
			int i=minY-1;
			while(i <= maxY+1){

				tablero->Matriz[i][maxX+1].dureza=(tablero->Matriz[i][maxX+1].dureza)-1;
				ptj=ptj+1;
				i++;
			} 
			
		}
		else if (maxX+1<tablero->ancho && minY >= 0 && maxY+1 < tablero->alto){

			
			int i=minY;
			while(i <= maxY+1){

				tablero->Matriz[i][maxX+1].dureza=(tablero->Matriz[i][maxX+1].dureza)-1;
				ptj=ptj+1;
				i++;
			} 
			
		}
		else if (maxX+1<tablero->ancho && minY >= 0 && maxY < tablero->alto){

			
			int i=minY;
			while(i <= maxY){

				tablero->Matriz[i][maxX+1].dureza=(tablero->Matriz[i][maxX+1].dureza)-1;
				ptj=ptj+1;
				i++;
			} 
			
		}
		else if (maxX+1<tablero->ancho && minY-1 >= 0 && maxY < tablero->alto){

			
			int i=minY-1;
			while(i <= maxY){

				tablero->Matriz[i][maxX+1].dureza=(tablero->Matriz[i][maxX+1].dureza)-1;
				ptj=ptj+1;
				i++;
			} 
			
		}


		//Eliminar arriba
		if (minY-1 >= 0){
			tablero->Matriz[minY-1][maxX].dureza=(tablero->Matriz[minY-1][maxX].dureza)-1;
		}
		//Eliminar abajo  
		if (maxY+1 < tablero->alto){
			tablero->Matriz[maxY+1][maxX].dureza=(tablero->Matriz[maxY+1][maxX].dureza)-1;
		}

	}



	//Horizonal 
	if(maxY == minY){

		//printf("\nPasa\n");
		//Eliminar arriba
		if (minY>0 && minX-1 >= 0 && maxX+1 <= tablero->ancho){

			
			int i=minX-1;
			while(i <= maxX+1){

				tablero->Matriz[minY-1][i].dureza=(tablero->Matriz[minY-1][i].dureza)-1;
				ptj=ptj+1;
				i++;
			} 
			
		}
		else if (minY>0 && minX >= 0 && maxX+1 <= tablero->ancho){

			
			int i=minX;
			while(i <= maxX+1){

				tablero->Matriz[minY-1][i].dureza=(tablero->Matriz[minY-1][i].dureza)-1;
				ptj=ptj+1;
				i++;
			} 
			
		}
		else if (minY>0 && minX-1 >= 0 && maxX <= tablero->alto){

			
			int i=minX-1;
			while(i <= maxX){

				tablero->Matriz[minY-1][i].dureza=(tablero->Matriz[minY-1][i].dureza)-1;
				ptj=ptj+1;
				i++;
			} 
			
		}
		else if (minY>0 && minX-1 >= 0 && maxX <= tablero->alto){

			
			int i=minX-1;
			while(i <= maxX){

				tablero->Matriz[minY-1][i].dureza=(tablero->Matriz[minY-1][i].dureza)-1;
				ptj=ptj+1;
				i++;
			} 
			
		}




		//Eliminar abajo 
		if (maxY+1 <= tablero->ancho && minX-1 >= 0 && maxX+1 <= tablero->ancho){

			
			int i=minX-1;
			while(i <= maxX+1){

				tablero->Matriz[maxY+1][i].dureza=(tablero->Matriz[maxY+1][i].dureza)-1;
				ptj=ptj+1;
				i++;
			} 
			
		}
		else if (maxY+1 <= tablero->ancho && minX >= 0 && maxX+1 <= tablero->ancho){

			
			int i=minX;
			while(i <= maxX+1){

				tablero->Matriz[maxY+1][i].dureza=(tablero->Matriz[maxY+1][i].dureza)-1;
				ptj=ptj+1;
				i++;
			} 
			
		}
		else if (maxY+1 <= tablero->ancho && minX >= 0 && maxX <= tablero->ancho){

			
			int i=minX;
			while(i <= maxX){

				tablero->Matriz[maxY+1][i].dureza=(tablero->Matriz[maxY+1][i].dureza)-1;
				ptj=ptj+1;
				i++;
			} 
			
		}
		else if (maxY+1 <= tablero->ancho && minX-1 >= 0 && maxX <= tablero->ancho){

			
			int i=minX-1;
			while(i <= maxX){

				tablero->Matriz[maxY+1][i].dureza=(tablero->Matriz[maxY+1][i].dureza)-1;
				ptj=ptj+1;
				i++;
			} 
			
		}


		//Eliminar izquierda 
		if (minX-1 >= 0){
			tablero->Matriz[minY][minX-1].dureza=(tablero->Matriz[minY][minX-1].dureza)-1;
		}
		//Eliminar derecha
		if (maxX+1 <= tablero->alto){
			tablero->Matriz[minY][maxX+1].dureza=(tablero->Matriz[minY][maxX+1].dureza)-1;
		}

	}

	//**********************************************************************************************************************************************+






	return ptj;


}




//Funcion que se encarga eliminar los dulces que ya no posean durezas 
void actualizarTablero(Board *tablero,code *statusCode){

	int i,j;

		for(i=0;i<tablero->alto;i++){
		
			for (j=0;j<tablero->ancho;j++){

				//Si ya se destruyo la dureza del dulce 
				if(tablero->Matriz[i][j].dureza < 0){
					int r =rand() %  tablero->dificultad;
					tablero->Matriz[i][j].letrasCandy=TiposCandys[r];
					tablero->Matriz[i][j].dureza=0;
					tablero->Matriz[i][j].poder='.';
				} 
				//Si el dulce tenia dureza
				if(tablero->Matriz[i][j].dureza == 0){
					int r =rand() %  tablero->dificultad;
					tablero->Matriz[i][j].letrasCandy=TiposCandys[r];
				} 


			
			}
		
		}
		//Que no se creen trios
		fixTablero(tablero,statusCode);


}




//Funcion que cuenta la cantidad de durezas en el tablero
int contarDurezas(Board *tablero){

	int durezas=0;
	int i,j;

	for(i=0;i<tablero->alto;i++){
		
			for (j=0;j<tablero->ancho;j++){

				//Si se encuentra dureza
				if(tablero->Matriz[i][j].dureza > 0){
					durezas=durezas+1;
				}


			
			}
		
		}


		return durezas;
}






//Funcion que realiza una jugada en el tablero
int play(Board *b,Position pOri,Position pDes, int *turnos,code *statusCode){

	

	int ptj=0;
	//Verificar entradas¿
	//Que sean numeros dentro de la matriz
	if (pOri.posX<0){
		printf("\nPosicion X de origen menor a 0 \n");
		return ptj;
	}
	if (pOri.posX >= b->ancho){
		printf("\nPosicion X de origen menor a ancho de tablero\n");
		return ptj;
	}
	if (pDes.posY<0){
		printf("\nPosicion Y de destino menor a 0 \n");
		return ptj;
	}
	if (pDes.posY >= b->alto){
		printf("\nPosicion Y de destino mayor a alto de tablero \n");
		return ptj;	
	}
	//Que alguna de la pos no sea una dureza(X)
	if (b->Matriz[pDes.posY][pDes.posY].letrasCandy == 'X'){
		printf("\nEl dulce en la posicion de destino posee dureza \n");
		return ptj;
	}
	if (b->Matriz[pOri.posY][pOri.posY].letrasCandy == 'X'){
		printf("\nEl dulce en la posicion de origen posee dureza \n");
		return ptj;
	}
	//Que las posiciones no sean la misma 
	if(pOri.posX == pDes.posX && pOri.posY == pDes.posY){
		printf("\nLa posicion de origen es la misma que la de destino \n");
		return ptj;
	}
	//Que las posciciones sean adyacentes 
	int difX=pOri.posX - pDes.posX;
	int difY=pOri.posY - pDes.posY;
	if(pOri.posX == pDes.posX && difY > 1){
		printf("\nPosicion de destino y de origen no son adyacentes \n");
		return ptj;
	}
	if (pOri.posX == pDes.posX && difY < -1){
		printf("\nPosicion de destino y de origen no son adyacentes \n");
		return ptj;
	}
	if(pOri.posY == pDes.posY && difX > 1){
		printf("\nPosicion de destino y de origen no son adyacentes \n");
		return ptj;
	}
	if (pOri.posY == pDes.posY && difX < -1){
		printf("\nPosicion de destino y de origen no son adyacentes \n");
		return ptj;
	}
	if (difX>1 && difY>1){
		printf("\nPosicion de destino y de origen no son adyacentes \n");
		return ptj;
	}
	if (difY<-1 && difY<-1){
		printf("\nPosicion de destino y de origen no son adyacentes \n");
		return ptj;
	}
	if (difX>1 && difY<-1){
		printf("\nPosicion de destino y de origen no son adyacentes \n");
		return ptj;
	}
	if (difY<-1 && difY>1){
		printf("\nPosicion de destino y de origen no son adyacentes \n");
		return ptj;
	}


	
	char letraOri;
	int durezaOri;
	char poderOri;

	//****************************************************************************************************************************************
	//intercambiar dulces de posicion

	//Se guardan info de dulce en Ori
	letraOri=b->Matriz[pOri.posY][pOri.posX].letrasCandy;
	durezaOri=b->Matriz[pOri.posY][pOri.posX].dureza;
	poderOri=b->Matriz[pOri.posY][pOri.posX].poder;
	//A la posOri se le asigna lo de posDes 
	b->Matriz[pOri.posY][pOri.posX].letrasCandy = b->Matriz[pDes.posY][pDes.posX].letrasCandy;
	b->Matriz[pOri.posY][pOri.posX].dureza = b->Matriz[pDes.posY][pDes.posX].dureza;
	b->Matriz[pOri.posY][pOri.posX].poder = b->Matriz[pDes.posY][pDes.posX].poder;
	//A pDes se le asigna los valores de pOri
	b->Matriz[pDes.posY][pDes.posX].letrasCandy = letraOri; 
	b->Matriz[pDes.posY][pDes.posX].dureza = durezaOri;
	b->Matriz[pDes.posY][pDes.posX].poder = poderOri;

	//*******************************************************************************************************************************************
	//Verificar si existen dulces para que se puedan eliminar
	Position *pos;
	pos=checkCandies(b,statusCode);
	int p=0;
		if (pos != NULL){

				
				do{

				//printf("\nLa pos X es: %d",pos[p].posX);
				//printf("\nLa pos Y es: %d",pos[p].posY);
				printf("\n");
				p++;
				}
				while (pos[p-1].ultimo != 1); 

			}
			if (pos == NULL){
				//printf("\nTablero Sin Grupos de 3 o mas \n");
			}
			//Si hay un grupo con mas de 3 dulces
			if(p >= 3){
				ptj=ptj+romperDurezas(b,pos,ptj);
			}
	
	//************************************************************************************************************************************************
	
	actualizarTablero(b,statusCode);

	return ptj;
}




//Funcion que despliega el menu y llama a las demas funciones
void displayMenu (){
	
	printf("%s","\n\n******************Bienvenido a Candy Crush **********************\n\n");
	printf("%s","Ingrese el numero correspondiente a la operacion que desee realizar: \n\n");
	printf("%s","1.- Crear tablero \n");
	printf("%s","2.- Grabar tablero \n");
	printf("%s","3.- Cargar tablero \n");
	printf("%s","4.- Verificar Tablero  \n");
	printf("%s","5.- Jugar \n");
	printf("%s","6.- Verificar dulces \n");
	printf("%s","7.- Visualizar tablero \n\n\n");
	printf("%s","Seleccion: ");
	
	int seleccion;
	scanf("%d",&seleccion);
	
	code status;
	Board *tablero;
	//Position *pos;
	Params parametros;
	int id;
	int alto,ancho;
	

	switch(seleccion){
		



		//Crear Tablero
		case 1:

			
			printf("\n------------------Ingreso a Crear un Tablero--------------------\n");
			//pedir o definir parametros
			printf("Ingrese nivel de dificultad: \n");
			printf("1.-Facil\n");
			printf("2.-Medio\n");
			printf("3.-Dificil\n");
			printf("Seleccion: ");
			scanf("%d",&seleccion);
			parametros.dificultad=seleccion+2;

			if(seleccion==1){
				printf("\n..............Ingreso dificultad Facil............\n");
				printf("Ingrese tamaño de tablero (tanto ancho como largo debe de mayor a 6)\n");
				printf("\nIngrese alto: ");
				scanf("%d",&alto);
				while (alto<6){
					printf("\n Ancho de tablero fuera de rango\n");
					printf("\nIngrese alto: ");
					scanf("%d",&alto);
				}
				printf("\nIngrese ancho: ");
				scanf("%d",&ancho);
				while (ancho<6){
					printf("\n Ancho de tablero fuera de rango\n");
					printf("\nIngrese ancho: ");
					scanf("%d",&ancho);
				
				//Se le dan los valores a los parametros
				}
				parametros.dificultad=seleccion+2;
				parametros.cantidadDulces=seleccion+2;
				parametros.cantidad0=2;
				parametros.cantidad1=2;
				parametros.cantidad2=1;
				//se crea en tablero
				tablero=createBoard(ancho,alto,parametros,&status);
				print(tablero,&status);
			}
		
				
			
			if(seleccion==2){
				printf("\n..............Ingreso dificultad Media............\n");
				printf("Ingrese tamaño de tablero (tanto ancho como largo debe de mayor a 10)\n");
				printf("\nIngrese alto: ");
				scanf("%d",&alto);
				while (alto<10){
					printf("\n Ancho de tablero fuera de rango\n");
					printf("\nIngrese alto: ");
					scanf("%d",&alto);
				}
				printf("\nIngrese ancho: ");
				scanf("%d",&ancho);
				while (ancho<10){
					printf("\n Ancho de tablero fuera de rango\n");
					printf("\nIngrese ancho: ");
					scanf("%d",&ancho);
				}

				//Se le dan los valores a los parametros

				parametros.dificultad=seleccion+2;
				parametros.cantidadDulces=seleccion+2;
				parametros.cantidad0=2;
				parametros.cantidad1=2;
				parametros.cantidad2=1;
				//se crea en tablero
				tablero=createBoard(ancho,alto,parametros,&status);
				print(tablero,&status);
			}
		
			
			
			if(seleccion==3){
				printf("\n..............Ingreso dificultad Dificil............\n");
				printf("Ingrese tamaño de tablero (tanto ancho como largo debe de mayor a 16)\n");
				printf("\nIngrese alto: ");
				scanf("%d",&alto);
				while (alto<16){
					printf("\n Ancho de tablero fuera de rango\n");
					printf("\nIngrese alto: ");
					scanf("%d",&alto);
				}
				printf("\nIngrese ancho: ");
				scanf("%d",&ancho);
				while (ancho<16){
					printf("\n Ancho de tablero fuera de rango\n");
					printf("\nIngrese ancho: ");
					scanf("%d",&ancho);
				}
				//Se le dan los valores a los parametros

				parametros.dificultad=seleccion+2;
				parametros.cantidadDulces=seleccion+2;
				parametros.cantidad0=1;
				parametros.cantidad1=1;
				parametros.cantidad2=1;
				//se crea en tablero
				tablero=createBoard(ancho,alto,parametros,&status);
				print(tablero,&status);
			}

			

			//free(pos);
			destruirTablero(tablero);
			
			break;



		//Guardar Tablero
		case 2:
			printf("\n------------------Ingreso a Crear un Tablero--------------------\n");
			printf("............Primero se debe crear el tablero a guardar..........\n");

			//pedir o definir parametros
			printf("Ingrese nivel de dificultad: \n");
			printf("1.-Facil\n");
			printf("2.-Medio\n");
			printf("3.-Dificil\n");
			printf("Seleccion: ");
			scanf("%d",&seleccion);
			parametros.dificultad=seleccion+2;

			if(seleccion==1){
				printf("\n..............Ingreso dificultad Facil............\n");
				printf("Ingrese tamaño de tablero (tanto ancho como largo debe de mayor a 6)\n");
				printf("\nIngrese alto: ");
				scanf("%d",&alto);
				while (alto<6){
					printf("\n Ancho de tablero fuera de rango\n");
					printf("\nIngrese alto: ");
					scanf("%d",&alto);
				}
				printf("\nIngrese ancho: ");
				scanf("%d",&ancho);
				while (ancho<6){
					printf("\n Ancho de tablero fuera de rango\n");
					printf("\nIngrese ancho: ");
					scanf("%d",&ancho);
				
				//Se le dan los valores a los parametros
				}
				parametros.dificultad=seleccion+2;
				parametros.cantidadDulces=seleccion+2;
				parametros.cantidad0=2;
				parametros.cantidad1=2;
				parametros.cantidad2=1;
				//se crea en tablero
				tablero=createBoard(ancho,alto,parametros,&status);
				print(tablero,&status);
			}
		
				
			
			if(seleccion==2){
				printf("\n..............Ingreso dificultad Media............\n");
				printf("Ingrese tamaño de tablero (tanto ancho como largo debe de mayor a 10)\n");
				printf("\nIngrese alto: ");
				scanf("%d",&alto);
				while (alto<10){
					printf("\n Ancho de tablero fuera de rango\n");
					printf("\nIngrese alto: ");
					scanf("%d",&alto);
				}
				printf("\nIngrese ancho: ");
				scanf("%d",&ancho);
				while (ancho<10){
					printf("\n Ancho de tablero fuera de rango\n");
					printf("\nIngrese ancho: ");
					scanf("%d",&ancho);
				}

				//Se le dan los valores a los parametros

				parametros.dificultad=seleccion+2;
				parametros.cantidadDulces=seleccion+2;
				parametros.cantidad0=2;
				parametros.cantidad1=2;
				parametros.cantidad2=1;
				//se crea en tablero
				tablero=createBoard(ancho,alto,parametros,&status);
				print(tablero,&status);
			}
		
			
			
			if(seleccion==3){
				printf("\n..............Ingreso dificultad Dificil............\n");
				printf("Ingrese tamaño de tablero (tanto ancho como largo debe de mayor a 16)\n");
				printf("\nIngrese alto: ");
				scanf("%d",&alto);
				while (alto<10){
					printf("\n Ancho de tablero fuera de rango\n");
					printf("\nIngrese alto: ");
					scanf("%d",&alto);
				}
				printf("\nIngrese ancho: ");
				scanf("%d",&ancho);
				while (ancho<10){
					printf("\n Ancho de tablero fuera de rango\n");
					printf("\nIngrese ancho: ");
					scanf("%d",&ancho);
				}
				//Se le dan los valores a los parametros

				parametros.dificultad=seleccion+2;
				parametros.cantidadDulces=seleccion+2;
				parametros.cantidad0=1;
				parametros.cantidad1=1;
				parametros.cantidad2=1;
				//se crea en tablero
				tablero=createBoard(ancho,alto,parametros,&status);
				print(tablero,&status);
			}

			
			saveBoard(tablero,&id,&status);
			printf("Su numero de identificacion de tablero es: %d\n\n",id);
			destruirTablero(tablero);

			
			break;





		//Cargar tablero 
		case 3:

			printf("Ingrese el id a Buscar: ");
			int id;
			scanf("%d",&id);
			//Board *tablero;
			tablero=loadBoard(id,&status);

			if (tablero != NULL){
				print(tablero,&status);
				destruirTablero(tablero);

			}
			if (tablero == NULL){
				return;
			}
			

			
			break;





		//Verificar Tablero
		case 4:
			printf("\n-------------------Ingreso a Verificar Tablero-----------------\n");
			printf("¿Desea crear un nuevo tablero o cargar tablero?\n");
			printf("1.-Crear\n");
			printf("2.-Cargar\n");
			scanf("%d",&seleccion);

			//Crear nuevo tablero
			if (seleccion==1){
				printf("Ingrese nivel de dificultad: \n");
				printf("1.-Facil\n");
				printf("2.-Medio\n");
				printf("3.-Dificil\n");
				printf("Seleccion: ");
				int seleccion2;
				scanf("%d",&seleccion2);
				parametros.dificultad=seleccion2+2;

				if(seleccion2==1){
					printf("\n..............Ingreso dificultad Facil............\n");
					printf("Ingrese tamaño de tablero (tanto ancho como largo debe de mayor a 6)\n");
					printf("\nIngrese alto: ");
					scanf("%d",&alto);
					while (alto<6){
						printf("\n Ancho de tablero fuera de rango\n");
						printf("\nIngrese alto: ");
						scanf("%d",&alto);
					}
					printf("\nIngrese ancho: ");
					scanf("%d",&ancho);
					while (ancho<6){
						printf("\n Ancho de tablero fuera de rango\n");
						printf("\nIngrese ancho: ");
						scanf("%d",&ancho);
				
					//Se le dan los valores a los parametros
					}
					parametros.dificultad=seleccion2+2;
					parametros.cantidadDulces=seleccion2+2;
					parametros.cantidad0=2;
					parametros.cantidad1=2;
					parametros.cantidad2=1;
					//se crea en tablero
					tablero=createBoard(ancho,alto,parametros,&status);
					print(tablero,&status);
				}
		
				
				
				if(seleccion2==2){
					printf("\n..............Ingreso dificultad Media............\n");
					printf("Ingrese tamaño de tablero (tanto ancho como largo debe de mayor a 10)\n");
					printf("\nIngrese alto: ");
					scanf("%d",&alto);
					while (alto<10){
						printf("\n Ancho de tablero fuera de rango\n");
						printf("\nIngrese alto: ");
						scanf("%d",&alto);
					}
					printf("\nIngrese ancho: ");
					scanf("%d",&ancho);
					while (ancho<10){
						printf("\n Ancho de tablero fuera de rango\n");
						printf("\nIngrese ancho: ");
						scanf("%d",&ancho);
					}

					//Se le dan los valores a los parametros

					parametros.dificultad=seleccion2+2;
					parametros.cantidadDulces=seleccion2+2;
					parametros.cantidad0=2;
					parametros.cantidad1=2;
					parametros.cantidad2=1;
					//se crea en tablero
					tablero=createBoard(ancho,alto,parametros,&status);
					print(tablero,&status);
				}
		
			
				
				if(seleccion2==3){
					printf("\n..............Ingreso dificultad Dificil............\n");
					printf("Ingrese tamaño de tablero (tanto ancho como largo debe de mayor a 16)\n");
					printf("\nIngrese alto: ");
					scanf("%d",&alto);
					while (alto<16){
						printf("\n Ancho de tablero fuera de rango\n");
						printf("\nIngrese alto: ");
						scanf("%d",&alto);
					}
					printf("\nIngrese ancho: ");
					scanf("%d",&ancho);
					while (ancho<16){
						printf("\n Ancho de tablero fuera de rango\n");
						printf("\nIngrese ancho: ");
						scanf("%d",&ancho);
					}
					//Se le dan los valores a los parametros
					parametros.dificultad=seleccion2+2;
					parametros.cantidadDulces=seleccion2+2;
					parametros.cantidad0=1;
					parametros.cantidad1=1;
					parametros.cantidad2=1;
					//se crea en tablero
					tablero=createBoard(ancho,alto,parametros,&status);
					print(tablero,&status);
				}

			}



			//Cargar
			if (seleccion==2){
				printf("Ingrese el id a Buscar: ");
				int id;
				scanf("%d",&id);
				//Board *tablero;
				tablero=loadBoard(id,&status);

				if (tablero != NULL){
					print(tablero,&status);
					//destruirTablero(tablero);

				}

			}



			//Verificar tablero
			int check;
			check=checkBoard(tablero,&status);
			if(check==1){
				printf("\nEl tablero es valido\n");
			}
			else if (check==0){
				printf("\nEl tablero no es valido\n");
			}
			

			destruirTablero(tablero);
			
			break;




		//Jugar
		case 5:


			//Se carga el tablero 
			printf("Ingrese el id a Buscar: ");
			
			scanf("%d",&id);
			//Board *tablero;
			tablero=loadBoard(id,&status);

			if (tablero != NULL){
				print(tablero,&status);
				//destruirTablero(tablero);

			}
			if (tablero == NULL){
				return;
			}
			

			//Jugar 
			int ptj=0;
			int turnos=15;
			Position posOri;
			Position posDes;
			char aux[3];

			//Solicitar pos de entrada y pos de 
			while (turnos>0){
				printf("\nIngrese valor de X de la posicion de origen: ");
				scanf("%s",aux);
				posOri.posX=atoi(aux);
				printf("\nIngrese valor de Y de la posicion de origen: ");
				scanf("%s",aux);
				posOri.posY=atoi(aux);
				printf("\nIngrese valor de X de la posicion de destino: ");
				scanf("%s",aux);
				posDes.posX=atoi(aux);
				printf("\nIngrese valor de Y de la posicion de destino: ");
				scanf("%s",aux);
				posDes.posY=atoi(aux);

				ptj=ptj+play(tablero,posOri,posDes,&turnos,&status);
				print(tablero,&status);
				turnos--;

			}


			if (contarDurezas(tablero) == 0){
				printf("\n!!!VICTORIA¡¡¡\n");	
			}
			else if (contarDurezas(tablero) != 0){
				printf("\nDERROTA\n");	
			}
			printf("Se acabo el juego\n");

			destruirTablero(tablero);
			
			break;



		//Verificar dulces
		case 6:

			printf("\n-------------------Ingreso a Verificar Tablero-----------------\n");
			printf("¿Desea crear un nuevo tablero o cargar tablero?\n");
			printf("1.-Crear\n");
			printf("2.-Cargar\n");
			scanf("%d",&seleccion);

			//Crear nuevo tablero
			if (seleccion==1){
				printf("Ingrese nivel de dificultad: \n");
				printf("1.-Facil\n");
				printf("2.-Medio\n");
				printf("3.-Dificil\n");
				printf("Seleccion: ");
				int seleccion2;
				scanf("%d",&seleccion2);
				parametros.dificultad=seleccion2+2;

				if(seleccion2==1){
					printf("\n..............Ingreso dificultad Facil............\n");
					printf("Ingrese tamaño de tablero (tanto ancho como largo debe de mayor a 6)\n");
					printf("\nIngrese alto: ");
					scanf("%d",&alto);
					while (alto<6){
						printf("\n Ancho de tablero fuera de rango\n");
						printf("\nIngrese alto: ");
						scanf("%d",&alto);
					}
					printf("\nIngrese ancho: ");
					scanf("%d",&ancho);
					while (ancho<6){
						printf("\n Ancho de tablero fuera de rango\n");
						printf("\nIngrese ancho: ");
						scanf("%d",&ancho);
				
					//Se le dan los valores a los parametros
					}
					parametros.dificultad=seleccion2+2;
					parametros.cantidadDulces=seleccion2+2;
					parametros.cantidad0=2;
					parametros.cantidad1=2;
					parametros.cantidad2=1;
					//se crea en tablero
					tablero=createBoard(ancho,alto,parametros,&status);
					print(tablero,&status);
				}
		
				
				
				if(seleccion2==2){
					printf("\n..............Ingreso dificultad Media............\n");
					printf("Ingrese tamaño de tablero (tanto ancho como largo debe de mayor a 10)\n");
					printf("\nIngrese alto: ");
					scanf("%d",&alto);
					while (alto<10){
						printf("\n Ancho de tablero fuera de rango\n");
						printf("\nIngrese alto: ");
						scanf("%d",&alto);
					}
					printf("\nIngrese ancho: ");
					scanf("%d",&ancho);
					while (ancho<10){
						printf("\n Ancho de tablero fuera de rango\n");
						printf("\nIngrese ancho: ");
						scanf("%d",&ancho);
					}

					//Se le dan los valores a los parametros

					parametros.dificultad=seleccion2+2;
					parametros.cantidadDulces=seleccion2+2;
					parametros.cantidad0=2;
					parametros.cantidad1=2;
					parametros.cantidad2=1;
					//se crea en tablero
					tablero=createBoard(ancho,alto,parametros,&status);
					print(tablero,&status);
				}
		
			
				
				if(seleccion2==3){
					printf("\n..............Ingreso dificultad Dificil............\n");
					printf("Ingrese tamaño de tablero (tanto ancho como largo debe de mayor a 16)\n");
					printf("\nIngrese alto: ");
					scanf("%d",&alto);
					while (alto<16){
						printf("\n Ancho de tablero fuera de rango\n");
						printf("\nIngrese alto: ");
						scanf("%d",&alto);
					}
					printf("\nIngrese ancho: ");
					scanf("%d",&ancho);
					while (ancho<16){
						printf("\n Ancho de tablero fuera de rango\n");
						printf("\nIngrese ancho: ");
						scanf("%d",&ancho);
					}
					//Se le dan los valores a los parametros
					parametros.dificultad=seleccion2+2;
					parametros.cantidadDulces=seleccion2+2;
					parametros.cantidad0=1;
					parametros.cantidad1=1;
					parametros.cantidad2=1;
					//se crea en tablero
					tablero=createBoard(ancho,alto,parametros,&status);
					print(tablero,&status);
				}

			}



			//Cargar
			if (seleccion==2){
				printf("Ingrese el id a Buscar: ");
				int id;
				scanf("%d",&id);
				//Board *tablero;
				tablero=loadBoard(id,&status);

				if (tablero != NULL){
					print(tablero,&status);
					//destruirTablero(tablero);

				}

			}





			//Se hace el check candies del tablero
			Position *pos;
			pos=checkCandies(tablero,&status);
			int p=0;
			if (pos == NULL){
				printf("\nTablero Sin Grupos de 3 o mas dulces iguales \n");
				destruirTablero(tablero);
				return;
			}
			if (pos != NULL){
				printf("Tablero con un grupo de al menos 3 dulces iguales\n\n");
				do{
					printf("El dulce numero %d esta ubicado en: \n",p+1);
					printf("La pos X es: %d\n",pos[p].posX);
					printf("La pos Y es: %d",pos[p].posY);
					printf("\n");
				p++;
				}while (pos[p-1].ultimo != 1); 
				destruirTablero(tablero);
				return;

			}
			

			
			



			
			break;




		//Visualizar tablero
		case 7:

			printf("\n-------------------Ingreso a Visualizar Tablero-----------------\n");
			printf("¿Desea crear un nuevo tablero o cargar tablero?\n");
			printf("1.-Crear\n");
			printf("2.-Cargar\n");
			scanf("%d",&seleccion);

			//Crear nuevo tablero
			if (seleccion==1){

				printf("Ingrese nivel de dificultad: \n");
				printf("1.-Facil\n");
				printf("2.-Medio\n");
				printf("3.-Dificil\n");
				printf("Seleccion: ");
				int seleccion2;
				scanf("%d",&seleccion2);
				parametros.dificultad=seleccion2+2;

				if(seleccion2==1){
					printf("\n..............Ingreso dificultad Facil............\n");
					printf("Ingrese tamaño de tablero (tanto ancho como largo debe de mayor a 6)\n");
					printf("\nIngrese alto: ");
					scanf("%d",&alto);
					while (alto<6){
						printf("\n Ancho de tablero fuera de rango\n");
						printf("\nIngrese alto: ");
						scanf("%d",&alto);
					}
					printf("\nIngrese ancho: ");
					scanf("%d",&ancho);
					while (ancho<6){
						printf("\n Ancho de tablero fuera de rango\n");
						printf("\nIngrese ancho: ");
						scanf("%d",&ancho);
				
					//Se le dan los valores a los parametros
					}
					parametros.dificultad=seleccion2+2;
					parametros.cantidadDulces=seleccion2+2;
					parametros.cantidad0=2;
					parametros.cantidad1=2;
					parametros.cantidad2=1;
					//se crea en tablero
					tablero=createBoard(ancho,alto,parametros,&status);
					print(tablero,&status);
				}
		
				
				
				if(seleccion2==2){
					printf("\n..............Ingreso dificultad Media............\n");
					printf("Ingrese tamaño de tablero (tanto ancho como largo debe de mayor a 10)\n");
					printf("\nIngrese alto: ");
					scanf("%d",&alto);
					while (alto<10){
						printf("\n Ancho de tablero fuera de rango\n");
						printf("\nIngrese alto: ");
						scanf("%d",&alto);
					}
					printf("\nIngrese ancho: ");
					scanf("%d",&ancho);
					while (ancho<10){
						printf("\n Ancho de tablero fuera de rango\n");
						printf("\nIngrese ancho: ");
						scanf("%d",&ancho);
					}

					//Se le dan los valores a los parametros

					parametros.dificultad=seleccion2+2;
					parametros.cantidadDulces=seleccion2+2;
					parametros.cantidad0=2;
					parametros.cantidad1=2;
					parametros.cantidad2=1;
					//se crea en tablero
					tablero=createBoard(ancho,alto,parametros,&status);
					print(tablero,&status);
				}
		
			
				
				if(seleccion2==3){
					printf("\n..............Ingreso dificultad Dificil............\n");
					printf("Ingrese tamaño de tablero (tanto ancho como largo debe de mayor a 16)\n");
					printf("\nIngrese alto: ");
					scanf("%d",&alto);
					while (alto<16){
						printf("\n Ancho de tablero fuera de rango\n");
						printf("\nIngrese alto: ");
						scanf("%d",&alto);
					}
					printf("\nIngrese ancho: ");
					scanf("%d",&ancho);
					while (ancho<16){
						printf("\n Ancho de tablero fuera de rango\n");
						printf("\nIngrese ancho: ");
						scanf("%d",&ancho);
					}
					//Se le dan los valores a los parametros
					parametros.dificultad=seleccion2+2;
					parametros.cantidadDulces=seleccion2+2;
					parametros.cantidad0=1;
					parametros.cantidad1=1;
					parametros.cantidad2=1;
					//se crea en tablero
					tablero=createBoard(ancho,alto,parametros,&status);
					print(tablero,&status);
				}

			}



			//Cargar
			if (seleccion==2){
				printf("Ingrese el id a Buscar: ");
				int id;
				scanf("%d",&id);
				//Board *tablero;
				tablero=loadBoard(id,&status);

				if (tablero != NULL){
					print(tablero,&status);
					//destruirTablero(tablero);

				}

			}

			destruirTablero(tablero);
			
			break;




		default:

			printf("\nSeleccion no valida\n");
			displayMenu();
			
			break;

			
	}

}
