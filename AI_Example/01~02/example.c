#include<stdio.h>
#include "OSLW_include.h"

OSLW_MEM_SIMPLE_DEF(mem, 32, 100)

OSlwToolBPNNSTU mynn;

ParaType xin[3] = { -1,0,1 };
ParaType yout[2];

ParaType we[2][3] = { 0.1,0,-0.2,0.3,0.4,-0.6 };
ParaType bi[2] = { 0.3,0.1 };

ParaType dwe[2][3], dbi[2];

OSlwToolNNLayerFullConSTU *pFC;


int main()
{

	OSLW_MEM_INIT(mem);

	OSlwToolBPNNInit(&mynn, 1);



	pFC=OSlwToolBPNNFullConAppend(
		&mynn,
		3, 2,
		xin, yout,
		we, bi,
		NULL, NULL, 0, 0,
		LwTanh, pmem
	);
	
	pFC->DeltW.a = dwe;
	pFC->DeltB.a = dbi;



	OSlwToolBPNNAllDataInit(&mynn, pmem);

	OSlwToolBPNNRun(&mynn, NULL);

	yout[0] = 1;
	yout[1] = 1;

	OSlwToolBPNNBackward(&mynn);



	return 0;
}