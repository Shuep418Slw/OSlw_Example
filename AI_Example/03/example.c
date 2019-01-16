OSlwCoreSTU myos;
OSlwTaskSTU mytask;

OSLW_MEM_SIMPLE_DEF(mem,32,100)

OSlwToolBPNNSTU mynn;

ParaType xin[10],yout[5];
ParaType we[10][5],bi[5];


OSlwToolRandomMTSTU myrand;
OSlwToolRandomBasicSTU *pr=(void *)(&myrand);

OSlwToolNNLayerFullConSTU *pfc;

void Mytask(OSlwTaskSTU *_pta)
{
	static OSlwTaskSTU *pta;
	static ParaType a=0.1;	
	pta=_pta;
	OSlwJiJi(_pta);
	
	OSLW_MEM_INIT(mem);
	OSlwToolRandomMTSeed(&myrand,1);
	
	
	OSlwToolBPNNInit(&mynn,1);
	
	pfc=OSlwToolBPNNFullConAppend(&mynn,10,5,xin,yout,(void *)we,bi,pr->rand,pr,0,10,NULL,pmem);
	
	//pfc->_BiasInit=&a;
	
	OSlwToolBPNNAllDataInit(&mynn,pmem);
	
	for(;;)	
	{
		OSlwSleepSec(pta,1,0);
	}
	OSlwWeiJi(_pta);

}