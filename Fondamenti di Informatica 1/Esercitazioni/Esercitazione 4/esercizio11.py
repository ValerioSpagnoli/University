s = input('Inserire una strniga: ')
i = 0
k = 0
M = 0
while i < len(s) and k < len(s):
    x = int(s.count(s[i]))
    while s[i]!=s[k]:
        y = int(s.count(s[k]))
        if x<y:
           M = y
           print(M)
        else:
            M = x
            print(M)
        k = k+1
        
    i = i+1
        
               



    
