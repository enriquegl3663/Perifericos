#include <stdio.h>
#include <dos.h>

#define BYTE unsigned char

int mi_getchar(){
	 union REGS inregs, outregs;
	 int caracter;

	 inregs.h.ah = 1;
	 int86(0x21, &inregs, &outregs);

	 caracter = outregs.h.al;
	 return caracter;
}

void mi_pausa(){
	 union REGS inregs, outregs;
	 inregs.h.ah = 8;
	 int86(0x21, &inregs, &outregs);
}

void mi_putchar(char c){
	 union REGS inregs, outregs;

	 inregs.h.ah = 2;
	 inregs.h.dl = c;
	 int86(0x21, &inregs, &outregs);
}
//Funcion 1
void gotoxy(int x, int y){
	union REGS inregs, outregs;
	inregs.h.ah = 0x02;
	inregs.h.bh = 0x00;
	inregs.h.dh = y;
	inregs.h.dl = x;
	int86(0x10,&inregs,&outregs);
	return;
}

//Funcion 2
void setcursortype(int tipo_cursor)
{
	union REGS inregs, outregs;
	inregs.h.ah = 0x01;
	switch(tipo_cursor){
		case 0: //Modo invisible
			inregs.h.ch = 010;
			inregs.h.cl = 000;
		break;

		case 1: //Modo normal
			inregs.h.ch = 010;
			inregs.h.cl = 010;
		break;

		case 2: //Modo grueso
			inregs.h.ch = 000;
			inregs.h.cl = 010;
		break;
	}
	int86(0x10, &inregs, &outregs);
}

//Funcion 3

void setvideomode(BYTE modo){
    union REGS inregs, outregs;
    inregs.h.al = modo;
    inregs.h.ah = 0x00;
    
    int86(0x10, &inregs, &outregs);
    return;
}

//Funcion 4

int getvideomode(){
    int modo_video;
    union REGS inregs, outregs;
		inregs.h.ah = 0x0F;
    int86(0x10, &inregs, &outregs);
    modo_video = outregs.h.al;

    return modo_video;
}

//Funcion 5
void textcolor(int color){// modifica el color de primer plano con que se mostrarán los caracteres
    union REGS inregs, outregs;
    inregs.h.ah = 0x09;
    inregs.h.bl = 0 << 4 | color;
    inregs.h.bh = 0x00;
    inregs.x.cx = 5;
    int86(0x10,&inregs,&outregs);
    return;
}

//Funcion 6
void textbackground(int color){ //: modifica el color de fondo con que se mostrarán los caracteres
    union REGS inregs, outregs;
    inregs.h.ah = 0x09;
    inregs.h.bl = color << 4;
    inregs.h.bh = 0x00;
    inregs.x.cx = 5;
    int86(0x10,&inregs,&outregs);
    return;
}

//Funcion 7
void clrscr()
{
	union REGS regs;
	regs.h.ah = 15;
	int86( 0x10, &regs, &regs );
	regs.h.ah = 0;
	int86( 0x10, &regs, &regs );
}

//Funcion 8
void cputchar(char letra, unsigned char cfondo, unsigned char cletra){
    union REGS inregs, outregs;
    inregs.h.ah = 0x09;
    inregs.h.al = letra;
    inregs.h.bl = cfondo << 4 | cletra;
    inregs.h.bh = 0x00;
    inregs.x.cx = 1;
    int86(0x10,&inregs,&outregs);
    return;
}

//Funcion 9
void getche()
{
	int resultado;
	printf("\nIntroduzca el caracter que desee mostrar...\n");
	resultado = mi_getchar();

	printf("\nEl caracter introducido es:");
	 mi_putchar( (char)resultado );
}


