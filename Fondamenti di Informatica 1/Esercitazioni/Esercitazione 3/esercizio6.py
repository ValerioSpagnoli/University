n = int(input('Inserire un intero: '))
primo = True
i = 2
        
while i<=n/2 and primo: 

    if n % i == 0:
        primo = False
        
    i = i+1

if primo == True and n!=1:
    print('N è primo.')
    
else:
    print('N non è primo')
