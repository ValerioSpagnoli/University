from math import *
n = int(input('Inserisci il numeratore: '))
d = int(input('Inserisci il denominatore: '))

if d % n == 0:
    print ('La frazione', n, '/', d, 'è apparente')

elif n < d and d % n != 0:
    print ('La frazione', n, '/', d, 'è propria')

elif n > d:
    print ('La frazione', n, '/', d, 'è impropria')

