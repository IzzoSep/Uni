def raiz_cuadrada(n):
    if n < 0:
        return None  
    estimacion = 0
    while estimacion * estimacion < n:
        estimacion += 1
    return estimacion 
if estimacion * estimacion == n else estimacion - 1

def raices_cuadratica(a, b, c):
    discriminante = b**2 - 4*a*c
    if discriminante < 0:
        return "No hay raíces reales"
    elif discriminante == 0:
        return -b / (2 * a),  # Una raíz
    else:
        raiz_discriminante = raiz_cuadrada(discriminante)
        raiz1 = (-b + raiz_discriminante) / (2 * a)
        raiz2 = (-b - raiz_discriminante) / (2 * a)
        return raiz1, raiz2

# Solicitar coeficientes al usuario
a = float(input("Ingrese a: "))
b = float(input("Ingrese b: "))
c = float(input("Ingrese c: "))
print("Raíces:", raices_cuadratica(a, b, c))