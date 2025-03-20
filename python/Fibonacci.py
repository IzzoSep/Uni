def fibonacci(n):
    a, b = 0, 1
    resultado = []  
    count = 0  
    while count < n:
        resultado += [a]  
        a, b = b, a + b  
        count += 1  
    return resultado


n = 10  
terminos_fibonacci = fibonacci(n)
print("Términos de Fibonacci:", terminos_fibonacci)