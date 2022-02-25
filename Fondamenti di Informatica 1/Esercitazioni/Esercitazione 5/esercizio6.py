#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Scrivere una funzione che prende in input una stringa s
e restituisce il carattere che compare più
spesso. Se più caratteri compaiono lo stesso numero di
volte deve restituire il primo carattere in ordine.
"""

from tester import tester_fun

def funzione3(s):
    if len(s)==0:
        mas = ''
    else:
        mas = s[0]
        for i in range (0, len(s)):
            if s.count(mas)<s.count(s[i]):
                mas = s[i]
            elif s.count(mas)>=s.count(s[i]):
                mas = mas
    return mas
            
                
                

        
    

    
    
    
###############################################################################

"""NON MODIFICARE, codice di testing della funzione"""
counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(funzione3, ['partecipazione'] ,'p')
counter_test_positivi += tester_fun(funzione3, ['cassetto'] ,'s')
counter_test_positivi += tester_fun(funzione3, ['pari'] ,'p')
counter_test_positivi += tester_fun(funzione3, ['a'] ,'a')
counter_test_positivi += tester_fun(funzione3, [''] ,'')

print('La funzione',funzione3.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
