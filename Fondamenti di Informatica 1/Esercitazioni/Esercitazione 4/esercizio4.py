c = 0
while c != '*':
    x = int(input('Inserisci un intero: '))
    r = x % 5 
    if r != 0:
        print('Resto =', r)
    else:
        print('Resto = 0')
        c = '*'
        
    

    
