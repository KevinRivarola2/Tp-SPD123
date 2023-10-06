# Tp-SPD
![alt text](https://github.com/KevinRivarola2/Tp-SPD/blob/main/TP1/Imagenes/9b8084d5-b1b7-4b05-be03-3ce359a2cd41.jpg)
## Integrantes
* Kevin Rivarola
* Tomás Sandoval
## Proyecto: Contador de 0 a 99 con Display 7 Segmentos y Multiplexación
![alt text](https://github.com/KevinRivarola2/Tp-SPD/blob/main/TP1/Imagenes/d3ab24f5-09f7-40dc-a2bc-bea4cfb72552.jpg)
## Descripción
Placa arduino que permite al usuario contar numeros del 0 al 99 haciendo uso de tres botones mostrandole los numeros en dos displays de 7 segmentos.
los botones son:
- sumar 1
- restar 1
- reiniciar conteo
## Codigo
### Función principal
Llama a 'determinar_boton_presionado' y guarda el numero del pin asociado al boton presionado en 'boton_presionado'.    
Luego Aumenta, decrementa o reinicia el contador segun el boton presionado. 
Finalmente llama a 'mostrar_contador' pasandole la variable 'contador' como argumento.   
~~~
void loop(){
  int boton_presionado = determinar_boton_presionado();
  if (boton_presionado == BOTON_SUMAR){
    contador++;
    if (contador > 99){
      contador = 0;
    }
  }
  else if(boton_presionado == BOTON_RESTAR){
    contador--;
    if (contador < 0){
      contador = 99;
    }
  }
  else if(boton_presionado == BOTON_RESET){
    contador = 0;
  }
  mostrar_contador(contador);  
}
~~~
### mostrar_contador
Función que se encarga de la multiplexacion.
Toma un int como argumento y no retorna nada.  
Llama a 'prender_display' con argumento 0 para apagar ambos display.
Luego llama a 'mostrar_digito' con el numero correspondiente a la decena para prender los leds que formen el numero.
Llama a 'prender_display' con argumento DISPLAY_DECENA para encender el display de la decena, mostrando la decena.

Finalmente repite los ultimos tres pasos pero para mostrar la unidad.
De esta forma, encendiendo y apagando los displays de manera rapida, se crea la ilusion de que ambos estan encendidos al mismo tiempo.
~~~
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
~~~
### prender_display
Función encargada de encender y apagar los displays. 
Toma un int que representa el pin de un display como argumento y no retorna nada. 
Dependiendo del argumento recidido prendera un display y apagara el otro o apagara ambos.
~~~
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
~~~
### mostrar_digito
Funcion encargada de prender los leds que para formar los numeros. 
Recibe un int que representa el digito a mostrar y no devuelve nada.
Primero apaga todos leds y luego dependiendo del numero recibido enciende los leds que correspondan.
~~~
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
~~~
### determinar_boton_presionado

Función encargada de determinar cual fue el boton que se presiono.
No recibe nada y devuelve un int que presenta el pin asociado al boton presionado.
Primero guarda el estado el estado actual de los 3 botones.
Luego si el estado actual del boton es 1 (no presionado) entonces el estado anterior tambien es 1.
Finalmente si el estado actual del boton es 0 (presionado) y es diferente al estado anterior (no presionado)
entonces, se cambia su estado anterior para que coincida con su estado actual y se devuelve el numero de pin
asociado al boton presionado.
~~~
int determinar_boton_presionado(){
  sumar_actual = digitalRead(BOTON_SUMAR);
  restar_actual = digitalRead(BOTON_RESTAR);
  reset_actual = digitalRead(BOTON_RESET);
  
  if (sumar_actual){
    sumar_anterior = 1;
  }
  if (restar_actual){
    restar_anterior = 1;
  }
  if (reset_actual){
    reset_anterior = 1;
  }
  
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
~~~
## Link al proyecto
[Proyecto en Tinkercad](https://www.tinkercad.com/things/6DMRPAP320x-utnfra-spd-parcial-domiciliario-parte-1/editel?sharecode=PUOihxmVQlLQXOCIsWMr3u3JhkNV6UVm6YN7wnlPke0 "Proyecto en Tinkercad")
## Diagrama
![alt text](https://github.com/KevinRivarola2/Tp-SPD/blob/main/TP1/Imagenes/diagrama_UTNFra_SPD_Parcial_domiciliario_Parte-1_.png)
