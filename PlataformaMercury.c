#include <18f252.h>
//#device ADC=16
#FUSES NOWDT      //No Watch Dog Timer
#FUSES WDT128     //Watch Dog Timer uses 1:128 Postscale
#FUSES NOBROWNOUT //No brownout reset
#FUSES NOLVP      //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=4MHz)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=PORT1,restart_wdt)  //Xbee
#use rs232(baud=9600,parity=N,xmit=PIN_A0,rcv=PIN_A1,bits=8,stream=PORT2,restart_wdt)  //Tarjeta servo


#define in1 PIN_C0//motor1 
#define in2 PIN_C4//motor1
#define m1 PIN_A2 //motor 2
#define m2 PIN_A5//motor2
//#define m1a  PIN_C0   //Rosa  IN3
//#define m1b  PIN_C1   //Amarillo IN1
//#define m2a  PIN_C2   //Café IN4
//#define m2b  PIN_C4   //Rojo IN2

#define buzzer PIN_C5

char c, r_motor='0';
int r_servo=0;
void Adelante();
void Atras();
void Derecha();
void Izquierda();
void Stop();
void pinza_abre();
void pinza_cierra();
void servo2_arriba();
void servo2_abajo();
void servo3_arriba();
void servo3_abajo();
void servo2_bola();
void servo2_abajo_bola();
void servo3_abajo_inicial();
void servo4_derecha();
void servo4_izquierda();
#INT_RDA //Interrupción 
void RDA_isr(void)
{
   c=getc();
   
       if(c=='w')  //Adelante
         {
         r_motor='w';
         }
      if(c=='z')  //Atrás
         {
         r_motor='z';
         }
      if(c=='d')  //Derecha
         {
         r_motor='d';
         }
      if(c=='a')  //Izquierda
         {
         r_motor='a';
         }
      if(c=='s')  //Parada
         {
         r_motor='s';
         }
      if(c=='p')
         {
          output_high(buzzer);   
          
         }
      
      if(c=='o')
         {
          output_low(buzzer);   
        
        
         }
       if(c=='i') //pinza arriba
         {
         printf("pinza abre");
         r_servo=1;
         
           
          
         } 
         if(c=='u') //pinza arriba
         {
         printf("pinza cierra");
         r_servo=2;
         

         }
        if(c=='k') //pinza arriba
         {
         printf("servo2 arriba");
         r_servo=3;

         }
         if(c=='j') //pinza arriba
         {
         printf("servo2 abajo");
         r_servo=4;

         }
         if(c=='m') //pinza arriba
         {
         printf("servo3 arriba");
         r_servo=5;

         }
         if(c=='n') //pinza arriba
         {
         printf("servo3 abajo");
         r_servo=6;

         }
         
         if(c=='l') //pinza arriba
         {
         printf("servo2 bola");
         r_servo=7;

         }
         
          if(c=='J') //SERVO2 ABAJO RECOGE BOLA
         {
         printf("SERVO2 BOLA");
         r_servo=8;

         }
         if(c=='N') //SERVO3 ABAJO POSICION INICIAL
         {
         printf("SERVO3 INICIAL");
         r_servo=9;

         }
         
            if(c=='b') //base derecha
         {
         printf("SERVO BASE D");
         r_servo=10;

         }
         if(c=='v') //base derecha
         {
         printf("SERVO BASE I");
         r_servo=11;

         }
         
         
         
      
}

void main ()
{

   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL); 
 //  set_tris_a(0x10);
   while (true)
   {
   
      if(r_motor=='w')  //Adelante
         {
         printf("Adelante");
         Adelante();
         }
      if(r_motor=='z')  //Atrás
         {
         printf("ATRAS");
         Atras();
         }
      if(r_motor=='d')  //Derecha
         {
         printf("DERECHA");
         Derecha();
         }
      if(r_motor=='a')  //Izquierda
         {
         printf("IZQUIERA");
         Izquierda();
         }
      if(r_motor=='s')  //Parada
         {
         printf("STOP");
         Stop();
         }
      
      if(r_servo==1)
      {
          pinza_abre();
      }
     if(r_servo==2)
      {
          pinza_cierra();
      }
      
      if(r_servo==3)
      {
          servo2_arriba();
      }
      
      if(r_servo==4)
      {
          servo2_abajo();
      }
        if(r_servo==5)
      {
          servo3_arriba();
      }
          if(r_servo==6)
      {
          servo3_abajo();
      }
           if(r_servo==7)
      {
          servo2_bola();
      }
          if(r_servo==8)
      {
         servo2_abajo_bola();
      }
       if(r_servo==9)
      {
         servo3_abajo_inicial();
      }
      
       if(r_servo==10)
      {
          servo4_derecha();
      }
     
     if(r_servo==11)
      {
          servo4_izquierda();
      }
     
          
       
   }
}//FIN MAIN

void Adelante()
{
  setup_timer_2(T2_DIV_BY_16, 255,1);//excel
   setup_ccp1(CCP_PWM);
   setup_ccp2(CCP_PWM);
   set_pwm1_duty(150);
   set_pwm2_duty(150);
  output_low(in1);
  output_high(in2);
  output_low(m2);
  output_high(m1);
   }
