using System;

namespace TD1_v2
{
	public class Matrice44 : Matrice43
	{
		public Vecteur l4 { get; set;}

		public Matrice44 ()
		{
		}

		public Matrice44 (Vecteur l1, Vecteur l2, Vecteur l3, Vecteur l4) : base (l1,l2,l3) {
			this.l4 = l4;
		}

		public new Matrice44 transpose(){
			Matrice44 res = new Matrice44();
			Vecteur resL1 = new Vecteur(base.l1.x, base.l2.x, base.l3.x,this.l4.x); //Création des valeurs transposées à chaque ligne de la matrice
			Vecteur resL2 = new Vecteur(base.l1.y, base.l2.y, base.l3.y,this.l4.y);
			Vecteur resL3 = new Vecteur(base.l1.z, base.l2.z, base.l3.z,this.l4.z);
			Vecteur resL4 = new Vecteur(base.l1.w, base.l2.w, base.l3.w,this.l4.w);
			res.l1 = resL1;
			res.l2 = resL2;
			res.l3 = resL3;
			res.l4 = resL4;
			return res;
		}

        public void translate()
        {
            Matrice44 m = new Matrice44();
            m
        }

	}
}

