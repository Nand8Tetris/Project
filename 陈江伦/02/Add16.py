print ("Xor(a=a[0],b=b[0],out=out[0]);")
print ("And(a=a[0],b=b[0],out=c0);")
for i in range(1,16) :
    print ( "Xor(a=a[%d],b=b[%d],out=d%d);" % (i,i,i) )
    print ( "Xor(a=d%d,b=c%d,out=out[%d]);" % (i,i-1,i) )
    print ( "And(a=c%d,b=d%d,out=x%d);" % (i-1,i,i) )
    print ( "And(a=a[%d],b=b[%d],out=y%d);" % (i,i,i) )
    print ( "Or(a=x%d,b=y%d,out=c%d);" % (i,i,i) )
