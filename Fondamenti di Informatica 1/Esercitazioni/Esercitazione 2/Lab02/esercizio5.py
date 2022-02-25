a=int(input("inserisci il primo intero positivo: "))
b=int(input("inserisci il secondo intero positivo: "))
c=int(input("inserisci il terzo intero positivo: "))
if a >= b and b >= c:
    print(a,b,c)
elif a >= c and c >= b:
    print(a,c,b)
elif b >= a and a >= c:
    print(b,a,c)
elif b >= c and c >= a:
    print(b,c,a)
elif c >= a and a >= b:
    print(c,a,b)
elif c >= b and b >= a:
    print(c,b,a)
 
##Soluzione alternativa che fa uso delle funzioni min e max
##
##m = max(a,b,c)
##if m==a:
##    print(a,max(b,c),min(b,c))
##elif m==b:
##    print(b,max(a,c),min(a,c))
##else:
##    print(c,max(a,b),min(b,a))
