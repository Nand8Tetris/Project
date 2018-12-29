print ("Not(in=in[0],out=xxx);")
print ("Not(in=xxx,out=res0);")
for i in range(1,16) :
    print ( "And(a=in[%d],b=res%d,out=res%d);" % (i,i-1,i) )
print ("Not(in=in[0],out=out[0]);")
for i in range(1,16) :
    print ( "Xor(a=res%d,b=in[%d],out=out[%d]);" % (i-1,i,i))
