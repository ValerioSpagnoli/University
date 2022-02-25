from tester import tester_fun

def A_Ex3(fileName):
    f=open(fileName, 'r', encoding='utf-8')
    f.readline()
    L = []
    for riga in f:
        rs = riga.split(',')
        matricola = rs[0]
        materia=rs[2].replace('\n','')
        if int(rs[1])>=18:
            x = (matricola, materia)
            L.append(x)
    return L
        

###############################################################################


"""NON MODIFICARE, codice di testing della funzione"""
counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(A_Ex3, ["esami1.csv"], [('1345','Fisica'),('1346','Analisi'),('1896','Geometria'),('1753','Fisica')])
counter_test_positivi += tester_fun(A_Ex3, ["esami2.csv"], [('1346','Analisi')])
counter_test_positivi += tester_fun(A_Ex3, ["esami3.csv"], [])
counter_test_positivi += tester_fun(A_Ex3, ["esami4.csv"], [])
counter_test_positivi += tester_fun(A_Ex3, ["esami5.csv"], [('1345','Fisica'),('1987','Fondamenti'),('1346','Analisi'),('1896','Geometria')])


print('La funzione',A_Ex3.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
