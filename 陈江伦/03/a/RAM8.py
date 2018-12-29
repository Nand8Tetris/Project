for i in range(8) :
    print ( "DFF16(in=out%c,out=in%c);" % (chr(i+97),chr(i+97)) )

print ( "Mux8Way16(a=ina,b=inb,c=inc,d=ind,e=ine,f=inf,g=ing,h=inh,sel=address,out=out); " )

print ( "DMux8Way16(in=in,sel=address,a=ta,b=tb,c=tc,d=td,e=te,f=tf,g=tg,h=th);" )

print ( "Mux16(a=false,b=true,sel=load,out=load16);" )

print ( "DMux8Way16(in=load16,sel=address,a=pa,b=pb,c=pc,d=pd,e=pe,f=pf,g=pg,h=ph);" )

for i in range(8) :
    print ( "Not16(in=p%c,out=R%c);" % (chr(i+97),chr(i+97)) )

for i in range(8) :
    print ( "And16(a=R%c,b=in%c,out=q%c);" % (chr(i+97),chr(i+97),chr(i+97)) )
    print ( "And16(a=p%c,b=t%c,out=w%c);" % (chr(i+97),chr(i+97),chr(i+97)) )
    print ( "Or16(a=q%c,b=w%c,out=out%c);" % (chr(i+97),chr(i+97),chr(i+97)) )
