from tester import tester_fun

def Ex4(file):
    f = open(file, 'r', encoding = 'utf-8')
    d ={}
    l = [0, 0]
    for riga in f:
        rs=riga.split(',')
        for gv in rs:
            l = [0, 0]
            gvs = gv.split()
            giocatore = gvs[0]
            valore = int(gvs[1].strip())
            if giocatore not in d:
                l[0]=l[0]+1
                l[1]= l[1]+valore
                d[giocatore] = l
            elif giocatore in d:
                l[0]=d[giocatore][0]+1
                l[1]= d[giocatore][1]+valore
                d[giocatore] = l
    return d  
                
                
            
            
            
            
            
            
        
        
        
        
        
    
 
###############################################################################

"""TEST FUNZIONE, NON MODIFICARE"""

counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(Ex4, ['partite1.csv'] , {'Paolo': [2, 15], 'Mario': [1, -5], 'Anna': [2, 3], 'Giorgio': [1, 0], 'Stefano': [1, -10], 'Paola': [1, -3]})
counter_test_positivi += tester_fun(Ex4, ['partite2.csv'] , {'Paolo': [4, 20], 'Mario': [2, 0], 'Anna': [4, 16], 'Giorgio': [3, -8], 'Stefano': [2, -20], 'Paola': [1, -3]})
counter_test_positivi += tester_fun(Ex4, ['partite3.csv'] , {'Paolo': [4, 20], 'Mario': [4, 16], 'Anna': [4, -20], 'Giorgio': [4, -11]})
counter_test_positivi += tester_fun(Ex4, ['partite4.csv'] , {'Paolo': [4, 20], 'Mario': [4, 16], 'Anna': [4, -20], 'Giorgio': [4, -11], 'Fabio': [1, 10], 'Carlo': [1, 10], 'Maria': [1, -12], 'Simona': [1, -8]})
counter_test_positivi += tester_fun(Ex4, ['partite5.csv'] , {})

print('La funzione',Ex4.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
