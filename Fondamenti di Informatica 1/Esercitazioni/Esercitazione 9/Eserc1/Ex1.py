from tester import tester_fun

def Ex1(l):
    d = {}
    for n in l:
        if n in d:
            d[n] = d[n]+1
        else:
            d[n] = 1
    return d
            
    
 
###############################################################################

"""TEST FUNZIONE, NON MODIFICARE"""

counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(Ex1, [['casa','orso','cane','casa','orso','casa']] , {'casa': 3, 'orso': 2, 'cane': 1})
counter_test_positivi += tester_fun(Ex1, [['casa','casa','casa']] , {'casa': 3})
counter_test_positivi += tester_fun(Ex1, [['casa','orso','cane','cassa','osso','casta']] , {'casa': 1, 'orso': 1, 'cane': 1, 'cassa': 1, 'osso': 1, 'casta': 1})
counter_test_positivi += tester_fun(Ex1, [['casa']] , {'casa': 1})
counter_test_positivi += tester_fun(Ex1, [[]] , {})

print('La funzione',Ex1.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
