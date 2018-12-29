print ( "DMux4Way(in=load,sel=address[12..13],a=fa,b=fb,c=fc,d=fd);" )

for i in range(4) :
        print ( "RAM4K(in=in,load=f%c,address=address[0..11],out=in%c);" % (chr(i+97),chr(i+97)) )
        
print ( "Mux4Way16(a=ina,b=inb,c=inc,d=ind,sel=address[12..13],out=out); " )

