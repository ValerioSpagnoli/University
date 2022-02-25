n = int(input('Inserisci un numero: '))
i = 1
f0 = n

if n==0:
    print('n! = 0')
elif n==1:
    print('n! = 1')
elif n==-1:
    print('n! = -1')
    
elif n>0:
    f0 = n
    while i<n:
        f = f0*(n-i)
        f0 = f
        i = i+1
    print('n! =', f)
    
elif n<0:
    n = -n
    f0 = n
    if n%2==0:
        while i<n:
            f = f0*(n-i)
            f0 = f
            i = i+1
        print('n! =', f)
    
    elif n%2==1:
        while i<n:
            f = f0*(n-i)
            f0 = f
            i = i+1
        print('n! =', -f)
        


    
    
    
