def burbuja(lista):
    n = len(lista)
    i = 0
    while i < n:
        j = 0
        while j < n - i - 1:
            if lista[j] > lista[j + 1]:
                lista[j], lista[j + 1] = lista[j + 1], lista[j]
            j += 1
        i += 1
    return lista

entrada = input("Ingrese números separados por espacio: ")
numeros = [0] * 100
contador = 0
numero_actual = ""

for caracter in entrada:
    if caracter == " ":
        if numero_actual:
            numeros[contador] = int(numero_actual)
            contador += 1
            numero_actual = ""
    else:
        numero_actual += caracter

if numero_actual:
    numeros[contador] = int(numero_actual)
    contador += 1

numeros = numeros[:contador]
print("Lista ordenada:", burbuja(numeros))