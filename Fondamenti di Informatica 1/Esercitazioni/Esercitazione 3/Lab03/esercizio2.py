i=input('inserisci un intero ( \'*\' per terminare) ')

somma=0
while i!='*':
    if int(i)<0:
        somma=somma+int(i)
    i=input('inserisci un intero ( \'*\' per terminare) ')
print(somma)
