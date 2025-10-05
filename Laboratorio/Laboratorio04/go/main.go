package main

import (
	"fmt"
	"trapezoidal/pooling"
)

func main() {
	f := func(x float64) float64 { return x * x }
	res := pooling.TrapezoidalPool(f, 0, 1, 1_000_000, 4)
	fmt.Println("Result:", res)
}