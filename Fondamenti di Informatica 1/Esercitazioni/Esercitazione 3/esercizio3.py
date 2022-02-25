s = input('Inserisci una stringa:')
while len(s)>0 and not( s.isalpha() and s.islower()):
    s = input('Inserisci una stringa:')

print('Fine programma.')
