package pooling

import "sync"

func TrapezoidalPool(
	f func(float64) float64,
	low, sup float64,
	n, numWorkers int,
) float64 {
	height := (sup - low) / float64(n)
	firstAndLast := (f(low) + f(sup)) / 2.0

	jobs := make(chan int, n)

	var wg sync.WaitGroup
	var mu sync.Mutex

	sum := 0.0

	for w := 0; w < numWorkers; w++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			localSum := 0.0
			for i := range jobs {
				x := low + float64(i) * height
				localSum += f(x)
			}
			mu.Lock()
			sum += localSum
			mu.Unlock()
		}()
	}

	for i := 1; i < n; i++ {
		jobs <- i
	}

	close(jobs)

	wg.Wait()
	return height * (firstAndLast + sum)
}