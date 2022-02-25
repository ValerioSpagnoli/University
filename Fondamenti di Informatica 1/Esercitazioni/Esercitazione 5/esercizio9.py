#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Scrivere una funzione booleana che prende come parametro una stringa
contenente almeno due caratteri e restituisce True se i caratteri
sono tutti in ordine crescente, False altrimenti.
"""

from tester import tester_fun

def funzione6(s):
    variabile = True
    if len(s)>2:
        for i in range(0, len(s)-1):
            if s[i]<s[i+1]:
                variabile = True
            else:
                variabile = False
                break
        return variabile


    
###############################################################################

"""NON MODIFICARE, codice di testing della funzione"""
counter_test_positivi = 0
total_tests = 3

counter_test_positivi += tester_fun(funzione6, ['abcd'] , True)
counter_test_positivi += tester_fun(funzione6, ['casale'] , False)
counter_test_positivi += tester_fun(funzione6, ['abaco'] , False)

print('La funzione',funzione6.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
