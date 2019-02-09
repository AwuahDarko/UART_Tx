/*
 * File:   main.c
 * Author: Yaw Awuah Darko
 *
 * Created on December 15, 2018, 7:12 PM
 */


#include "m_UART.h"


#define UP PORTBbits.RB0
#define Down PORTBbits.RB1
#define Send PORTBbits.RB2

void LCD_Init();
void LCD_Clear();
void LCD_Command(char );
void LCD_Char(char x);
void LCD_String(const char *);
void LCD_String_xy(char ,char ,const char*);
void MSdelay(unsigned int); 

void initUART_tx(void);
void writeUART(uint8_t );
uint8_t emptyUART_tx();
void FOSC(void);
void setupPort(void);
void getKey(uint8_t val[]);
void screenFormat(void);
void setupInterrupt(void);
void reset(void);

uint8_t Data[100];
short index = -1;
short pos = -1;
short row = 1;
//*********************************************************
void __interrupt ISR()
{
    if(RBIF == 1){
        if(PORTBbits.RB4 == 1){
            for(int i = 0; i <= index; ++i)
            {
               writeUART(Data[i]); 
            }
            reset();
            
        } 
        RBIF = 0;
    }
}
//*********************************************************
void main(void) {
    FOSC();
    setupPort();
    setupInterrupt();
    initUART_tx();
    LCD_Init();
    
    LCD_String_xy(1,0,"Initializing...");
    __delay_ms(1000);
    LCD_Clear();
    LCD_String_xy(1,0,"Welcome!");
    __delay_ms(1000);
    LCD_Clear();
    
    
    while(1)
  {
   getKey(Data);
   __delay_ms(10);
   
  } 
    return;
}


void initUART_tx(void)
{
    BRGH = 1;
    SPBRG = 52;
    
    SYNC = 0;
    SPEN = 1;
    
    TRISCbits.RC6 = 1;
    TRISCbits.RC7 = 1;
    
    TXEN = 1;
}

void FOSC(void)
{
   //setting internal oscillator = 8000000MHz
    IRCF0 = 1;
    IRCF1 = 1;
    IRCF2 = 1;
}

void writeUART(uint8_t data)
{
  while(!TRMT);
  TXREG = data;
}
uint8_t emptyUART_tx()
{
   return TRMT; 
}

void setupPort(void)
{
    TRISBbits.RB0 = 1;
    TRISBbits.RB1 = 1;
    TRISBbits.RB2 = 1;
    TRISBbits.RB3 = 1;
    
    TRISDbits.RD0 = 0;
    TRISDbits.RD1 = 0;
    TRISDbits.RD2 = 0;
    TRISDbits.RD3 = 0;
    TRISDbits.RD4 = 0;
    TRISDbits.RD5 = 0;
    TRISDbits.RD6 = 0;
    TRISDbits.RD7 = 0;
    
    PORTDbits.RD0 = 0;
    PORTDbits.RD1 = 0;
    PORTDbits.RD2 = 0;
    PORTDbits.RD3 = 0;
    PORTDbits.RD4 = 0;
    PORTDbits.RD5 = 0;
    PORTDbits.RD6 = 0;
    PORTDbits.RD7 = 0;
    
    TRISAbits.RA0 = 0;
    TRISAbits.RA1 = 0;
    TRISAbits.RA2 = 0;
    TRISAbits.RA3 = 0;
    
    PORTAbits.RA0 = 0;
    PORTAbits.RA1 = 0;
    PORTAbits.RA2 = 0;
    PORTAbits.RA3 = 0;
    
}

void LCD_Init()
{
    MSdelay(15);           /*15ms,16x2 LCD Power on delay*/
   	LCD_Port = 0x00;       /*Set PORTD as output PORT for LCD data(D0-D7) pins*/
    LCD_Control = 0x00;    /*Set PORTC as output PORT LCD Control(RS,EN) Pins*/
	LCD_Command(0x38);     /*uses 2 line and initialize 5*7 matrix of LCD*/
    LCD_Command(0x01);     /*clear display screen*/
    LCD_Command(0x0c);     /*display on cursor off*/
    LCD_Command(0x06);     /*increment cursor (shift cursor to right)*/
}

void LCD_Clear()
{
    LCD_Command(0x01);     /*clear display screen*/
}

void LCD_Command(char cmd )
{
	ldata= cmd;            /*Send data to PORT as a command for LCD*/   
	RS = 0;                /*Command Register is selected*/
	EN = 1;                /*High-to-Low pulse on Enable pin to latch data*/ 
	NOP();
	EN = 0;
	MSdelay(3);	
}

void LCD_Char(char dat)
{
	ldata= dat;            /*Send data to LCD*/  
	RS = 1;                /*Data Register is selected*/
	EN=1;                  /*High-to-Low pulse on Enable pin to latch data*/   
	NOP();
	EN=0;
    MSdelay(1);
}

void LCD_String(const char *msg)
{
	while((*msg)!=0)
	{		
	  LCD_Char(*msg);
	  msg++;	
    }		
}

