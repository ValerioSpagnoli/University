b = int(input('Inserisci la base del triangolo: '))
x = int(b//2)
c = 0
for i in range (1, b+1, 2):
    print (' '*(x-c),'*'*i)
    c = c+1
