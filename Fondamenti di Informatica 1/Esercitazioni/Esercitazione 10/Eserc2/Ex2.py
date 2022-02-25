from tester import tester_fun
import re

def Ex2(file):
    f = open(file, 'r', encoding='utf-8')
    c = 0
    for t in f:
        pattern = r'[a-z]*([a-z])\1[a-z]*[^a-z]+[a-z]*\1\1[a-z]*[^a-z]+[a-z]*\1\1[a-z]*'
        i = re.findall(pattern, t, re.IGNORECASE)
        c = c+len(i)
    return c
    
    



 
###############################################################################

"""TEST FUNZIONE, NON MODIFICARE"""

counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(Ex2, ["file1.txt"] , 1)
counter_test_positivi += tester_fun(Ex2, ["file2.txt"] , 2)
counter_test_positivi += tester_fun(Ex2, ["file3.txt"] , 3)
counter_test_positivi += tester_fun(Ex2, ["IMalavogliaNoAccenti.txt"] , 18)
counter_test_positivi += tester_fun(Ex2, ["IMalavogliaNoAccenti_50.txt"] , 1)


print('La funzione',Ex2.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
