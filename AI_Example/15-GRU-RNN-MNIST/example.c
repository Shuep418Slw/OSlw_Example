/*

GRU-RNN
mnist 测试

*/

void Mytask(OSlwTaskSTU *_pta)
{
	static OSlwTaskSTU *pta;
	static lw_u16 num=0;

	pta=_pta;
	OSlwJiJi(_pta);
	for(;;)	
	{
		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
		OSlwSleepSec(pta,1,0);
	}
	OSlwWeiJi(_pta);

}

OSlwTaskSTU task_sd;
lw_u8 rx_buf[500];
void SDtask(OSlwTaskSTU *_pta)
{
	static OSlwTaskSTU *pta;
	static lw_u8 *pstr;
	
	pta=_pta;
	OSlwJiJi(_pta);
	
	pta->TaskGroupFlag.AimStatus.all=0xff;
	for(;;)	
	{
		OSlwWaitFlag(pta);
		pstr=myos.StrDbgFun(&myos,rx_buf);
		HAL_UART_Transmit(&huart1,pstr,strlen(pstr),1000); 
		LwClearFlag(pta,0);
	}
	OSlwWeiJi(_pta);
}

#include "MNIST_RNN.h"

OSLW_MEM_SIMPLE_DEF(mem, 32, 1500)

OSlwToolBPnnSTU mynn;
ParaType xin[28],yout[10];
OSlwToolNNSubLayerBasicSTU **p;
lw_u32 xin_c[28];
STR_DBG_DEF(xin_c,"image")


const ParaType xin_d[28][28] = { _ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(1.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0),_ParaFrom(0.0) };


OSlwMat X = OSlwMatDef(1, 28, xin_d);
void RNNtestRun()
{
	int i ,j;
	lw_u8 outs[30];
	
	p[0]->RunningStopFlag=1;
	
	for(i=0;i<28;++i)
	{
		for(j=0;j<28;j++)
		{
			if(xin_c[i] & (1<<j))
			{
				xin[j]=_ParaFrom(1);
			}
			else
			{
				xin[j]=_ParaFrom(0);
			}
		}
		if(i==27)
		{
			p[0]->RunningStopFlag=0;
		}			
		OSlwToolBPnnRun(&mynn,NULL);	
	}
	
	
	
	for(i=0;i<10;++i)
	{
		sprintf(outs,"%d:%f\n",i,_ParaToF(yout[i]));
		HAL_UART_Transmit(&huart1,outs,strlen(outs),1000); 	
	}
	
	
	OSlwToolBPnnClear(&mynn);
	
	
}
STR_DBG_DEF(RNNtestRun,"MNIST")


OSlwTaskSTU task_NN;
void NNtask(OSlwTaskSTU *_pta)
{
	static OSlwTaskSTU *pta;
	static lw_u16 num=0;
	static lw_u32 i, j;
	static int out;
	static int x1, x2;
	static char outs[50];
	static lw_u32 t1,t2;
	pta=_pta;
	OSlwJiJi(_pta);
	
	STR_DBG_INC(myos.StrDbg,xin_c,'l',28);
	STR_DBG_INC(myos.StrDbg,RNNtestRun,'F',0);
	
	OSLW_MEM_INIT(mem);

	
	OSlwToolBPnnInit(&mynn, 1);

	mynn.Train.Flag.NeedTrain = 1;

	 OSlwToolBPnnGruRnnAppend(
		&mynn,
		28, 128,
		xin, NULL,
		(void *)we1, (void *)bi1,
		NULL, NULL, 0, 0,
		LwRnnCellType1,//0.94版本之后要加上
		LwReLU, pmem
	);

	p=OSlwToolBPnnFullConAppend(
		&mynn,
		128, 10,
		NULL, yout,
		(void *)we2, (void *)bi2,
		NULL, NULL, 0, 0,
		NULL, pmem
	);

	OSlwToolBPnnAllDataInit(&mynn, pmem);

	p[0]->RunningStopFlag = 1;

	for (i = 0; i < 27; i++)
	{
		X.a = (void *)xin_d[i];
		OSlwToolBPnnRun(&mynn, &X);
	}

	p[0]->RunningStopFlag = 0;

	X.a = (void *)xin_d[27];
	OSlwToolBPnnRun(&mynn, &X);
	
	OSlwToolBPnnClear(&mynn);
	
	for(;;)	
	{		
		OSlwTaskStop(pta);			
	}
	
	OSlwWeiJi(_pta);

}

/*
int main(void)
{
	//。。。各种初始化。。。
	
	OSlwCoreInitial(&myos);
	
	OSlwTaskInit(&mytask,3,"T1",0,NULL,Mytask);
	myos.TaskAppendFun(&myos,&mytask);	

	OSlwTaskInit(&task_NN, 4, "NN", 0, NULL, NNtask);
	myos.TaskAppendFun(&myos, &task_NN);

	OSlwTaskInit(&task_sd,5,"SD",0,NULL,SDtask);
	myos.TaskAppendFun(&myos,&task_sd);
	
	//。。。开启OS定时器。。。
	
	myos.StartFun(&myos);
	
	return;
}

*/

