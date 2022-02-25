x = input('Inserire un intero [0, 10]: ')
y = input('Inserire un intero [0, 10]: ')

s = '0 1 2 3 4 5 6 7 8 9 10'

s1 = s.replace(x, '', 1)
s2 = s1.replace(y, '', 1)

print (s2)

