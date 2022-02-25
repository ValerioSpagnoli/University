from tester import tester_fun
import re
def Ex1(l,c1,c2):
    q = c1+c2
    w =c2+c1
    a = 0
    for s in l:
        m = re.search(q, s)
        m1 = re.search(w, s)
        if m:
            a = a+1
            print('m', m.group())
        elif m1:
            a = a+1
            print('m1',m1.group())
    return a
            
 
###############################################################################

"""TEST FUNZIONE, NON MODIFICARE"""

counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(Ex1, [['palla','pallone','casa','casolare'],'l','a'] , 3)
counter_test_positivi += tester_fun(Ex1, [['palla','pallone','casa','casolare'],'l','l'] , 2)
counter_test_positivi += tester_fun(Ex1, [['palla','pallone','casa','casolare'],'a','p'] , 2)
counter_test_positivi += tester_fun(Ex1, [['palla','pallone','casa','casolare'],'o','n'] , 1)
counter_test_positivi += tester_fun(Ex1, [[],'a','b'] , 0)

print('La funzione',Ex1.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
