def contar_elementos(texto):
    palabras = 0
    letras = 0
    digitos = 0
    palabra = False  

    for char in texto:
       
        if char == ' ':
            if palabra:
                palabras += 1
                palabra = False
        if char == '\n':
            if palabra:
                palabras += 1
                en_palabra = False
        if char == '\t':
            if palabra:
                palabras += 1
                palabra = False
        if char != ' ':
            if char != '\n':
                if char != '\n':
                    if 'a' <= char <= 'z':
                        letras += 1
                        palabra = True
                    if 'A' <= char <= 'Z':
                        letras += 1
                        palabra = True
                    if '0' <= char <= '9':
                        digitos += 1
                        palabra = True

    if palabra:
        palabras += 1

    return palabras, letras, digitos

texto = input("Ingrese un texto: ")
palabras, letras, digitos = contar_elementos(texto)
print("Palabras:", palabras, "Letras:", letras, "Dígitos:", digitos)