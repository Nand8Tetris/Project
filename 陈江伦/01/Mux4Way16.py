for i in range(16) :

    print ( "And(a=a[%d],b=nsel2,out=x%d0);" % (i,i))
    print ( "And(a=x%d0,b=nsel1,out=y%d0);" % (i,i))
    print ( "And(a=y%d0,b=nsel0,out=f%dt0);" % (i,i))

    print ( "And(a=b[%d],b=nsel2,out=x%d1);" % (i,i))
    print ( "And(a=x%d1,b=nsel1,out=y%d1);" % (i,i))
    print ( "And(a=y%d1,b=sel0,out=f%dt1);" % (i,i))

    print ( "And(a=c[%d],b=nsel2,out=x%d2);" % (i,i))
    print ( "And(a=x%d2,b=sel1,out=y%d2);" % (i,i))
    print ( "And(a=y%d2,b=nsel0,out=f%dt2);" % (i,i))

    print ( "And(a=d[%d],b=nsel2,out=x%d3);" % (i,i))
    print ( "And(a=x%d3,b=sel1,out=y%d3);" % (i,i))
    print ( "And(a=y%d3,b=sel0,out=f%dt3);" % (i,i))

    print ( "And(a=e[%d],b=sel2,out=x%d4);" % (i,i))
    print ( "And(a=x%d4,b=nsel1,out=y%d4);" % (i,i))
    print ( "And(a=y%d4,b=nsel0,out=f%dt4);" % (i,i))

    print ( "And(a=f[%d],b=sel2,out=x%d5);" % (i,i))
    print ( "And(a=x%d5,b=nsel1,out=y%d5);" % (i,i))
    print ( "And(a=y%d5,b=sel0,out=f%dt5);" % (i,i))

    print ( "And(a=g[%d],b=sel2,out=x%d6);" % (i,i))
    print ( "And(a=x%d6,b=sel1,out=y%d6);" % (i,i))
    print ( "And(a=y%d6,b=nsel0,out=f%dt6);" % (i,i))

    print ( "And(a=h[%d],b=sel2,out=x%d7);" % (i,i))
    print ( "And(a=x%d7,b=sel1,out=y%d7);" % (i,i))
    print ( "And(a=y%d7,b=sel0,out=f%dt7);" % (i,i))

    print ( "Or(a=f%dt0,b=f%dt1,out=f%d01);" % (i,i,i))
    print ( "Or(a=f%dt2,b=f%dt3,out=f%d23);" % (i,i,i))
    print ( "Or(a=f%dt4,b=f%dt5,out=f%d45);" % (i,i,i))
    print ( "Or(a=f%dt6,b=f%dt7,out=f%d67);" % (i,i,i))
    print ( "Or(a=f%d01,b=f%d23,out=f%d0123);" % (i,i,i))
    print ( "Or(a=f%d45,b=f%d67,out=f%d4567);" % (i,i,i))
    print ( "Or(a=f%d0123,b=f%d4567,out=out[%d]);" % (i,i,i))

    '''
    if i==1 :
        print ("Or(a=ans0,b=ans1,out=pre1);")
    else :
        if i>1 :
            if i==15 :
                print ("Or(a=pre%d,b=ans%d,out=out[i]);" % (i-1,i))
            else :
                print ("Or(a=pre%d,b=ans%d,out=pre%d);" % (i-1,i,i))
    '''
    
