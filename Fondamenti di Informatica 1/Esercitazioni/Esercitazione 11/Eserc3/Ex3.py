from tester import tester_fun

def Ex3(file):
    f = open(file, 'r', encoding='utf-8')
    s = f.readline().split(' ')
    righe = int(s[0])
    colonne = int(s[1].strip())
    l=f.readlines()
    d={}
    for i in range(righe):
        riga=l[i].split(' ')
        d[i]=0
        for j in range(colonne):
            e = riga[j].strip()
            if int(e)<0:
                d[i]=d[i]+1
    c = list(d.keys())
    n = 0
    p = 0
    for key in c:
        val = d[key]
        if val>=p:
            p = val
            n = key

    return n
                
                
                
    
    
    
    

 
###############################################################################

"""TEST FUNZIONE, NON MODIFICARE"""

counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(Ex3, ["matrice1.txt"] , 3)
counter_test_positivi += tester_fun(Ex3, ["matrice2.txt"] , 0)
counter_test_positivi += tester_fun(Ex3, ["matrice3.txt"] , 1)
counter_test_positivi += tester_fun(Ex3, ["matrice4.txt"] , 3)
counter_test_positivi += tester_fun(Ex3, ["matrice5.txt"] , 4)

print('La funzione',Ex3.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
