/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.
#include <stdint.h>

#define key_column1 PORTBbits.RB0
#define key_column2 PORTBbits.RB1
#define key_column3 PORTBbits.RB2
#define key_column4 PORTBbits.RB3

#define key_row1  LATAbits.LA0
#define key_row2  LATAbits.LA1
#define key_row3  LATAbits.LA2
#define key_row4  LATAbits.LA3

  
char getKey(uint8_t val[])
{
    key_row1 = 1;
    key_row2 = 0;
    key_row3 = 0;
    key_row4 = 0;
    
    if(key_row1 == 1)
    {
    if(key_column1 == 1) //KEY 1
    { __delay_ms(200);
    
    return '1';
    }
    else if(key_column2 == 1) //KEY 2
    { __delay_ms(200);
    return '2';  
    }
    else if(key_column3 == 1) //KEY 3
    { __delay_ms(200);
    return '3';
    }
    else if(key_column4== 1) //KEY 4
    { __delay_ms(200);
    return '4';
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
    return '4';
    }
    else if(key_column2 == 1) //KEY 5
    { __delay_ms(200);
    return '5';
    }
    else if(key_column3 == 1) //KEY 6
    { __delay_ms(200);
    return '6';
    }
    else if(key_column4 == 1) //KEY B
    { __delay_ms(200);
    return 'B'
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
    return '7';
    }
    else if(key_column2 == 1) //KEY 8
    { __delay_ms(200);
    return '8';
    }
    else if(key_column3 == 1) //KEY 9
    { __delay_ms(200);
    return '9';
    }
    else if(key_column4 == 1) //KEY C
    { __delay_ms(200);
    return 'C';
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
    return '*';
    }
    else if(key_column2 == 1) // KEY 0
    { __delay_ms(200);
    return '0';
    }
    else if(key_column3 == 1) //KEY #
    { __delay_ms(200);
    return '#';
    }
    else if(key_column4 == 1) //KEY D
    { __delay_ms(200);
    return 'D';
    }
    }
    
}

#endif	/* XC_HEADER_TEMPLATE_H */

