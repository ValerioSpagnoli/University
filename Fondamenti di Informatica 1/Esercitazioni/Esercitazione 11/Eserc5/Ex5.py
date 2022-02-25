from tester import tester_fun

def Ex5(file):
    f = open(file, 'r', encoding = 'utf-8')
    g = 0
    for riga in f:
        rs=riga.strip()
        g = g+1
        r = len(rs)
    if g<5 or r<5:
        return False
    f.close()
    d = {}
    f = open(file, 'r', encoding = 'utf-8')
    for riga in f:
        s = riga.strip()
        for i in range(len(s)):
            c = s[i]
            if s.count(c)>1:
                return False
            l = []
            if c not in d:
                l.append(i)
                d[c]=l
            else:
                d[c].append(i)
    v = list(d.values())
    for val in v:
        for e in val:
            if val.count(e)>1:
                stato = False
                return stato
            else:
                stato =  True
    return stato
        
            

                
        
 
    
        
###############################################################################

"""TEST FUNZIONE, NON MODIFICARE"""

counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(Ex5, ['file1.txt'] , True)
counter_test_positivi += tester_fun(Ex5, ['file2.txt'] , False)
counter_test_positivi += tester_fun(Ex5, ['file3.txt'] , False)
counter_test_positivi += tester_fun(Ex5, ['file4.txt'] , False)
counter_test_positivi += tester_fun(Ex5, ['file5.txt'] , False)

print('La funzione',Ex5.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
