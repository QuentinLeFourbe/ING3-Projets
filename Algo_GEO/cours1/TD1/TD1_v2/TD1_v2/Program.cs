using System;

namespace TD1_v2
{
	class MainClass
	{
		public static void Main (string[] args)
		{
			Console.WriteLine ("Test vecteurs");

            Vecteur3 v1 = new Vecteur3(1, 2, 3);
            Vecteur3 v2 = new Vecteur3(-2, 5, 6);
            Vecteur3 v3 = new Vecteur3(-3, -6, 1);

            Vecteur3 v4 = new Vecteur3(1.0/9.0, 8.0/9.0, (-4.0/9.0));
            Vecteur3 v5 = new Vecteur3(4.0/9.0, -4.0/9.0, -7.0/9.0);
            Vecteur3 v6 = new Vecteur3(8.0/9.0, 1.0/9.0, 4.0/9.0);

            Matrice3 m1 = new Matrice3 (v4, v5, v6);
			Matrice3 m2 = new Matrice3 (v4, v5, v6);

            Console.WriteLine ("Matrice de base :");
			m1.view ();
			m2 = m2.transpose ();
			Console.WriteLine ();
            m2.view();
			Console.WriteLine ();


            Console.WriteLine("Matrice orthogonale : " + m1.isOrthogonale ());

			m1.multiply (m2);
			m1.view ();

		}
	}
}
