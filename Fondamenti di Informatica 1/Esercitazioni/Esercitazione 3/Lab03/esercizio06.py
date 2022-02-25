n=int(input("inserisci un numero: "))
i=2
primo=True
while i<n:
    if n%i==0:
        primo=False
    i=i+1
if primo:
    print("Numero primo")
else:
    print("Numero non primo")

    


