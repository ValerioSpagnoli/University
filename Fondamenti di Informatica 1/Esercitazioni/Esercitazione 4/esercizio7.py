x = input('Inserisci una stringa x: ')
y = input('Inserisci una stringa y: ')
z = input('Inserisci una stringa z: ')

while len(x) + len(y) != len (z):
    x = y
    y = z
    z = input('Inserisci una stringa: ')
