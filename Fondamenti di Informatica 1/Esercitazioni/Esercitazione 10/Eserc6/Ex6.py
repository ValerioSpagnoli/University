from tester import tester_fun
import re

def Ex6(file):
    f = open(file, 'r', encoding='utf-8')
    l = []
    riga = f.readline()
    while riga != '':
        cf = riga.replace(' ', '').strip()
        if len(cf)!=16:
            l.append('Codice errato')
            riga = f.readline()
        else:
            cf = cf[:3]+' '+cf[3:6]+' '+cf[6:11]+' '+cf[11:16]
            cfs = cf.split(' ')
            nome = cfs[0]
            if nome.isalpha()==False:
                l.append('Codice errato')
                riga = f.readline()
            cognome = cfs[1]
            if cognome.isalpha()==False:
                l.append('Codice errato')
                riga = f.readline()
            luogo = cfs[3].strip()
            data=cfs[2]
            ds = data[:2]+' '+data[2:3]+' '+data[3:5]
            ds = ds.split()
            gg = ds[2].strip() # giorno
            if int(gg)>71 or (int(gg)>31 and int(gg)<41):
                giorno = 'Giorno errato'
            elif int(gg)>40 and int(gg)<72:
                giorno = int(gg)-40
                giorno = str(giorno)
                if len(giorno)==1:
                    giorno = '0'+giorno
            elif int(gg)<32 and int(gg)>0:
                giorno = str(gg)
                if len(giorno)==1:
                    giorno = '0'+giorno
            M = ds[1] # mese
            if M == 'F' or M == 'G' or M == 'I' or M == 'N' or M == 'O' or M == 'Q' or M == 'U' or M == 'V' or M == 'Z':
                mese = 'Mese errato'
            elif M == 'A':
                mese = '01'
            elif M == 'B':
                mese = '02'
            elif M == 'C':
                mese = '03'
            elif M == 'D':
                mese = '04'
            elif M == 'E':
                mese = '05'
            elif M == 'H':
                mese = '06'
            elif M == 'L':
                mese = '07'
            elif M == 'M':
                mese = '08'
            elif M == 'P':
                mese = '09'
            elif M == 'R':
                mese = '10'
            elif M == 'S':
                mese = '11'
            elif M == 'T':
                mese = '12'
            aa = ds[0] # anno
            if int(aa)<=18:
                anno = '20'+str(aa)
            elif int(aa)>18:
                anno = '19'+str(aa)
            ####
            if mese == 'Mese errato':
                l.append(mese)
                riga = f.readline()
            elif giorno == 'Giorno errato':
                l.append(giorno)
                riga = f.readline()
            elif mese == '02' and int(giorno)>28:
                giorno = 'Giorno errato'
                l.append(giorno)
                riga = f.readline()
            else:
                data = giorno + '/' + mese + '/' + anno
                l.append(data)
                riga = f.readline()
    return l       
                    
              
###############################################################################

"""TEST FUNZIONE, NON MODIFICARE"""

counter_test_positivi = 0
total_tests = 5

counter_test_positivi += tester_fun(Ex6, ["codici1.txt"] , ['12/03/1971', 'Codice errato', '15/04/2011', 'Mese errato', 'Giorno errato'])
counter_test_positivi += tester_fun(Ex6, ["codici2.txt"] , ['12/03/1971', 'Codice errato', '15/04/2011', 'Mese errato', 'Giorno errato', 'Giorno errato', 'Codice errato', 'Giorno errato'])
counter_test_positivi += tester_fun(Ex6, ["codici3.txt"] , ['12/03/1971', 'Codice errato', '15/04/2011', 'Mese errato', 'Giorno errato', 'Giorno errato', 'Codice errato', 'Giorno errato', '01/11/1921'])
counter_test_positivi += tester_fun(Ex6, ["codici4.txt"] , ['12/03/1971', 'Codice errato', '15/04/2011', 'Mese errato', 'Giorno errato', 'Giorno errato', 'Codice errato', 'Giorno errato', '01/11/1921', '01/11/1931'])
counter_test_positivi += tester_fun(Ex6, ["codici5.txt"] , ['12/03/1971', 'Codice errato', '15/04/2011', 'Mese errato', 'Giorno errato', 'Giorno errato', 'Codice errato', 'Giorno errato', '01/11/1921', '01/11/1931', 'Codice errato', 'Giorno errato'])

print('La funzione',Ex6.__name__,'ha superato',counter_test_positivi,'test su',total_tests)
