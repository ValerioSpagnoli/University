from tester import tester_fun

def A_Ex5(l):
    c = 0
    M = []
    for i in range(len(l)):
        c = 0
        L = l[i:i+1]+l[0:i]+l[i+1:len(l)]
        for j in L:
            if len(j)==len(l[i]):
                c = c+1
        a = (l[i], c)
        M.append(a)
    return M
        

###############################################################################

"""NON MODIFICARE, codice di testing della funzione"""
counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(A_Ex5, [['jkl', 'h', 'plqa', 'a', 'xkj']] , [('jkl', 2), ('h', 2), ('plqa', 1), ('a', 2), ('xkj', 2)] )
counter_test_positivi += tester_fun(A_Ex5, [[]] , [])
counter_test_positivi += tester_fun(A_Ex5, [['a', 'ab', 'abc']] , [('a', 1), ('ab', 1), ('abc', 1)])
counter_test_positivi += tester_fun(A_Ex5, [['e', 'a', 'lp', 'ql', 'cl']] ,  [('e', 2), ('a', 2), ('lp', 3), ('ql', 3), ('cl', 3)] )
counter_test_positivi += tester_fun(A_Ex5, [['hjkl', 'hjkp']] , [('hjkl', 2), ('hjkp', 2)])


print('La funzione',A_Ex5.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
