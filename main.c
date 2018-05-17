#include <stdio.h>

void salida(unsigned char x) {

};

void autoFantastico() {

};

void choque() {

};

void carrera() {

};

void opcion4() {

};

int main() {
    char entrada[1];
    while (1 == 1) {
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
                return 1;

            default:
                printf("\nEntrada invalida\nSeleccione nuevamente una opción\n");
                break;
        }
    }
}