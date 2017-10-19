using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TD1_v2.Models.Coord
{
    class cQuaternion
    {
        public double w { get; set; }
        public Vecteur3 v { get; set; }

        public cQuaternion() { }

        public cQuaternion(double teta, Vecteur3 n)
        {
            this.w = Math.Cos(teta / 2.0);

            n.multiplyK(Math.Sin(teta / 2.0));
            this.v = n;
        }

        public cQuaternion(double w, double x, double y, double z)
        {
            this.w = w;
            this.v = new Vecteur3(x, y, z);
        }

        public void view()
        {
            Console.WriteLine("[ %d (%d, %d, %d) ]", this.w, this.v.x, this.v.y, this.v.z);
        }

        public cQuaternion negate()
        {
            var vRes = this.v;
            vRes.negate();
            var res = new cQuaternion(-this.w, vRes);
            return res;
        }

        public double getMagnetude()
        {
            var res = w * w + v.length() * v.length();
            return Math.Sqrt(res);
        }

        public cQuaternion getConjugue()
        {
            var tmp = this.v;
            tmp.negate();
            return new cQuaternion(w, tmp);
        }

        public cQuaternion getInverse()
        {
            var magnetude = this.getMagnetude();
            var res = new cQuaternion(this.w / magnetude
                                        , this.v.x / magnetude
                                        , this.v.y / magnetude
                                        , this.v.z / magnetude);
            return res;
        }

        public cQuaternion add( cQuaternion quat)
        {
            var res = this;
            res.v.add(quat.v);
            res.w = res.w + quat.w;
            return res;
        }

        public cQuaternion minus(cQuaternion quat)
        {
            var res = this;
            res.v.minus(quat.v);
            res.w = res.w - quat.w;
            return res;
        }

        public cQuaternion getMultiply(cQuaternion quat)
        {
            var res = this;
            res.w =   quat.w * res.w -   quat.v.x * res.v.x - quat.v.y * res.v.y - quat.v.z * res.v.z;
            res.v.x = quat.w * res.v.x + quat.v.x * res.w -   quat.v.y * res.v.z + quat.v.z * res.v.y;
            res.v.y = quat.w * res.v.y + quat.v.x * res.v.z + quat.v.y * res.w -   quat.v.z * res.v.x;
            res.v.z = quat.w * res.v.z - quat.v.x * res.v.y + quat.v.y * res.v.x + quat.v.z * res.w;
            return res;
        }

        public cQuaternion getDifference(cQuaternion quat)
        {
            var tmp = this.getInverse();
            var res = quat.getMultiply(tmp);
            return res;
        }

        public double getProduitScalaire(cQuaternion quat)
        {
            return (this.w * quat.w 
                    + this.v.x * quat.v.x 
                    + this.v.y * quat.v.y 
                    + this.v.z * quat.v.z);
        }

        public cQuaternion getLogarithme()
        {
            var res = this;
            var alpha = Math.Acos(this.w); //w = cos a => a = cos^-1 w
            res.w = 0;
            res.v.multiplyK(alpha); 
            return res;
        }

        public cQuaternion getExponentielle()
        {
            var res = this;
            var alpha = Math.Acos(w); //w = cos a => a = cos^-1 w
            res.w = Math.Cos(alpha);
            res.v.multiplyK(Math.Sin(alpha));
            return res;
        }

        public cQuaternion getExponentiation(double t)
        {
            var res = this.getLogarithme();
            res.w = res.w * t;
            res.v.multiplyK(t);
            res = res.getExponentielle();
            return res;
        }









    }
}
