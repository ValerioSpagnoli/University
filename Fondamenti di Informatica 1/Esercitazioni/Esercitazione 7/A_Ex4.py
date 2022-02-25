from tester import tester_fun

def A_Ex4(l):
    M = []
    for i in range(len(l)):
        x = len(l[i])
        L = l[i:i+1]+l[0:i]+l[i+1:len(l)]
        for j in L:
            if len(j) == x and l[i]!=j:
                a = (l[i], j)
                M.append(a)
    return M

###############################################################################

"""NON MODIFICARE, codice di testing della funzione"""
counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(A_Ex4, [['jkl', 'h', 'plqa', 'a', 'xkj']] , [('jkl','xkj'), ('h','a'), ('a','h'), ('xkj','jkl')])
counter_test_positivi += tester_fun(A_Ex4, [[]] , [])
counter_test_positivi += tester_fun(A_Ex4, [['a', 'ab', 'abc']] , [])
counter_test_positivi += tester_fun(A_Ex4, [['e', 'a', 'lp', 'ql', 'cl']] ,  [('e', 'a'), ('a', 'e'), ('lp', 'ql'), ('lp', 'cl'), ('ql', 'lp'), ('ql', 'cl'), ('cl', 'lp'), ('cl', 'ql')])
counter_test_positivi += tester_fun(A_Ex4, [['hjkl', 'hjkp']] , [('hjkl', 'hjkp'), ('hjkp', 'hjkl')] )


print('La funzione',A_Ex4.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
