#include <stdio.h>
#include <conio.h>
#include <stdlib.h> //para system()
#include "EasyPIO.h"

#define TMAX 1600
#define TMED 900
#define TMIN 100
#define INTERVALO 100

char login();

void salida(unsigned char, unsigned long int);

char retardo(unsigned long int*);

void autoFantastico(unsigned long int*); // algoritmo

void choque(unsigned long int*); // tabla

void policia(unsigned long int*); // tabla

void piedraEstanque(unsigned long int*); // tabla

void embotellamiento(unsigned long int*); //algoritmo

inline void clearScreen();

char arraycmp(const char*, const char*, unsigned int);

void main()
{
    unsigned long int tiempoAutoFantastico = TMED;
    unsigned long int tiempoChoque = TMED;
    unsigned long int tiempoPolicia = TMED;
    unsigned long int tiempoPiedraEstanque = TMED;
    unsigned long int tiempoEmbotellamiento = TMED;
    unsigned long int tiempoError = TMAX;
    char entrada;
    if (login())
    {
        do
        {
            clearScreen();
            printf("Menu principal\n 1)Auto fantastico\n 2)Choque\n 3)Policia\n 4)Piedra cayendo sobre estanque\n 5)Embotellamiento\n 6)Salir\n");
            entrada = getch();
            switch (entrada)
            {
                case '1':
                    autoFantastico(&tiempoAutoFantastico); // algoritmo
                    salida(0, tiempoAutoFantastico);
                    break;

                case '2':
                    choque(&tiempoChoque); // tabla
                    salida(0, tiempoChoque);
                    break;

                case '3':
                    policia(&tiempoPolicia); // tabla
                    salida(0, tiempoPolicia);
                    break;

                case '4':
                    piedraEstanque(&tiempoPiedraEstanque); // tabla
                    salida(0, tiempoPiedraEstanque);
                    break;

                case '5':
                    embotellamiento(&tiempoEmbotellamiento); // algoritmo
                    salida(0, tiempoEmbotellamiento);
                    break;

                case '6':
                    break;

                default:
                    clearScreen();
                    printf("\n\n     ENTRADA INVALIDA");
                    retardo(&tiempoError);
                    break;
            }
        } while (entrada != '6');
    }
}

char login()
{
    const char clave[] = { 'c', 'l', 'a', 'v', 'e' };
    unsigned long int tiempoBienvenida = TMAX * 2;
    printf("Ingrese su password de 5 digitos\n");
    int i;
    char c[5];
    int cantIntentos = 3;
    while (cantIntentos != 0)
    {
        cantIntentos--;
        i = 5;
        do
        {
            i--;
            c[4 - i] = getch();
            printf("*");

        } while (i != 0);

        if (0 == arraycmp(clave, c, 5))
        {
            clearScreen();
            printf(" ----------------------- ");
            printf("\n");
            printf("| Bienvenido al sistema |");
            printf("\n");
            printf(" ----------------------- ");
            printf("\n");
            retardo(&tiempoBienvenida);
            return 1;
        }
        else
        {
            printf("\nPassword no valida. Intentos restantes: ");
            printf("%d", cantIntentos);
            printf("\n");
        }
    }
    retardo(&tiempoBienvenida);
    return 0;
}

void salida(unsigned char x, unsigned long int tiempo)
{
    unsigned char i = 8;
    printf("\r");
    do
    {
        i--;
        if ((x & (1 << i)) != 0)
            printf("*"); // en caso de implementarse sobre LEDs, deberia cambiarse por la funcion de
                         // salida adecuada
        else
            printf("_"); // en caso de implementarse sobre LEDs, deberia cambiarse por la funcion de
                         // salida adecuada
    } while (i != 0);

    // impreson de velocidad actual
    printf("   Retardo minimo: ");
    printf("%d", TMIN);
    printf("   Retardo actual: ");
    printf("%d", tiempo);
    printf("   Retardo maximo: ");
    printf("%d", TMAX);
    printf("   ");
}

char retardo(unsigned long int* a)
{
    unsigned long int b = *a;
    int c;
    while (b--)
    {
        if (kbhit())
        {
            c = getch();
            // 224: teclas de las fechas de navegacion principales, 0: funciones especiales, flechas de navegacion secundarias (del teclado numerico, cuadno no esta activado el bloc num) incluidas
            if (c == 224 || c == 0)
            {
                if (kbhit())
                    c = getch();
                else
                    return 0; // en caso de que el usuario ingrese (no se como) el char 0 (NULL)
                switch (c)
                {
                    case 80:
                        if ((*a) < TMAX)
                        {
                            b = b / (*a);
                            (*a) = (*a) + INTERVALO;
                            b = b * (*a);
                        }
                        break;
                    case 72:
                        if ((*a) > TMIN)
                        {
                            b = b / (*a);
                            (*a) = (*a) - INTERVALO;
                            b = b * (*a);
                        }
                        break;
                    default:
                        return 1;
                }
            }
            else
            {
                if (kbhit())
                    getch(); // en caso de que el usuario ingrese un doble char, y que el primero no
                             // sea "0" ni "224"
                return 1;
            }
        }
    }
    return 0;
}

