from tester import tester_fun

def A_Ex5(s1,s2):
    r = ''
    if s1 == '' or s2 == '':
        return r
    
    else:
        
        if len(s1)>len(s2):
            for i in range(len(s2)):
                if s1[i]==s2[i]:
                    r = r + s1[i]
                elif s1[i]!=s2[i]:
                    break
            return r
        
        if len(s2)>len(s1):
            for i in range(len(s1)):
                if s1[i]==s2[i]:
                    r = r + s1[i]
                elif s1[i]!=s2[i]:
                    break
            return r
            
    

###############################################################################

"""NON MODIFICARE, codice di testing della funzione"""
counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(A_Ex5, ['amaca','amaranto'], 'ama')
counter_test_positivi += tester_fun(A_Ex5, ['asso','assolato'], 'asso')
counter_test_positivi += tester_fun(A_Ex5, ['','stringa'], '')
counter_test_positivi += tester_fun(A_Ex5, ['stringa',''], '')
counter_test_positivi += tester_fun(A_Ex5, ['ciao mamma','ciao '], 'ciao ')

print('La funzione',A_Ex5.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
