m = int(input('Inserisci il mese: '))
a = int(input("Inserisci l'anno: "))

if 0<m<13:
    if 0<m<12:
        print(m+1, a)
    elif m==12:
        print('1', a+1)

else:
    print ('Errore inserimento valori.')
    
