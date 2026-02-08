package main

import (
	"fmt"
)

// Función principal
func main() {
	arr := []int{0xAA, 0x1F, 0x75, 0x5B, 0x2A3, 0x1C, 0x02, 0x66}
	radixSort(arr)

	fmt.Println("Arreglo ordenado (en hexadecimal):")
	for _, v := range arr {
		fmt.Printf("%X ", v)
	}
}

// Counting Sort basado en dígitos hexadecimales (base 16)
func countingSort(arr []int, exp int) {
	n := len(arr)
	output := make([]int, n)
	count := make([]int, 16) // Para dígitos 0–F (0–15 decimal)

	for i := 0; i < n; i++ {
		index := (arr[i] / exp) % 16
		count[index]++
	}

	for i := 1; i < 16; i++ {
		count[i] += count[i-1]
	}

	for i := n - 1; i >= 0; i-- {
		index := (arr[i] / exp) % 16
		output[count[index]-1] = arr[i]
		count[index]--
	}

	for i := 0; i < n; i++ {
		arr[i] = output[i]
	}
}

// Radix Sort para base 16
func radixSort(arr []int) {
	max := getMax(arr)

	for exp := 1; max/exp > 0; exp *= 10 {
		countingSort(arr, exp)
	}
}

// Obtener el valor máximo del arreglo
func getMax(arr []int) int {
	max := arr[0]
	for _, num := range arr {
		if num > max {
			max = num
		}
	}
	return max
}
