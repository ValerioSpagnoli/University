#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Scrivere una funzione che prende in input 2 stringhe e
restituisce la stringa composta da tutti i caratteri che appaiono
in s1 ma NON in s2, nell’ordine in cui appaiono in s1.
"""

from tester import tester_fun

def funzione5(s1,s2):
    
    x = s1
    
    for i in range (0, len(s2)):
        if s2[i] in s1:
            z = x.replace(s2[i], '')
            x = z
            
    return x
        

    
    
###############################################################################

"""NON MODIFICARE, codice di testing della funzione"""
counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(funzione5, ['casa','martellare'] , 'cs')
counter_test_positivi += tester_fun(funzione5, ['orbi','botte'] ,'ri')
counter_test_positivi += tester_fun(funzione5, ['botte','orbi'] ,'tte')
counter_test_positivi += tester_fun(funzione5, ['pippo','pluto'] ,'i')
counter_test_positivi += tester_fun(funzione5, ['casa',''] ,'casa')

print('La funzione',funzione5.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
