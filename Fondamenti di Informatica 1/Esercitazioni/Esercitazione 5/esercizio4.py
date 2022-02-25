#!/usr/bin/env python3
# -*- coding: utf-8 -*-





from tester import tester_fun

def funzione1(s):
    
    variabile = True
    if len(s)==0:
        variabile = False
        return variabile

    for i in range(0, len(s)):
        if s.count(s[i]) > 1 :
            variabile = True
            break
        elif s.count(s[i])==1:
            variabile = False
            
    return variabile


            

###############################################################################

"""NON MODIFICARE, codice di testing della funzione"""
counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(funzione1, ['casa'] ,True)
counter_test_positivi += tester_fun(funzione1, ['tre'] ,False)
counter_test_positivi += tester_fun(funzione1, [''] ,False)
counter_test_positivi += tester_fun(funzione1, ['  '] ,True)
counter_test_positivi += tester_fun(funzione1, ['pallonata'] ,True)

print('La funzione',funzione1.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
