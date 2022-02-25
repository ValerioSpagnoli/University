from tester import tester_fun

def Ex6(file):
    d = {}
    f = open(file, 'r', encoding = 'utf-8')
    m1 = []
    m2 = []
    m3 = []
    m4 = []
    m5 = []
    m6 = []
    m7 = []
    m8 = []
    m9 = []
    i = 0
    while i < 3:
        q = 0
        s = f.readline().split(' ')
        l1 = []
        while q < 3:
            l1.append(s[q])
            q = q+1
        m1.append(l1)
        l2 = []
        while q < 6:
            l2.append(s[q])
            q = q+1
        m2.append(l2)
        l3 = []
        while q < 9:
            l3.append(s[q])
            q = q+1
        m3.append(l3)
        i = i +1
    while i < 6:
        q = 0
        s = f.readline().split(' ')
        l1 = []
        while q < 3:
            l1.append(s[q])
            q = q+1
        m4.append(l1)
        l2 = []
        while q < 6:
            l2.append(s[q])
            q = q+1
        m5.append(l2)
        l3 = []
        while q < 9:
            l3.append(s[q])
            q = q+1
        m6.append(l3)
        i = i +1
    while i < 9:
        q = 0
        s = f.readline().split(' ')
        l1 = []
        while q < 3:
            l1.append(s[q])
            q = q+1
        m7.append(l1)
        l2 = []
        while q < 6:
            l2.append(s[q])
            q = q+1
        m8.append(l2)
        l3 = []
        while q < 9:
            l3.append(s[q])
            q = q+1
        m9.append(l3)
        i = i +1
    d1 = {}
    d2 = {}
    d3 = {}
    d4 = {}
    d5 = {}
    d6 = {}
    d7 = {}
    d8 = {}
    d9 = {}
    for riga in m1:
        for n in riga:
            if n not in d1:
                d1[n]=1
            elif n in d1:
                d1[n]=d1[n]+1
    for riga in m2:
        for n in riga:
            if n not in d2:
                d2[n]=1
            elif n in d2:
                d2[n]=d2[n]+1
    for riga in m3:
        for n in riga:
            if n not in d3:
                d3[n]=1
            elif n in d3:
                d3[n]=d3[n]+1
    for riga in m4:
        for n in riga:
            if n not in d4:
                d4[n]=1
            elif n in d:
                d4[n]=d4[n]+1
    for riga in m5:
        for n in riga:
            if n not in d5:
                d5[n]=1
            elif n in d5:
                d5[n]=d5[n]+1
    for riga in m6:
        for n in riga:
            if n not in d6:
                d6[n]=1
            elif n in d6:
                d6[n]=d6[n]+1
    for riga in m7:
        for n in riga:
            if n not in d7:
                d7[n]=1
            elif n in d:
                d7[n]=d7[n]+1
    for riga in m8:
        for n in riga:
            if n not in d8:
                d8[n]=1
            elif n in d8:
                d8[n]=d8[n]+1
    for riga in m9:
        for n in riga:
            if n not in d9:
                d9[n]=1
            elif n in d9:
                d9[n]=d9[n]+1

    stato = True
    
    k1 = list(d1.keys())
    for key in k1:
        if d1[key]>1:
            stato = False
    k2 = list(d2.keys())
    for key in k2:
        if d2[key]>1:
            stato = False
    k3 = list(d3.keys())
    for key in k3:
        if d3[key]>1:
            stato = False
    k4 = list(d4.keys())
    for key in k4:
        if d4[key]>1:
            stato = False
    k5 = list(d5.keys())
    for key in k5:
        if d5[key]>1:
            stato = False
    k6 = list(d6.keys())
    for key in k6:
        if d6[key]>1:
            stato = False
    k7 = list(d7.keys())
    for key in k7:
        if d7[key]>1:
            stato = False
    k8 = list(d8.keys())
    for key in k8:
        if d8[key]>1:
            stato = False
    k9 = list(d9.keys())
    for key in k9:
        if d9[key]>1:
            stato = False
    f.close()
    f = open(file, 'r', encoding = 'utf-8')
    for riga in f:
        s = riga.split(' ')
        for n in s:
            if s.count(n)>1:
                stato = False
    f.close()
    return stato      
###############################################################################

"""TEST FUNZIONE, NON MODIFICARE"""

counter_test_positivi = 0
total_tests = 3

counter_test_positivi += tester_fun(Ex6, ['sudoku1.txt'], False)
counter_test_positivi += tester_fun(Ex6, ['sudoku3.txt'], True)
counter_test_positivi += tester_fun(Ex6, ['sudoku4.txt'], False)

print('La funzione',Ex6.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
