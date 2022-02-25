s = input('Inserisci una stringa: ')
i = 0
somma = ord(s[0])
controllo = True
while controllo :
    
    i = i+1
    
    somma = somma + ord(s[i]) 
    
    
    if (i<len(s)-1) and (somma<500):
        controllo = True
        
    elif (i==len(s)-1) or (somma>500):
        controllo = False

if (i==len(s)-1):
    print('La stringa è terminata.')
elif (somma>500):
    print('La somma dei caratteri Unicode della stringa ha raggiunto 500.')
    
    
