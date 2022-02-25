#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Scrivere una funzione che prende in ingresso una stringa s e calcola la più lunga distanza tra 2
caratteri uguali. Se nessun carattere si ripete allora il risultato deve essere 0. Ad esempio, se s=
‘agfhjskieaha’ la più lunga distanza è tra la prima e l’ultima ‘a’ ed è 11 (la prima volta è in posizione
0 e l’ultima in posizione 11). Consiglio, usate la funzione rfind
"""

from tester import tester_fun

def funzione8(s):
    mas = 0
    for i in range(0, len(s)):
        x = s.find(s[i])
        for j in range(-1, -len(s), -1):
            y = s.rfind(s[j])
            if s[i]==s[j]:
                mas = y-x
                return mas
        
    
        
        


###############################################################################

"""NON MODIFICARE, codice di testing della funzione"""
counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(funzione8, ["agfhjskieaha"] , 11)
counter_test_positivi += tester_fun(funzione8, ["abcd"] , 0)
counter_test_positivi += tester_fun(funzione8, ["casale"] , 2)
counter_test_positivi += tester_fun(funzione8, ["abaco"] , 2)
counter_test_positivi += tester_fun(funzione8, ["alle"] , 1)


print('La funzione',funzione8.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
