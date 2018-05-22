#include <stdio.h>

char clave[5] = {'c','l','a','v','e'};

int login(){
	printf("Ingrese su contrasena de 5 digitos\n");
	int i;
	char c[5];
	int cantIntentos = 3;
	
	while(0 != cantIntentos){
		cantIntentos--;
		i = 5;
		do{
			i--;
			c[4 - i] = getch();
			printf("*");
		
		} while(i != 0);
	
		if(0 == strcmp(clave, c)){
	 		printf("\nBienvenido al sistema");
	 		return 1;
		}		
		else{
			printf("\nEntrada incorrecta. Intentos restantes: ");
			printf("%d", cantIntentos); 
			printf("\n");
		}		
	}
	return 0;
}

void salida(unsigned char x) {
    unsigned char i = 8;
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

};

void choque() {

};

void carrera() {

};

void opcion4() {

};

int main() {
    char entrada[1];
    if(login()){
    	do {
       		printf("\nMenu principal\n 1)Auto fantastico\n 2)Choque\n 3)Carrera\n 4)Opcion4\n 5)Salir\n");
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
    	} while (1);
	}
}
