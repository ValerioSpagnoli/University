from tester import tester_fun

def Ex2(s,n):
    d = {}
    sp = s.split()
    for parola in sp:
        if len(parola)>=n:
            chiave = parola[0]
            if chiave in d:
                d[chiave] = d[chiave] + 1
            else:
                d[chiave] = 1
    return d
            
###############################################################################

"""TEST FUNZIONE, NON MODIFICARE"""

counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(Ex2, ['tanto va la gatta al lardo che ci lascia lo zampino',3] , {'t': 1, 'g': 1, 'l': 2, 'c': 1, 'z': 1})
counter_test_positivi += tester_fun(Ex2, ['tanto va la gatta al lardo che ci lascia lo zampino',5] , {'t': 1, 'g': 1, 'l': 2, 'z': 1})
counter_test_positivi += tester_fun(Ex2, ['scrivere una funzione che prende in ingresso una stringa s composta di caratteri alfabetici e spazi bianchi e restituisce una lista con tutte le parole diverse della stringa',5] , {'s': 4, 'f': 1, 'p': 2, 'i': 1, 'c': 2, 'a': 1, 'b': 1, 'r': 1, 'l': 1, 't': 1, 'd': 2})
counter_test_positivi += tester_fun(Ex2, ['calcoli il dizionario che ha come chiavi le lettere minuscole e come valore il numero di parole di s che cominciano per quella lettera e sono lunghe almeno n caratteri',3] , {'c': 8, 'd': 1, 'l': 3, 'm': 1, 'v': 1, 'n': 1, 'p': 2, 'q': 1, 's': 1, 'a': 1})
counter_test_positivi += tester_fun(Ex2, ['',2] , {})


print('La funzione',Ex2.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
