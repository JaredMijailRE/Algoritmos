package main

import (
	"fmt"
)

// Función principal
func main() {
	arr := []int{170, 45, 75, 90, 802, 24, 2, 66}
	radixSort(arr)

	fmt.Println("Arreglo ordenado:")
	for _, v := range arr {
		fmt.Print(v, " ")
	}
}

// Función para hacer Counting Sort según el dígito representado por exp (1s, 10s, 100s, etc.)
func countingSort(arr []int, exp int) {
	n := len(arr)
	output := make([]int, n) // Arreglo de salida
	count := make([]int, 10) // Contador para dígitos 0-9

	// Contar ocurrencias de cada dígito
	for i := 0; i < n; i++ {
		index := (arr[i] / exp) % 10
		count[index]++
	}

	// Cambiar count[i] para que contenga la posición real en output[]
	for i := 1; i < 10; i++ {
		count[i] += count[i-1]
	}

	// Construir el arreglo de salida (de derecha a izquierda para estabilidad)
	for i := n - 1; i >= 0; i-- {
		index := (arr[i] / exp) % 10
		output[count[index]-1] = arr[i]
		count[index]--
	}

	// Copiar el arreglo ordenado de vuelta al original
	for i := 0; i < n; i++ {
		arr[i] = output[i]
	}
}

// Función principal de Radix Sort
func radixSort(arr []int) {
	// Obtener el número máximo para conocer la cantidad de dígitos
	max := getMax(arr)

	// Hacer Counting Sort para cada dígito (1s, 10s, 100s, ...)
	for exp := 1; max/exp > 0; exp *= 10 {
		countingSort(arr, exp)
	}
}

// Función auxiliar para encontrar el número máximo en el arreglo
func getMax(arr []int) int {
	max := arr[0]
	for _, num := range arr {
		if num > max {
			max = num
		}
	}
	return max
}
