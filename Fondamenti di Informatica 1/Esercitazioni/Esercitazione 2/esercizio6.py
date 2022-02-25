from math import *
a = int(input())
b = int(input())
c = int(input())

ab = a+b
ac = a+c
bc = b+c

if a>0 and b>0 and c>0 and a < bc and b < ac and c < ab:
   if a == b and b == c and c == a:
       print ('è un triangolo equilatero')
   elif (a == b or a == c or b == c) and (a != b or b != c or c != a):
        print ('è un triangolo isoscele')
   elif (a != b and b != c and c != a):
        print ('è un triangolo scaleno')
            
else:
    print ('I valori inseriti non possono formare un triangolo')
