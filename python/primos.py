def es_primo(n):
    if n <= 1:
        return False
    i = 2
    while i * i <= n:
        if n % i == 0:
            return False
        i += 1
    return True

def factores_primos(n):
    factores = []
    i = 2
    while i <= n:
        while n % i == 0:
            factores += [i]  
            n //= i  #Divide un numero entero en otro
        i += 1
    return factores

num = int(input("Ingrese un número: "))
print("Es primo:", es_primo(num))
print("Factores primos:", factores_primos(num))