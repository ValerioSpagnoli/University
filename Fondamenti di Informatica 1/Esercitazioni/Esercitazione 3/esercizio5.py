s = input('Inserisci una stringa: ')

if (len(s)>0):
    massimo = s[0]
    
i = 0

while i<len(s):
    
    if (s[i]>massimo):
        massimo = s[i]
        
    i=i+1

if (len(s)>0):
    print('Il valore massimo nella tabella Unicode è:', ord(massimo))
    
else:
    print('Inserita una stringa vuota.')
   
