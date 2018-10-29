#include <msp430.h> 



unsigned char i;

/*
#pragma vector = TIMERA0_VECTOR
__interrupt void Timer_A0(void){

    P6OUT=~(TAR>>8);
}
*/

//
//作为溢出捕获时，不能（指：不准）触发TACTL0。因为比较的就是CCR0和TAR；
#pragma vector = TIMERA1_VECTOR
__interrupt void Timer_A1(void){
    //unsigned long a=0;
    //if(i%1000==0)
    //P6OUT=~(((P6OUT>>1)<<1)+1-(P6OUT%2));
/*    if(TAIV==2){
        P6OUT=~0x02;
    }else if(TAIV==1){
        P6OUT=~0x01;
    }else if(TAIV==4){
        P6OUT=~4;
    }else if(TAIV==10){
        P6OUT=~10;
    }else{
        P6OUT=0x00;
    }
    i++;
*/
    P6OUT=~TACCR1;
}
/*
#pragma vector = TIMERA2_VECTOR
__interrupt void Timer_A2(void){
    //unsigned long a=0;
    //if(i%1000==0)
    //P6OUT=~(((P6OUT>>1)<<1)+1-(P6OUT%2));
    if(TAIV==1){
        P6OUT=~0x01;
    }else if(TAIV==2){
        P6OUT=~0x02;
    }else if(TAIV==10){
        P6OUT=~10;
    }else{
        P6OUT=0;
    }
    i++;

}
*/
#define CPU_F ((double)32768)   //外部高频晶振8MHZ
//#define CPU_F ((double)32768)   //外部低频晶振32.768KHZ
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))


void main(void)
{   i=0;


    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P6DIR=0xff;
    P6OUT=0x55;

    BCSCTL1&=~XT2OFF;//0xff-DIVA_3-XT2OFF;//+DIVA_3;//-XT5V-7;//-DIVA1-DIVA0;
    /*
    BCSCTL2=SELM_2+SELS+DIVS_3;//+DIVM_3;//+DIVS_3;//SELM0+SELM1;//+SELM0;//+DIVM0+DIVM1+DIVS0+DIVS1;

    TACTL = TASSEL_1;//+ID_3;
    */
    TACCTL0=CAP+CM_1+CCIS_0;//+CM1+CM0;//+CAP;
    TACCTL1=CCIE+CAP+CM_1+CCIS_0;//+CM1+CM0;//+CAP;
    TACCTL2=CCIE+CAP+CM_1+CCIS_0;//+CM1+CM0;//+CAP;
    TACCTL0 &=(~CCIFG);
    TACCTL1 &=(~CCIFG);
    TACCTL2 &=(~CCIFG);
    TACCR0=32768;
    TACCR1=32768;
    //CCR0=32768;

    TACTL=TASSEL_1+MC_1+TAIE;
    P1SEL=0xff;
    P1DIR=0x00;
    _EINT();
    unsigned int a=0;
    while(1){
        //P6OUT = ((P6OUT>>1)<<1)+1-(P6OUT%2);
        //delay_ms(4096);
        //TACCTL1 &=(~CCIFG);

    }
    //return 0;
}
