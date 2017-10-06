using System;

namespace TD1_v2
{
	public class Vecteur
	{
		public double x { get; set;}
		public double y { get; set;}
		public double z { get; set;}
		public double w { get; set; }

        public Vecteur(){}

		public Vecteur (double a, double b, double c, double d)
		{
			this.x = a;
			this.y = b;
			this.z = c;
			this.w = d;
        }

		public virtual void view(){
			Console.WriteLine(this.x + " " + this.y + " " + this.z + " " + this.w);
		}

		public virtual void setVector(Vecteur v){
			this.x = v.x;
			this.y = v.y;
			this.z = v.z;
            this.w = v.w;
		}

		public virtual bool egal(Vecteur v){
			return (this.x == v.x && this.y == v.y && this.z == v.z && this.w == v.w);
		}	

		public virtual void negate() {
			this.x = - this.x;
			this.y = - this.y;
			this.z = - this.z;
		}

		public double length(){
			return (Math.Sqrt(this.x * this.x + this.y * this.y + this.z * this.z));
		}

		public void multiplyK(double k){
			this.x = k * x;
			this.y = k * y;
			this.z = k * z;
		}

		public void divideK(double k){
			this.x = x / k;
			this.y = y / k;
			this.z = z / k;
		}

		public virtual Vecteur getNormalisation () {
			Vecteur res = new Vecteur();
			res.x = this.x / this.length ();
			res.y = this.y / this.length ();
			res.z = this.z / this.length ();
			return res;
		}

		public virtual void add(Vecteur v) {
			this.x += v.x;
			this.y += v.y;
			this.z += v.z;
		}

		public virtual void minus(Vecteur v) {
			this.x -= v.x;
			this.y -= v.y;
			this.z -= v.z;
		}

		public virtual double distance(Vecteur v) {
			Vecteur res = this;
			res.minus (v);
			return res.length ();
		}

		public virtual bool sup(Vecteur v){
			return this.length() > v.length();
		}

		public virtual double getScalarAlgebr(Vecteur v) {
			return (this.x * v.x + this.y * v.y + this.z * v.z);
		}

		public virtual double getScalarGeoAngle(Vecteur v, double angle){
			return (this.length() * v.length() * Math.Cos(angle));
		}

		public virtual double getAngleScalar(Vecteur v){
			return Math.Acos(this.getScalarAlgebr(v) 
				/ (this.length() * v.length())
			);
		}




	



	}
}

