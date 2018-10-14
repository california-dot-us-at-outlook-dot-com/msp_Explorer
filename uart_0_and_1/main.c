#include<msp430f169.h>
#include"Config.h"

void UART0_Init()
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

  P3SEL|= BIT6;               //设置IO口为普通I/O模式
  P3DIR|= BIT6;               //设置IO口方向为输出
  P3SEL|= BIT7;
}

//*************************************************************************
//              串口0发送数据函数
//*************************************************************************

void Uart0Send_Byte(uchar data)
{
  while((IFG1&UTXIFG0)==0);          //发送寄存器空的时候发送数据
    U0TXBUF=data;
}

//*************************************************************************
//               处理来自串口 0 的接收中断
//*************************************************************************

#pragma vector=USART0RX_VECTOR
__interrupt void USART0_RX_ISR(void)
{
  uchar data=0;
  data=U0RXBUF;                       //接收到的数据存起来
  Uart0Send_Byte(data);                    //将接收到的数据再发送出去

}

//*************************************************************************
//            处理来自串口 0 的发送中断，预留
//*************************************************************************

#pragma vector=USART0TX_VECTOR
__interrupt void USART0_TX_ISR(void)
{

}
//////////////////////////////////////////////////////////////////
//下面是UART1，上面是UART0
//////////////////////////////////////////////////////////////////
void UART1_Init()
{
  U1CTL|=SWRST;               //复位SWRST
  U1CTL|=CHAR;                //8位数据模式
  U1TCTL|=SSEL1;              //SMCLK为串口时钟
  U1BR1=baud_h;               //BRCLK=8MHZ,Baud=BRCLK/N
  U1BR0=baud_l;               //N=UBR+(UxMCTL)/8
  U0MCTL=0x00;                //微调寄存器为0，波特率9600bps
  ME2|=UTXE1;                 //UART0发送使能
  ME2|=URXE1;                 //UART0接收使能
  U1CTL&=~SWRST;
  IE2|=URXIE1;                //接收中断使能位
/*
  P3SEL|= BIT4;               //设置IO口为普通I/O模式
  P3DIR|= BIT4;               //设置IO口方向为输出
  P3SEL|= BIT5;
*/
  P3SEL|= BIT6;               //设置IO口为普通I/O模式
  P3DIR|= BIT6;               //设置IO口方向为输出
  P3SEL|= BIT7;
}

//*************************************************************************
//              串口0发送数据函数
//*************************************************************************

void Uart1Send_Byte(uchar data)
{
  while((IFG2&UTXIFG1)==0);          //发送寄存器空的时候发送数据
    U1TXBUF=data;
}

//*************************************************************************
//               处理来自串口 0 的接收中断
//*************************************************************************

#pragma vector=USART1RX_VECTOR
__interrupt void USART1_RX_ISR(void)
{
  uchar data=0;
  data=U1RXBUF;                       //接收到的数据存起来
  Uart1Send_Byte(data);                    //将接收到的数据再发送出去

}

//*************************************************************************
//            处理来自串口 0 的发送中断，预留
//*************************************************************************

#pragma vector=USART1TX_VECTOR
__interrupt void USART1_TX_ISR(void)
{

}
/**
 * main.c
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    Clock_Init();
    UART0_Init();
    UART1_Init();

    _EINT();
    while(1);
}
