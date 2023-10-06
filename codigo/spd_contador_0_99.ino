//Se le asigna un nombre a cada pin.
#define LED_A 11
#define LED_B 12
#define LED_C 8
#define LED_D 7
#define LED_E 6
#define LED_F 10 
#define LED_G 9
#define BOTON_SUMAR 3
#define BOTON_RESTAR 4
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




//Configuracion de pines.
void setup()
{
  pinMode(BOTON_SUMAR, INPUT_PULLUP);
  pinMode(BOTON_RESTAR, INPUT_PULLUP);
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
  /*
  se obtiene el numero del pin asociado al boton 
  presionado y se guarda en una variable.
  */
  int boton_presionado = determinar_boton_presionado();
  //si se presionó el boton de sumar, se suma 1 al contador.
  if (boton_presionado == BOTON_SUMAR){
    contador++;
    //si el contador supera el maximo, se reinicia.
    if (contador > 99){
      contador = 0;
    }
  }
  //si se presionó el boton de resta, se resta 1 al contador.
  else if(boton_presionado == BOTON_RESTAR){
    contador--;
    //si el contador es menor de 0, se va hasta 99.
    if (contador < 0){
      contador = 99;
    }
  }
  //si se presionó el boton de reset, se pone el contador en 0.
  else if(boton_presionado == BOTON_RESET){
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
    delay(10);
  }
  else if (display == DISPLAY_DECENA){
    digitalWrite(DISPLAY_UNIDAD, HIGH);
    digitalWrite(DISPLAY_DECENA, LOW);
    delay(10);
  }
  else{
    digitalWrite(DISPLAY_UNIDAD, LOW); 
    digitalWrite(DISPLAY_DECENA, LOW); 
  } 
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
  restar_actual = digitalRead(BOTON_RESTAR);
  reset_actual = digitalRead(BOTON_RESET);
  
  /*
  si el estado actual del boton es 1 (no presionado)
  entonces el estado anterior tambien es 1.
  */
  if (sumar_actual){
    sumar_anterior = 1;
  }
  if (restar_actual){
    restar_anterior = 1;
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
  if(restar_actual == 0 && restar_actual != restar_anterior){
    restar_anterior = restar_actual;
    return BOTON_RESTAR;
  }
  if(reset_actual == 0 && reset_actual != reset_anterior){
    reset_anterior = reset_actual;
    return BOTON_RESET;
  }
}

  
