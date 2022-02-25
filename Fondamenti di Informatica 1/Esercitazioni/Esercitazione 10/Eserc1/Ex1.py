from tester import tester_fun
import re

def Ex1(file):
        f = open(file, 'r', encoding='utf-8')
        stringa = f.read()
        pattern = r'([a-z])[a-z]*([a-z])[a-z]*([a-z]) \1[a-z]*\2[a-z]*\3'
        i = re.findall(pattern ,stringa, re.IGNORECASE)
        c = len(i)
        return c
                
        



        
###############################################################################

"""TEST FUNZIONE, NON MODIFICARE"""

counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(Ex1, ["file1.txt"] , 2)
counter_test_positivi += tester_fun(Ex1, ["file2.txt"] , 2)
counter_test_positivi += tester_fun(Ex1, ["file3.txt"] , 3)
counter_test_positivi += tester_fun(Ex1, ["IMalavogliaNoAccenti.txt"] , 512)
counter_test_positivi += tester_fun(Ex1, ["IMalavogliaNoAccenti_50.txt"] , 19)

print('La funzione',Ex1.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
