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
    K.append(x) # K lista di tuple (nome, importo relativo)
m.close()
####

m = open('movimenti.csv', 'r', encoding='utf-8')
FileRes = open('resoconto.csv', 'w', encoding='utf-8')
FileRes.write('Nome,TotaleMovimento'+'\n')

P = []
for nome in M:
    somma = 0
    Riga = ''
    for tupla in K:
        if nome in tupla:
            x = tupla[1]
            somma = somma + int(x)
    Riga = (nome, somma) #tupla (nome, somma)
    P.append(Riga) #lista di tuple (nome,somma)

G = []
for i in P:
    G.append(i[1])
G.sort(reverse=True) #lista degli importi finali in ordine decrescente

resocontofinale = ''
for importo in G:
    for tupla in P:
        if importo in tupla and tupla[0] not in resocontofinale:
            if str(importo)[0] not in '-':
                a = tupla[0]+','+'+'+str(importo)+'\n'
            else:
                a = tupla[0]+','+str(importo)+'\n'
            resocontofinale = resocontofinale + a
FileRes.write(resocontofinale)
FileRes.close()
