from tester import tester_fun

def A_Ex4(l):
    r = ''
    if len(l)>0:
        for i in range(len(l)):
            x = l[i]
            if x%2==0:
                r = r + 'P'
            if x%2==1:
                r = r + 'D'
        return r
    if len(l)==0:
        return r


    

###############################################################################

"""NON MODIFICARE, codice di testing della funzione"""
counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(A_Ex4, [[3,7,8,9]], 'DDPD')
counter_test_positivi += tester_fun(A_Ex4, [[3]], 'D')
counter_test_positivi += tester_fun(A_Ex4, [[8]], 'P')
counter_test_positivi += tester_fun(A_Ex4, [[]], '')
counter_test_positivi += tester_fun(A_Ex4, [[7,7,7,7,8]], 'DDDDP')

print('La funzione',A_Ex4.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
