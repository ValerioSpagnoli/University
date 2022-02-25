from tester import tester_fun

def A_Ex2(fileName):
    f = open(fileName, 'r', encoding='utf-8')
    testo = f.read()
    f.close()
    c = 0
    i = 0
    while i < len(testo):
        if testo[i].isalpha():
            c = c+1
            i = i+1
        else:
            i = i+1
    return c
    
    

###############################################################################


"""NON MODIFICARE, codice di testing della funzione"""
counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(A_Ex2, ["Esempio1.txt"], 7)
counter_test_positivi += tester_fun(A_Ex2, ["Esempio2.txt"], 53)
counter_test_positivi += tester_fun(A_Ex2, ["Esempio3.txt"], 26)
counter_test_positivi += tester_fun(A_Ex2, ["I_Malavoglia_50.txt"], 11808)
counter_test_positivi += tester_fun(A_Ex2, ["I_Malavoglia.txt"], 382468)

print('La funzione',A_Ex2.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
