package integrator

import (
	"sync"
)

func Trapezoidal(
	f func(float64) float64,
	low, sup float64,
	n, numWorkers int,
) float64 {

	height := (sup - low) / float64(n)
	firstAndLast := (f(low) + f(sup)) / 2.0

	var wg sync.WaitGroup
	var mu sync.Mutex

	sum := 0.0

	chunk := n / numWorkers

	for w := 0; w < numWorkers; w++ {
		start := w * chunk + 1
		end := (w + 1) * chunk
		if w == numWorkers-1 {
			end = n - 1
		}

		wg.Add(1)
		go func(start, end int) {
			defer wg.Done()
			localSum := 0.0
			for i := start; i <= end; i++ {
				x := low + float64(i) * height
				localSum += f(x)
			}
			mu.Lock()
			sum += localSum
			mu.Unlock()
		}(start, end)
	}

	wg.Wait()
	return height * (firstAndLast + sum)
}