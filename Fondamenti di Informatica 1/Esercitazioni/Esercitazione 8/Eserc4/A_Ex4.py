from tester import tester_fun

def A_Ex4(fileName):
    f = open(fileName, 'r', encoding='utf-8')
    f.readline()
    L = []
    I = set()
    for riga in f:
        rs = riga.split(',')
        if int(rs[1])>=29:
            L.append(rs[2].replace('\n',''))
    for i in L:
        if L.count(i)>=2:
            I.add(i)
    return I
            
            
        
        
        

###############################################################################


"""NON MODIFICARE, codice di testing della funzione"""
counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(A_Ex4, ["esami1.csv"], {'Fisica'})
counter_test_positivi += tester_fun(A_Ex4, ["esami2.csv"], set())
counter_test_positivi += tester_fun(A_Ex4, ["esami3.csv"], {'Ricerca Operativa','Analisi'})
counter_test_positivi += tester_fun(A_Ex4, ["esami4.csv"], {'Basi di Dati'})
counter_test_positivi += tester_fun(A_Ex4, ["esami5.csv"], set())


print('La funzione',A_Ex4.__name__,'ha superato',counter_test_positivi,'test su',total_tests)

