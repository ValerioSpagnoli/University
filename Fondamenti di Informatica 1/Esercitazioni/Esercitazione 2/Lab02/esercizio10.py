carattere = str(input("Celsisus[C] o Fahrenheit[F]?: "))
temperatura = int(input("inserisci temperatura: "))
if carattere=="F":
    temperatura = (temperatura-32)/1.8
if temperatura >= 100 :
    print("gassosa")
elif temperatura < 100 and temperatura > 0:
    print("liquida")
else:
    print("solida")
