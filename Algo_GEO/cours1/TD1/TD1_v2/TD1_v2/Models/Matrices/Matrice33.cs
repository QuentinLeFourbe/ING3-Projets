using System;

namespace TD1_v2
{
	public class Matrice33 : Matrice
	{

		public Matrice33 ()
		{
		}

		public Matrice33(Vecteur l1, Vecteur l2, Vecteur l3) : base (l1,l2,l3, new Vecteur(0,0,0,1) ) {
		}

		

	}
}

