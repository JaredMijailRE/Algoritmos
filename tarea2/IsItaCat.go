package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	var t int
	fmt.Fscan(reader, &t)
	for i := 0; i < t; i++ {
		var n int
		var s string
		fmt.Fscan(reader, &n, &s)
		if isMeow(s) {
			fmt.Println("YES")
		} else {
			fmt.Println("NO")
		}
	}
}

func isMeow(s string) bool {
	counts := [4]int{}
	pattern := []rune{'m', 'e', 'o', 'w'}
	idx := 0

	for _, ch := range s {
		c := ch
		if 'A' <= ch && ch <= 'Z' {
			c = ch + ('a' - 'A')
		}
		if c == pattern[idx] {
			counts[idx]++
		} else if idx < 3 && c == pattern[idx+1] {
			idx++
			counts[idx]++
		} else {
			return false
		}
	}
	if idx != 3 {
		return false
	}
	for _, cnt := range counts {
		if cnt == 0 {
			return false
		}
	}
	return true
}
