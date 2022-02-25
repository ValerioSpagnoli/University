import math
a = int(input("inserisci a : "))
b = int(input("inserisci b : "))
c = int(input("inserisci c : "))
delta=math.sqrt(b*b-4*a*c)
print((-b+delta)/(2*a))
print((-b-delta)/(2*a))
