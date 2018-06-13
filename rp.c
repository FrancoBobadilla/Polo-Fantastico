#include <stdio.h>
#include <conio.h>
#include <stdlib.h> //para system()
#include "EasyPIO.h"

#define TMAX 1600
#define TMED 900
#define TMIN 100
#define INTERVALO 100

void embotellamiento(unsigned long int*);

void salida(unsigned char);

char leerLlaves();

char led[] = { 14,15,18,23,24,25,8,7 };

char llaves[] = { 12,16,20,21 };

int main(){
	pioInit();
	pinMode(14, OUTPUT);
	pinMode(15, OUTPUT);
	pinMode(18, OUTPUT);
	pinMode(23, OUTPUT);
	pinMode(24, OUTPUT);
	pinMode(25, OUTPUT);
	pinMode(8, OUTPUT);
	pinMode(7, OUTPUT);

	pinMode(12, INPUT);
	pinMode(16, INPUT);
	pinMode(20, INPUT);
	pinMode(21, INPUT);
;

	while(leerLlaves() != 15){
		switch(leerLlaves()){
			case 1:
				embotellamiento(500);
				break;
			case 2:
				policia(500);
				break;
				
			default:
				break;
		}
		
	}
	
}

void embotellamiento(unsigned long int direccionTiempo)
{
    unsigned char i;
    clearScreen();
    printf("Embotellamiento!!!\n Para aumentar la velocidad presione la flecha para arriba\n Para disminuir la velocidad presione la flecha para abajo\n Para volver al menu presione cualquier otra tecla\n\n");
    int j;

    unsigned char potenciasDeDos[] = { 1, 2, 4, 8, 16 };
    // para no incluir math.h

    while (!leerLlaves())
    {
        i = 128;
        // avanzan todos
        for (j = 12; j >= 0; j--)
        {
            salida(i, *direccionTiempo);
      		delayMillis(direccionTiempo);
            i >>= 1;
            if (i < 64)
                i = i | 128;
        }

        // se frena el primero
        for (j = 5; j > 0; j--)
        {
            salida(i, *direccionTiempo); // i = 85
            delayMillis(direccionTiempo);
     
        }

        unsigned char g = 1;
        unsigned char count = 0;

        while (i > 0)
        {
            while (g > 0)
            {
                i ^= g;
                g >>= 1;
                salida(i, *direccionTiempo);
                if (delayMillis(direccionTiempo))
                    return;
            }
            g = 6 * potenciasDeDos[count];
            count += 2;
        }

        // espera para la siguiente ola de autos
        for (j = 5; j > 0; j--)
        {
            salida(i, *direccionTiempo); // i = 85
            delayMillis(direccionTiempo);
        }
    }
}

void policia(unsigned long int* direccionTiempo)
{
    char i;
    clearScreen();
    printf("Policia!!!\n Para aumentar la velocidad presione la flecha para arriba\n Para disminuir la velocidad presione la flecha para abajo\n Para volver al menu presione cualquier otra tecla\n\n");

    unsigned char tablaPolicia[] = {
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0xF0,
                                    0x00, 0x00, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0x0F,
                                    0x00, 0x00, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF0
                                    };  

    while (!leerLlaves())
        for (i = 31; i >= 0; i--)
        {
            salida(tablaPolicia[i]);
            delayMillis(direccionTiempo);
        }
}

void salida(unsigned char x)
{
    unsigned char i = 8;
    do
    {
		i--;  
        digitalWrite(led[i], (x & (1 << i)));        
    } while (i != 0);
}

char leerLlaves(){
	char r = 0;
	unsigned i = 3;
	do{
		r |= digitalRead(llave[i]) << i;
	} while(i != 0)
}

