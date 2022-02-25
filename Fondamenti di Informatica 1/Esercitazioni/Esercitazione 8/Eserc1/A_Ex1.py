f = open('Fibonacci.txt', 'w', encoding='utf-8')

s = ''
x = 1
y = 1
s = s+str(x)+'\n'
s = s+str(y)+'\n'
i = 2
while i<=100:
    y = y+x
    s = s+str(y)+'\n'
    x = y-x
    i = i+1

f.write(s)
f.close()






