from tester import tester_fun

def A_Ex1(l1,l2):
    somma = 0
    l =[]
    for i in range (len(l1)):
        somma = l1[i]+l2[i]
        l.append(somma)
    for i in range(len(l1), len(l2)):
        somma = l2[i]+0
        l.append(somma)
    return l



###############################################################################

"""NON MODIFICARE, codice di testing della funzione"""
counter_test_positivi = 0
total_tests = 6

counter_test_positivi += tester_fun(A_Ex1, [[3,6],[3,4,9]] , [6, 10, 9])
counter_test_positivi += tester_fun(A_Ex1, [[],[3,4,9]] , [3, 4, 9])
counter_test_positivi += tester_fun(A_Ex1, [[3,6],[3,4]] ,[6, 10])
counter_test_positivi += tester_fun(A_Ex1, [[1],[9]] ,[10])
counter_test_positivi += tester_fun(A_Ex1, [[],[9]] ,[9])
counter_test_positivi += tester_fun(A_Ex1, [[],[]] ,[])

print('La funzione',A_Ex1.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
