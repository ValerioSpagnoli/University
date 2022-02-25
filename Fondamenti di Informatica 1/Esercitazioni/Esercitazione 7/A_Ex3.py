from tester import tester_fun

def A_Ex3(l):
    I = set()
    for i in l:
        for j in i:
            if i.count(j)>=2:
                I.add(j)
    return I
                

###############################################################################

"""NON MODIFICARE, codice di testing della funzione"""
counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(A_Ex3, [['casa', 'albero', 'bello']] , {'a','l'})
counter_test_positivi += tester_fun(A_Ex3, [['ciao', 'ciao']] , set())
counter_test_positivi += tester_fun(A_Ex3, [['aa','aa','hghjklhl']] , {'a','h','l'})
counter_test_positivi += tester_fun(A_Ex3, [[]] , set())
counter_test_positivi += tester_fun(A_Ex3, [['cogito', 'ergo', 'sum']] , {'o'})


print('La funzione',A_Ex3.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
