n = int(input('Inserire il valore a cui tende n: '))
e = 0
for i in range (1, n):
    e = ( 1 + 1/n) **n
print('Il lim(n->', n,') (1+ 1/n)**n = ',e)
