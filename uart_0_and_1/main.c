#include<msp430f169.h>
#include"Config.h"

void UART0_Init()
{
  U0CTL|=SWRST;               //��λSWRST
  U0CTL|=CHAR;                //8λ����ģʽ
  U0TCTL|=SSEL1;              //SMCLKΪ����ʱ��
  U0BR1=baud_h;               //BRCLK=8MHZ,Baud=BRCLK/N
  U0BR0=baud_l;               //N=UBR+(UxMCTL)/8
  U0MCTL=0x00;                //΢���Ĵ���Ϊ0��������9600bps
  ME1|=UTXE0;                 //UART0����ʹ��
  ME1|=URXE0;                 //UART0����ʹ��
  U0CTL&=~SWRST;
  IE1|=URXIE0;                //�����ж�ʹ��λ

  P3SEL|= BIT4;               //����IO��Ϊ��ͨI/Oģʽ
  P3DIR|= BIT4;               //����IO�ڷ���Ϊ���
  P3SEL|= BIT5;

  P3SEL|= BIT6;               //����IO��Ϊ��ͨI/Oģʽ
  P3DIR|= BIT6;               //����IO�ڷ���Ϊ���
  P3SEL|= BIT7;
}

//*************************************************************************
//              ����0�������ݺ���
//*************************************************************************

void Uart0Send_Byte(uchar data)
{
  while((IFG1&UTXIFG0)==0);          //���ͼĴ����յ�ʱ��������
    U0TXBUF=data;
}

//*************************************************************************
//               �������Դ��� 0 �Ľ����ж�
//*************************************************************************

#pragma vector=USART0RX_VECTOR
__interrupt void USART0_RX_ISR(void)
{
  uchar data=0;
  data=U0RXBUF;                       //���յ������ݴ�����
  Uart0Send_Byte(data);                    //�����յ��������ٷ��ͳ�ȥ

}

//*************************************************************************
//            �������Դ��� 0 �ķ����жϣ�Ԥ��
//*************************************************************************

#pragma vector=USART0TX_VECTOR
__interrupt void USART0_TX_ISR(void)
{

}
//////////////////////////////////////////////////////////////////
//������UART1��������UART0
//////////////////////////////////////////////////////////////////
void UART1_Init()
{
  U1CTL|=SWRST;               //��λSWRST
  U1CTL|=CHAR;                //8λ����ģʽ
  U1TCTL|=SSEL1;              //SMCLKΪ����ʱ��
  U1BR1=baud_h;               //BRCLK=8MHZ,Baud=BRCLK/N
  U1BR0=baud_l;               //N=UBR+(UxMCTL)/8
  U0MCTL=0x00;                //΢���Ĵ���Ϊ0��������9600bps
  ME2|=UTXE1;                 //UART0����ʹ��
  ME2|=URXE1;                 //UART0����ʹ��
  U1CTL&=~SWRST;
  IE2|=URXIE1;                //�����ж�ʹ��λ
/*
  P3SEL|= BIT4;               //����IO��Ϊ��ͨI/Oģʽ
  P3DIR|= BIT4;               //����IO�ڷ���Ϊ���
  P3SEL|= BIT5;
*/
  P3SEL|= BIT6;               //����IO��Ϊ��ͨI/Oģʽ
  P3DIR|= BIT6;               //����IO�ڷ���Ϊ���
  P3SEL|= BIT7;
}

//*************************************************************************
//              ����0�������ݺ���
//*************************************************************************

void Uart1Send_Byte(uchar data)
{
  while((IFG2&UTXIFG1)==0);          //���ͼĴ����յ�ʱ��������
    U1TXBUF=data;
}

//*************************************************************************
//               �������Դ��� 0 �Ľ����ж�
//*************************************************************************

#pragma vector=USART1RX_VECTOR
__interrupt void USART1_RX_ISR(void)
{
  uchar data=0;
  data=U1RXBUF;                       //���յ������ݴ�����
  Uart1Send_Byte(data);                    //�����յ��������ٷ��ͳ�ȥ

}

//*************************************************************************
//            �������Դ��� 0 �ķ����жϣ�Ԥ��
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
