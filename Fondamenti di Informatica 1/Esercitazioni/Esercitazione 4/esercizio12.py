n = int(input('Inserire un intero: '))
primo = True
i = 2
while n > 1:        
    while i<=n/2 and primo:

        if n % i == 0 :
            primo = False
        
        i = i+1

    if primo == True and n!=1:
        print(n)
        
    


    n = n-1
    i = 2
    primo = True



    
    
    


