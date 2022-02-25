somma = 0
i = 'c'
while i != '*':
    i = input ('Inserisci un intero (* per terminare): ')
    
    if i != '*' and i[0] in '-':
        somma = somma - (int(i))
        print('La somma parizale dei numeri negativi è:', -somma)
        
    elif i != '*' and (i[0].isdecimal or i[0] in '+'):
        print('La somma dei numeri negativi è:', -somma)

print('La somma totale dei numeri negativi è:', -somma)
        

