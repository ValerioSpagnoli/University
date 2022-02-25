from tester import tester_fun
import re

def Ex3(file):
    f = open(file, 'r', encoding='utf-8')
    testo = f.read()
    pattern = r' ([a-z])[a-z]*([a-z])\2[a-z]*\1'
    i = re.findall(pattern, testo, re.IGNORECASE)
    f.close()
    return(len(i))

 
###############################################################################

"""TEST FUNZIONE, NON MODIFICARE"""

counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(Ex3, ["file1.txt"] , 3)
counter_test_positivi += tester_fun(Ex3, ["file2.txt"] , 3)
counter_test_positivi += tester_fun(Ex3, ["file3.txt"] , 2)
counter_test_positivi += tester_fun(Ex3, ["file4.txt"] , 2)
counter_test_positivi += tester_fun(Ex3, ["file5.txt"] , 3)

print('La funzione',Ex3.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
