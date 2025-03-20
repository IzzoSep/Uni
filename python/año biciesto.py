def bisiesto(year):
    bisiesto = False  
    if (year % 4 == 0 and year % 100 != 0):
        bisiesto = True
    elif (year % 400 == 0):
        es_bisiesto = True
    return bisiesto

year = int(input("Ingrese un año: "))
print("Es bisiesto:", bisiesto(year))