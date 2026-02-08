import sys
import heapq

def main():
    datos = sys.stdin.read().split()
    if not datos:
        return
    
    cantidadCursos = int(datos[0])
    maxCursosPorSemestre = int(datos[1])
    listaCursos = list(map(int, datos[2:2 + cantidadCursos]))    
    siguienteCurso = [0] * (cantidadCursos + 1)
    for i in range(1, cantidadCursos + 1):
        siguienteCurso[i] = listaCursos[i - 1]
    longitudCadena = [0] * (cantidadCursos + 1)
    for i in range(1, cantidadCursos + 1):
        if longitudCadena[i] == 0:
            camino = []
            cursoActual = i
            while cursoActual != 0 and longitudCadena[cursoActual] == 0:
                camino.append(cursoActual)
                cursoActual = siguienteCurso[cursoActual]
            if cursoActual == 0:
                longitud = 0
                for nodo in reversed(camino):
                    longitud += 1
                    longitudCadena[nodo] = longitud
            else:
                longitud = longitudCadena[cursoActual]
                for nodo in reversed(camino):
                    longitud += 1
                    longitudCadena[nodo] = longitud
    gradoEntrada = [0] * (cantidadCursos + 1)
    for i in range(1, cantidadCursos + 1):
        if siguienteCurso[i] != 0:
            gradoEntrada[siguienteCurso[i]] += 1
    heap = []
    for i in range(1, cantidadCursos + 1):
        if gradoEntrada[i] == 0:
            heapq.heappush(heap, (-longitudCadena[i], i))
    semestres = 0
    while heap:
        cantidadTomados = min(len(heap), maxCursosPorSemestre)
        semestres += 1
        tomados = []
        for t in range(cantidadTomados):
            t, curso = heapq.heappop(heap)
            tomados.append(curso)
        for curso in tomados:
            siguiente = siguienteCurso[curso]
            if siguiente != 0:
                gradoEntrada[siguiente] -= 1
                if gradoEntrada[siguiente] == 0:
                    heapq.heappush(heap, (-longitudCadena[siguiente], siguiente))
    
    print(semestres)

if _name_ == "_main_":
    main()