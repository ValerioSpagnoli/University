etaCane = float(input("Inserisci eta' del cane: "))
if etaCane < 0:
    print("L'eta' deve essere positiva!")
elif etaCane <= 2 :
    etaCaneUmana = etaCane * 10.5
    print("L'eta' del cane è':", etaCaneUmana)
elif etaCane > 2:
    etaCaneUmana = 21 + (etaCane - 2)*4
    print("L'eta' del cane è':", etaCaneUmana)

## Soluzione alternativa: si noti che nel codice possiamo 
## fare a meno di una istruzione print, ma abbiamo un livello
## di indentazione in più
##        
##etaCane = float(input("Inserisci eta' del cane: "))
##if etaCane < 0:
##        print("L'eta' deve essere positiva!")
##else:
##        if etaCane <= 2 :
##                etaCaneUmana = etaCane * 10.5
##        elif etaCane > 2:
##                etaCaneUmana = 21 + (etaCane - 2)*4
##        print("L'eta' del cane è':", etaCaneUmana)
