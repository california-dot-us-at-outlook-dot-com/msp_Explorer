#include <msp430.h> 
#include"Config.h"
#include<string.h>
/**
 * main.c
 */

//#define CPU_F ((double)8000000)   //外部高频晶振8MHZ

void UART_Init()
{
  U0CTL|=SWRST;               //复位SWRST
  U0CTL|=CHAR;                //8位数据模式
  U0TCTL|=SSEL1;              //SMCLK为串口时钟
  U0BR1=baud_h;               //BRCLK=8MHZ,Baud=BRCLK/N
  U0BR0=baud_l;               //N=UBR+(UxMCTL)/8
  U0MCTL=0x00;                //微调寄存器为0，波特率9600bps
  ME1|=UTXE0;                 //UART0发送使能
  ME1|=URXE0;                 //UART0接收使能
  U0CTL&=~SWRST;
  IE1|=URXIE0;                //接收中断使能位

  P3SEL|= BIT4;               //设置IO口为普通I/O模式
  P3DIR|= BIT4;               //设置IO口方向为输出
  P3SEL|= BIT5;
}

void Send_Byte(uchar data)
{
  while((IFG1&UTXIFG0)==0);          //发送寄存器空的时候发送数据
    U0TXBUF=data;
}

unsigned char a=0;
unsigned char if_int=0;
unsigned char b=0;
unsigned char c[10];
#pragma vector=USART0RX_VECTOR
__interrupt void UART0_RX_ISR(void)
{
  uchar data=0;
  data=U0RXBUF;
/*
  if(a==9){
      P6OUT=~data;
  }
  a++;
*/
  //Send_Byte(data);
  if(data==')' && b==0 ){
      //P6OUT=data;
      c[0]=data;
      b=1;

  }else if(b<8 && b>0){
      c[b]=data;
      b++;
  }
  if(b==8){
      b=0;
  }
  if_int=1;
}


void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	Clock_Init();

	UART_Init();
	c[8]='\0';
	P6DIR=0xff;
	P2DIR=0x00;
	P6OUT=0xfe;
	delay_ms(30);
	//unsigned char sign=0;
	//unsigned char *s=(char*)malloc(sizeof(char)*4096);
	//unsigned long i=0;
	//unsigned long j=0;
	_EINT();
	P6OUT=0xff;
	unsigned char cc=0;

	unsigned char if_1=1;
	unsigned char if_2=1;
	unsigned char if_3=1;
	    unsigned char if_4=1;
	    unsigned char if_5=1;
	        unsigned char if_6=1;
	        unsigned char if_7=1;
	            unsigned char if_8=1;
	            unsigned char if_9=1;
	                unsigned char if_0=1;
	unsigned char key_1[8]={41,185,187,187,185,169,171,0b10111011};
	unsigned char key_2[8]={41,185,187,187,105,105,171,187};
	unsigned char key_3[8]={41,185,187,187,0b01101101,0b01101011,0b00101011,0b01101011};
	unsigned char key_4[8]={41,185,187,187,0b01101001,
	                        0b01101001,
	                         0b01101011,
	                         0b10111011};
	unsigned char key_5[8]={41,185,187,187,0b10111001,
	                        0b00101011,
	                        0b00101011,
	                        0b10111011

	};
	unsigned char key_6[8]={41,185,187,187,0b10101101,
	                        0b01101011,
	                        0b01101011,
	                        0b10101101,

	};
	unsigned char key_7[8]={41,185,187,187,0b00101101,
	                        0b10101101,
	                        0b01101101,
	                        0b01101011,

	};
	unsigned char key_8[8]={41,185,187,187,0b00101101,
	                        0b10101101,
	                        0b01101101,
	                        0b01101011,

	};
	unsigned char key_9[8]={41,185,187,187,0b10101101,
	                        0b00111001,
	                        0b10101101,
	                        0b01101011,

	};
	unsigned char key_0[8]={41,185,187,187,0b01101101,
	                        0b00101011,
	                        0b00111001,
	                        0b10111011,

	};
	/*
	unsigned char key_4[8]={41,185,187,187,

	};
	unsigned char key_4[8]={41,185,187,187,

	};
	*/
	while(1){
	    if(if_int){
	        for(cc=0;cc<8;cc++){
	            if(c[cc]!=key_1[cc]){
	                if_1=0;
	            }
	            if(c[cc]!=key_2[cc]){
	                if_2=0;
	            }
	            if(c[cc]!=key_3[cc]){
	                                if_3=0;
	                            }
	            if(c[cc]!=key_4[cc]){
	                                if_4=0;
	                            }
	            if(c[cc]!=key_5[cc]){
	                                if_5=0;
	                            }
	            if(c[cc]!=key_6[cc]){
	                                if_6=0;
	                            }
	            if(c[cc]!=key_7[cc]){
	                                if_7=0;
	                            }
	            if(c[cc]!=key_8[cc]){
	                                if_8=0;
	                            }
	            if(c[cc]!=key_9[cc]){
	                                if_9=0;
	                            }
	            if(c[cc]!=key_0[cc]){
	                                if_0=0;
	                            }
	        }
	        if(if_1){
	            P6OUT=~0x01;
	        }else if(if_2){
	            P6OUT=~2;
	        }else if(if_3){
	            P6OUT=~3;
	        }else if(if_4){
                P6OUT=~4;
            }else if(if_5){
                P6OUT=~5;
            }else if(if_6){
                P6OUT=~6;
            }else if(if_7){
                P6OUT=~7;
            }else if(if_8){
                P6OUT=~8;
            }else if(if_9){
                P6OUT=~9;
            }else if(if_0){
                P6OUT=~0;
            }
            /*else{
                P6OUT=0;
            }*/
	        if_int=0;
	        if_1=1;
	        if_2=1;
	        if_3=1;
	        if_4=1;
	        if_5=1;
	        if_6=1;
	        if_7=1;
	        if_8=1;
	        if_9=1;
	        if_0=1;
	    }

	}
}
