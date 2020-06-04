using System;
using System.Net.Http;

namespace LabaSharp2
{
    class A
    {
        public int a;
        public A(int i) { a = i; }
        public A() { }
        public static A operator ++(A a1)
        {
            return new A { a = a1.a + 1 };
        }

        public static A operator +(A a1, A b1)
        {
            return new A { a = a1.a + b1.a };
        }

        public static bool operator ==(A a1, B b1)
        {
            if (a1.a == b1.b) return true;
            return false;
        }

        public static bool operator !=(A a1, B b1)
        {
            if (a1.a != b1.b) return true;
            return false;
        }
    }

    class B
    {
        public int b;
        public int[] b1;


        public B(int i) {
            b = i;
            b1 = new int[5];
            for (int j = 0; i < 5; i++)
                b1[j] = j;
        }

        public int this[int i]
        {
            get
            {
                return b1[i];
            }
            set
            {
                b1[i] = value;
            }
        }
        public B() { }
    }
    

    class Program
    {
        delegate void Message();

        public static void Greeting()
        {
            Console.WriteLine("Hop hey hi");
        }

        static void Main(string[] args)
        {
            Message mes = Greeting;
            mes();
            A a = new A(2);
            Console.WriteLine($"{a.a}");
            B b = new B(3);
            a++;
            Console.WriteLine($"{a.a}");
            A a1 = a + a;
            Console.WriteLine($"{a1.a}");
            Console.WriteLine($"{a == b}");
            Console.WriteLine($"{a != b}");
            Console.WriteLine($"{b[0]}");
            b[0] = 5;
            Console.WriteLine($"{b[0]}");


        }
    }
}
