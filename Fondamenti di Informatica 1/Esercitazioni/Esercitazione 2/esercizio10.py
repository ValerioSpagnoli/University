t = int(input('Inserisci una temperatura: '))
a = input('Celsius o Fahrenheit? ')

if a == 'Celsius':
    if t>=100:
        print('Stato gassoso.')
    elif 0<t<100:
        print('Stato liquido.')
    elif t<=0:
        print('Stato solido.')

elif a == 'Fahrenheit':
    if t >= 212:
        print('Stato gassoso.')
    elif 32<t<212:
        print('Stato liquido.')
    elif t<=32:
        print('Stato solido.')

