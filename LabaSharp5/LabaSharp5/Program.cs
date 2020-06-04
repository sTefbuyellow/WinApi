using System;
using System.Collections.Generic;
using System.Linq.Expressions;

class DivideByZeroException: Exception
{
    public DivideByZeroException(string message) : base(message) { }
}

class OverflowException : Exception
{
    public OverflowException(string message) : base(message) { }
}
class ShortException : Exception
{
    public ShortException(string message) : base(message) { }
}

class Read
{
    public string buff;
    
    public static string getString()
    {
         return Console.ReadLine();
    }

    public static void mainWithExceptions()
    {
        try
        {
            Console.WriteLine(Calculate.main());
        }
        catch(Exception exception)
        {
            Console.WriteLine(exception.Message);
        }
    }
}

class Calculate
{
    delegate void Operation();

    public static double[] numbers = new double[20];
    public static string[] symbols = new string[20];

    public static void getSymbols(string buff)
    {
        if (buff.Length > 20)
        {
            throw new OverflowException("Too many values!");
        }
        if (buff.Length < 3)
        {
            throw new ShortException("");
        }
        string[] split = buff.Split(new string[]{"/-","*-", "+", "-", "*", "/" }, StringSplitOptions.None);
        for (int i = 0; i < split.Length; i++)
            numbers[i] = Convert.ToDouble(split[i]);
        string[] split1 = buff.Split(new char[] { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', ','});
        for (int i = 0; i < split1.Length; i++)
        {
            if (split1[i] == "")
            {
                split1 = deleteElem1(split1, i);
                i--;
            }
        }
        for (int i = 0; i < split1.Length; i++)
            symbols[i] = split1[i];
    }

    public static void operations()
    {
       for (int i=0; i<symbols.Length; i++)
       {
            if (symbols[i] == "*-")
            {
                numbers[i + 1] = -1 * numbers[i + 1];
                numbers[i] = numbers[i] * numbers[i + 1];
                numbers = deleteElem(numbers, i + 1);
                symbols = deleteElem1(symbols, i);
                i--;
                continue;
            }
            if (symbols[i] == "/-")
            {
                numbers[i + 1] = -1 * numbers[i + 1];
                numbers[i] = numbers[i] / numbers[i + 1];
                numbers = deleteElem(numbers, i + 1);
                symbols = deleteElem1(symbols, i);
                i--;
                continue;
            }
            if (symbols[i] == "*")
            {
                numbers[i] = numbers[i] * numbers[i + 1];
                numbers = deleteElem(numbers, i+1);
                symbols = deleteElem1(symbols, i);
                i--;
                continue;
            }
            if (symbols[i] == "/")
            {
                if (numbers[i + 1] == 0)
                    throw new DivideByZeroException("Cannot divide by zero");
                numbers[i] = numbers[i] / numbers[i + 1];
                numbers = deleteElem(numbers, i+1);
                symbols = deleteElem1(symbols, i);
                i--;
                continue;
            }
            if (symbols[i] == "-")
            {
                numbers[i+1] = -1*numbers[i+1];
            }
       }
    }
    
    public static double getAnswer()
    {
        double sum = 0;
        foreach (double i in numbers)
            sum += i;
        return sum;
    }

    public static double[] deleteElem(double[] mass, int n)
    {
        var tmp = new List<double>(mass);
        tmp.RemoveAt(n); 
        return tmp.ToArray();
    }

    public static string[] deleteElem1(string[] mass, int n)
    {
        var tmp = new List<string>(mass);
        tmp.RemoveAt(n);
        return tmp.ToArray();
    }

    public static double main()
    {
        getSymbols(Read.getString());
        operations();
        return getAnswer();
    }
}

namespace LabaSharp5
{
    class Program
    {
        static void Main(string[] args)
        {

            Read.mainWithExceptions();
        }
    }
}
