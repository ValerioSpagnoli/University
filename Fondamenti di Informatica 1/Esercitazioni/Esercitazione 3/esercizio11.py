x = int(input('Inserisci un intero: '))
y = int(input('Inserisci un intero: '))
z = int(input('Inserisci un intero: '))

while x + y != z:
    x = y
    y = z
    z = int(input('Inserisci un intero: '))
print(x, '+', y, '=', z)
