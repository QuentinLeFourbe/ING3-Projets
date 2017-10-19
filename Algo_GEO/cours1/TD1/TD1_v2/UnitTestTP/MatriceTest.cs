using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using TD1_v2;

namespace UnitTestTP
{
    [TestClass]
    public class MatriceTest
    {
        [TestMethod]
        public void egal_egalite()
        {
            var v1 = new Vecteur3(2, 3, 4);
            var v2 = new Vecteur3(2, 1, 4);
            var v3 = new Vecteur3(4, 3, 4);
            var m1 = new Matrice(v1, v2, v3);
            var m2 = new Matrice(v1, v2, v3);
            Assert.IsTrue(m1.egal(m2));
        }

        [TestMethod]
        public void egal_inegalite()
        {
            var v1 = new Vecteur3(2, 3, 4);
            var v2 = new Vecteur3(2, 1, 4);
            var v3 = new Vecteur3(4, 3, 4);
            var m1 = new Matrice(v1, v2, v3);
            var m2 = new Matrice(v3, v2, v3);
            Assert.IsFalse(m1.egal(m2));
        }

        [TestMethod]
        public void add()
        {
            var v1 = new Vecteur3(2, 3, 4);
            var v2 = new Vecteur3(2, 1, 4);
            var v3 = new Vecteur3(4, 3, 4);
            var m1 = new Matrice(v1, v2, v3);
            var m2 = new Matrice(v3, v2, v3);

            var mExpect = new Matrice(6,6,8,4,2,8,8,6,8);
            m1.add(m2);
            Assert.IsTrue(mExpect.egal(m1));
        }



    }
}
