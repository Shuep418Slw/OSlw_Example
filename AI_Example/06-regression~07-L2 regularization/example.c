/*

函数逼近测试
被逼近函数y=x(含噪声)
可观察有无L2正则效果

*/
//定义OS
OSlwCoreSTU myos;

//定义任务
OSlwTaskSTU mytask;
uint16_t status;


//定义随机数
OSlwToolRandomWELL512STU myrand;
OSlwToolRandomBasicSTU *pr=&myrand;
char out_s[30];
ParaType data;
static lw_sf buf;

//定义内存堆
OSLW_MEM_SIMPLE_DEF(mem,16,200);
//定义神经网络
OSlwToolBPnnSTU mynn;
//定义返回层
OSlwToolNNLayerFullConSTU **pFC;
//偏置初始化
ParaType BIASINIT = _ParaFrom(0.1);
ParaType xin[1]={_ParaFrom(-0.5)};
ParaType yout[1];
ParaType yref[1];

//被训练数据
ParaType x_date[4]={_ParaFrom(-0.5),_ParaFrom(-0.25),_ParaFrom(0.25),_ParaFrom(0.5)};
ParaType y_date[4]={_ParaFrom(-0.5),_ParaFrom(-0.6),_ParaFrom(0.4),_ParaFrom(0.5)};

void Mytask(OSlwTaskSTU *_pta)
{
    static OSlwTaskSTU *pta;
    static int i,j;
    static ParaType sum=0;
    static lw_sf temp;
    pta=_pta;
    OSlwJiJi(_pta);

	//初始化随机数 内存 神经网络
    OSlwToolRandomWELL512Seed(pr,(1));
    OSLW_MEM_INIT(mem);
    OSlwToolBPnnInit(&mynn, 1);

	//追加层
    pFC=OSlwToolBPnnFullConAppend(
        &mynn,
        1,20,
        xin, NULL,
        NULL,NULL,
        pr->rand, pr, _ParaFrom(-1), _ParaFrom(1),
        LwTanh, pmem
    );
    pFC[0]->_BiasInit = &BIASINIT;

	//追加层 输出层 没有激活函数
    pFC=OSlwToolBPnnFullConAppend(
        &mynn,
        20, 1,
        NULL, yout,
        NULL, NULL,
        pr->rand, pr, _ParaFrom(-1), _ParaFrom(1),
        LwTanh, pmem
    );
    pFC[0]->_BiasInit = &BIASINIT;

	//训练
    OSlwToolBPnnTrainInit(&mynn, yref, pmem, pOSlwToolMatrixLossSquare, _ParaFrom(0.3));
	//使用L2正则 系数0.1
    OSlwToolBPnnL2ReguInit(&mynn,_ParaFrom(0.1));
	//初始化参数
    OSlwToolBPnnAllDataInit(&mynn, pmem);
    for ( i = 0; i < 10000; i++)
    {
		//采用4次梯度代替一次batch 等价4个样本的minibatch
        for ( j = 0; j < 4; j++)
        {
            xin[0] = x_date[j];
            yref[0] = y_date[j];
			//运行神经网络
            OSlwToolBPnnRun(&mynn, NULL);
			//求误差(梯度)
            OSlwToolBPnnCalErr(&mynn);
            sum += mynn.Error;
        }
		//梯度下降
        OSlwToolBPnnReview(&mynn);

        if(i%100==0)
        {
			//sprintf+串口发送等价于printf
            LwSprintf(out_s,"%f\n",_ParaToF(sum));
            Sci_TxStr(out_s);
			
            sum = 0;
        }
    }

	//测试
    mynn.Train.Flag.NeedTrain = 1;

    for (i = 0; i < 100; i++)
    {
        xin[0] = _ParaFrom(-0.5+i*0.01);
        OSlwToolBPnnRun(&mynn, NULL);
        temp=_ParaToF(yout[0]);
		
		//sprintf+串口发送等价于printf
        LwSprintf(out_s,"%f,",temp);
        Sci_TxStr(out_s);
    }

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