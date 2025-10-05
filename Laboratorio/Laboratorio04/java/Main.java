public class Main {
    public static void main(String[] args) throws Exception {
        double result = Trapezoidal.integrate(
                x -> x * x,
                0.0,
                1.0,
                1_000_000_000,
                4
        );

        System.out.println("Resultado aproximado: " + result);
        System.out.println("Resultado exacto: " + (1.0 / 3.0));
    }
}

// 0.3333333314583361
// 0.3333314583354972
// 0.3333333323958061