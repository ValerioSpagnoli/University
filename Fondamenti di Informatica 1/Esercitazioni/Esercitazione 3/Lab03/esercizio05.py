s=input("inserisci una stringa: ")
massimo=ord(s[0])
i=0
while(i<len(s)):
    if ord(s[i])>massimo:
        massimo=ord(s[i])
    i=i+1
print(massimo)
