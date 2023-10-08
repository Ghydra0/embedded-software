#include <p18f4620.h>
#include <stdio.h>
#include <math.h>
#include <usart.h>
#pragma config OSC = INTIO67
#pragma config WDT=OFF
#pragma config LVP=OFF
#pragma config BOREN =OFF

#define D1_RED PORTCbits.RC3
#define D1_GREEN PORTCbits.RC4
#define D1_BLUE PORTCbits.RC5

#define D2_RED PORTCbits.RC0
#define D2_GREEN PORTCbits.RC1
#define D2_BLUE PORTCbits.RC2

#define D3_GREEN PORTEbits.RE0
#define D3_BLUE PORTEbits.RE2

char LED_7seg[10] = {0x01,0x4F,0x12,0x06,0x4C,0x24,0x20,0x0F,0x00,0x04}; // 7 segment display values 0-9

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

void Init_TRIS()                                           // Init_Tris function
{
    TRISA = 0X0F;                                          // TRISA = lower 4 bits are input
    TRISB = 0X00;                                          // TRISB = output
    TRISC = 0X00;                                          // TRISC = output
    TRISD = 0X00;                                          // TRISD = output
    TRISE = 0X00;                                          // TRISE = output
    
}

void Init_ADC(void)                                        // Init_ADC function
{
    ADCON0=0x01;                                           // select channel AN0, and turn on the ADC subsystem
    ADCON1=0x1B;                                           // select pins AN0 through AN3 as analog signal, VDD-VSS as
                                                           // reference voltage
    ADCON2=0xA9;                                           // right justify the result. Set the bit conversion time (TAD) and
                                                           // acquisition time
}

void Select_ADC_Channel(char channel)                      // used to select ADC channel
{
    ADCON0 = channel * 4 + 1;                              // ADCON0 channel select conversion
}

void display_lower_digit(char digit)                       // display_lower_digit function
{
    PORTB = LED_7seg[digit];                               // PORTB = lower digit of temp
}

