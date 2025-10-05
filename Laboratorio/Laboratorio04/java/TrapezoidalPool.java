import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.function.Function;

public class TrapezoidalPool {
    public static double integrate(Function<Double, Double> function,
                                   double low,
                                   double sup,
                                   int n,
                                   int numThreads) throws InterruptedException, ExecutionException {
        double height = (sup - low) / n;
        double firstAndLast = (function.apply(low) + function.apply(sup)) / 2.0;

        ExecutorService executor = Executors.newFixedThreadPool(numThreads);
        Future<Double>[] futures = new Future[numThreads];

        int chunk = n / numThreads;

        for (int i = 0; i < numThreads; i++) {
            int start = i * chunk + 1;
            int end = (i == numThreads - 1) ? n - 1 : (i + 1) * chunk;

            futures[i] = executor.submit(() -> {
                double localSum = 0.0;
                for (int j = start; j <= end; j++) {
                    double xi = low + j * height;
                    localSum += function.apply(xi);
                }
                return localSum;
            });
        }

        double total = 0.0;
        for (Future<Double> future : futures) {
            total += future.get();
        }

        executor.shutdown();

        return (firstAndLast + total) * height;
    }
}
