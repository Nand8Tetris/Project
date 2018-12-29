n=2**14
def build(i,l,r,d) :
	if l+1!=r :
		mid=(l+r)>>1
		build(i<<1,l,mid,d-1)
		build(i<<1|1,mid,r,d-1)
		print ( "Mux16(a=in%d,b=in%d,sel=address[%d],out=in%d);" % (i<<1,i<<1|1,d,i) )
	else :
		print ( "DFF16(in=out%d,out=in%d);" % (i,i) )

def write(i,l,r,d) :
	if l+1!=r :
		mid=(l+r)>>1
		print ( "Mux(a=f%d,b=false,sel=address[%d],out=f%d);" % (i,d,i<<1) )
		print ( "Mux(a=false,b=f%d,sel=address[%d],out=f%d);" % (i,d,i<<1|1) )
		write(i<<1,l,mid,d-1)
		write(i<<1|1,mid,r,d-1)
	else :
		print ( "Mux16(a=in%d,b=in,sel=f%d,out=out%d);" % (i,i,i) )

import math
build(1,0,n,math.log(n,2)-1)

print ("And16(a=in1,b=true,out=out);")

print ( "And(a=load,b=true,out=f1);" )

write(1,0,n,math.log(n,2)-1)
