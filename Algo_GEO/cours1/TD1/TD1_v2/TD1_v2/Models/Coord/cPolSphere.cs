using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TD1_v2.Models.Coord
{
    class cPolSphere
    {
        public double r { get; set; }
        public double teta { get; set; }
        public double phi { get; set; }

        public cPolSphere() { }

        public cPolSphere(double r, double t, double f)
        {
            this.r = r;
            this.teta = t;
            this.phi = f;
        }

        public cCartesienne toCartesienne()
        {
            return new cCartesienne(r * Math.Sin(phi) * Math.Cos(teta) //x
                                    , r * Math.Sin(phi) * Math.Sin(teta) //y
                                    , r * Math.Cos(phi)); //z

        }

    }
}
