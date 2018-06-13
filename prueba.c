#include "EasyPIO.h"
#include <stdio.h>

int pinSalidas[] = {14, 15, 18, 23, 24, 25, 8, 7};

void main(void){
	pioInit();
	
	for(int i = 0; i < 7; i++)
		pinMode(pinSalidas[i], OUTPUT);
	
	
	pinMode(12, INPUT);
	pinMode(16, INPUT);
	pinMode(20, INPUT);
	pinMode(21, INPUT);
	
	while(!digitalRead(23)){
	
	
	if(digitalRead(12) && !digitalRead(16) && !digitalRead(18)){
		autofantastico();
	}
/*	
	if(!digitalRead(12) && digitalRead(16) && !digitalRead(18) && !digitalRead(23)){
		choque();
	}
	
	if(!digitalRead(12) && !digitalRead(16) && digitalRead(18) && !digitalRead(23)){
		billar();
	}
	
	if(!digitalRead(12) && !digitalRead(16) && !digitalRead(18) && digitalRead(23)){
		canicas();
	}*/
	
	}
	
	salida(0);
}

void salida(unsigned char c){
	
	int i;
	
	//For decremental
	for(i = 7; i >= 0; i--){
		//Verificamos el resultado del corrimiento de c & 1
		if((c >> i) & 1){
			digitalWrite(pinSalidas[i]);
		}else{
			digitalWrite(pinSalidas[i]);
		}					
	}
		
}

void autofantastico(){
	int estado = 0;
	int i = 128;

	do{	
	
		salida(i);
		delay(1000);
	
		if(!estado)			
			i = i >> 1;
		else
			i = i << 1;
			
		if(i == 128)
			estado = 0;
		
		if(i == 1)
			estado = 1;		

	}while(digitalRead(12));
}
