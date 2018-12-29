for i in range(16) :
    print ("And(a=a[%d],b=nsel,out=x%d);" % (i,i))
    print ("And(a=b[%d],b=sel,out=y%d);" % (i,i))
    print ("Or(a=x%d,b=y%d,out=out[%d]);" % (i,i,i))
