using System;

namespace LabaSharp4
{
    interface Figure
    {
        public void scaling(int s);

        public void mooving(int x1, int y1);
    }

    interface Initialisation: Figure
    {
        public void init(int x1, int y1, int parameter);

    }

    class Square: Figure, Initialisation
    {
        int x, y, a;

        public void init(int x1, int y1, int a1)
        {
            x = x1;
            y = y1;
            a = a1;
        }
        public void scaling(int s) {
            a*=s;
        }
        public void mooving(int x1, int y1) {
            x+=x1; y += y1;
        }
    }

    class Circle : Figure, Initialisation
    {
        int x, y, radius;
        public void init(int x1, int y1, int radius1)
        {
            x = x1;
            y = y1;
            radius = radius1;
        }
        public void scaling(int s)
        {
            radius*=s;
        }
        public void mooving(int x1, int y1)
        {
            x += x1; y += y1;
        }
    }

    class Rhombus : Square
    {
        int x, y, a;

        public void init(int x1, int y1, int a1)
        {
            x = x1;
            y = y1;
            a = a1;
        }
        public void scaling(int s)
        {
            a *= s;
        }
        public void mooving(int x1, int y1)
        {
            x += x1; y += y1;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Square square = new Square();
            Circle circle = new Circle();
            Rhombus rhombus = new Rhombus();
        }
    }
}
