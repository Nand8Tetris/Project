print ( "DMux8Way(in=load,sel=address[6..8],a=fa,b=fb,c=fc,d=fd,e=fe,f=ff,g=fg,h=fh);" )

for i in range(8) :
        print ( "RAM64(in=in,load=f%c,address=address[0..5],out=in%c);" % (chr(i+97),chr(i+97)) )
        
print ( "Mux8Way16(a=ina,b=inb,c=inc,d=ind,e=ine,f=inf,g=ing,h=inh,sel=address[6..8],out=out); " )

