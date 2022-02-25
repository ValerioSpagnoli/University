from tester import tester_fun

def A_Ex2(l):
    i = 0
    while i<len(l)-1:
        if l[i]<l[i+1]:
            l.append(l[i+1]-l[i])
            i = i+1
        else:
            i = i+1
    return l
        

###############################################################################

"""NON MODIFICARE, codice di testing della funzione"""
counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(A_Ex2, [[10,1,11,31,251]] , [10,1,11,31,251,10,20,220,10,200,190])
counter_test_positivi += tester_fun(A_Ex2, [[]] , [])
counter_test_positivi += tester_fun(A_Ex2, [[2,7,3]] , [2,7,3,5,2])
counter_test_positivi += tester_fun(A_Ex2, [[200,501,300]] , [200,501,300,301,1])
counter_test_positivi += tester_fun(A_Ex2, [[3,2,0]] , [3,2,0])


print('La funzione',A_Ex2.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
