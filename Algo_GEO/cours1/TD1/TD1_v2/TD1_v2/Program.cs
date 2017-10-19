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



		}
	}
}
