i=input('inserisci un intero ( \'*\' per terminare) ')

cont=0
while i!='*':
    if int(i)>0:
        cont=cont+1
    i=input('inserisci un intero ( \'*\' per terminare) ')
print(cont)
    
