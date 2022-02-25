c = input ('Inserisci un carattere: ')
x = 0
while x < 3:
   s = input ('Inserisci una stringa: ')
   x = s.count(c)
   print ('Il carattere', c, 'compare nella stringa', s, x, 'volte')
   
