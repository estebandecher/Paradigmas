using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GatoConcurrente
{
    class Program
    {

        public class MetronomoEventArg : EventArgs
        {

        }




        public delegate void tickHander(Metronomo m, MetronomoEventArg e);

        static void Main(string[] args)
        {

            Listener l1 = new Listener();
            Metronomo m1 = new Metronomo();

            l1.suscribe(m1);

            m1.Start();



        }




    }
}
