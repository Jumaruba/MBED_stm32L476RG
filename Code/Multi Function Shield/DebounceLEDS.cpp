/* -------------------------------------------------------------------
 * Project   : Practical_2_MBED_Debounce
 * File name : main.cpp
 * ------------------------------------------------------------------- */

/* -------------------------------------------------------------------
 * Preamble
 * ------------------------------------------------------------------- */
 
#include "mbed.h"

DigitalOut led_D1( PA_5 );  // LED D1
DigitalOut led_D2( PA_6 );  // LED D2
DigitalOut led_D3( PA_7 );  // LED D3
DigitalOut led_D4( PB_6 );  // LED D4

DigitalIn sw_S1( PA_1 );    // Push-button S1-A1
DigitalIn sw_S2( PA_4 );    // Push-button S2-A2
DigitalIn sw_S3( PB_0 );    // Push-button S3-A3

#define LED_ON         0    // Value for LED ON
#define LED_OFF        1    // Value for LED OFF

Ticker my_tick_1;           // Ticker for implementing a counter for debounce

volatile int status_S1 = 0; // Status of S1-A1 (not pressed or pressed) for D1
volatile int status_S2 = 0; // Status of S2-A2 (not pressed or pressed) for D2
volatile int status_S3 = 0; // Status of S3-A3 (not pressed or pressed) for D3
volatile int status_S4 = 0; // Status of S3-A3 (toggles on S3-A3 press) for D4

void switch_read( void );   // Function prototype for switch_read( void )

/* -------------------------------------------------------------------
 * int main()
 * ------------------------------------------------------------------- */
 
int main( void )
{

  /* ---------------------------------------------- */
  /* Initially turn on LEDS OFF                     */
  /* ---------------------------------------------- */
  
  led_D1 = LED_OFF;
  led_D2 = LED_OFF;
  led_D3 = LED_OFF;
  led_D4 = LED_OFF;
 
  /* ---------------------------------------------- */
  /* Attach ticker my_tick_1 -> 1 ms                */
  /* ---------------------------------------------- */
  
  my_tick_1.attach(&switch_read, 0.001);
 
  /* ---------------------------------------------- */
  /* while loop - never ends                        */
  /* ---------------------------------------------- */
             
  while ( true )
  {
      
     if ( status_S1 == 0 )
     {
       led_D1 = LED_ON;
     } else 
     {
       led_D1 = LED_OFF;
     }
  
     if ( status_S2 == 0 )
     {
       led_D2 = LED_ON;
     } else 
     {
       led_D2 = LED_OFF;
     }    
      
     if ( status_S3 == 0 )
     {
       led_D3 = LED_ON;
     } else 
     {
       led_D3 = LED_OFF;
     }

     if ( status_S4 == 0 )
     {
       led_D4 = LED_ON;
     } else 
     {
       led_D4 = LED_OFF;
     }
     
  }     

}

/* -------------------------------------------------------------------
 * void debouncer( void )
 * ------------------------------------------------------------------- */

void switch_read( void )
{
 
  /* ----------------------------------------------------------------- */
  
  static int debounce_count = 50;
  
  static int in_S1 = 0;  
  static int in_S1_0 = 0;
  static int in_S1_1 = 0; 

  static int in_S2 = 0;  
  static int in_S2_0 = 0;
  static int in_S2_1 = 0; 
  
  static int in_S3 = 0;  
  static int in_S3_0 = 0;
  static int in_S3_1 = 0; 
   
  /* -----------------------------------------------------------------
   * Read in from switches
   * ----------------------------------------------------------------- */

  in_S1 = sw_S1;    
  in_S2 = sw_S2;
  in_S3 = sw_S3; 
   
  /* -----------------------------------------------------------------]
   * Switch S1-A1
   * Counter to count to debounce_limit that will give a 0 or 1 if the
   * read switch value is 0 or 1 for the entire debounce_limit 
   * ----------------------------------------------------------------- */
    
  if ( in_S1 == 0 )
  {
    
    in_S1_0 = in_S1_0 + 1;
    in_S1_1 = 0;
    
    if ( in_S1_0 >= debounce_count )
    {
      in_S1_0 = debounce_count;
      status_S1 = 0;  
    }
    
  } else
  {
    
    in_S1_1 = in_S1_1 + 1;
    in_S1_0 = 0;
    
    if ( in_S1_1 >= debounce_count )
    {
      in_S1_1 = debounce_count;
      status_S1 = 1;  
    }
       
  }
  
  /* -----------------------------------------------------------------]
   * Switch S2-A2
   * Counter to count to debounce_limit that will give a 0 or 1 if the
   * read switch value is 0 or 1 for the entire debounce_limit 
   * ----------------------------------------------------------------- */
  
   if ( in_S2 == 0 )
  {
    
    in_S2_0 = in_S2_0 + 1;
    in_S2_1 = 0;
    
    if ( in_S2_0 >= debounce_count )
    {
      in_S2_0 = debounce_count;
      status_S2 = 0;  
    }
    
  } else
  {
    
    in_S2_1 = in_S2_1 + 1;
    in_S2_0 = 0;
    
    if ( in_S2_1 >= debounce_count )
    {
      in_S2_1 = debounce_count;
      status_S2 = 1;  
    }
       
  } 
  
  /* -----------------------------------------------------------------]
   * Switch S3-A3
   * Counter to count to debounce_limit that will give a 0 or 1 if the
   * read switch value is 0 or 1 for the entire debounce_limit 
   * ----------------------------------------------------------------- */

  if ( in_S3 == 0 )
  {
    
    in_S3_0 = in_S3_0 + 1;
    in_S3_1 = 0;
    
    if ( in_S3_0 >= debounce_count )
    { 
        
      if ( in_S3_0 == debounce_count )
      {
        status_S4 = !status_S4;
      }
      
      in_S3_0 = debounce_count + 1;   
      status_S3 = 0;
                  
    }
    
  } else
  {
    
    in_S3_1 = in_S3_1 + 1;
    in_S3_0 = 0;
    
    if ( in_S3_1 >= debounce_count )
    {
      in_S3_1 = debounce_count;
      status_S3 = 1;  
    }
       
  } 

  /* ----------------------------------------------------------------- */  

}
    
/* -------------------------------------------------------------------
 * End of file
 * ------------------------------------------------------------------- */