using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TD1_v2.Models.Coord
{
    class cCartesienne
    {
        public double x { get; set; }
        public double y { get; set; }
        public double z { get; set; }

        public cCartesienne() { }

        public cCartesienne(double x, double y, double z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }
    }

}
