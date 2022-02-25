from tester import tester_fun

def Ex5(file):
    f = open(file, 'r', encoding= 'utf-8')
    d={}
    I=set()
    i = 0
    for riga in f:
        i = i+1 #numero riga
        rs = riga.split(',')
        for j in range(len(rs)):
            I=set()
            N = int(rs[j].strip())
            if N not in d:
                I.add(i)
                d[N] = I
            elif N in d:
                d[N].add(i)
    return d
                
                
                
                
                
            
            
    
 
###############################################################################

"""TEST FUNZIONE, NON MODIFICARE"""

counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(Ex5, ['numeri1.txt'] , {10: {1,2}, -5: {1,2}, 0: {1}, 8: {2}, -3: {2}})
counter_test_positivi += tester_fun(Ex5, ['numeri2.txt'] , {10: {1,2}, 0: {2}})
counter_test_positivi += tester_fun(Ex5, ['numeri3.txt'] , {3: {1,2}, 4: {1}, 5: {1}, 2: {2,3}, 0: {2,3}})
counter_test_positivi += tester_fun(Ex5, ['numeri4.txt'] , {2: {1,2,3,4,5}, 1: {1,2,6}, 3: {6}})
counter_test_positivi += tester_fun(Ex5, ['numeri5.txt'] , {})

print('La funzione',Ex5.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
