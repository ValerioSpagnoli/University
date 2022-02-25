from tester import tester_fun

def A_Ex8(l,c,n):
    i= 0
    while i < len(l):
        x = l[i]
        if x.count(c)>=n:
            l.remove(x)
        else:
            i = i+1
    return l

###############################################################################

"""NON MODIFICARE, codice di testing della funzione"""
counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(A_Ex8, [['palla','casse','palo'],'a',2] ,['casse','palo'])
counter_test_positivi += tester_fun(A_Ex8, [['palla','casse','palo'],'p',1] ,['casse'])
counter_test_positivi += tester_fun(A_Ex8, [['pallone','casse','palla','pappa'],'p',2] ,['pallone','casse','palla'])
counter_test_positivi += tester_fun(A_Ex8, [['pallone','casse','palla','pappa'],'a',1], [])
counter_test_positivi += tester_fun(A_Ex8, [[],'a',1] , [])

print('La funzione',A_Ex8.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
