somma=0
s=input("inserisci una stringa: ")
i=0

while i<len(s) and somma<=500:
    somma=somma+ord(s[i])
    i=i+1

if i>=len(s) and somma> 500:
    print("stringa consumata e somma >500")
elif i>=len(s):
    print("stringa consumata")
else:
    print("somma > 500")

print("i =",i,"somma =",somma)    
    

    


