def palindromo(cadena):
    i = 0
    j = len(cadena) - 1

    while i < j:
        if cadena[i] != cadena[j]:
            return False  
        i += 1
        j -= 1
    return True  


texto = input("Ingrese una cadena de texto: ")
resultado = palindromo(texto)

# Imprimir el resultado
i = 0  
while i < 1: 
    if resultado:
        print("La cadena es un palíndromo.")
    else:
        print("La cadena no es un palíndromo.")
    i += 1  