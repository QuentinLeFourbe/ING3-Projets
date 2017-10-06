using NUnit.Framework;
using System;
using TD1_v2;

namespace Tests_Project
{
	[TestFixture ()]
	public class Matrice3Test
	{
		[Test ()]
		public void TestMultIdent ()
		{
			Vecteur3 l1 = new Vecteur3 (1, 2, 3);
			Vecteur3 l2 = new Vecteur3 (1, 3, 1);
			Vecteur3 l3 = new Vecteur3 (2, 3, 2);
			Matrice3 m = new Matrice3 (l1, l2, l3);
			Matrice3 i = new Matrice3 ();
			i.setIdentite ();
			
		}
	}
}

