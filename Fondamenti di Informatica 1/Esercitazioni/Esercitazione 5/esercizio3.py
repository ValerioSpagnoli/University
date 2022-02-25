l = int(input('Inserisci il lato del quadrato: '))
print('*'*l)

x = 0
y = l-4
z = 0
f=int(l/2)
while z<=y:

    for i in range(1, f):
    
        print('*' + ' '*(x) + '*' + ' '*(y-z) + '*' + ' '*(x) + '*' )
        
        x = x+1
        z = z+2

q = x-1
w = 0
while w <= l-4:

    for i in range(1, f):
    
        print('*' + ' '*(q) + '*' + ' '*(w) + '*' + ' '*(q) + '*' )
        
        q = q-1
        w = w+2

print('*'*l)
    




        
    
