using System;

namespace TD1_v2
{
	public class Matrice
	{
		public Vecteur l1 { get; set;}
		public Vecteur l2 { get; set;}
		public Vecteur l3 { get; set;}
		public Vecteur l4 { get; set;}

		public Matrice ()
		{
		}

		public Matrice (Vecteur x, Vecteur y, Vecteur z, Vecteur w)
		{
			this.l1 = x;
			this.l2 = y;
			this.l3 = z;
            this.l4 = w;
		}

        public Matrice(Vecteur x, Vecteur y, Vecteur z)
        {
            this.l1 = x;
            this.l2 = y;
            this.l3 = z;
            this.l4 = new Vecteur(0,0,0,1);
        }

        public void setIdentite(){
			this.l1 = new Vecteur(1,0,0,this.l1.w);
			this.l2 = new Vecteur(0,1,0, this.l2.w);
			this.l3 = new Vecteur(0,0,1, this.l3.w);
		}

		public void setIdentite(double x, double y, double z){
			this.l1 = new Vecteur(x,0,0,this.l1.w);
			this.l2 = new Vecteur(0,y,0,this.l2.w);
			this.l3 = new Vecteur(0,0,z,this.l3.w);
		}

		public virtual void view(){
			this.l1.view();
			this.l2.view();
			this.l3.view();
		}

		public bool egal(Matrice m){
			return this.l1.egal(m.l1) && this.l2.egal(m.l2) && this.l3.egal(m.l3);
		}

		public void add(Matrice m){
			this.l1.add(m.l1);
			this.l2.add(m.l2);
			this.l3.add(m.l3);
		}

		public void minus(Matrice m){
			this.l1.minus(m.l1);
			this.l2.minus(m.l2);
			this.l3.minus(m.l3);
		}

		public Vecteur multiplyVect(Vecteur v){
			Vecteur res = new Vecteur();
			res.x = (this.l1.x * v.x + this.l1.y * v.y + this.l1.z * v.z);
			res.y = (this.l2.x * v.x + this.l2.y * v.y + this.l2.z* v.z);
			res.z = (this.l3.x * v.x + this.l3.y * v.y + this.l3.z* v.z);
            res.w = v.w * this.l4.w;
			return res;
		}

		public void divideK(double k){
			this.l1.divideK(k);
			this.l2.divideK(k);
			this.l3.divideK(k);
		}

		public Matrice transpose(){

			Matrice res = new Matrice();
			Vecteur3 resL1 = new Vecteur3(this.l1.x, this.l2.x, this.l3.x); //Création des valeurs transposées à chaque ligne de la matrice
			Vecteur3 resL2 = new Vecteur3(this.l1.y, this.l2.y, this.l3.y);
			Vecteur3 resL3 = new Vecteur3(this.l1.z, this.l2.z, this.l3.z);
			res.l1 = resL1;
			res.l2 = resL2;
			res.l3 = resL3;
			return res;
		}

		public void multiply(Matrice m){
			Vecteur3 l1 = new Vecteur3();
			Vecteur3 l2 = new Vecteur3();
			Vecteur3 l3 = new Vecteur3();

			l1.x = this.l1.x * m.l1.x + this.l1.y * m.l2.x + this.l1.z * m.l3.x;
			l1.y = this.l1.x * m.l1.y + this.l1.y * m.l2.y + this.l1.z * m.l3.y;
			l1.z = this.l1.x * m.l1.z + this.l1.y * m.l2.z + this.l1.z * m.l3.z;

			l2.x = this.l2.x * m.l1.x + this.l2.y * m.l2.x + this.l2.z * m.l3.x;
			l2.y = this.l2.x * m.l1.y + this.l2.y * m.l2.y + this.l2.z * m.l3.y;
			l2.z = this.l2.x * m.l1.z + this.l2.y * m.l2.z + this.l2.z * m.l3.z;

			l3.x = this.l3.x * m.l1.x + this.l3.y * m.l2.x + this.l3.z * m.l3.x;
			l3.y = this.l3.x * m.l1.y + this.l3.y * m.l2.y + this.l3.z * m.l3.y;
			l3.z = this.l3.x * m.l1.z + this.l3.y * m.l2.z + this.l3.z * m.l3.z;

			this.l1 = l1;
			this.l2 = l2;
			this.l3 = l3;
		}

