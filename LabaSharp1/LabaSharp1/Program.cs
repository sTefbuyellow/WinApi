using System;

namespace LabaSharp1
{
    abstract class musicalInstrument
    {
        public string sound;

        public string getSound(){
            return sound;
        }

        public void setSound(string sound1)
        {
            sound=sound1;
        }
    }

    class StringedInstruments : musicalInstrument
    {
        public int numberOfStrings;
        public bool needABow;

        public StringedInstruments(string sound1, int number, bool bow) {
            setSound(sound1);
            numberOfStrings = number;
            needABow = bow;
        }
        public StringedInstruments(string sound1)
        {
            setSound(sound1);
        }
        public StringedInstruments(int number)
        {
            numberOfStrings = number;
        }
        public StringedInstruments(bool bow)
        {
            needABow = bow;
        }
        public StringedInstruments(){}

        public int getNumber()
        {
            return numberOfStrings;
        }
        public bool getBow()
        {
            return needABow;
        }
    }

    class AcousticGuitar : StringedInstruments{

        public AcousticGuitar()
        {
            setSound("bryin");
            numberOfStrings = 6;
            needABow = false;
        }
        public AcousticGuitar(string sound1) : base(sound1) {}
       
    }

    class ClassicGuitar : StringedInstruments {
        public ClassicGuitar(StringedInstruments instrument) {
            sound = instrument.sound;
            numberOfStrings = instrument.numberOfStrings;
            needABow = instrument.needABow;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            AcousticGuitar guitar1 = new AcousticGuitar("bruin");
            Console.WriteLine(guitar1.getSound());
            AcousticGuitar guitar2 = new AcousticGuitar();
            Console.WriteLine(guitar2.getSound());
            ClassicGuitar guitar3 = new ClassicGuitar(guitar2);
            Console.WriteLine(guitar3.getSound());
        }
    }
}
