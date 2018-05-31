#include <stdio.h>
#include <conio.h>

unsigned long int tiempoAutoFantastico = 1000;
unsigned long int tiempoChoque = 1000;
unsigned long int tiempoCarrera = 1000;
unsigned long int tiempoOpcion4 = 1000;
const char clave[] = {'c','l','a','v','e'};
unsigned char tablaChoque[] = {0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81};
	
char retardo(unsigned long int *);

void clearScreen();

int login();

void salida(unsigned char);

void autoFantastico();

void choque();

void carrera();

void opcion4();

void main() {	
    char entrada[1];
    if (login()) {
        do {
            clearScreen();
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
                    printf("\nEntrada invalida\nSeleccione nuevamente una opci�n\n");
                    break;
            }
        } while (entrada[0] != '5');
    }
}



void clearScreen() {
   system("cls");
   //clrscr();
}

int login() {
	return 1; 										/**//**//**//**//**//**//**//**//**/
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
            clearScreen();
            printf("Bienvenido al sistema");
            retardo(& tiempoAutoFantastico);
            return 1;
        } else {
            printf("\nEntrada incorrecta. Intentos restantes: ");
            printf("%d", cantIntentos);
            printf("\n");
        }
    }
    return 0;
}

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
}

char retardo(unsigned long int *a) {
	unsigned long int b = * a;
	while (b) {
        b--;
        
        if(kbhit()){
        	char c = getch();
        	if('x' == c){
        		b = b * 2;
        		(*a) = (*a) * 2;
			}else{
				if('y' == c){
					b = b / 2;
					(*a) = (*a) / 2;
				}else{
					return 1;
				}
			}
		}
		
    }
    return 0;
}

void autoFantastico() {
    unsigned char i;
    clearScreen();
    printf("Auto fantastico!!!\n Para aumentar la velocidad presione la flecha para arriba\n Para disminuir la velocidad presione la flecha para abajo\n Para volver al menu presione cualquier otra tecla\n\n");
    while (1) {
        for (i = 128; i > 0; i >>= 1) {
            salida(i);
            if (retardo(& tiempoAutoFantastico))
                return;
        }
        for(i= 2; i < 128; i <<= 1){
        	salida(i);
            if (retardo(& tiempoAutoFantastico))
                return;
		}
    }
}

void choque() {
	char i;	//notar que es char y no unsigned char
	clearScreen();
	printf("Choque!!!\n Para aumentar la velocidad presione la flecha para arriba\n Para disminuir la velocidad presione la flecha para abajo\n Para volver al menu presione cualquier otra tecla\n\n");
    while(1){
    	 for (i = 6; i >= 0; i--) {
            salida(tablaChoque[i]);
            if (retardo(& tiempoChoque))
                return;
        }
	}
}

void carrera() {

}

void opcion4() {

}
