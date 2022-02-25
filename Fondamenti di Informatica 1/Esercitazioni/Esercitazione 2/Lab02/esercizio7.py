mese = int(input("inserire mese: "))
anno = int(input("inserire anno: "))
if mese<0 or mese>12:
    print("[Errore] Valori Inseriti ERRATI!!")
else:
    if mese==12:
        print("mese: 1 anno:", anno + 1)
    else:
        print("mese:", mese + 1, "anno:",anno)
