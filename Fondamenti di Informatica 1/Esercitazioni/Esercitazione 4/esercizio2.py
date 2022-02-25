x = int(input('Inserire un intero: '))
somma  = 0
if x % 3 == 0:
    somma = x
while x != 0:
    x = int(input('Inserire un intero: '))
    if x % 3 == 0:
        somma = somma + x
        
if x % 3 == 0:
    print(somma)
    
        
    
