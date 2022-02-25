from tester import tester_fun

def Ex3(file):
    p = open(file, 'r', encoding = 'utf-8')
    p.readline()
    d = {}
    for riga in p:
        rs=riga.split(',')
        s1=rs[0]
        if s1 not in d:
            d[s1] = 0
        s2=rs[1]
        if s2 not in d:
            d[s2] = 0
        g1=int(rs[2])
        g2=int(rs[3].strip())
        if g1>g2:
             d[s1]=d[s1]+3
        elif g2>g1:
            d[s2]=d[s2]+3
        elif g1==g2:
            d[s1]=d[s1]+1
            d[s2]=d[s2]+1
    return d
        
        
    



        
        
        
            
            
        
        
    
###############################################################################

"""TEST FUNZIONE, NON MODIFICARE"""

counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(Ex3, ["partite1.csv"] , {'Chelsea': 3, 'Everton': 3, 'Arsenal': 4, 'Tottenham': 1})
counter_test_positivi += tester_fun(Ex3, ["partite2.csv"] , {'Chelsea': 4, 'Everton': 6, 'Arsenal': 4, 'Tottenham': 2})
counter_test_positivi += tester_fun(Ex3, ["partite3.csv"] , {'Bayern': 4, 'Schalke': 3, 'Amburgo': 4, 'Werder': 1, 'Colonia': 4, 'Stoccarda': 0})
counter_test_positivi += tester_fun(Ex3, ["partite4.csv"] , {'Bayern': 8, 'Schalke': 6, 'Amburgo': 8, 'Werder': 2, 'Colonia': 8, 'Stoccarda': 0})
counter_test_positivi += tester_fun(Ex3, ["partite5.csv"] , {'Bayern': 5, 'Schalke': 6, 'Amburgo': 5, 'Werder': 5, 'Colonia': 5, 'Stoccarda': 6})

print('La funzione',Ex3.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