		public void rotateX(double angle){
			//Création matrice de rotation
			Vecteur3 l1 = new Vecteur3 (1, 0, 0);
			Vecteur3 l2 = new Vecteur3 (0, Math.Cos(angle), Math.Sin(angle));
			Vecteur3 l3 = new Vecteur3 (0, - Math.Sin(angle), Math.Cos(angle));
			Matrice rotateMatrice = new Matrice (l1, l2, l3);
			//rotation
			this.multiply (rotateMatrice);
		}

		public void rotateY(double angle){
			//Création matrice de rotation
			Vecteur3 l1 = new Vecteur3 (Math.Cos(angle), 0, - Math.Sin(angle));
			Vecteur3 l2 = new Vecteur3 (0, 1, 0 );
			Vecteur3 l3 = new Vecteur3 (Math.Sin(angle),0 , Math.Cos(angle));
			Matrice rotateMatrice = new Matrice (l1, l2, l3);
			//rotation
			this.multiply (rotateMatrice);
		}

		public void rotateZ(double angle){
			//Création matrice de rotation
			Vecteur3 l1 = new Vecteur3 (Math.Cos(angle), Math.Sin(angle), 0);
			Vecteur3 l2 = new Vecteur3 (- Math.Sin(angle), Math.Cos(angle), 0 );
			Vecteur3 l3 = new Vecteur3 (0, 0, 1);
			Matrice rotateMatrice = new Matrice (l1, l2, l3);
			//rotation
			this.multiply (rotateMatrice);
		}

		public void rotateN(Vecteur3 n,double angle){
			Vecteur3 l1 = new Vecteur3(	n.x*n.x*(1 - Math.Cos(angle)) + Math.Cos(angle), 
										n.x*n.y*(1 - Math.Cos(angle)) + n.z*Math.Sin(angle), 
										n.x*n.z*(1 - Math.Cos(angle)) - n.y*Math.Sin(angle) );
			
			Vecteur3 l2 = new Vecteur3(	n.x*n.y*(1 - Math.Cos(angle)) - n.z * Math.Sin(angle), 
										n.y*n.y*(1 - Math.Cos(angle)) + Math.Cos(angle), 
										n.y*n.z*(1 - Math.Cos(angle)) + n.x*Math.Sin(angle) );
			
			Vecteur3 l3 = new Vecteur3(	n.x*n.z*(1 - Math.Cos(angle)) + n.y*Math.Sin(angle), 
										n.y*n.z*(1 - Math.Cos(angle)) - n.x*Math.Sin(angle), 
										n.z*n.z*(1 - Math.Cos(angle)) + Math.Cos(angle) );
			Matrice m = new Matrice (l1, l2, l3); //Création de la matrice de rotation
			this.multiply (m); //On applique la matrice de rotation
		}

		public void scale(double kx,double ky,double kz)  {
			Matrice m = new Matrice();
			m.setIdentite (kx, ky, kz); //Création matrice de scale

			this.multiply (m); //Application du scale
		}

		public void scaleN(Vecteur3 n, double k) {
			Vecteur3 l1 = new Vecteur3(1 + (k-1) * n.x * n.x,
				(k-1) * n.x * n.y,
				(k-1) * n.x * n.z);
			Vecteur3 l2 = new Vecteur3((k-1) * n.x * n.y,
				1 + (k-1) * n.y * n.y,
				(k-1) * n.y * n.z);
			Vecteur3 l3 = new Vecteur3((k-1) * n.z * n.x,
				(k-1) * n.z * n.y,
				1 + (k-1) * n.z * n.z);
			Matrice m = new Matrice (l1, l2, l3); //Création matrice scale

			this.multiply (m); //Application du scale
		}

		public void projectionXY(){
			Matrice m = new Matrice();
			m.setIdentite (1, 1, 0); //Matrice de projection

			this.multiply (m); //Application de la projection
		}

		public void projectionXZ(){
			Matrice m = new Matrice();
			m.setIdentite (1, 0, 1); //Matrice de projection

			this.multiply (m); //Application de la projection
		}

		public void projectionYZ(){
			Matrice m = new Matrice();
			m.setIdentite (0, 1, 1); //Matrice de projection

			this.multiply (m); //Application de la projection
		}

		public void projectionN(Vecteur3 n){
			Vecteur3 l1 = new Vecteur3( 1 - n.x * n.x, -n.x * n.y, -n.x * n.z);
			Vecteur3 l2 = new Vecteur3( -n.x * n.y, 1 - n.y * n.y, -n.y*n.z);
			Vecteur3 l3 = new Vecteur3(-n.x*n.z, -n.z*n.y, 1-n.z*n.z);
			Matrice m = new Matrice (l1, l2, l3);//Matrice de projection celon n
		
			this.multiply (m); //Application de la projection
		}