void display_upper_digit(char digit)                       // display_upper_digit function
{
    PORTD = LED_7seg[digit];                               // PORTD = upper digit of temp
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

void Delay_One_Sec()                                       // create a one second delay
{
    for(int I=0; I <17000; I++);
}

//D1
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

//D2
void SET_D2_OFF()                                          // D2 = 0FF
{
    D2_RED = 0;                                            //
    D2_GREEN = 0;                                          //
    D2_BLUE = 0;                                           //
}
void SET_D2_RED()                                          // D2 = RED
{
    D2_RED = 1;                                            //
    D2_GREEN = 0;                                          //
    D2_BLUE = 0;                                           //
}
void SET_D2_GREEN()                                        // D2 = GREEN
{
    D2_RED = 0;                                            //
    D2_GREEN = 1;                                          //
    D2_BLUE = 0;                                           //
}

void SET_D2_YELLOW()                                       // D2 = YELLOW
{
    D2_RED = 1;                                            //
    D2_GREEN = 1;                                          //
    D2_BLUE = 0;                                           //
}
void SET_D2_BLUE()                                         // D2 = BLUE
{
    D2_RED = 0;                                            //
    D2_GREEN = 0;                                          //
    D2_BLUE = 1;                                           //
}
void SET_D2_PURPLE()                                       // D2 = PURPLE
{
    D2_RED = 1;                                            //
    D2_GREEN = 0;                                          //
    D2_BLUE = 1;                                           //
}
void SET_D2_CYAN()                                         // D2 = CYAN
{
    D2_RED = 0;                                            //
    D2_GREEN = 1;                                          //
    D2_BLUE = 1;                                           //
}
void SET_D2_WHITE()                                        // D2 = WHITE
{
    D2_RED = 1;                                            //
    D2_GREEN = 1;                                          //
    D2_BLUE = 1;                                           //
}

//D3
void SET_D3_OFF()                                          // D3 = OFF
{
    D3_GREEN = 0;                                          //
    D3_BLUE = 0;                                           //
}

void SET_D3_GREEN()                                        // D3 = GREEN
{
    D3_GREEN = 1;                                          //
    D3_BLUE = 0;                                           //
}
void SET_D3_BLUE()                                         // D3 = BLUE
{
    D3_GREEN = 0;                                          //
    D3_BLUE = 1;                                           //
}
void SET_D3_CYAN()                                         // D3 = CYAN
{
    D3_GREEN = 1;                                          //
    D3_BLUE = 1;                                           //
}

void main()                                                // start main
{
    Init_UART();                                           // initialize UART
    Init_ADC();                                            // initialize ADC
    Init_TRIS();                                           // initialize TRIS
    
    for (int i=0; i<10; i++)                               // startup test loop for seven segment
        {                                                  // will display numbers 1-10 on lower and upper digit
            display_lower_digit(i);                        // display i on lower digit
            display_upper_digit(i);                        // display i on upper digit
            Delay_One_Sec();                               // one second delay
        }
    
    while(1)                                               // start infinite while loop
    {
        Select_ADC_Channel(0);                             // Select Channel AN0
        int num_step = get_full_ADC();                     // number of A/D conversion steps
        float voltage_mv = num_step * 4.0;                 // steps * 4mv/step = voltage(mv)
        float temp_C = (1035.0 - voltage_mv) / 5.50;       // get temp in C from voltage
        float temp_F = 1.80 * temp_C + 32.0;               // convert temp to F
        int tempF = (int) temp_F;                          // turn temp_F into int
        char temp_upper = tempF / 10;                      // get only upper digit of temp
        char temp_lower = tempF % 10;                      // get only lower digit of temp
        
        display_lower_digit(temp_lower);                   // call display_lower_digit function
        display_upper_digit(temp_upper);                   // call display_upper_digit function
        printf ("Voltage = %f (mV) \r\n", voltage_mv);     // print out thermistor voltage to TeraTerm
        printf ("Temperature = %d F \r\n\n", tempF);       // print out tempF to TeraTerm
        
                                                           // set D2 color
        if(tempF < 10) SET_D2_OFF();                       // if tempF < 10, D2 = OFF
        else if (tempF >= 70) SET_D2_WHITE();              // else if temp>=70, D2 = WHITE
        else (PORTC = tempF/10);                           // else set D2 LED color based off temp/10
        
                                                           // set D1 color
        if (tempF < 40)                                    // if tempF < 40, D1 = OFF
        {
            SET_D1_OFF();
        }
        else if (tempF >= 40 && tempF <=49)                // if tempF 40-49, D1 = RED
        {
            SET_D1_RED();
        }
        else if (tempF >= 50 && tempF <=59)                // if tempF 50-59, D1 = GREEN
        {
            SET_D1_GREEN();
        }
        else if (tempF >= 60 && tempF <=69)                // if tempF 60-69, D1 = BLUE
        {
            SET_D1_BLUE();
        }
        else if (tempF >= 70 && tempF <=75)                // if tempF 70-75, D1 = PURPLE
        {
            SET_D1_PURPLE();
        }
        else if (tempF >= 76 && tempF <=80)                // if tempF 76-80, D1 = CYAN
        {
            SET_D1_CYAN();
        }
        else if (tempF >= 81)                              // if tempF >= 81, D1 = WHITE
        {
            SET_D1_WHITE();
        }                                                  // end set D1 color

        Select_ADC_Channel(2);                             // Select channel AN1 to read photo resistor values
        int num_step = get_full_ADC();                     // get number of steps from channel AN1
        float voltage_mv1 = (num_step *4.0) / 1000;        // photo resistor value in volts
        if (voltage_mv1 <2.6)                              // if voltage less than 2.6
        {
            SET_D3_OFF();                                  // set RGB LED D3 to OFF
        }
        else if (voltage_mv1 >= 2.6 && voltage_mv1 < 3.0)  // if voltage between 2.6 and 3.0
        {
            SET_D3_GREEN();                                // set RBG LED D3 to GREEN
        }
        else if (voltage_mv1 >= 3.0 && voltage_mv1 < 3.3)  // if voltage between 3 and 3.3
        {
            SET_D3_BLUE();                                 // set RGB LED D3 to BLUE
        }
        else SET_D3_CYAN();                                // else set RGB D3 to CYAN
        
        printf ("Light Voltage = %f V \r\n", voltage_mv1); // print out the light voltage ADC value on TeraTerm
        Delay_One_Sec();                                   // delay one sec to see TeraTerm results slower
    }                                                      // end while loop
    
    
}                                                          // end main
