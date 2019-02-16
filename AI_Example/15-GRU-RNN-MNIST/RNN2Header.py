import numpy as np

NUM_UNITS=128
INPUT_SIZE = 28

def bi2str(bi):
    lb=list(bi)
    ss=""
    for nn in lb:
        ss+=("_ParaFrom(%.8f),"%(nn))
    return ss[0:len(ss)-1]

def we2str(we):
    we=np.reshape(we,(1,np.size(we)))[0]
    lw=list(we)
    ss=""
    for nn in lw:
        ss+=("_ParaFrom(%.8f),"%(nn))
    return ss[0:len(ss)-1]

npzfile=np.load('RnnData2.npz')

we1=npzfile['W_RU']
bi1=npzfile['B_RU']

we2=npzfile['W_core']
bi2=npzfile['B_core']

we3=npzfile['W_f']
bi3=npzfile['B_f'][0]

xin=npzfile['xin']
ypre=npzfile['ypre']
yref=npzfile['yref']

WR=we1[:,:NUM_UNITS]
BR=bi1[:NUM_UNITS]


WU=we1[:,NUM_UNITS:]
BU=bi1[NUM_UNITS:]

wrx=WR[:INPUT_SIZE,:]
wrh=WR[INPUT_SIZE:,:]

wux=WU[:INPUT_SIZE,:]
wuh=WU[INPUT_SIZE:,:]

wcx=we2[:INPUT_SIZE,:]
wch=we2[INPUT_SIZE:,:]


we1str=""
we1str+=(we2str(wrh)+",\n")
we1str+=(we2str(wrx)+",\n")
we1str+=(we2str(wuh)+",\n")
we1str+=(we2str(wux)+",\n")
we1str+=(we2str(wch)+",\n")
we1str+=(we2str(wcx))

bi1str=""
bi1str+=(bi2str(BR)+",")
bi1str+=(bi2str(BU)+",")
bi1str+=(bi2str(bi2)+",")

restr="#ifndef MINST_RNN_H_\n#define MINST_RNN_H_\n"
restr+="const ParaType we1[]={"+we1str+"};\n"
restr+="const ParaType bi1[]={"+bi1str+"};\n"
restr+="const ParaType we2[]={"+we2str(we3)+"};\n"
restr+="const ParaType bi2[]={"+bi2str(bi3)+"};\n"
restr+="#endif\n"

file=open("MNIST_RNN.h",'w+')
file.write(restr)
file.close()
print(list(xin[0]))
print(list(yref[0]))
print(list(ypre[0]))