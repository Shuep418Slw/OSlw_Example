/*

CNN简单分类测试

用于分类5*5图像上的矩形是长>宽 长<宽还是长=宽

长>宽:
0 1 0 0 0
0 1 0 0 0
0 1 0 0 0
0 0 0 0 0
0 0 0 0 0 

长>宽:
0 0 0 0 0
0 0 0 0 0
0 1 1 1 0
0 1 1 1 0
0 0 0 0 0 

长=宽:
0 0 0 0 0
0 0 0 0 0
0 0 0 1 1
0 0 0 1 1
0 0 0 0 0 

*/
//定义OS
OSlwCoreSTU myos;

#define CNN_MODE 1

//闪灯任务 确认OS在运行
OSlwTaskSTU mytask;
void Mytask(OSlwTaskSTU *_pta)
{
	static OSlwTaskSTU *pta;
	pta=_pta;
	OSlwJiJi(_pta);
	for(;;)	
	{		
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		OSlwSleepSec(pta,1,0);
	}
	OSlwWeiJi(_pta);

}

//StrDbg任务 用于测试
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

//定义内存堆
OSLW_MEM_SIMPLE_DEF(mem, 32, 2000)

//定义NN
OSlwToolBPnnSTU mynn;
//定义随机数
OSlwToolRandomWELL512STU myrand;
OSlwToolRandomBasicSTU *pr = (void *)(&myrand);
//定义输入输出 方便测试
ParaType xin[5][5], yout[3], yref[3];

OSlwToolNNLayerFullConSTU **pfc;

//创造一个数据 边创造边测试
void CREATE_data()
{
	
	int i, j;
	int l1, l2;
	int r1, r2;
	memset(xin, 0, sizeof(xin));
	memset(yref, 0, sizeof(yref));
	l1 = pr->randint(pr, 0, 5);
	l2 = pr->randint(pr, 0, 5);
	r1 = pr->randint(pr, l1, 5);
	r2 = pr->randint(pr, l2, 5);


	for ( i = 0; i < 5; i++)
	{
		for ( j = 0; j < 5; j++)
		{
			if (i >= l1 && i <= r1 && j >= l2 &&j <= r2)
			{
				xin[i][j] = 1;
			}
		}

	}

	if ((r1-l1) == (r2-l2))
	{
		yref[0] = 1;
	}
	else if ((r1 - l1) > (r2 - l2))
	{
		yref[1] = 1;
	}
	else if ((r1 - l1) < (r2 - l2))
	{
		yref[2] = 1;
	}

	else
	{
		OSLW_assert(1);
	}

}

lw_u8 xin_c[5];
//strdbg定义:输入变量 用于测试接口
STR_DBG_DEF(xin_c,"XIN")

//测试函数
void CNNtestRun()
{
	int i ,j;
	lw_u8 outs[30];
	for(i=0;i<5;++i)
	{
		for(j=0;j<5;j++)
		{
			if(xin_c[i] & (1<<j))
			{
				xin[i][j]=1;
			}
			else
			{
				xin[i][j]=0;
			}
		}
	}
	
	OSlwToolBPnnRun(&mynn,NULL);
	for(i=0;i<3;++i)
	{
		//串口发送+sprintf=printf
		LwSprintf(outs,"%d:%f\n",i,yout[i]);
		HAL_UART_Transmit(&huart1,outs,strlen(outs),1000); 	
	}	
}
//strdbg定义：CNN测试函数 测试使用 @CNN
STR_DBG_DEF(CNNtestRun,"CNN")



OSlwTaskSTU task_NN;

void NN_Train(lw_u16 *p)
{
	if(*p)
	{
		task_NN.TaskFrozenFlag=0;
	}
	else
	{
		task_NN.TaskFrozenFlag=1;
	}
	
}
//strdbg定义：训练使能函数 用于暂停训练
STR_DBG_DEF(NN_Train,"TRAIN")

void NNtask(OSlwTaskSTU *_pta)
{
	static OSlwTaskSTU *pta;
	static ParaType a= 0.1;
	static lw_u32 info[4];
	static int i, j;
	static lw_u8 str[50];
	static ParaType sum=0;	
	pta=_pta;
	OSlwJiJi(_pta);
	
	//strdbg追加函数
	STR_DBG_INC(myos.StrDbg,xin_c,'c',5);
	STR_DBG_INC(myos.StrDbg,CNNtestRun,'F',0);
	STR_DBG_INC(myos.StrDbg,NN_Train,'F',1);
	
	//初始化内存 随机数 NN
	OSLW_MEM_INIT(mem);
	OSlwToolRandomWELL512Seed(&myrand, 1);
	OSlwToolBPnnInit(&mynn, 1);
	//使用ADAM优化算法
	OSlwToolBPnnOptimInit(&mynn, OSlwToolNNOptim_Adam, 0.9, 0.999);

	//追加CNN层 
	pfc=OSlwToolBPnnConvAppend(
		&mynn,
		5, 5, 1,//输入 5*5*1
		2, 2, 8,//8个核 每个核2*2
		(void *)xin, NULL,
		NULL, NULL,
		pr->randn, pr, 0, 0.1,//正态分布初始化 均值0方差0.1
		LwReLU,//ReLU激活函数
		pmem, info//info用于保存输出tensor信息
	);
	pfc[0]->_BiasInit = &a;

	//追加池化层
	OSlwToolBPnnPoolAppend(
		&mynn,
		info[0], info[1], info[2],//info前3个代表输出tensor长宽高
		2, 2,//池化间隔2*2
		NULL, NULL,
		OSlwToolNNPoolingMethod_Avg,//平均值池化
		pmem,
		info
	);

	//追加全连接层
	pfc=OSlwToolBPnnFullConAppend(
		&mynn,
		info[3], info[3],//info[3]代表tensor总大小
		NULL, NULL,
		NULL, NULL,
		pr->randn, pr, 0, 0.1,
		LwReLU, pmem
	);
	pfc[0]->_BiasInit = &a;
	//追加全连接层
	pfc=OSlwToolBPnnFullConAppend(
		&mynn,
		info[3], 3,//3分类问题
		NULL, yout,
		NULL, NULL,
		pr->randn, pr, 0, 0.1,
		LwSoftMax, pmem//使用softmax激活
	);
	pfc[0]->_BiasInit = &a;

	//训练层初始化 使用交叉熵损失
	OSlwToolBPnnTrainInit(&mynn, yref, pmem, pOSlwToolMatrixLossCrossEntropyForSoftMax, 1e-3);
	
	OSlwToolBPnnAllDataInit(&mynn, pmem);


	pta->TaskFrozenFlag=1;
	OSlwSleepSec(pta,1,0);
	OSlwSleepSec(pta,1,0);
	
	
	for (i = 0; i < 10000; i++)
	{
		//batch=20
		for (j = 0; j < 20; j++)
		{
			//创造数据
			CREATE_data();
			//运行神经网络
			OSlwToolBPnnRun(&mynn, NULL);
			//求误差(偏导)
			OSlwToolBPnnCalErr(&mynn);
			sum += mynn.Error;
		}
		//批梯度下降
		OSlwToolBPnnReview(&mynn);

		if (i%20==0)
		{
			//串口发送+sprintf=printf
			sprintf(str,"%d:%f\n",i, sum/50.0);
			HAL_UART_Transmit(&huart1,str,strlen(str),1000); 
			
			sum = 0;
			//延时让其他任务执行
			OSlwSleepN(pta,10);
		}

	}
	
	while(1)
	{
		pta->TaskFrozenFlag=1;
		OSlwSleepSec(pta,10,0);
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