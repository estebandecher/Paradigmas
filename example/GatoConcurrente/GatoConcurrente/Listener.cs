using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GatoConcurrente
{
    class Listener
    {

       public void accion(Metronomo m, EventArgs e)
        {
            Console.WriteLine("escuche un tick de "+ m.Name);
        }


        public void suscribe(Metronomo m)
        {
            m += new Metronomo.tickHandler(accion);

        }


        public void unSuscribe(Metronomo m)
        {
            m -= accion;

        }

    }
}
