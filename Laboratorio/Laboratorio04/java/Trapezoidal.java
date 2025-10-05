import java.util.ArrayList;
import java.util.List;
import java.util.function.Function;

public class Trapezoidal {
    public static double integrate(Function<Double, Double> function,
                                   double low,
                                   double sup,
                                   int n,
                                   int numThreads) throws InterruptedException {
        double height = (sup - low) / n;
        double firstAndLast = (function.apply(low) + function.apply(sup)) / 2.0;


        List<Thread> threads = new ArrayList<>();
        Box box = new Box();

        int chunk = n / numThreads;

        for (int i = 0; i < numThreads; i++) {
            int start = i * chunk + 1;
            int end = (i == numThreads - 1) ? n - 1 : (i + 1) * chunk;

            Thread worker = new Thread(() -> {
                double localSum = 0.0;
                for (int j = start; j <= end; j++) {
                    double xi = low + j * height;
                    localSum += function.apply(xi);
                }

                synchronized (box) {
                    box.value += localSum;
                }
            });

            threads.add(worker);
            worker.start();
        }

        for (Thread thread : threads) {
            thread.join();
        }

        return box.value * height + firstAndLast * height;
    }
}
