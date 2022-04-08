#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

#define DELAY 60000

int main(int argc, char *argv[]){

int ch = 0;
int rows, cols;

//Bola
int xb = 50;
int yb = 15;

int next_x = 0;
int directionx = 1;

int next_y = 0;
int directiony = 1;

//Puntuación
int marcador1 = 0;
int marcador2 = 0;
int ganador1 = 0;
int ganador2 = 0;

//Jugador 1

int xj1 = 5, yj1 = 11;

//Jugador 2

int xj2 = 95, yj2 = 11;

initscr();

if (has_colors() == FALSE) {
    endwin();
    printf("El terminal no tiene soporte de color \n");
    exit(1);
}

start_color();  
init_pair(1, COLOR_YELLOW, COLOR_BLACK);
clear();

refresh();  
getmaxyx(stdscr, rows, cols);

WINDOW *window1 = newwin(rows,cols,0,0);
wbkgd(window1, COLOR_PAIR(1));
box(window1, '|', '-');

mvwprintw(window1, 3, cols/2-42, "PPPPPPPPPPPPPPPPP        OOOOOOOOO     NNNNNNNN        NNNNNNNN        GGGGGGGGGGGGG");
mvwprintw(window1, 4, cols/2-42, "P::::::::::::::::P     OO:::::::::OO   N:::::::N       N::::::N     GGG::::::::::::G");
mvwprintw(window1, 5, cols/2-42, "P::::::PPPPPP:::::P  OO:::::::::::::OO N::::::::N      N::::::N   GG:::::::::::::::G");
mvwprintw(window1, 6, cols/2-42, "PP:::::P     P:::::PO:::::::OOO:::::::ON:::::::::N     N::::::N  G:::::GGGGGGGG::::G");
mvwprintw(window1, 7, cols/2-42, "  P::::P     P:::::PO::::::O   O::::::ON::::::::::N    N::::::N G:::::G       GGGGGG");
mvwprintw(window1, 8, cols/2-42, "  P::::P     P:::::PO:::::O     O:::::ON:::::::::::N   N::::::NG:::::G ");
mvwprintw(window1, 9, cols/2-42, "  P::::PPPPPP:::::P O:::::O     O:::::ON:::::::N::::N  N::::::NG:::::G");
mvwprintw(window1, 10, cols/2-42, "  P:::::::::::::PP  O:::::O     O:::::ON::::::N N::::N N::::::NG:::::G    GGGGGGGGGG");
mvwprintw(window1, 11, cols/2-42, "  P::::PPPPPPPPP    O:::::O     O:::::ON::::::N  N::::N:::::::NG:::::G    G::::::::G");
mvwprintw(window1, 12, cols/2-42, "  P::::P            O:::::O     O:::::ON::::::N   N:::::::::::NG:::::G    GGGGG::::G");
mvwprintw(window1, 13, cols/2-42, "  P::::P            O:::::O     O:::::ON::::::N    N::::::::::NG:::::G        G::::G");
mvwprintw(window1, 14, cols/2-42, "  P::::P            O::::::O   O::::::ON::::::N     N:::::::::N G:::::G       G::::G");
mvwprintw(window1, 15, cols/2-42, "PP::::::PP          O:::::::OOO:::::::ON::::::N      N::::::::N  G:::::GGGGGGGG::::G");
mvwprintw(window1, 16, cols/2-42, "P::::::::P           OO:::::::::::::OO N::::::N       N:::::::N   GG:::::::::::::::G");
mvwprintw(window1, 17, cols/2-42, "P::::::::P             OO:::::::::OO   N::::::N        N::::::N     GGG::::::GGG:::G");
mvwprintw(window1, 18, cols/2-42, "PPPPPPPPPP               OOOOOOOOO     NNNNNNNN         NNNNNNN        GGGGGG   GGGG");


mvwprintw(window1, rows/2, cols/2-16, "EL JUGADOR (1) SE MUEVE CON W Y S");
mvwprintw(window1, rows/2+1, cols/2-16, "EL JUGADOR (2) SE MUEVE CON O Y L");
mvwprintw(window1, rows/2+5, cols/2-10, "PRESS 'INTRO' TO PLAY");

wrefresh(window1);

getch();
cbreak();
noecho();
curs_set(FALSE);
nodelay(stdscr, TRUE);

while(ganador1 == 0 && ganador2 == 0) {
    clear();
    refresh();

    //Dibujar el campo
    WINDOW *window2 = newwin(30,100,0,0);
    wbkgd(window2, COLOR_PAIR(1));
    box(window2, '|', '-');

    wrefresh(window2);

    for(int i = 1; i < 29; i++)
    {
        mvprintw(i, 50, "|");
    }

    //Marcador
    mvprintw(31, 47, "MARCADOR");

    if(marcador1 == 0)
    {
        mvprintw(32, 24, "0");
    }
    else if(marcador1 == 1)
    {
        mvprintw(32, 24, "1");
    }
    else if(marcador1 == 2)
    {
        mvprintw(32, 24, "2");
    }
    else if(marcador1 == 3)
    {
        mvprintw(32, 24, "3");
    }
    else if(marcador1 == 4)
    {
        mvprintw(32, 24, "4");
    }

    if(marcador2 == 0)
    {
        mvprintw(32, 74, "0");
    }
    else if(marcador2 == 1)
    {
        mvprintw(32, 74, "1");
    }
    else if(marcador2 == 2)
    {
        mvprintw(32, 74, "2");
    }
    else if(marcador2 == 3)
    {
        mvprintw(32, 74, "3");
    }
    else if(marcador2 == 4)
    {
        mvprintw(32, 74, "4");
    }
    
    //Crear los objetos
    for(int i = 0; i < 8; i++)
    {
        mvprintw(yj1+i, xj1, "#");
    }

    for(int i = 0; i < 8; i++)
    {
        mvprintw(yj2+i, xj2, "#");
    }

    mvprintw(yb, xb, "0");

    refresh();

    ch = getch();

    // Mover las barras    
    if(ch == 'W' || ch == 'w')
    {
        if(yj1 != 1)
        {
            yj1 -= 1;
        }
    }
    else if(ch == 'S' || ch == 's')
    {
        if(yj1 != 21)
        {
            yj1 += 1;
        }
    }

    if(ch == 'O' || ch == 'o')
    {
        if(yj2 != 1)
        {
            yj2 -= 1;
        }
    }
    else if(ch == 'L' || ch == 'l')
    {
        if(yj2 != 21)
        {
            yj2 += 1;
        }
    }

    usleep(DELAY);

    next_x = xb + directionx;
 	next_y = yb + directiony;

    //Rebote con las paredes
 	if (next_x >= 100 || next_x < 0) {
 		xb = 50;
        yb = 15;
        directionx*= -1;
        yb+= directiony;
        if(next_x >= 100)
        {
            marcador1 +=1;
        }
        else if(next_x < 0)
        {
            marcador2 +=1;
        } 
 	}
    else
    {
        xb+= directionx;
    }

 	if (next_y >= 29 || next_y < 1) {
 		directiony*= -1;
 	} else {
 		yb+= directiony;
 	}

    //Rebote con los jugadores
    if ((next_x == xj1 && (next_y == yj1 || next_y == yj1+1 || next_y == yj1+2 || next_y == yj1+3 || next_y == yj1+4 || next_y == yj1+5 || next_y == yj1+6 ||
    next_y == yj1+7))|| (next_x == xj2 && (next_y == yj2 || next_y == yj2+1 || next_y == yj2+2 || next_y == yj2+3 || next_y == yj2+4 || next_y == yj2+5 ||
    next_y == yj2+6 || next_y == yj2+7))) {
        directionx*= -1;
 	}

    if(marcador1 == 5)
    {
        ganador1 = 1;
    }

    if(marcador2 == 5)
    {
        ganador2 = 1;
    }
}

if(ganador1 == 1)
{
    mvprintw(32, 24, "5");
    mvprintw(31, cols/2-8, "GANA EL JUGADOR 1");
}
else if(ganador2 == 1)
{
    mvprintw(32, 74, "5");
    mvprintw(31, cols/2-8, "GANA EL JUGADOR 2");
}

nodelay(stdscr, FALSE);
getch();
endwin();
return 0;
}