using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;


namespace GatoConcurrente
{
    public class Metronomo
    {
        public String Name;

        public EventArgs e=null;
        public delegate void tickHandler(Metronomo m, EventArgs e);
        // creamos el evento public event tickHandler tick;
        public event tickHandler tick;
        public void Start()
        {
            Thread.Sleep(1000);
            if (tick == null)
            {
                tick(this, e);
            }
        }
        


}
