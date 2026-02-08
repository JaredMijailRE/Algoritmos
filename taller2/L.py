import sys
from collections import deque

def main():
    datos = sys.stdin.read().splitlines()
    if not datos:
        print('No')
        return

    filas, columnas = map(int, datos[0].split())
    mapa = [linea.strip() for linea in datos[1:1 + filas]]
    secuenciaMovimientos = datos[1 + filas].strip() if len(datos) > 1 + filas else ""
    inicioPacman = None
    inicioFantasma = None
    for fila in range(filas):
        for columna in range(columnas):
            if mapa[fila][columna] == 'P':
                inicioPacman = (fila, columna)
            elif mapa[fila][columna] == 'G':
                inicioFantasma = (fila, columna)
    if not inicioPacman or not inicioFantasma:
        print('No')
        return

    movimientosPacman = {'U': (-1, 0), 'D': (1, 0), 'L': (0, -1), 'R': (0, 1)}
    rutaPacman = []
    celdasObjetivo = set()
    filaPac, colPac = inicioPacman
    rutaPacman.append((filaPac, colPac))
    celdasObjetivo.add(filaPac * columnas + colPac)

    for movimiento in secuenciaMovimientos:
        dFila, dCol = movimientosPacman[movimiento]
        nuevaFila, nuevaCol = filaPac + dFila, colPac + dCol
        if not (0 <= nuevaFila < filas and 0 <= nuevaCol < columnas):
            nuevaFila %= filas
            nuevaCol %= columnas
        if mapa[nuevaFila][nuevaCol] != '#':
            filaPac, colPac = nuevaFila, nuevaCol
        rutaPacman.append((filaPac, colPac))
        celdasObjetivo.add(filaPac * columnas + colPac)
    tamaño = filas * columnas
    distancia = [-1] * tamaño
    cola = deque()
    filaFant, colFant = inicioFantasma
    idxInicio = filaFant * columnas + colFant
    distancia[idxInicio] = 0
    cola.append(idxInicio)
    encontrados = 0
    if idxInicio in celdasObjetivo:
        encontrados += 1
    movimientos = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    while cola and encontrados < len(celdasObjetivo):
        idx = cola.popleft()
        r, c = divmod(idx, columnas)
        distActual = distancia[idx]
        for dFila, dCol in movimientos:
            nuevaFila = r + dFila
            nuevaCol = c + dCol
            if 0 <= nuevaFila < filas and 0 <= nuevaCol < columnas:
                nuevoIdx = nuevaFila * columnas + nuevaCol
                if mapa[nuevaFila][nuevaCol] != '#' and distancia[nuevoIdx] == -1:
                    distancia[nuevoIdx] = distActual + 1
                    cola.append(nuevoIdx)
                    if nuevoIdx in celdasObjetivo:
                        encontrados += 1
    for pasoTiempo, (r, c) in enumerate(rutaPacman):
        idx = r * columnas + c
        if distancia[idx] != -1 and distancia[idx] <= pasoTiempo:
            print('Yes')
            return

    print('No')

if _name_ == "_main_":
    main()