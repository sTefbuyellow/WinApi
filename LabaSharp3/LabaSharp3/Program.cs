using System;

namespace LabaSharp3
{
    delegate void Message();
    class Events
    {
        public event Message operations;

        public void OnEvent()
        {
            operations();
        }
    }
    class Money
    {
        public int amountOfMoney;
        public Events events = new Events();

        public void eventsListner()
        {
            Console.WriteLine("Event1");
        }

        public Money()
        {
            amountOfMoney = 0;
            events.operations += eventsListner;

        }

        public void getMoney(int amountOfMoney1)
        {
            amountOfMoney -= amountOfMoney1;
            events.OnEvent();
        }
        public void sendMoney(int amountOfMoney1)
        {
            amountOfMoney += amountOfMoney1;
            events.OnEvent();
        }
    }

    class Mail
    {
        public Events events = new Events();
        public void eventListner()
        {
            Console.WriteLine("Event2");
        }
        public Mail()
        {
            events.operations += eventListner;
        }
        public void gotMessage()
        {
            events.OnEvent();
        }
        public void sendMessage()
        {
            events.OnEvent();
        }

    }
    class Program
    {
        static void Main(string[] args)
        {
            Money money = new Money();
            money.sendMoney(500);
            money.getMoney(30);
            Mail mail = new Mail();
            mail.sendMessage();
            mail.gotMessage();
        }
    }
}
