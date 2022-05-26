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


u8 num=0;//num用于控制输出哪条语音
u8 i=0,j=0,k=0,l=0;//ijk用于控制语音的完整性。只有语音文件完全播放完了ijk的值才会变。
//此四个变量都在timer.c中再次调用。所以main.c与timer.c文件需要同时看才好理解

 int main(void)
 {	 
	char order1[]="正弦波";
	char order2[]="急救车声音";
	char order3[]="防空警报-预告";
	char order4[]="music";
	u16 adcx;
	float temp;
	float temperate;	 
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为9600
 	LED_Init();			     //LED端口初始化
 	T_Adc_Init();		  		//ADC初始化
	Dac1_Init();				//DAC初始化
  TIM3_Int_Init(11250,0);//10Khz的计数频率，计数到5000为500ms  
	printf("ADC DAC实验\r\n");
	printf("秦扬 易晨歆 组合\r\n");	  
	
	 DAC_SetChannel1Data(DAC_Align_8b_R, 0);//初始值为0	    	      
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
 			adcx=T_Get_Adc_Average(ADC_CH_TEMP,10);		//得到ADC转换值	  
			temp=(float)adcx*(3.3/4096);			//得到ADC电压值
			adcx=temp;
	    temperate=temp;
 			temperate=(1.43-temperate)/0.0043+25;		//计算出当前温度值	   
		  LED0=!LED0;
		  delay_ms(200);
		  printf("%.2f\r\n",temperate);
     
	}
 }
}
