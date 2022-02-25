#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Scrivere una funzione che prende in ingresso due stringhe
della stessa lunghezza e restituisce la
stringa composta dai caratteri alternati delle due stringhe
"""

from tester import tester_fun

def funzione2(s1,s2):
    if len(s1)==len(s2):
        s = ''
        for i in range(0, len(s1)):
            x = s1[i]+s2[i]
            s = s+x
        return s
            
    
    
    
    
###############################################################################

"""NON MODIFICARE, codice di testing della funzione"""
counter_test_positivi = 0
total_tests = 4

counter_test_positivi += tester_fun(funzione2, ['casa','mora'] ,'cmaosraa')
counter_test_positivi += tester_fun(funzione2, ['il','la'] ,'illa')
counter_test_positivi += tester_fun(funzione2, ['a','a'] ,'aa')
counter_test_positivi += tester_fun(funzione2, ['',''] ,'')

print('La funzione',funzione2.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
