using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TD1_v2.Models.Coord
{
    class cEuler
    {
        public double phi { get; set; }
        public double teta { get; set; }
        public double alpha { get; set; }

        public cEuler() { }

        public cEuler(double p, double t, double a)
        {
            this.phi = p;
            this.teta = t;
            this.alpha = a;
        }

        public void view()
        {
            Console.WriteLine("phi = %d, teta = %d, alpha = %d", phi, teta, alpha);
        }

    }
}
