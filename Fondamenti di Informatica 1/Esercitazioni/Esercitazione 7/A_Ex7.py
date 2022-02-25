from tester import tester_fun

def A_Ex7(l):
    
    m = []
    for i in l:
        a = list(i)
        m.extend(a)
    
    for i in m:
        x = m.count(i)
        if x>1:
            for j in range(0, x):
                m.remove(i)
                
    m = set(m)
    return m
            

            
        
        

###############################################################################

"""NON MODIFICARE, codice di testing della funzione"""
counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(A_Ex7, [[{3,2,90},{2,87,23},{2,23,3}]] , {90,87})
counter_test_positivi += tester_fun(A_Ex7, [[set(),{-10},{2}]] , {-10,2})
counter_test_positivi += tester_fun(A_Ex7, [[set()]] , set())
counter_test_positivi += tester_fun(A_Ex7, [[set(),{10,-2},{10},{-2}]] , set())
counter_test_positivi += tester_fun(A_Ex7, [[set(),{10,-9,4},{4,-5,2},{3,7,4}]] , {10,-9,-5,2,3,7})


print('La funzione',A_Ex7.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
