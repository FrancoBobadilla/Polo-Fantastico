#include <stdio.h>
#include <conio.h>
#include <stdlib.h>        //para system()

#define TMAX 1000
#define TMED 500
#define TMIN 100
#define INTERVALO 100

char retardo(unsigned long int *);

void clearScreen();

int login();

void salida(unsigned char, unsigned long int);

void autoFantastico(unsigned long int *);    //algoritmo

void choque(unsigned long int *);    //tabla

void policia(unsigned long int *);    //algoritmo

void piedraEstanque(unsigned long int *);    //tabla

char arraycmp(const char *, const char *, unsigned int);

void main() {
    unsigned long int tiempoAutoFantastico = TMED;
    unsigned long int tiempoChoque = TMED;
    unsigned long int tiempoPolicia = TMED;
    unsigned long int tiempoPiedraEstanque = TMED;
    unsigned long int tiempoError = TMAX;
    char entrada;
    if (login()) {
        do {
            clearScreen();
            printf("Menu principal\n 1)Auto fantastico\n 2)Choque\n 3)Policia\n 4)Piedra cayendo sobre estanque\n 5)Salir\n");
            entrada = getch();
            switch (entrada) {
                case '1':
                    autoFantastico(&tiempoAutoFantastico);    //algoritmo
                    break;

                case '2':
                    choque(&tiempoChoque);    //tabla
                    break;

                case '3':
                    policia(&tiempoPolicia);    //algoritmo
                    break;

                case '4':
                    piedraEstanque(&tiempoPiedraEstanque);    //tabla
                    break;

                case '5':
                    break;

                default:
                    clearScreen();
                    printf("\n\n     ENTRADA INVALIDA");
                    retardo(&tiempoError);
                    break;
            }
        } while (entrada != '5');
    }
}

void clearScreen() {
    system("cls");
}

int login() {
    const char clave[] = {'c', 'l', 'a', 'v', 'e'};
    unsigned long int tiempoBienvenida = TMAX;
    printf("Ingrese su contrasena de 5 digitos\n");
    int i;
    char c[5];
    int cantIntentos = 3;
    while (cantIntentos != 0) {
        cantIntentos--;
        i = 5;
        do {
            i--;
            c[4 - i] = getch();
            printf("*");

        } while (i != 0);
        if (0 == arraycmp(clave, c, 5)) {
            clearScreen();
            printf(" ----------------------- ");
            printf("\n");
            printf("| Bienvenido al sistema |");
            printf("\n");
            printf(" ----------------------- ");
            printf("\n");
            retardo(&tiempoBienvenida);
            return 1;
        } else {
            printf("\nEntrada incorrecta. Intentos restantes: ");
            printf("%d", cantIntentos);
            printf("\n");
        }
    }
    return 0;
}

void salida(unsigned char x, unsigned long int tiempo) {
    unsigned char i = 8;
    printf("\r");
    do {
        i--;
        if ((x & (1 << i)) != 0) {
            printf("*"); //en caso de implementarse sobre LEDs, deberia cambiarse por la funcion de salida adecuada
        } else {
            printf("_"); //en caso de implementarse sobre LEDs, deberia cambiarse por la funcion de salida adecuada
        }
    } while (i != 0);

    //impreson de velocidad actual
    printf("   Retardo minimo: ");
    printf("%d", TMIN);
    printf("   Retardo actual: ");
    printf("%d", tiempo);
    printf("   Retardo maximo: ");
    printf("%d", TMAX);
    printf("   ");
}

char retardo(unsigned long int *a) {
    unsigned long int b = *a;
    int c;
    while (b--) {
        if (kbhit()) {
            c = getch();
            if (c == 224 || c ==
                            0) {    //224: teclas de las fechas de navegacion principales, 0: funciones especiales, flechas de navegacion secundarias (del teclado numerico, cuadno no esta activado el bloc num) incluidas
                if (kbhit())
                    c = getch();
                else
                    return 0;    //en caso de que el usuario ingrese (no se como) el char 0 (NULL)
                switch (c) {
                    case 80:
                        if ((*a) < TMAX) {
                            b = b / (*a);
                            (*a) = (*a) + INTERVALO;
                            b = b * (*a);
                        }
                        break;
                    case 72:
                        if ((*a) > TMIN) {
                            b = b / (*a);
                            (*a) = (*a) - INTERVALO;
                            b = b * (*a);
                        }
                        break;
                    default:
                        return 1;
                }
            } else {
                if (kbhit())
                    getch();    //en caso de que el usuario ingrese un doble char, y que el primero no sea "0" ni "224"
                return 1;
            }

        }
    }
    return 0;
}

