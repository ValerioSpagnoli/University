from tester import tester_fun

def Ex4(file):
    f = open(file, 'r', encoding='utf-8')
    f.readline()
    d = {}
    for riga in f:
        l=[]
        rs = riga.split(',')
        oggetto=rs[0]
        antenato=rs[1]
        erede=rs[2].strip()
        if oggetto not in d:
            l.append(antenato)
            l.append(erede)
            d[oggetto]=l
        elif oggetto in d and antenato in d[oggetto][1]:
            d[oggetto].pop()
            d[oggetto].append(erede)
    return d
     
            
            
        
    
    
###############################################################################

"""TEST FUNZIONE, NON MODIFICARE"""

counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(Ex4, ["eredita1.csv"] , {'bracelet': ['Maria', 'Giorgia'], 'Signore_Degli_Anelli': ['Silvia', 'Paolo']})
counter_test_positivi += tester_fun(Ex4, ["eredita2.csv"] , {'bracelet': ['Marco', 'Giorgio'], 'ring': ['Silvia', 'Sergio']})
counter_test_positivi += tester_fun(Ex4, ["eredita3.csv"] , {'bracelet': ['Marco', 'Giorgio'], 'ring': ['Silvia', 'Sergio'], 'vase': ['Anna', 'Sergio']})
counter_test_positivi += tester_fun(Ex4, ["eredita4.csv"] , {'bracelet': ['Marco', 'Giorgio'], 'ring': ['Silvia', 'Giorgio'], 'vase': ['Anna', 'Anna']})
counter_test_positivi += tester_fun(Ex4, ["eredita5.csv"] , {'bracelet': ['Marco', 'Giorgio'], 'ring': ['Silvia', 'Sergio'], 'vase': ['Sergio', 'Anna']})

print('La funzione',Ex4.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
