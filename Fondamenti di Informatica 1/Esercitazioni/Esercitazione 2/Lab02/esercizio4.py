n=int(input("Inserisci il numeratore n: "))
d=int(input("Inserisci il denominatore d: "))
if n<d:
    print("La frazione è propria")
elif n%d == 0:
    print("La frazione è apparente")
else:
    print("La frazione è impropria")
    