void autoFantastico(unsigned long int *direccionTiempo) {    //algoritmo
    unsigned char i;
    clearScreen();
    printf("Auto fantastico!!!\n Para aumentar la velocidad presione la flecha para arriba\n Para disminuir la velocidad presione la flecha para abajo\n Para volver al menu presione cualquier otra tecla\n\n");
    while (1) {
        for (i = 128; i > 0; i >>= 1) {
            salida(i, *direccionTiempo);
            if (retardo(direccionTiempo)) {
                salida(0, *direccionTiempo);
                return;
            }
        }
        for (i = 2; i < 128; i <<= 1) {
            salida(i, *direccionTiempo);
            if (retardo(direccionTiempo)) {
                salida(0, *direccionTiempo);
                return;
            }
        }
    }
}

void choque(unsigned long int *direccionTiempo) {
    char i;    //notar que es char y no unsigned char
    unsigned char tablaChoque[] = {0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81};
    clearScreen();
    printf("Choque!!!\n Para aumentar la velocidad presione la flecha para arriba\n Para disminuir la velocidad presione la flecha para abajo\n Para volver al menu presione cualquier otra tecla\n\n");
    while (1) {
        for (i = 6; i >= 0; i--) {
            salida(tablaChoque[i], *direccionTiempo);
            if (retardo(direccionTiempo)) {
                salida(0, *direccionTiempo);
                return;
            }
        }
    }
}

void policia(unsigned long int *direccionTiempo) {    //algoritmo
    char i;
    clearScreen();
    printf("Policia!!!\n Para aumentar la velocidad presione la flecha para arriba\n Para disminuir la velocidad presione la flecha para abajo\n Para volver al menu presione cualquier otra tecla\n\n");

    /*
	unsigned char tablaPolicia[] = {
            0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F,
            0x00, 0x00, 0x00, 0xF0, 0xF0, 0xF0,
            0x00, 0x0F, 0x00, 0x0F, 0x00, 0x0F,
            0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF0
    };
    */

    while (1) {
        for (i = 3; i > 0; i--) {
            salida(0xF0, *direccionTiempo);
            if (retardo(direccionTiempo)) {
                salida(0, *direccionTiempo);
                return;
            }
            salida(0x00, *direccionTiempo);
            if (retardo(direccionTiempo)) {
                salida(0, *direccionTiempo);
                return;
            }
        }

        salida(0x00, *direccionTiempo);
        if (retardo(direccionTiempo)) {
            salida(0, *direccionTiempo);
            return;
        }

        for (i = 3; i > 0; i--) {
            salida(0x0F, *direccionTiempo);
            if (retardo(direccionTiempo)) {
                salida(0, *direccionTiempo);
                return;
            }
            salida(0x00, *direccionTiempo);
            if (retardo(direccionTiempo)) {
                salida(0, *direccionTiempo);
                return;
            }
        }

        salida(0x00, *direccionTiempo);
        if (retardo(direccionTiempo)) {
            salida(0, *direccionTiempo);
            return;
        }

        for (i = 3; i > 0; i--) {
            salida(0xF0, *direccionTiempo);
            if (retardo(direccionTiempo)) {
                salida(0, *direccionTiempo);
                return;
            }
        }

        for (i = 3; i > 0; i--) {
            salida(0x00, *direccionTiempo);
            if (retardo(direccionTiempo)) {
                salida(0, *direccionTiempo);
                return;
            }
        }

        salida(0x00, *direccionTiempo);
        if (retardo(direccionTiempo)) {
            salida(0, *direccionTiempo);
            return;
        }

        for (i = 3; i > 0; i--) {
            salida(0x0F, *direccionTiempo);
            if (retardo(direccionTiempo)) {
                salida(0, *direccionTiempo);
                return;
            }
        }

        for (i = 3; i > 0; i--) {
            salida(0x00, *direccionTiempo);
            if (retardo(direccionTiempo)) {
                salida(0, *direccionTiempo);
                return;
            }
        }
        salida(0x00, *direccionTiempo);
        if (retardo(direccionTiempo)) {
            salida(0, *direccionTiempo);
            return;
        }
    }
}

void piedraEstanque(unsigned long int *direccionTiempo) {
    char i;    //notar que es char y no unsigned char
    unsigned char tablaPiedraEstanque[] = {0x00, 0x00, 0x18, 0x18, 0x18, 0x24, 0x24, 0x24, 0x42, 0x42, 0x42, 0x81, 0x81,
                                           0x42, 0x24, 0x18, 0x10, 0x20, 0x40, 0x80};
    clearScreen();
    printf("Piedra cayendo sobre estanque!!!\n Para aumentar la velocidad presione la flecha para arriba\n Para disminuir la velocidad presione la flecha para abajo\n Para volver al menu presione cualquier otra tecla\n\n");
    while (1) {
        for (i = 20; i >= 0; i--) {
            salida(tablaPiedraEstanque[i], *direccionTiempo);
            if (retardo(direccionTiempo)) {
                salida(0, *direccionTiempo);
                return;
            }
        }
    }
}

char arraycmp(const char *a, const char *b, unsigned int tamanio) {    //usada unicamente en funcion login()
    int i;
    for (i = 0; i < tamanio; i++) {
        if (a[i] != b[i])
            return 1;    //retorna 1 si no son iguales
    }
    return 0;    //retorna 0 si son iguales
}