void LCD_String_xy(char row,char pos,const char *msg)
{
    char location=0;
    if(row<=1)
    {
        location=(0x80) | ((pos) & 0x0f); /*Print message on 1st row and desired location*/
        LCD_Command(location);
    }
    else
    {
        location=(0xC0) | ((pos) & 0x0f); /*Print message on 2nd row and desired location*/
        LCD_Command(location);    
    }  
    LCD_String(msg);
}

void MSdelay(unsigned int val)
{
     unsigned int i,j;
        for(i=0;i<=val;i++)
            for(j=0;j<81;j++);      /*This count Provide delay of 1 ms for 8MHz Frequency */
}

void getKey(uint8_t val[])
{
    screenFormat();
    
    key_row1 = 1;
    key_row2 = 0;
    key_row3 = 0;
    key_row4 = 0;
    
    if(key_row1 == 1)
    {
    if(key_column1 == 1) //KEY 1
    { __delay_ms(200);
    
    ++index;
    val[index] = 1;
    ++pos;
    LCD_String_xy(row, pos, "1");
    }
    else if(key_column2 == 1) //KEY 2
    { __delay_ms(200);
    
    ++index;
    val[index] = 2;
    ++pos;
    LCD_String_xy(row, pos, "2"); 
    }
    else if(key_column3 == 1) //KEY 3
    { __delay_ms(200);
    
    ++index;
    val[index] = 3;
    ++pos;
    LCD_String_xy(row, pos, "3");
    }
    else if(key_column4 == 1) //KEY A
    { __delay_ms(200);
    
    ++index;
    val[index] = 4;
    ++pos;
    LCD_String_xy(row, pos, "A");
    }
    }
    //--------------------------------------------
    key_row1 = 0;
    key_row2 = 1;
    key_row3 = 0;
    key_row4 = 0;
    
    if(key_row2 == 1)
    {
    if(key_column1 == 1) //KEY 4
    { __delay_ms(200);
    
    ++index;
    val[index] = 5;
    ++pos;
    LCD_String_xy(row, pos, "4");
    }
    else if(key_column2 == 1) //KEY 5
    { __delay_ms(200);
    
    ++index;
    val[index] = 6;
    ++pos;
    LCD_String_xy(row, pos, "5");
    }
    else if(key_column3 == 1) //KEY 6
    { __delay_ms(200);
    ++index;
    val[index] = 7;
    ++pos;
    LCD_String_xy(row, pos, "6");
    }
    else if(key_column4 == 1) //KEY B
    { __delay_ms(200);
    ++index;
    val[index] = 8;
    ++pos;
    LCD_String_xy(row, pos, "B");
    }
    }
    //----------------------------------------------
    
    key_row1 = 0;
    key_row2 = 0;
    key_row3 = 1;
    key_row4 = 0;
    
    if(key_row3 == 1)
    {
    if(key_column1 == 1) //KEY 7
    { __delay_ms(200);
    ++index;
    val[index] = 9;
    ++pos;
    LCD_String_xy(row, pos, "7");
    }
    else if(key_column2 == 1) //KEY 8
    { __delay_ms(200);
    ++index;
    val[index] = 10;
    ++pos;
    LCD_String_xy(row, pos, "8");
    }
    else if(key_column3 == 1) //KEY 9
    { __delay_ms(200);
    ++index;
    val[index] = 11;
    ++pos;
    LCD_String_xy(row, pos, "9");
    }
    else if(key_column4 == 1) //KEY C
    { __delay_ms(200);
    ++index;
    val[index] = 12;
    ++pos;
    LCD_String_xy(row, pos, "C");
    }
    }
    //----------------------------------------------
    
    key_row1 = 0;
    key_row2 = 0;
    key_row3 = 0;
    key_row4 = 1;
    
    if(key_row4 == 1)
    {
    if(key_column1 == 1) //KEY *
    { __delay_ms(200);
    ++index;
    val[index] = 13;
    ++pos;
    LCD_String_xy(row, pos, "*");
    }
    else if(key_column2 == 1) // KEY 0
    { __delay_ms(200);
    ++index;
    val[index] = 14;
    ++pos;
    LCD_String_xy(row, pos, "0");
    }
    else if(key_column3 == 1) //KEY #
    { __delay_ms(200);
    ++index;
    val[index] = 15;
   ++pos;
    LCD_String_xy(row, pos, "#");
    }
    else if(key_column4 == 1) //KEY D
    { __delay_ms(200);
    ++index;
    val[index] = 16;
    ++pos;
    LCD_String_xy(row, pos, "D");
    }
    }
}

void screenFormat(void)
{
    if(row == 1 && pos >= 15)
    {
        row = 3; pos = -1;
    }
    else if(row == 2 && pos > 15)
    {
        row = 1; pos = -1;
        LCD_Clear();
    }
}

void setupInterrupt()
{
     RBIE = 1;
    RBIP = 1;
    RBIF = 0;
    GIE = 1;
    
}

void reset(void)
{
   index = -1;
   
}