import numpy as np

npzfile=np.load('CnnData.npz')

we1=npzfile['wec1']
bi1=npzfile['bic1']

we2=npzfile['wec2']
bi2=npzfile['bic2']

we3=npzfile['we3']
bi3=npzfile['bi3']

we4=npzfile['we4']
bi4=npzfile['bi4']

xin=npzfile['xin']
ypre=npzfile['ypre']
yref=npzfile['yref']


def ConvToStr(c):
    re_str=""
    c_shape=c.shape
    length=c_shape[0]*c_shape[1]
    for n in range(0,c_shape[3]):
        for m in range(0,c_shape[2]):
            temp=np.reshape(c[:,:,m,n],(1,length))[0]
            for i in temp:
                re_str+=("%f,"%i)
    return re_str[0:len(re_str)-1]

def FisrtFullConTrans(a,shape_l):
    buf=np.zeros_like(a)
    length=shape_l[0]*shape_l[1]
    a_shape=a.shape
    for n in range(0,a_shape[0]):
        n1=n%shape_l[2]
        n2=n/shape_l[2]
        m=int(length*n1+n2)
        buf[m,:]=a[n,:]
    #print(buf)
    buf2=np.reshape(buf,(1,a_shape[0]*a_shape[1]))[0]
    restr=""
    for t in buf2:
        restr+=("%f,"%(t))

    return restr[0:len(restr)-1]

def bi2str(bi):
    ss=str(list(bi))
    return ss[1:len(ss)-1]

def we2str(we):
    we=np.reshape(we,(1,np.size(we)))[0]
    ss=str(list(we))
    return ss[1:len(ss)-1]

restr="#ifndef MINST_CNN_H_\n#define MINST_CNN_H_\n"
restr+="const ParaType we1[]={"+ConvToStr(we1)+"};\n"
restr+="const ParaType bi1[]={"+bi2str(bi1)+"};\n"
restr+="const ParaType we2[]={"+ConvToStr(we2)+"};\n"
restr+="const ParaType bi2[]={"+bi2str(bi2)+"};\n"
restr+="const ParaType we3[]={"+FisrtFullConTrans(we3,[4,4,64])+"};\n"
restr+="const ParaType bi3[]={"+bi2str(bi3)+"};\n"
restr+="const ParaType we4[]={"+we2str(we4)+"};\n"
restr+="const ParaType bi4[]={"+bi2str(bi4)+"};\n"
restr+="#endif\n"
file=open("MNIST_CNN.h",'w+')
file.write(restr)
file.close()


print(list(xin[0]))
print(list(yref[0]))
print(list(ypre[0]))