// secuencia por algoritmo
void autoFantastico(unsigned long int* direccionTiempo)
{
    unsigned char i;
    clearScreen();
    printf("Auto fantastico!!!\n Para aumentar la velocidad presione la flecha para arriba\n Para disminuir la velocidad presione la flecha para abajo\n Para volver al menu presione cualquier otra tecla\n\n");

    while (1)
    {
        for (i = 128; i > 0; i >>= 1)
        {
            salida(i, *direccionTiempo);
            if (retardo(direccionTiempo))
                return;
        }
        for (i = 2; i < 128; i <<= 1)
        {
            salida(i, *direccionTiempo);
            if (retardo(direccionTiempo))
                return;
        }
    }
}

// secuencia por tabla
void choque(unsigned long int* direccionTiempo)
{
    char i; 
    unsigned char tablaChoque[] = { 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81 };
    clearScreen();
    printf("Choque!!!\n Para aumentar la velocidad presione la flecha para arriba\n Para disminuir la velocidad presione la flecha para abajo\n Para volver al menu presione cualquier otra tecla\n\n");
    
    while (1)
        for (i = 6; i >= 0; i--)
        {
            salida(tablaChoque[i], *direccionTiempo);
            if (retardo(direccionTiempo))
                return;
        }
}

// secuencia por tabla
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

    while (1)
        for (i = 31; i >= 0; i--)
        {
            salida(tablaPolicia[i], *direccionTiempo);
            if (retardo(direccionTiempo))
                return;   
        }
}

// secuencia por tabla
void piedraEstanque(unsigned long int* direccionTiempo)
{
    char i;
    unsigned char tablaPiedraEstanque[] = { 0x00, 0x00, 0x18, 0x18, 
                                            0x18, 0x24, 0x24, 0x24, 
                                            0x42, 0x42, 0x42, 0x81, 
                                            0x81, 0x42, 0x24, 0x18, 
                                            0x10, 0x20, 0x40, 0x80 };
    clearScreen();
    printf("Piedra cayendo sobre estanque!!!\n Para aumentar la velocidad presione la flecha para arriba\n Para disminuir la velocidad presione la flecha para abajo\n Para volver al menu presione cualquier otra tecla\n\n");
    while (1)
        for (i = 19; i >= 0; i--)
        {
            salida(tablaPiedraEstanque[i], *direccionTiempo);
            if (retardo(direccionTiempo))
                return;
        }
}

// secuencia por algoritmo
void embotellamiento(unsigned long int* direccionTiempo)
{
    unsigned char i;
    clearScreen();
    printf("Embotellamiento!!!\n Para aumentar la velocidad presione la flecha para arriba\n Para disminuir la velocidad presione la flecha para abajo\n Para volver al menu presione cualquier otra tecla\n\n");
    int j;

    unsigned char potenciasDeDos[] = { 1, 2, 4, 8, 16 };
    // para no incluir math.h

    while (1)
    {
        i = 128;
        // avanzan todos
        for (j = 12; j >= 0; j--)
        {
            salida(i, *direccionTiempo);
            if (retardo(direccionTiempo))
                 return;
            i >>= 1;
            if (i < 64)
                i = i | 128;
        }

        // se frena el primero
        for (j = 5; j > 0; j--)
        {
            salida(i, *direccionTiempo); // i = 85
            if (retardo(direccionTiempo))
                return;
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
                if (retardo(direccionTiempo))
                    return;
            }
            g = 6 * potenciasDeDos[count];
            count += 2;
        }

        // espera para la siguiente ola de autos
        for (j = 5; j > 0; j--)
        {
            salida(i, *direccionTiempo); // i = 85
            if (retardo(direccionTiempo))
                return;
        }
    }
}

inline void clearScreen()
{
    system("cls");
}

 // usada unicamente en funcion login()
char arraycmp(const char* a, const char* b, unsigned int tamanio)
{
    int i;
    for (i = 0; i < tamanio; i++)
        if (a[i] != b[i])
            return 1; // retorna 1 si no son iguales
    return 0; // retorna 0 si son iguales
}
