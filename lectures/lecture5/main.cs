using static System.Console;    //Purists say never do this, write the whole thing! E.g. .System.Console.WriteLine;
using complex = System.Numerics.Complex;

class main {
    static void echo<T>(T arg) {
        WriteLine($"echo: {arg}");
    }

    // static void addition<T>(T x, T y) {
    //     WriteLine($"echo: {x+y}");
    // }

    static void fun_of_one(System.Func<double, double> f) {
        WriteLine($"f(2) = {f(2)}");
    }

    static int Main() {
        System.Func<double, double> f = delegate(double x) {return x*x;};
        f = (double x) => x*x;  //Might be able to skip (double x) and write just x instead because compiler knows f is of <double, double>
        f = System.Math.Sin;
        fun_of_one(f);
        fun_of_one(x => x*x);   //Anonymous function
        echo("string");
        echo(1);
        echo(1.23);
        // echo(complex.Sqrt((complex)(-1)));
        complex I = complex.Sqrt(-1);
        echo(complex.Sqrt(-1));
        echo(complex.Pow(I, I));
        echo(complex.Sin(I));
        // string s = "original string";
        // System.Action prints = delegate(){WriteLine($"prints: s={s}");}
        // s = "new string";
        return 0;
    }
}