using System;

namespace TD1_v2
{
	public class Matrice43 : Matrice
	{

		public Matrice43 ()
		{
		}

		public Matrice43(Vecteur3 l1, Vecteur3 l2, Vecteur3 l3, Vecteur3 l4) : base(l1,l2,l3,l4){ }


		public override void view(){
			this.l1.view();
			this.l2.view();
			this.l3.view();
			this.l4.view();
        }

		public void add(Matrice43 m){
			this.l1.add(m.l1);
			this.l2.add(m.l2);
			this.l3.add(m.l3);
		}

		public void minus(Matrice43 m){
			this.l1.minus(m.l1);
			this.l2.minus(m.l2);
			this.l3.minus(m.l3);
		}

		


		//Fonction surement fausse
		public virtual Matrice43 transpose(){

			Matrice43 res = new Matrice43();
			Vecteur resL1 = new Vecteur(this.l1.x, this.l2.x, this.l3.x,this.l1.w); //Création des valeurs transposées à chaque ligne de la matrice
			Vecteur resL2 = new Vecteur(this.l1.y, this.l2.y, this.l3.y,this.l2.w);
			Vecteur resL3 = new Vecteur(this.l1.z, this.l2.z, this.l3.z,this.l3.w);
			res.l1 = resL1;
			res.l2 = resL2;
			res.l3 = resL3;
			return res;
		}
	}
}

