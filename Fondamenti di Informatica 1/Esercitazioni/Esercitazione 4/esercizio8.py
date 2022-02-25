s = int(input('Inserisci un intero N: '))
x = 1
y = 1
i = 2
if s == 1:
    print('La successione di Fibonacci da 1 a N:')
    print(x)
elif s == 2:
    print('La successione di Fibonacci da 1 a N:')
    print(x)
    print(y)
else:
    print('La successione di Fibonacci da 1 a N:')
    print(x)
    print(y)
    while i<s:
        y = y+x
        print(y)
        x = y-x
        i = i+1
    
    
