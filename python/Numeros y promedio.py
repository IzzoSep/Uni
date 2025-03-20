def promedio(numeros):
    suma = 0
    maximo = minimo = numeros[0]
    contador = 0

    while contador < len(numeros):
        suma += numeros[contador]
        if numeros[contador] > maximo:
            maximo = numeros[contador]
        if numeros[contador] < minimo:
            minimo = numeros[contador]
        contador += 1

    return suma / len(numeros), maximo, minimo


numeros = [10, 20, 30, 40, 50]
promedio, maximo, minimo = promedio(numeros)
print("Promedio:", promedio)
print("Número más grande:", maximo)
print("Número más pequeño:", minimo)