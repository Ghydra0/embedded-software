#include <p18f4620.h>
#include <stdio.h>
#include <math.h>
#include <usart.h>
#pragma config OSC = INTIO67
#pragma config WDT=OFF
#pragma config LVP=OFF
#pragma config BOREN =OFF

#define decimal PORTEbits.RE0

#define D1_RED PORTCbits.RC3
#define D1_GREEN PORTCbits.RC4
#define D1_BLUE PORTCbits.RC5

#define D2_RED PORTCbits.RC0
#define D2_BLUE PORTCbits.RC2

char LED_7seg[10] = {0x01,0x4F,0x12,0x06,0x4C,0x24,0x20,0x0F,0x00,0x04}; // 7 segment display values 0-9

void SET_D1_OFF()                                          // the following functions control the LED colors for D1-3
{
    D1_RED = 0;                                            //
    D1_GREEN = 0;                                          //
    D1_BLUE = 0;                                           //
}
void SET_D1_RED()                                          // D1 = RED
{
    D1_RED = 1;                                            //
    D1_GREEN = 0;                                          //
    D1_BLUE = 0;                                           //
}
void SET_D1_GREEN()                                        // D1 = GREEN
{
    D1_RED = 0;                                            //
    D1_GREEN = 1;                                          //
    D1_BLUE = 0;                                           //
}

void SET_D1_YELLOW()
{
    D1_RED = 1;                                            //
    D1_GREEN = 1;                                          //
    D1_BLUE = 0;                                           //
}

void SET_D1_BLUE()                                         // D1 = BLUE
{
    D1_RED = 0;                                            //
    D1_GREEN = 0;                                          //
    D1_BLUE = 1;                                           //
}

void SET_D1_PURPLE()                                       // D1 = PURPLE
{
    D1_RED = 1;                                            //
    D1_GREEN = 0;                                          //
    D1_BLUE = 1;                                           //
}
void SET_D1_CYAN()                                         // D1 = CYAN
{
    D1_RED = 0;                                            //
    D1_GREEN = 1;                                          //
    D1_BLUE = 1;                                           //
}
void SET_D1_WHITE()                                        // D1 = WHITE
{
    D1_RED = 1;                                            //
    D1_GREEN = 1;                                          //
    D1_BLUE = 1;                                           //
}

void SET_D2_OFF()                                        // D2 = OFF
{
    D2_RED = 0;                                            //
    D2_BLUE = 0;                                           //
}

void SET_D2_RED()                                        // D2 = OFF
{
    D2_RED = 1;                                            //
    D2_BLUE = 0;                                           //
}

void SET_D2_BLUE()                                        // D2 = OFF
{
    D2_RED = 0;                                            //
    D2_BLUE = 1;                                           //
}

void SET_D2_PURPLE()                                        // D2 = OFF
{
    D2_RED = 1;                                            //
    D2_BLUE = 1;                                           //
}

void Init_UART()
{
 OpenUSART (USART_TX_INT_OFF & USART_RX_INT_OFF &
USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX &
USART_BRGH_HIGH, 25);
 OSCCON = 0x60;
}
void putch (char c)
{
 while (!TRMT);
 TXREG = c;
} 

unsigned int get_full_ADC(void)                            // get_full_ADC function
{
int result;
    ADCON0bits.GO=1;                                       // Start Conversion
    while(ADCON0bits.DONE==1);                             // wait for conversion to be completed
    result = (ADRESH * 0x100) + ADRESL;                    // combine result of upper byte and
                                                           // lower byte into result
    return result;                                         // return the result.
}

void Select_ADC_Channel(char channel)                      // used to select ADC channel
{
    ADCON0 = channel * 4 + 1;                              // ADCON0 channel select conversion
}

void Init_TRIS()                                           // Init_Tris function
{
    TRISA = 0XFF;                                          // TRISA = input
    TRISB = 0X00;                                          // TRISB = output
    TRISC = 0X00;                                          // TRISC = output
    TRISD = 0X00;                                          // TRISD = output
    TRISE = 0X00;                                          // TRISE = output
    
}

void Init_ADC(void)                                        // Init_ADC function
{
    ADCON1=0x1A;                                           // select pins AN0 as analog input, VREF+ reference,
    ADCON2=0xA9;                                           // right justify the result. Set the bit conversion time (TAD) and
                                                           // acquisition time
}

void display_lower_digit(char digit)                       // display_lower_digit function
{
    PORTB = LED_7seg[digit];                               // PORTB = lower digit of temp
}

void display_upper_digit(char digit)                       // display_upper_digit function
{
    PORTD = LED_7seg[digit];                               // PORTD = upper digit of temp
}

void Activate_Buzzer()
{
    PR2 = 0b11111001 ;
    T2CON = 0b00000101 ;
    CCPR2L = 0b01001010 ;
    CCP2CON = 0b00111100 ;
} 

void Deactivate_Buzzer()
{
    CCP2CON = 0x0;
    PORTCbits.RC1 = 0;
} 

void Delay_One_Sec()                                       // create a one second delay
{
    for(int I=0; I <17000; I++);
}

void main()
{
    Init_ADC();                                            // initialize ADC
    Init_TRIS();                                           // initialize TRIS
    Init_UART();                                           // initialize UART
    
    char U;
    char L;
    
    while(1)
    {
        Select_ADC_Channel(4);                             // Select Channel AN4
        int num_step = get_full_ADC();                     // number of A/D conversion steps
        float voltage_v = (num_step *4.0) / 1000;          // potentiometer voltage drop in volts
        float RL = (100.0*voltage_v) / (4.096-voltage_v);  // Calculation of resistance using voltage divider rule
        
        if(RL < 10.0)                                      // if unknown resistor value < 10
        {
            U = (int) RL;                                  // get RL upper digit
            L = ((int)((RL - U) * 10));                    // get RL lower digit
            display_upper_digit(U);                        // display upper digit
            display_lower_digit(L);                        // display lower digit
            decimal = 0;                                   // decimal point on
            printf("RL = %f\r\n\n\n", RL);                 // print RL value to teraterm
        }
        
        else                                               // if unknown resistor value is >= 10
        {
            U = (int) RL / 10;                             // get RL upper digit
            L = (int) RL % 10;                             // get RL lower digit
            display_upper_digit(U);                        // display upper digit
            display_lower_digit(L);                        // display lower digit
            decimal = 1;                                   // decimal point off
            printf("RL = %f\r\n\n\n", RL);                 // print RL value to teraterm
        }
        
        int PORTC_preshift = (RL >= 70) ? 7 : (RL/10);     // set LED D1 color
        PORTC = PORTC_preshift << 3;                       // bit shift and output to PORTC
        
        if(RL > 0.20)                                      // SET LED D2 color
        {
            SET_D2_OFF();
        }
        else if (RL >= .10 && RL <= .20)
        {
            SET_D2_RED();
        }
        else if (RL >= .050 && RL < .10)
        {
            SET_D2_BLUE();
        }
        else if (RL < .050)
        {
            SET_D2_PURPLE();
        }
        
        if (RL < .070)                                   
        {
            Activate_Buzzer();                             // activate buzzer
        }
        else
        {
            Deactivate_Buzzer();                           // deactivate buzzer
        }
        
        Delay_One_Sec();
    }
}