#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Scrivere una funzione che prende in input una stringa s
ed un intero n e restituisce una nuova stringa
in cui ogni carattere di s è ripetuto n volte. Ad esempio,
se s= ‘casa’ e n = 2 allora deve restituire la
stringa ‘ccaassaa’
"""

from tester import tester_fun

def funzione4(s,n):
    z = ''
    for i in range(0, len(s)):
        x = s[i]*n
        z = z+x
    return z

    
    
###############################################################################

"""NON MODIFICARE, codice di testing della funzione"""
counter_test_positivi = 0
total_tests = 4

counter_test_positivi += tester_fun(funzione4, ['casa',2] ,'ccaassaa')
counter_test_positivi += tester_fun(funzione4, ['casa',4] ,'ccccaaaassssaaaa')
counter_test_positivi += tester_fun(funzione4, ['a',4] ,'aaaa')
counter_test_positivi += tester_fun(funzione4, ['',0] ,'')

print('La funzione',funzione4.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
