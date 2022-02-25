x = input('Inserisci una stringa1:')
y = input('Inserisci una stringa2:')

controllo = True

if x[len(x)-1] == y[0]:
    print(x, y)
    
elif x[len(x)-1] != y[0] or y[len(y)-1] != x[0] :   

    while controllo:
        
        x = input('Inserisci una stringa1.1:')
    
        if y[len(y)-1] != x[0] or x[len(x)-1] != y[0]:
            y = input('Inserisci una stringa1.2:')
            if y[len(y)-1] != x[0] or x[len(x)-1] != y[0]:
                controllo = True
            else:
                controllo = True

        else:
            y[len(y)-1] == x[0]
            controllo = False


    print (y, x)    
            
        
            
    
    
    
