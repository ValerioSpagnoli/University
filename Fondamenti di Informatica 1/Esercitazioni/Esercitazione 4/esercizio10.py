x = int(input('Inserisci un intero: '))
y = int(input('moltiplicalo per: '))
i = 0
somma = 0
if y<0:
    x = -x
    y = -y

while i < y :

    somma = somma+x
    i = i+1

print('Il risultato è:',somma)


