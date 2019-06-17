#include <18f4550.h>          // la librería del PIC
#Fuses HSPLL, NOWDT, NOPROTECT, NOLVP, NODEBUG, USBDIV, PLL2, CPUDIV1, VREGEN
#use delay (clock=48M)        //Seleccionamos la frecuencia de reloj de 48MHz
#use standard_io(C)        //Preconfiguramos el puerto C
#use standard_io(e)        //Preconfiguramos el puerto E
#use standard_io(b)
#include <MLCD.c>
void main(){    //Inicio de la función principal
   lcd_init();
   enum state_t{state1, state2, state3};
   int state;


   set_tris_e(0x00);       //Configuramos puerto E como salida
   set_tris_C(0x01);       //Configuramos pin C0 como entrada
   set_tris_B(0x00);
   output_e(0x07);         //Apagamos el LED RGB
   output_b(0x00);

   while(true){ //Inicia ciclo infinito

  state = welcome; //Entramos dentro de la máquina de estados.

   switch (state) {
     case state1:

     if (input_state(PIN_C0)){  //Revisamos el estado del PIN_C0
        printf(lcd_putc,"\f");  //limpiamos pantalla
        lcd_gotoxy(6,2);        //posicion del mensaje
        printf(lcd_putc,"Running"); //mensaje

        output_high(PIN_B1); //empuja el refresco

        output_high(PIN_E2); //apaga led azul
        state = state2; //Cambia al siguiente estado de poner tapa.


   }

      case state2:
      output_low(PIN_E1);     //Encender LED rojo
      delay_ms(5000);          //Esperamos 5 Segundos
      output_high(PIN_E1); //apaga el led rojo
      output_low(PIN_B1); //se detiene
      output_high(PIN_B2);delay_ms(600); //PONE LA TAPA

      printf(lcd_putc,"\f");
      lcd_gotoxy(4,2);
      output_low(PIN_B2); se apaga el led
      printf(lcd_putc,"Done");
      delay_ms(2000); //espera 2 segundos

      output_high(PIN_B1); //avanza (empuje)

         printf(lcd_putc,"\f");
         lcd_gotoxy(6,2);
         printf(lcd_putc,"Running");

         output_low(PIN_E1);  //se apaga enciende el led azul
         delay_ms(2000);
         output_low(PIN_B1); // se detiene el motor
         printf(lcd_putc,"\f");
         lcd_gotoxy(6,2);
         printf(lcd_putc,"Thanks");
         delay_ms(1000);

      case welcome:                     //Si no se presionó el pulsador

           printf(lcd_putc,"\f");


           output_high(PIN_E1);//Apagar LED
           output_low(PIN_E2);
           lcd_gotoxy(5,1);
           printf(lcd_putc,"\WElCOME");
           delay_ms(500);

           lcd_gotoxy(5,2);
           printf(lcd_putc,"press C0");
           delay_ms(1000);

           if (input_state(PIN_C0)){

             state = state1;

      }
      }
   }
 }
