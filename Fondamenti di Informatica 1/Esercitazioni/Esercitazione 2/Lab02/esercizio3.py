a=int(input("Inserisci un anno a: "))
if ((a%4 == 0 and a%100 != 0) or a%400==0):
    print("L'anno "+str(a)+" è bisestile")
else:
    print("L'anno "+str(a)+" non è bisestile")
