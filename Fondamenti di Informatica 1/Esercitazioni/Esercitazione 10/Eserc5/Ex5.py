from tester import tester_fun

def Ex5(file):
    f = open(file, 'r', encoding='utf-8')
    d = {}
    d['invalidi'] = 0
    d['domestici'] = 0
    d['altri']= 0
    for riga in f:
        rs = riga.split('.')
        n1 = rs[0]
        N1=int(n1)
        n2 = rs[1]
        N2=int(n2)
        n3 = rs[2]
        N3 = int(n3)
        n4 = rs[3].strip()
        N4 = int(n4)
        Len = len(n1)>=0 and len(n1)<=3 and len(n2)>=0 and len(n2)<=3 and len(n3)>=0 and len(n3)<=3 and len(n4)>=0 and len(n4)<=3
        if N1 == 192 and N2 == 168 and N3>=0 and N3<=255 and N4>=0 and N4<=255 and Len:
            d['domestici']=d['domestici']+1
        elif N1>=0 and N1<=255 and N2>=0 and N2<=255 and N3>=0 and N3<=255 and N4>=0 and N4<=255 and Len:
            d['altri']=d['altri']+1
        elif N1<=0 or N1>=255 or N2<=0 or N2>=255 or N3<=0 or N3>=255 or N4<=0 or N4>=255:
            d['invalidi']=d['invalidi']+1
    return d
    

    
    
###############################################################################

"""TEST FUNZIONE, NON MODIFICARE"""

counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(Ex5, ["ip1.txt"] , {'invalidi': 0, 'domestici': 0, 'altri': 5})
counter_test_positivi += tester_fun(Ex5, ["ip2.txt"] , {'invalidi': 2, 'domestici': 1, 'altri': 2})
counter_test_positivi += tester_fun(Ex5, ["ip3.txt"] , {'invalidi': 1, 'domestici': 1, 'altri': 3})
counter_test_positivi += tester_fun(Ex5, ["ip4.txt"] , {'invalidi': 1, 'domestici': 1, 'altri': 3})
counter_test_positivi += tester_fun(Ex5, ["ip5.txt"] , {'invalidi': 3, 'domestici': 0, 'altri': 2})

print('La funzione',Ex5.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
