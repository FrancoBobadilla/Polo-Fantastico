#include <stdio.h>
#include <conio.h>

unsigned long int TIEMPO = 3000;
char clave[5] = {'c', 'l', 'a', 'v', 'e'};

char retardo(unsigned long int a) {
    while (a) {
        a--;
        if (kbhit())return 1;
    }
    return 0;
};

int login() {
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

        if (0 == strcmp(clave, c)) {
            system("cls");
            printf("Bienvenido al sistema");
            retardo(TIEMPO * 3);
            return 1;
        } else {
            printf("\nEntrada incorrecta. Intentos restantes: ");
            printf("%d", cantIntentos);
            printf("\n");
        }
    }
    return 0;
};

void salida(unsigned char x) {
    unsigned char i = 8;
    printf("\r");
    do {
        i--;
        if ((x & (1 << i)) != 0) {
            printf("*");
        } else {
            printf("_");
        }
    } while (i != 0);
};

void autoFantastico() {
    unsigned char i;
    system("cls");
    while (1) {
        for (i = 128; i > 0; i >>= 1) {
            salida(i);
            if (retardo(TIEMPO))
                return;
        }
        for (i = 64; i > 1; i >>= 1) {
            salida(128 / i);
            retardo(TIEMPO);
        }
    }
};

void choque() {

};

void carrera() {

};

void opcion4() {

};

void main() {
    char entrada[1];
    if (login()) {
        do {
            system("cls");
            printf("Menu principal\n 1)Auto fantastico\n 2)Choque\n 3)Carrera\n 4)Opcion4\n 5)Salir\n");
            scanf("%c", entrada);
            //printf("%c", entrada[0]);
            switch (entrada[0]) {
                case '1':
                    autoFantastico();
                    break;

                case '2':
                    choque();
                    break;

                case '3':
                    carrera();
                    break;

                case '4':
                    opcion4();
                    break;

                case '5':
                    break;

                default:
                    printf("\nEntrada invalida\nSeleccione nuevamente una opciÃ³n\n");
                    break;
            }
        } while (entrada[0] != '5');
    }
}