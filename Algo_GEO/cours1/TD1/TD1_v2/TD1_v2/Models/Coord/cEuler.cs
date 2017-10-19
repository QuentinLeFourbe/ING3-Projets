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

        public cEuler getInterpolationPhi(cEuler angle, double t)
        {
            if (t > 1 || t < 0)
            {
                throw new ArgumentException("t doit être compris entre 0 et 1");
            }

            var res = this;
            res.phi += t * (angle.phi - res.phi);
            return res;
        }

        public cEuler getInterpolationTeta(cEuler angle, double t)
        {
            if (t > 1 || t < 0)
            {
                throw new ArgumentException("t doit être compris entre 0 et 1");
            }
            var res = this;
            res.teta += t * (angle.teta - res.teta);
            return res;
        }

        public cEuler getInterpolationAlpha(cEuler angle, double t)
        {
            if (t > 1 || t < 0)
            {
                throw new ArgumentException("t doit être compris entre 0 et 1");
            }
            var res = this;
            res.alpha += t * (angle.alpha - res.alpha);
            return res;
        }

    }
}
