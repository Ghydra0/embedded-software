#include <p18f4620.h>
#include <stdio.h>
#include <math.h>
#include <usart.h>
#pragma config OSC = INTIO67
#pragma config WDT=OFF
#pragma config LVP=OFF
#pragma config BOREN =OFF // placeholder: teraterm - dvm / dvm * 1000

#define decimal PORTEbits.RE0

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
    ADCON1=0x1E;                                           // select pins AN0 as analog input, VREF+ reference,
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

void Delay_One_Sec()                                       // create a one second delay
{
    for(int I=0; I <17000; I++);
}

void Deactivate_Buzzer()                                   // deactivates the buzzer
{
    CCP2CON = 0x0;
    PORTCbits.RC1 = 0;
} 

void main()
{
    Init_ADC();                                            // initialize ADC
    Init_TRIS();                                           // initialize TRIS
    Init_UART();                                           // initialize UART
    
    while(1)
    {
        Deactivate_Buzzer();                           // deactivate buzzer
        Select_ADC_Channel(0);                             // Select Channel AN0
        int num_step = get_full_ADC();                     // number of A/D conversion steps
        float voltage_v = (num_step *4.0) / 1000.0;        // potentiometer voltage drop in volts
        char voltage_upper = (int) voltage_v;              // get only upper digit of temp
        char voltage_lower = (int)((voltage_v - voltage_upper)*10);   // get only lower digit of temp
     
        //PORTE = 0xFF;                                      // PORTE is on, displays decimal point
        decimal = 0;
        display_lower_digit(voltage_lower);                // call display_lower_digit function
        display_upper_digit(voltage_upper);                // call display_upper_digit function
        printf ("Voltage = %f (V) \r\n", voltage_v);       // print out potentiometer voltage to TeraTerm   
        
        Delay_One_Sec();
    }
    
    
}