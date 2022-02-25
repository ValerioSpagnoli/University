a=int(input("inserisci un intero positivo per il lato a: "))
b=int(input("inserisci un intero positivo per il lato b: "))
c=int(input("inserisci un intero positivo per il lato c: "))
if a+b>c and a+c>b and b+c>a: #La somma di due lati è sempre maggiore del terzo
    if a==b and b==c: #I tre lati sono tutti uguali
        print ("Equilatero")
    elif a==b or a==c or b==c: #Almeno due lati sono uguali
        print("Isoscele")
    else:
        print("Scaleno")
else: #Un lato è più corto o uguale alla somma degli altri 2
    print("I tre interi non corrispondono a un triangolo valido")
