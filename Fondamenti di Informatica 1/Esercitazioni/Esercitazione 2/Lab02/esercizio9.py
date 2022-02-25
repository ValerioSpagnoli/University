temperatura=float(input("inserisci la temperatura "))
if temperatura > 30:
    print("molto caldo")
elif temperatura <= 30 and temperatura > 20:    
    print("caldo")
elif temperatura <= 20 and temperatura > 10:
    print("gradevole")
else:
    print("freddo")
