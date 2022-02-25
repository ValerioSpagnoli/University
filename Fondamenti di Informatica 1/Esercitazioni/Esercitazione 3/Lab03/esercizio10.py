c=input("inserisci un carattere: ")
conta = 0
while conta < 3:
    s=input("inserisci una stringa: ")
    conta = s.count(c)
    print('Il carattere',c,'compare',conta,'volte in',s)

