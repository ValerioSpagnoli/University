m = open('movimenti.csv', 'r', encoding='utf-8')
m.readline()
L = m.readlines()
M = []
for i in L:
    Is = i.split(',')
    if Is[0] not in M:
        M.append(Is[0]) # M è la lista con i nomi in ordine
m.close()
####

K = []
m = open('movimenti.csv', 'r', encoding='utf-8')
m.readline()
for riga in m:
    rs = riga.split(',')
    nome = rs[0]
    importo = rs[1].replace('\n', '')
    x = (nome, importo)
    K.append(x) # K lista di tuple (nome, importo)
m.close()
####

m = open('movimenti.csv', 'r', encoding='utf-8')
FileRes = open('resoconto.csv', 'w', encoding='utf-8')
FileRes.write('Nome,TotaleMovimento'+'\n')
for nome in M:
    somma = 0
    Riga = ''
    for tupla in K:
        if nome in tupla:
            x = tupla[1]
            somma = somma + int(x)
            S = str(somma)
            if S[0] not in '-':
                S = '+'+S
    Riga = Riga + nome + ',' + S + '\n'
    FileRes.write(Riga)
FileRes.close()
