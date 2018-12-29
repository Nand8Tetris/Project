from os import system
print ("input the path")
folder=input()
system("getfile.exe "+folder+" > "+folder+"/list.txt")
system("part1 "+folder)
system("part2 "+folder)
system("part3 "+folder)
