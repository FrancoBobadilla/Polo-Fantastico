#include <stdio.h>
#include <conio.h>
#include <stdlib.h>        //para system()

#define TMAX 5700				
#define TMED 1000
#define TMIN 200

char retardo(unsigned long int *);

void clearScreen();

int login();

void salida(unsigned char);

void autoFantastico(unsigned long int *);

void choque(unsigned long int *);

void policia(unsigned long int *);

void opcion4(unsigned long int *);

char arraycmp(const char *, const char *, unsigned int);

void main() {
    unsigned long int tiempoAutoFantastico = TMED;
    unsigned long int tiempoChoque = TMED;
    unsigned long int tiempoPolicia = TMED;
    unsigned long int tiempoOpcion4 = TMED;

    char entrada[1];
    if (login()) {
        do {
            clearScreen();
            printf("Menu principal\n 1)Auto fantastico\n 2)Choque\n 3)Policia\n 4)Opcion4\n 5)Salir\n");
            scanf("%c", entrada);
            switch (entrada[0]) {
                case '1':
                    autoFantastico(&tiempoAutoFantastico);
                    break;

                case '2':
                    choque(&tiempoChoque);
                    break;

                case '3':
                    policia(&tiempoPolicia);
                    break;

                case '4':
                    opcion4(&tiempoOpcion4);
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
	return 1;
    const char clave[] = {'c', 'l', 'a', 'v', 'e'};
    unsigned long int tiempoBienvenida = 100000;
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
    unsigned long int b = *a;
    int c;
    printf("%d",*a);   
    while (b) {
        b--;
        if (kbhit()) {
            c = getch();
            if (224 == c) {
                c = getch();
    			switch (c){
    				case 80:
    					if((*a) < TMAX){
                			(*a) = (*a) + 100;
							//falta alterear b
						}
						break;
						
					case 72:
						if((*a) > TMIN){
							(*a) = (*a) - 100;
							//falta alterear b
						}
						break;
						
					default:
						return 1;
						
				}
    		}else
    			return 1;
        }
    }
    return 0;
}

void autoFantastico(unsigned long int *tiempoAutoFantastico) {
    unsigned char i;
    clearScreen();
    printf("Auto fantastico!!!\n Para aumentar la velocidad presione la flecha para arriba\n Para disminuir la velocidad presione la flecha para abajo\n Para volver al menu presione cualquier otra tecla\n\n");
    while (1) {
        for (i = 128; i > 0; i >>= 1) {
            salida(i);
            if (retardo(tiempoAutoFantastico)) {
                //salida(0);
                return;
            }
        }
        for (i = 2; i < 128; i <<= 1) {
            salida(i);
            if (retardo(tiempoAutoFantastico)) {
                //salida(0);
                return;
            }
        }
    }
}

void choque(unsigned long int *tiempoChoque) {
    char i;    //notar que es char y no unsigned char
    unsigned char tablaChoque[] = {0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81};
    clearScreen();
    printf("Choque!!!\n Para aumentar la velocidad presione la flecha para arriba\n Para disminuir la velocidad presione la flecha para abajo\n Para volver al menu presione cualquier otra tecla\n\n");
    while (1) {
        for (i = 6; i >= 0; i--) {
            salida(tablaChoque[i]);
            if (retardo(tiempoChoque))
                return;
        }
    }
}

void policia(unsigned long int *tiempoPolicia) {
	char i;    
    unsigned char tablaPolicia[] = {
    								0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F,
    								0x00, 0x00, 0x00, 0xF0, 0xF0, 0xF0,
    								0x00, 0x0F, 0x00, 0x0F, 0x00, 0x0F,
    								0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF0
		    						};

    clearScreen();
    printf("Policia!!!\n Para aumentar la velocidad presione la flecha para arriba\n Para disminuir la velocidad presione la flecha para abajo\n Para volver al menu presione cualquier otra tecla\n\n");
    // while (1) {
    //     for (i = 23; i >= 0; i--) {
    //         salida(tablaPolicia[i]);
    //         if (retardo(tiempoPolicia))
    //             return;
    //     }
    // }

    while(1){
    	for (i = 3; i > 0; i--)
    	{
    		salida(0xF0);
    		if (retardo(tiempoPolicia))
            	    return;
    		salida(0x00);
    		if (retardo(tiempoPolicia))
                	return;
    	}
    	for (i = 3; i > 0; i--)
    	{
	    	salida(0x0F);
    		if (retardo(tiempoPolicia))
                	return;
    		salida(0x00);
    		if (retardo(tiempoPolicia))
    	            return;
	    }
    	for (i = 3; i > 0; i--)
    	{
    		salida(0xF0);
    		if (retardo(tiempoPolicia))
        	        return;
    	}
    	for (i = 3; i > 0; i--)
    	{
    		salida(0x00);
    		if (retardo(tiempoPolicia))
        	        return;
    	}
    	for (i = 3; i > 0; i--)
    	{
    		salida(0x0F);
    		if (retardo(tiempoPolicia))
        	        return;
    	}
		for (i = 3; i > 0; i--)
    	{
    		salida(0x00);
    		if (retardo(tiempoPolicia))
        	        return;
    	}
	}
}

void opcion4(unsigned long int *tiempoOpcion4) {

}

char arraycmp(const char *a, const char *b, unsigned int tamanio) {
    int i;
    for (i = 0; i < tamanio; ++i) {
        if (a[i] != b[i])
            return 1;
    }
    return 0;
}
