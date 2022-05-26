#include "timer.h"
#include "led.h"
#include "usart.h"	

#include "yinpin.h"   	 

//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
u16 wavecount=0;
extern u8 num;
extern u8 i;
extern u8 j;
extern u8 k;
extern u8 l;	

void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
}
//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{ 
	u16 tmpCap;
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
		{
			if(num==1){
			if(wavecount < 32000 )//���ݶ�Ӧ��Ƶ���볤�ȶ������
		{
			i=1;
			tmpCap = SINE[wavecount];
			wavecount++;
			/* Set DAC Channel1 DHR register */
			DAC_SetChannel1Data(DAC_Align_8b_R,tmpCap);                        
		}
		else
		{
			// ��ɴ��䣬�ر��ж�
			i=0;
			wavecount = 0;
			TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
			TIM_Cmd(TIM3, DISABLE);
			 // ��Ҫ�ر�DAC����Ȼ��û��������ʱ���������
			DAC_Cmd(DAC_Channel_1, DISABLE);
		}
		}
			else if(num==2){
			if( wavecount < 32000 )
		{
			j=1;
			tmpCap = anjian2[wavecount];
			wavecount++;
			DAC_SetChannel1Data(DAC_Align_8b_R,tmpCap);                        
		}
		else
		{
			// ��ɴ��䣬�ر��ж�
			j=0;
			wavecount = 0;
			TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
			TIM_Cmd(TIM3, DISABLE);
			 // ��Ҫ�ر�DAC����Ȼ��û��������ʱ���������
			DAC_Cmd(DAC_Channel_1, DISABLE);
		}
		}
				else if(num==3){
			if( wavecount < 36831 )
		{
			k=1;
			tmpCap = anjian3[wavecount];
			wavecount++;
			/* Set DAC Channel1 DHR register */
			DAC_SetChannel1Data(DAC_Align_8b_R,tmpCap);                        
		}
		else
		{
			// ��ɴ��䣬�ر��ж�
		  k=0;
			wavecount = 0;
			TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
			TIM_Cmd(TIM3, DISABLE);
			 // ��Ҫ�ر�DAC����Ȼ��û��������ʱ���������
			DAC_Cmd(DAC_Channel_1, DISABLE);
		}
		}
				else if(num==4){
			if( wavecount < 63098)
		{
			l=1;
			tmpCap = anjian4[wavecount];
			wavecount++;
			/* Set DAC Channel1 DHR register */
			DAC_SetChannel1Data(DAC_Align_8b_R,tmpCap);                        
		}
		else
		{
			// ��ɴ��䣬�ر��ж�
		  l=0;
			wavecount = 0;
			TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
			TIM_Cmd(TIM3, DISABLE);
			 // ��Ҫ�ر�DAC����Ȼ��û��������ʱ���������
			DAC_Cmd(DAC_Channel_1, DISABLE);
		}
		}
			else	
				{
			// ��ɴ��䣬�ر��ж�
			wavecount = 0;
			TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
			TIM_Cmd(TIM3, DISABLE);
			 // ��Ҫ�ر�DAC����Ȼ��û��������ʱ���������
			DAC_Cmd(DAC_Channel_1, DISABLE);
		}
		}
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
		
		}












