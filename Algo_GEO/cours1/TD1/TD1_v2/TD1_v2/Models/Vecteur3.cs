using System;

namespace TD1_v2
{
	public class Vecteur3 : Vecteur	{

		public Vecteur3 ()
		{
            this.w = 1;
		}

		public Vecteur3(double x, double y, double z) : base  (x, y, z, 1){
		}

		public override void view(){
			Console.WriteLine(base.x + " " + base.y + " " + base.z + " " + this.w);
		}



				


	}
}