		public void reflexion(Vecteur3 n){

			Vecteur3 l1 = new Vecteur3(1 - 2* n.x * n.x, -2*n.x*n.y, -2*n.x*n.z);
			Vecteur3 l2 = new Vecteur3(-2*n.x*n.y, 1-2*n.y*n.y,-2*n.y*n.z);
			Vecteur3 l3 = new Vecteur3(-2*n.x*n.z,-2*n.y*n.z,1-2*n.z*n.z);
			Matrice m = new Matrice (l1, l2, l3); //Création de la matrice de réflexion

			this.multiply (m); //Application de la reflexion
		}

		public void cisailleXY(double s, double t){
			Vecteur3 l1 = new Vecteur3(1,0,0);
			Vecteur3 l2 = new Vecteur3 (0, 1, 0);
			Vecteur3 l3 = new Vecteur3 (s, t, 1);
			Matrice m = new Matrice (l1, l2, l3); //Création matrice de cisaillement

			this.multiply (m); //Application du cisaillement
		}

		public void cisailleXZ(double s, double t){
			Vecteur3 l1 = new Vecteur3(1,0,0);
			Vecteur3 l2 = new Vecteur3 (s, 1, t);
			Vecteur3 l3 = new Vecteur3 (0, 0, 1);
			Matrice m = new Matrice (l1, l2, l3); //Création matrice de cisaillement

			this.multiply (m); //Application du cisaillement
		}

		public void cisailleYZ(double s, double t){
			Vecteur3 l1 = new Vecteur3(1,s,t);
			Vecteur3 l2 = new Vecteur3 (0, 1, 0);
			Vecteur3 l3 = new Vecteur3 (0, 0, 1);
			Matrice m = new Matrice (l1, l2, l3); //Création matrice de cisaillement

			this.multiply (m); //Application du cisaillement
		}

		public double getDeterminant(){
			return this.l1.x * this.l2.y * this.l3.z
			+ this.l1.y * this.l2.z * this.l3.x
			+ this.l1.z * this.l2.x * this.l3.y
			- this.l1.z * this.l2.y * this.l3.x
			- this.l1.y * this.l2.x * this.l3.z
			- this.l1.x * this.l2.z * this.l3.y;
		}

		protected double getCofacteur(int x, int y){
			Vecteur c1 = new Vecteur();
			Vecteur c2 = new Vecteur();

			double[] r1;
			double[] r2;

			switch (x) {
			case 1:
				c1 = this.l2;
				c2 = this.l3;
				break;
			case 2:
				c1 = this.l1;
				c2 = this.l3;
				break;
			case 3:
				c1 = this.l1;
				c2 = this.l2;
				break;
			}

			switch(y){
			case 1:
				r1 = new double[2] { c1.y, c1.z };
				r2 = new double[2] { c2.y, c2.z };
				break;
			case 2:
				r1 = new double[2] { c1.x, c1.z };
				r2 = new double[2] { c2.x, c2.z };
				break;
			case 3:
				r1 = new double[2] { c1.x, c1.y };
				r2 = new double[2] { c2.x, c2.y };
				break;
			default:
				throw new System.ArgumentException ("Les valeurs de x et y doivent être entre 1 et 3");
			}

			return Math.Pow(-1,x+y) *( (r1[0] * r2[1]) - (r1[1] * r2[0]) );

		}

		public Matrice getComatrice(){
			Vecteur3 l1 = new Vecteur3(this.getCofacteur(1,1),this.getCofacteur(1,2),this.getCofacteur(1,3));
			Vecteur3 l2 = new Vecteur3(this.getCofacteur(2,1),this.getCofacteur(2,2),this.getCofacteur(2,3));
			Vecteur3 l3 = new Vecteur3(this.getCofacteur(3,1),this.getCofacteur(3,2),this.getCofacteur(3,3));
			Matrice m = new Matrice (l1, l2, l3);
			return m.transpose ();
		}
			
		public Matrice getInverse(){
			double deter = this.getDeterminant();

			if (deter == 0){
				throw new System.ArgumentException ("Déterminant = 0");
			}
			Matrice m = this.getComatrice();
			m.divideK (deter);
			return m;
		}

		public bool isOrthogonale(){
			Matrice m1 = new Matrice(this.l1,this.l2,this.l3);
			Matrice m2 = new Matrice(this.l1,this.l2,this.l3);
			m2 = m2.transpose ();
			m1.multiply (m2);
			m2.setIdentite ();
			return m1.egal(m2);
		}

	}
}









