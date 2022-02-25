dividendo=int(input("Introduci un dividendo: "))
divisore=int(input("Introduci un divisore: "))
if divisore==0:
  print("divisione per zero non definita")
else:
  print(dividendo, "//", divisore,"=", end=" ")
  segno = "positivo"
  if (divisore < 0 and dividendo >0) or (divisore > 0 and dividendo < 0) :
    segno = "negativo"
  dividendo = abs(dividendo)
  divisore = abs(divisore)
  quoziente = 0
  while (dividendo >= divisore): 
    dividendo -= divisore
    quoziente += 1
  if segno == "positivo" :
    print(quoziente)
  elif dividendo%divisore==0:
    print(-quoziente)
  else:
    print(-quoziente-1)
