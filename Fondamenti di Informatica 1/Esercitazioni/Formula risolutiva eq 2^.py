from math import *
a = int(input("inserisci il valore del coeffciente a : "))
b = int(input("inserisci il valore del coeffciente b : "))
c = int(input("inserisci il valore del coeffciente c : "))

Δ = b**2 - 4*a*c
X1 = (-b + sqrt(Δ))/2
X2 = (-b - sqrt(Δ))/2

if Δ  > 0:
    print ('X1 =', X1, ';', 'X2 =', X2)

elif Δ == 0:
    print('Δ = 0 ==> X1 = X2 =', X1)
    
else:
    print('Non esistono soluzioni reali.')


    
        
        