int main(){
	int tmp, tipocursor, videomode;
	int terminado = 0;
	int valido = 0;

	while(terminado == 0)
	{
		printf("\nVamos a mostrar las distintas funciones de las que dispone el programa\n");
		printf("\nPulsa 1 para gotoxy()");
		printf("\nPulsa 2 para setcursortype()");
		printf("\nPulsa 3 para setvideomode()");
		printf("\nPulsa 4 para getvideomode()");
		printf("\nPulsa 5 para textcolor()");
		printf("\nPulsa 6 para textbackground()");
		printf("\nPulsa 7 para clrscr()");
		printf("\nPulsa 8 para cputchar()");
		printf("\nPulsa 9 para getche()");
		printf("\nPulsa a para funcion extra 1");
		printf("\nPulsa 0 para cerrar el programa");

		printf("\n\nPulsa una tecla...  ");
		tmp = mi_getchar();

		if(tmp == '1')
		{
			printf("\nEsta funcion coloca el cursor en varias posiciones de la pantalla");
			mi_pausa();
			gotoxy(1,1);
			printf("*");
			gotoxy(40,22);
			printf("?");
			gotoxy(50,5);
			printf("&");
			gotoxy(15,12);
			printf("!");
			mi_pausa();
			printf("\n\n");
		}
		else if(tmp == '2')
		{
			printf("\nEsta funcion fijar el aspecto del cursor, admite tres valores");
			printf("\n 0 -- Modo invisible\n 1 -- Modo normal\n 2 -- Modo grueso\n");
			tipocursor = mi_getchar();
			
			if(tipocursor == '0')
			{
				setcursortype(0);
			}
			else if(tipocursor == '1')
			{
				setcursortype(1);
			}
			else if(tipocursor == '2')
			{
				setcursortype(2);
			}
			else
			{
				printf("\nValor no valido");
			}
			mi_pausa();
			printf("\n\n");
		}
		else if(tmp == '3')
		{
			BYTE MODOTEXTO;
			BYTE MODOGRAFICO;
			
			MODOTEXTO = 3;
			MODOGRAFICO = 4;
			
			printf("\nEsta funcion fija el modo de video");
			printf("\n 3 -- Modo texto\n 4 -- Modo grafico\n");
			videomode = mi_getchar();
			
			if(videomode == '3')
			{
				setvideomode(MODOTEXTO);
			}
			else if(videomode == '4')
			{
				setvideomode(MODOGRAFICO);
			}
			else
			{
				printf("\nValor no valido");
			}

			mi_pausa();	
			printf("\n\n");
		}
		else if(tmp == '4')
		{
			int resultado;
			printf("\nEsta funcion devuelve el modo de  video usado");
			printf("\n 3 -- Modo texto\n 4 -- Modo grafico");
			printf("\n");
			resultado = getvideomode();
			printf("\nEl modo usado es: ");
			mi_putchar((char) resultado);
			printf("\nComo la respuesta la devuelve en ascii:\nEl corazon es 3 que es modo texto\nEl diamante es 4 que es modo grafico");
			mi_pausa();
			printf("\n\n");
		}
		else if(tmp == '5')
		{
			int color;
			printf("\nEsta funcion cambia el primer plano de color");
			printf("\nIntroduzca un numero entre el 0 y el 7: ");
			color = mi_getchar()-48;
			printf("\n");
			textcolor(color);
			mi_pausa();
			printf("\n\n");
		}
		else if(tmp == '6')
		{
			int fondo;
			printf("\nEsta funcion cambia el fondo de color");
			printf("\nIntroduzca un numero entre el 0 y el 7: ");
			fondo = mi_getchar()-48;
			printf("\n");
			textbackground(fondo);
			mi_pausa();
			printf("\n\n");
		}
		else if(tmp == '7')
		{
			printf("\nEsta funcion borra la pantalla, ademas usamos esta funcion en el programa para borrar el menu tras cada uso. \nPulsa cualquier tecla para continuar");
			mi_pausa();
			clrscr();
			printf("\n\n");
		}
		else if(tmp == '8')
      {
      	int letra, fondo, color;
			printf("\nEsta funcion escribe un caracter con los parámetros de color elegidos");
			printf("\nIntroduzca un caracter: ");
			letra = mi_getchar();
			printf("\nIntroduzca un color de fondo entre el 0 y el 7: ");
			fondo = mi_getchar()-48;
			printf("\nIntroduzca un color de letra entre el 0 y el 7: ");
			color = mi_getchar()-48;
			printf("\n");
			cputchar((char)letra, fondo, color);
		
			mi_pausa();
			printf("\n\n");
	   }
		else if(tmp == '9')
		{
			printf("\nEsta funcion obtiene un caracter de teclado y lo muestra en pantalla");
			getche();
			mi_pausa();
			printf("\n\n");
		}
		else if(tmp == 'a')
		{
				int x1,x2,y1,y2,j,i,fondo, color,letra;
				printf("\nEsta es la función extra 1: ");
				printf("\nIntroduzca la coordenada x de la esquina superior izquierda\n");
				x1 = mi_getchar()-48;
				printf("\nIntroduzca la coordenada y de la esquina superior izquierda\n");
				y1 = mi_getchar()-48;
				printf("\nIntroduzca la coordenada x de la esquina inferior derecha \n");
				x2 = mi_getchar()-48;
				printf("\nIntroduzca la coordenada y de la esquina inferior derecha\n");
				y2 = mi_getchar()-48;	
				printf("\nIntroduzca un color de fondo entre el 0 y el 7: ");
				fondo = mi_getchar()-48;
				printf("\nIntroduzca un color de letra entre el 0 y el 7: ");
				color = mi_getchar()-48;
				printf("\nPulsa cualquier letra para dibujar...");
				mi_pausa();
				
				clrscr();
				
				for(j = x1; j <= x2; j++)
				{
					if( j != x1 && j != x2 )
					{
							gotoxy(j,y1);
							cputchar('/', fondo, color);
							gotoxy(j,y2);
							cputchar('/', fondo, color);
					}
					else
					{
						for(i = y1; i <= y2; i++)
						{					
							gotoxy(j,i);
							cputchar('/', fondo, color);
						}
					}
				}
				mi_pausa();
		}
		else if(tmp != '1' && tmp != '2' && tmp != '3' && tmp != '4' && tmp != '5' && tmp != '6' && tmp != '7' && tmp != '8' && tmp != '9' && tmp != '0' && tmp != 'a')
		{
			printf("\nEl caracter introducido no es valido, prueba otra vez");
			mi_pausa();
			printf("\n\n");
		}
		else if(tmp == '0')
		{
			terminado = 1;
		}
		
		clrscr();
	}
	
	printf("\nCerrando el programa");
	mi_pausa();
	clrscr();
	
	return 0;
}
