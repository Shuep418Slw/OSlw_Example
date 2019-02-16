/*
RNN GRURNN 测试8bit加法
*/

OSlwCoreSTU myos;
OSlwTaskSTU mytask;

static int rx_count=0;
lw_u8 aRxBuffer1[1];
char tx_buf[]="OSLW\n";


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


OSLW_MEM_SIMPLE_DEF(mem, 32, 1500)
OSlwToolRandomWELL512STU myrand;
OSlwToolRandomBasicSTU *pr = (void *)&myrand;
OSlwToolBPnnSTU mynn;


ParaType xin_i[8][2], yout_o[8], yref_o[8];
//ParaType hout[5][2];
//ParaType we1[4][2], dwe1[4][2];
//ParaType bi1[2], dbi1[2];
ParaType xin[8][2], yref[8];
OSlwMat X, REF;
OSlwToolNNLayerFullConSTU **pfc;
ParaType binit = 0;
ParaType bi1[100];
ParaType bi2[1];
ParaType hout[8][20];
ParaType we_out[20];
ParaType out_bi[1];

//创造数据
void CreateData(ParaType xin[8][2], ParaType yref[8], int*px1, int *px2)
{
	int x1 = pr->randint(pr, 0, (120));
	int x2 = pr->randint(pr, 0, (120));

	int out = x1 + x2;
	int i;
	for (i = 0; i < 8; i++)
	{
		xin[i][0] = _ParaFrom((x1 >> i) & 1);
		xin[i][1] = _ParaFrom((x2 >> i) & 1);
		yref[i] = _ParaFrom((out >> i) & 1);
	}

	*px1 = x1;
	*px2 = x2;

}

//数组转为定点
int Data2int(ParaType yout[8])
{
	int re = 0;
	int i;
	for (i = 0; i < 8; i++)
	{
		if (yout[i] >= _ParaFrom(0.5))
		{
			re += (1 << i);
		}

	}

	return re;
}

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
	
	OSLW_MEM_INIT(mem);
	OSlwToolRandomWELL512Seed(&myrand, 1);
	
	OSlwToolBPnnInit(&mynn, 8);

	//OSlwToolBPnnOptimInit(&mynn, OSlwToolNNOptim_Adam, _ParaFrom(0.9), _ParaFrom(0.999));

	pfc = OSlwToolBPnnGruRnnAppend(
		&mynn,
		2, 20,
		(void *)xin_i, (void *)hout,
		NULL, bi1,
		pr->rand, pr, _ParaFrom(-0.5), _ParaFrom(0.5),
		LwRnnCellType1,//0.94版本之后要加上
		LwReLU, pmem
	);
	pfc[0]->_BiasInit = &binit;


	pfc = OSlwToolBPnnFullConAppend(
		&mynn,
		20, 1,
		(void *)hout, yout_o,
		we_out, out_bi,
		pr->rand, pr, _ParaFrom(-0.5), _ParaFrom(0.5),
		LwSigmoid, pmem
	);
	pfc[0]->_BiasInit = &binit;

	OSlwToolBPnnTrainInit(&mynn, yref_o, pmem, pOSlwToolMatrixLossSquare, _ParaFrom(0.01));

	OSlwToolBPnnAllDataInit(&mynn, pmem);

	OSlwMatInit(&X, 8, 2, (void *)xin);
	OSlwMatInit(&REF, 8, 1, yref);


	
	for(;;)	
	{
		for (i = 0; i < 100000; i++)
		{
			//创造数据	
			CreateData(xin, yref, &x1, &x2);
			//运行网络
			OSlwToolBPnnRun(&mynn, &X);
			//训练
			OSlwToolBPnnTrain(&mynn, &REF);
			
			if (i % 100 == 0)
			{
				
				CreateData(xin, yref, &x1, &x2);
				t1= myos.NormalRunningTimerCount;//用来测试时间
				OSlwToolBPnnRun(&mynn, &X);
				t2= myos.NormalRunningTimerCount;//用来测试时间
				out = Data2int(yout_o);
				
				//sprintf+串口发送等价于printf
				sprintf(outs,"%d:%d + %d = %d\n",i/100, x1, x2,out);
				HAL_UART_Transmit(&huart1,outs,strlen(outs),1000); 
				
				OSlwToolBPnnClear(&mynn);//RNN执行测试之后要清除无用数据
				OSlwSleepN(pta,5);
			}
		}
		
		OSlwTaskStop(pta);
			
	}
	OSlwWeiJi(_pta);

}

