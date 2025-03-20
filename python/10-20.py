def calcular(calificaciones):
    suma = 0
    i = 0
    while i < len(calificaciones):
        suma = suma + calificaciones[i]
        i = i + 1
    if len(calificaciones) == 0:
        return 0
    return suma / len(calificaciones)

calificaciones = []
n = int(input("¿Cuántos estudiantes deseas ingresar? "))
i = 0
while i < n:
    calificacion = float(input("Ingresa la calificación del estudiante: "))
    calificaciones = calificaciones + [calificacion]  # Concatenar la calificación ingresada
    i = i + 1

promedio = calcular(calificaciones)
print("El promedio de las calificaciones es:", promedio)