void Atras()
{   setup_timer_2(T2_DIV_BY_16, 255,1);//excel
   setup_ccp1(CCP_PWM);
   setup_ccp2(CCP_PWM);
   set_pwm1_duty(40);
   set_pwm2_duty(40);
   output_low(in2);
  output_high(in1);
  output_high(m2);
  output_low(m1);
}
void Izquierda()
{
  setup_timer_2(T2_DIV_BY_16, 255,1);//excel
   setup_ccp1(CCP_PWM);
   setup_ccp2(CCP_PWM);
   set_pwm1_duty(150);
   set_pwm2_duty(150);
   output_low(in2);
  output_high(in1);
  output_low(m2);
  output_high(m1);
}
void Derecha()
{
  
  setup_timer_2(T2_DIV_BY_16, 255,1);//excel
   setup_ccp1(CCP_PWM);
   setup_ccp2(CCP_PWM);
   set_pwm1_duty(150);
   set_pwm2_duty(150);
 output_low(in1);
  output_high(in2);
  output_low(m1);
  output_high(m2); 
}
void Stop()
{
  setup_timer_2(T2_DIV_BY_16, 255,1);//excel
   setup_ccp1(CCP_PWM);
   setup_ccp2(CCP_PWM);
   set_pwm1_duty(0);
   set_pwm2_duty(0);
  output_low(in2);
  output_low(in1);
  output_low(m2);
  output_low(m1);
}
void pinza_abre()
{
      fputc(0xAA,PORT2);
      fputc(0x0C,PORT2);
      fputc(0x04,PORT2);
      fputc(0x00,PORT2); // Canal = 0
      fputc(0x28,PORT2); // Posicion destino = 1000 us (minima para servos) 90º
      fputc(0x2D,PORT2);
      delay_ms(1000);
      r_servo=0;
}

void pinza_cierra()
{
      fputc(0xAA,PORT2);
      fputc(0x0C,PORT2);
      fputc(0x04,PORT2);
      fputc(0x00,PORT2); // Canal = 0
      fputc(0x00,PORT2); // Posicion destino = 1000 us (minima para servos) 0º
      fputc(0x4B,PORT2);
      delay_ms(1000);
      r_servo=0;
}
void servo2_arriba()
{
      fputc(0xAA,PORT2);
      fputc(0x0C,PORT2);
      fputc(0x04,PORT2);
      fputc(0x01,PORT2); // Canal = 1
      fputc(0x08,PORT2); // Posicion destino = 1000 us (minima para servos) 90º
      fputc(0x27,PORT2);
      delay_ms(1000);
      r_servo=0;
}
void servo2_abajo()
{
      fputc(0xAA,PORT2);
      fputc(0x0C,PORT2);
      fputc(0x04,PORT2);
      fputc(0x01,PORT2); // Canal = 1
      fputc(0x00,PORT2); // Posicion destino = 1000 us (minima para servos) 0º
      fputc(0x4B,PORT2);
      delay_ms(1000);
      r_servo=0;
}
void servo3_arriba()
{
      fputc(0xAA,PORT2);
      fputc(0x0C,PORT2);
      fputc(0x04,PORT2);
      fputc(0x02,PORT2); // Canal = 2
      fputc(0x00,PORT2); // Posicion destino = 1000 us (minima para servos) 0º
      fputc(0x4B,PORT2);
      delay_ms(1000);
      r_servo=0;
}

void servo3_abajo()
{
      fputc(0xAA,PORT2);
      fputc(0x0C,PORT2);
      fputc(0x04,PORT2);
      fputc(0x02,PORT2); // Canal = 2
      fputc(0x60,PORT2); // Posicion destino = 1000 us (minima para servos) 0º
      fputc(0x12,PORT2);
      delay_ms(1000);
      r_servo=0;
}

void servo2_abajo_bola()
{
      fputc(0xAA,PORT2);
      fputc(0x0C,PORT2);
      fputc(0x04,PORT2);
      fputc(0x01,PORT2); // Canal = 1
      fputc(0x00,PORT2); // Posicion destino = 1000 us (minima para servos) 0º
      fputc(0x32,PORT2);
      delay_ms(1000);
      r_servo=0;
}

void servo2_bola()
{
      fputc(0xAA,PORT2);
      fputc(0x0C,PORT2);
      fputc(0x04,PORT2);
      fputc(0x01,PORT2); // Canal = 1
      fputc(0x68,PORT2); // Posicion destino = 1000 us (minima para servos) 90º
      fputc(0x05,PORT2);
      delay_ms(1000);
      r_servo=0;
}

void servo3_abajo_inicial()
{
      fputc(0xAA,PORT2);
      fputc(0x0C,PORT2);
      fputc(0x04,PORT2);
      fputc(0x02,PORT2); // Canal = 2
      fputc(0x28,PORT2); // Posicion destino = 1000 us (minima para servos) 0º
      fputc(0x2D,PORT2);
      delay_ms(1000);
      r_servo=0;
}

void servo4_derecha()
{
      fputc(0xAA,PORT2);
      fputc(0x0C,PORT2);
      fputc(0x04,PORT2);
      fputc(0x03,PORT2); // Canal = 3
      fputc(0x30,PORT2); // Posicion destino = 1000 us (minima para servos) 0º
      fputc(0x3B,PORT2);
      delay_ms(1000);
      r_servo=0;
}

void servo4_izquierda()
{
      fputc(0xAA,PORT2);
      fputc(0x0C,PORT2);
      fputc(0x04,PORT2);
      fputc(0x03,PORT2); // Canal = 3
      fputc(0x30,PORT2); // Posicion destino = 1000 us (minima para servos) 0º
      fputc(0x22,PORT2);
      delay_ms(1000);
      r_servo=0;
}
