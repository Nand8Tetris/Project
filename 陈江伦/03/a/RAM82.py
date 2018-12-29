for i in range(8) :
    print ( "DFF16(in=out%c,out=in%c);" % (chr(i+97),chr(i+97)) )

print ( "Mux8Way16(a=ina,b=inb,c=inc,d=ind,e=ine,f=inf,g=ing,h=inh,sel=address,out=out); " )

print ( "DMux8Way(in=load,sel=address,a=fa,b=fb,c=fc,d=fd,e=fe,f=ff,g=fg,h=fh);" )

for i in range(8) :
    print ( "Mux16(a=in%c,b=in,sel=f%c,out=out%c);" % (chr(i+97),chr(i+97),chr(i+97)) )
