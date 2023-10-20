//Se le asigna un nombre a cada pin.
#define LED_A 11
#define LED_B 12
#define LED_C 8
#define LED_D 7
#define LED_E 6
#define LED_F 10 
#define LED_G 9
#define BOTON_SUMAR 3
#define SWITCH 4
#define BOTON_RESET 5
#define DISPLAY_UNIDAD A0
#define DISPLAY_DECENA A1

//Declaracion de variables a utilizar en el programa.
int contador = 0;
int sumar_actual = 1;
int restar_actual = 1;
int reset_actual = 1;
int sumar_anterior = 1;
int restar_anterior = 1;
int reset_anterior = 1;
int switch_actual = 1;
int switch_anterior = 1;





//Configuracion de pines.
void setup()
{
  pinMode(BOTON_SUMAR, INPUT_PULLUP);
  pinMode(SWITCH, INPUT_PULLUP);
  pinMode(BOTON_RESET, INPUT_PULLUP);
  pinMode(DISPLAY_UNIDAD, OUTPUT);
  pinMode(DISPLAY_DECENA, OUTPUT);
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_C, OUTPUT);
  pinMode(LED_D, OUTPUT);
  pinMode(LED_E, OUTPUT);
  pinMode(LED_F, OUTPUT);
  pinMode(LED_G, OUTPUT);
}

//Funcion principal
void loop(){
  switch_actual = digitalRead(SWITCH);
  int boton_presionado = determinar_boton_presionado();
  if(boton_presionado == BOTON_SUMAR){
    if (switch_actual == 0){
     do{contador++;}while(es_primo(contador) == 0);
    }
    else{
      contador++;  
    }
    if (contador > 99){
      contador = 0;
    }
  }
  if(boton_presionado == BOTON_RESET){
    contador = 0;
  }
  mostrar_contador(contador);  
}

void mostrar_contador(int contador) {
  int decena = contador / 10;
  int unidad = contador -  decena * 10;
  prender_display(0);
  mostrar_digito(decena);
  prender_display(DISPLAY_DECENA);
  prender_display(0);
  mostrar_digito(unidad);
  prender_display(DISPLAY_UNIDAD); 
}

void prender_display(int display){
  if (display == DISPLAY_UNIDAD){	
    digitalWrite(DISPLAY_UNIDAD, LOW); 
    digitalWrite(DISPLAY_DECENA, HIGH); 
  }
  else if (display == DISPLAY_DECENA){
    digitalWrite(DISPLAY_UNIDAD, HIGH);
    digitalWrite(DISPLAY_DECENA, LOW);
    
  }
  else{
    digitalWrite(DISPLAY_UNIDAD, LOW); 
    digitalWrite(DISPLAY_DECENA, LOW); 
  }
  delay(10);
}

void mostrar_digito(int digito){
  digitalWrite(LED_A, HIGH);
  digitalWrite(LED_B, HIGH);
  digitalWrite(LED_C, HIGH);
  digitalWrite(LED_D, HIGH);
  digitalWrite(LED_E, HIGH);
  digitalWrite(LED_F, HIGH);
  digitalWrite(LED_G, HIGH);
  switch (digito){
    case 0:{
      digitalWrite(LED_A, LOW);
      digitalWrite(LED_B, LOW);
      digitalWrite(LED_C, LOW);
      digitalWrite(LED_D, LOW);
      digitalWrite(LED_E, LOW);
      digitalWrite(LED_F, LOW);
      break;
    } 
    case 1:{
      digitalWrite(LED_B, LOW);
 	  digitalWrite(LED_C, LOW);
      break;
  	}
    case 2:{
      digitalWrite(LED_A, LOW);
      digitalWrite(LED_B, LOW);
      digitalWrite(LED_D, LOW);
      digitalWrite(LED_E, LOW);
      digitalWrite(LED_G, LOW);
      break;
    }
    case 3:{
      digitalWrite(LED_A, LOW);
      digitalWrite(LED_B, LOW);
      digitalWrite(LED_C, LOW);
      digitalWrite(LED_D, LOW);
      digitalWrite(LED_G, LOW);
      break;
  	}
    case 4:{
      digitalWrite(LED_B, LOW);
      digitalWrite(LED_C, LOW);
      digitalWrite(LED_F, LOW);
      digitalWrite(LED_G, LOW);
      break;
  	}
    case 5:{
      digitalWrite(LED_A, LOW);
      digitalWrite(LED_C, LOW);
      digitalWrite(LED_D, LOW);
      digitalWrite(LED_F, LOW);
      digitalWrite(LED_G, LOW);
      break;
    }
    case 6:{
      digitalWrite(LED_A, LOW);
      digitalWrite(LED_C, LOW);
      digitalWrite(LED_D, LOW);
      digitalWrite(LED_E, LOW);
      digitalWrite(LED_F, LOW);
      digitalWrite(LED_G, LOW);
      break;
  	}
    case 7:{
      digitalWrite(LED_A, LOW);
      digitalWrite(LED_B, LOW);
      digitalWrite(LED_C, LOW);
      break;
  	}
    case 8:{
      digitalWrite(LED_A, LOW);
      digitalWrite(LED_B, LOW);
      digitalWrite(LED_C, LOW);
      digitalWrite(LED_D, LOW);
      digitalWrite(LED_E, LOW);
      digitalWrite(LED_F, LOW);
      digitalWrite(LED_G, LOW);
      break;
  	} 
    case 9:{
      digitalWrite(LED_A, LOW);
      digitalWrite(LED_B, LOW);
      digitalWrite(LED_C, LOW);
      digitalWrite(LED_D, LOW);
      digitalWrite(LED_F, LOW);
      digitalWrite(LED_G, LOW);
      break;
    }      
  }
}

//declarion funcion "determinar_boton_presionado".
int determinar_boton_presionado(){
  
  //se guardan los valores actuales de los botones.
  sumar_actual = digitalRead(BOTON_SUMAR);
  reset_actual = digitalRead(BOTON_RESET);
  
  /*
  si el estado actual del boton es 1 (no presionado)
  entonces el estado anterior tambien es 1.
  */
  if (sumar_actual){
    sumar_anterior = 1;
  }
  if (reset_actual){
    reset_anterior = 1;
  }
  
  /*
  si el estado actual del boton es 0 (presionado)
  y es diferente al estado anterior (no presionado)
  entonces, se cambia su estado anterior para que coincida con su estado actual
  y se devuelve el numero de pin asociado al boton presionado.
  */
  if(sumar_actual == 0 && sumar_actual != sumar_anterior){
    sumar_anterior = sumar_actual;
    return BOTON_SUMAR;
  }
  if(reset_actual == 0 && reset_actual != reset_anterior){
    reset_anterior = reset_actual;
    return BOTON_RESET;
  } 
}

  
bool es_primo(int numero){
  if(numero <= 1){
    return false;
  }
  for (int i = 2; i <= sqrt(numero); i++) {
    if (numero % i == 0){
      return false;
    }
  }
  return true;
} 
