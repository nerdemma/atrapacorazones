/*AtrapaCorazones*/
/*Idea: Valeria */
/*Desarrollado por Emmanuel D. Breyaue */
/*De Argentina con Amor!*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 15

int kbhit(void)
{
struct termios oldt, newt;
int ch;
int oldf;

if(tcgetattr(STDIN_FILENO, &oldt)==-1) return 0;
newt = oldt;
newt.c_lflag &= ~(ICANON | ECHO);
tcsetattr(STDIN_FILENO, TCSANOW, &newt);

oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

ch = getchar();

tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
fcntl(STDIN_FILENO, F_SETFL, oldf);

if(ch !=EOF)
	{
	ungetc(ch, stdin);
	return 1;
	}
	return 0;
}

int main()
{
int x_cesta = WIDTH / 2;
int x_corazon = rand() % WIDTH;
int y_corazon = 0;
int atrapadas = 0;
int perdidas = 0;
int jugando = 1;
int contador_caida=0;
int dificultad=3; /*si pierdes 3 corazones*/

srand((unsigned int)time(NULL));
	printf("\e[?25l");


while(jugando)
{
	printf("\033[H\033[J");
	printf("Puntos: %d | Perdidas: %d\n",atrapadas,perdidas);
	printf("Controles: [A] Izquierda [D] Derecha [Q] Salir\n\n");


// dibujar area del juego
	for(int y = 0; y < HEIGHT; y++)
	{
	for(int x=0; x < WIDTH; x++)
	{
	if(y == y_corazon && x == x_corazon)
	{
	printf("<3");
	}
	
	else if(y== HEIGHT - 1 && (x >= x_cesta -1 && x<= x_cesta + 1))
	{
	printf("=");
	}

	else {
	printf(" ");
	}

}
printf("\n");
}

// leer teclado

if(kbhit())
{
char tecla = getchar();
if((tecla == 'a' || tecla =='A') && x_cesta > 1) x_cesta--;
if((tecla == 'd' || tecla == 'D') && x_cesta < WIDTH -2) x_cesta++;
if(tecla == 'q' || tecla =='Q') jugando = 0;
}

// logica de la caida
static int contador_caida = 0;
if(++contador_caida >=2){
y_corazon++;
contador_caida=0;
}

// verificar colision o caida
if(y_corazon >= HEIGHT -1)
{
	if(x_corazon >= x_cesta -1 && x_corazon <= x_cesta +1)
	{
	atrapadas++;
	}

else 
{
perdidas++;
}

//resetear corazones
y_corazon = 0;
x_corazon = rand()% WIDTH;
}

//condiciones del juego
if(perdidas==dificultad)
{
jugando=0;
}


//velocidad de caida
usleep(60000);
} //end while

printf("\e[?25h");
printf("\n!Game Over\nResultado Final:%d atrapadas\n",atrapadas);
return 0;

}
