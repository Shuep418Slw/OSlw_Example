/*

简单分类任务
异或门 
使用了ADAM算法


*/


//定义OS
OSlwCoreSTU myos;
//定义任务
OSlwTaskSTU mytask;
//定义内存堆
OSLW_MEM_SIMPLE_DEF(mem,32,400)
//定义神经网络结构体
OSlwToolBPnnSTU mynn;

ParaType xin[4][2],yout[4],yref[4];
//异或门输入数据 batch=4
ParaType x_data[]={0,0,
0,1,
1,0,
1,1
};
//异或门标签数据 batch=4
ParaType y_data[]={0,
1,
1,
0
};

OSlwMat X,Y;

//定义随机数
OSlwToolRandomMTSTU myrand;
OSlwToolRandomBasicSTU *pr=(void *)(&myrand);

//保存层输出
OSlwToolNNLayerFullConSTU **pfc;

void Mytask(OSlwTaskSTU *_pta)
{
	static OSlwTaskSTU *pta;
	static ParaType a=0.1;//用于初始化偏置	
	static int i;
	pta=_pta;
	OSlwJiJi(_pta);
	
	//初始化内存
	OSLW_MEM_INIT(mem);
	//设置随机数种子
	OSlwToolRandomMTSeed(&myrand,1);
	//初始化矩阵
	OSlwMatInit(&X,4,2,x_data);
	OSlwMatInit(&Y,4,1,y_data);
	
	//神经网络初始化
	OSlwToolBPnnInit(&mynn,4);
	//选择优化算法
	OSlwToolBPnnOptimInit(&mynn,OSlwToolNNOptim_Adam,0.9,0.999);
	
	//追加全连接层 隐藏层 10个神经元 使用tanh激活函数
	pfc=OSlwToolBPnnFullConAppend(&mynn,2,10,(void *)xin,NULL,NULL,NULL,pr->randn,pr,0,1/10.0,LwTanh,pmem);
	pfc[0]->_BiasInit=&a;

	//追加全连接层 输出层 1个神经元 使用sigmoid激活函数
	pfc=OSlwToolBPnnFullConAppend(&mynn,10,1,NULL,yout,NULL,NULL,pr->randn,pr,0,1/10.0,LwSigmoid,pmem);
	pfc[0]->_BiasInit=&a;
	
	
	//训练层初始化 学习速率0.01 
	OSlwToolBPnnTrainInit(&mynn,yref,pmem,pOSlwToolMatrixLossSquare,0.01);
	
	//全部数据初始化
	OSlwToolBPnnAllDataInit(&mynn,pmem);
	
	//训练10000次
	for(i=0;i<10000;i++)
	{
		//运行神经网络
		OSlwToolBPnnRun(&mynn,&X);
		
		//训练数据
		OSlwToolBPnnTrain(&mynn,&Y);
		
		//每100次打印误差
		if(i%100==0)
		{
			printf("%f\n",mynn.Error);
		}
		
	}
	
	//测试
	OSlwToolBPnnRun(&mynn,&X);
	printf("0^0 = %f\n",yout[0]);
	printf("0^1 = %f\n",yout[1]);
	printf("1^0 = %f\n",yout[2]);
	printf("1^1 = %f\n",yout[3]);
	
	for(;;)	
	{
		OSlwSleepSec(pta,1,0);
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
	
	//。。。开启OS定时器。。。
	
	myos.StartFun(&myos);
	
	return;
}

*/

