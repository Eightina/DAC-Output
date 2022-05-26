#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 	 
#include "dac.h"
#include "adc.h"
#include "usmart.h"
#include "timer.h"


u8 num=0;//num���ڿ��������������
u8 i=0,j=0,k=0,l=0;//ijk���ڿ��������������ԡ�ֻ�������ļ���ȫ��������ijk��ֵ�Ż�䡣
//���ĸ���������timer.c���ٴε��á�����main.c��timer.c�ļ���Ҫͬʱ���ź����

 int main(void)
 {	 
	char order1[]="���Ҳ�";
	char order2[]="���ȳ�����";
	char order3[]="���վ���-Ԥ��";
	char order4[]="music";
	u16 adcx;
	float temp;
	float temperate;	 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
 	T_Adc_Init();		  		//ADC��ʼ��
	Dac1_Init();				//DAC��ʼ��
  TIM3_Int_Init(11250,0);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms  
	printf("ADC DACʵ��\r\n");
	printf("���� �׳�� ���\r\n");	  
	
	 DAC_SetChannel1Data(DAC_Align_8b_R, 0);//��ʼֵΪ0	    	      
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{
     if(USART_RX_BUF[0]==order1[0])
      {
      num=1; 
		  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
		  TIM_Cmd(TIM3, ENABLE);
			DAC_Cmd(DAC_Channel_1, ENABLE);
			USART_RX_STA=0;
      }
		 else if (USART_RX_BUF[0]==order2[0])
			{
      num=2; 
		  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
			TIM_Cmd(TIM3, ENABLE);
			DAC_Cmd(DAC_Channel_1, ENABLE);
			USART_RX_STA=0;
      }
		 else if (USART_RX_BUF[0]==order3[0])
			{
      num=3; 
		  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
			TIM_Cmd(TIM3, ENABLE);
			DAC_Cmd(DAC_Channel_1, ENABLE);
			USART_RX_STA=0;
     }
		else if (USART_RX_BUF[0]==order4[0])
			{
      num=4; 
		  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
			TIM_Cmd(TIM3, ENABLE);
			DAC_Cmd(DAC_Channel_1, ENABLE);
			USART_RX_STA=0;
     }
	}
		else
			{
 			adcx=T_Get_Adc_Average(ADC_CH_TEMP,10);		//�õ�ADCת��ֵ	  
			temp=(float)adcx*(3.3/4096);			//�õ�ADC��ѹֵ
			adcx=temp;
	    temperate=temp;
 			temperate=(1.43-temperate)/0.0043+25;		//�������ǰ�¶�ֵ	   
		  LED0=!LED0;
		  delay_ms(200);
		  printf("%.2f\r\n",temperate);
     
	}
 }
}
