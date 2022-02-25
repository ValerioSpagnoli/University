from tester import tester_fun

def Ex6(file):
    f = open(file, 'r', encoding = 'utf-8')
    f.readline()
    d = {}
    l = []
    for riga in f:
        l = []
        p = []
        rs = riga.split(',')
        s1 = rs[0]
        if s1 not in d:
            d[s1] = l
        s2 = rs[1]
        if s2 not in d:
            d[s2] = p
        g1 = int(rs[2])
        g2 = int(rs[3].strip())
        if g1>g2:
            k = d.get(s1)
            k.append(s2)
            d[s1] = k
        elif g1<g2:
            k = d.get(s2)
            k.append(s1)
            d[s2] = k
    f.close()
##########
    for key in d:
        f = open(file, 'r', encoding = 'utf-8')
        f.readline()
        for riga in f:
            rs = riga.split(',')
            s1 = rs[0]
            s2 = rs[1]
            g1 = int(rs[2])
            g2 = int(rs[3].strip())
            if key == s1 or key == s2:
                if key == s1 and g1<g2 and s2 in d[key]:
                    d[key].remove(s2)
                elif key == s2 and g1>g2 and s1 in d[key]:
                    d[s2].remove(s1)
                elif key == s2 and g2<g1 and s1 in d[key]:
                    d[key].remove(s1)
                elif key == s1 and g1>g2 and s1 in d[key]:
                    d[s2].remove(s1)
        f.close()
    return d

###############################################################################

"""TEST FUNZIONE, NON MODIFICARE"""

counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(Ex6, ["partite1.csv"] , {'Chelsea': [], 'Everton': ['Tottenham'], 'Arsenal': ['Chelsea'], 'Tottenham': []})
counter_test_positivi += tester_fun(Ex6, ["partite2.csv"] , {'Chelsea': ['Everton'], 'Everton': ['Tottenham', 'Arsenal'], 'Arsenal': ['Chelsea'], 'Tottenham': []})
counter_test_positivi += tester_fun(Ex6, ["partite3.csv"] , {'Bayern': ['Schalke'], 'Schalke': ['Stoccarda'], 'Amburgo': ['Werder'], 'Werder': [], 'Stoccarda': [], 'Colonia': ['Stoccarda']})
counter_test_positivi += tester_fun(Ex6, ["partite4.csv"] , {'Bayern': ['Schalke', 'Schalke'], 'Schalke': ['Stoccarda', 'Stoccarda'], 'Amburgo': ['Werder', 'Werder'], 'Werder': [], 'Stoccarda': [], 'Colonia': ['Stoccarda', 'Stoccarda']})
counter_test_positivi += tester_fun(Ex6, ["partite5.csv"] , {'Bayern': [], 'Schalke': [], 'Amburgo': [], 'Werder': [], 'Stoccarda': [], 'Colonia': []})

print('La funzione',Ex6.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
