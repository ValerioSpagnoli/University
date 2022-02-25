from tester import tester_fun

def Ex4(file):
    f = open(file, 'r', encoding='utf-8')
    f. readline()
    d = {}
    l = []
    for riga in f:
        rs = riga.split(',')
        
        p1 = rs[0]
        if p1 not in d:
            d[p1] = l
            
        p2 = rs[1]
        if p2 not in d:
            d[p2] = l
            
        r = rs[2].strip()
    nomi = list(d.keys()) # lista con i nomi
    f.close()
    ####
    f = open(file, 'r', encoding='utf-8')
    f. readline()
    for N in nomi:
        print(N)
        g = []
        f = open(file, 'r', encoding='utf-8')
        f. readline()
        for riga in f:
            rs = riga.split(',')
            p1 = rs[0]
            p2 = rs[1]
            r = rs[2].strip()
            if N == p1 and r == 'amici' and p2 not in d[p1]:
                g.append(p2)
                d[p1]=g
            elif N == p2 and r == 'amici' and p1 not in d[p2]:
                g.append(p1)
                d[p2]=g
            elif N == p1 and r == 'nemici' and p2 in d[p1]:
                g.remove(p2)
                d[p1]=g
            elif N == p2 and r == 'nemici' and p1 in d[p2]:
                g.remove(p1)
                d[p2]=g
        f.close()
    for N in nomi:
        g=d[N]
        g.sort()
        d[N]=g
    return d
                
        
        
        
    
    
    
    


                
        
    

    
        

            
            
    

    

        


    
###############################################################################

"""TEST FUNZIONE, NON MODIFICARE"""

counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(Ex4, ["amici1.csv"] , {'Paolo': ['Marco'], 'Marco': ['Paolo'], 'Anna': ['Maria', 'Paola'], 'Maria': ['Anna'], 'Paola': ['Anna'], 'Giorgio': []})
counter_test_positivi += tester_fun(Ex4, ["amici2.csv"] , {'Paolo': ['Marco'], 'Marco': ['Paolo'], 'Anna': ['Maria'], 'Maria': ['Anna'], 'Paola': [], 'Giorgio': []})
counter_test_positivi += tester_fun(Ex4, ["amici3.csv"] , {'Paolo': ['Marco'], 'Marco': ['Paolo'], 'Anna': ['Maria', 'Paola'], 'Maria': ['Anna'], 'Paola': ['Anna'], 'Giorgio': []})
counter_test_positivi += tester_fun(Ex4, ["amici4.csv"] , {'Marco': ['Giorgio', 'Paolo'], 'Giorgio': ['Marco'], 'Paolo': ['Marco'], 'Anna': ['Maria', 'Paola'], 'Maria': ['Anna'], 'Paola': ['Anna']})
counter_test_positivi += tester_fun(Ex4, ["amici5.csv"] , {'Marco': [], 'Giorgio': [], 'Paola': [], 'Anna': []})

print('La funzione',Ex4.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
