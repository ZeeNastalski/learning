using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace EventsAndCallbacks
{
    [TestClass]
    public class Delegates
    {
        
        public delegate void Del();
        public delegate int Calculate(int x, int y);

        private string str;


        private void MethodA()
        {
            str += "A";
        }

        private void MethodB()
        {
            str += "B";
        }

        [TestInitialize]
        public void SetUp() { str = ""; }


        [TestMethod]
        [ExpectedException(typeof(NullReferenceException))]
        public void CallingNullDelegate()
        {
            Del d = null;
            d();
        }



        [TestMethod]
        public void MulticastDelegate()
        {
            
            Del d = null;

            d += MethodA;
            d += MethodB;

            Assert.AreEqual(2, d.GetInvocationList().Length);
            d();

            Assert.AreEqual("AB", str);

        }



        [TestMethod]
        public void SubtractingDelegate()
        {

            Del d = null;

            d += MethodA;
            d += MethodB;

            d = d - MethodA;
            d();

            Assert.AreEqual("B", str);

        }

        [TestMethod]
        public void LambdaExpression()
        {
            Calculate calc = (x, y) => x + y;


            Assert.AreEqual(7, calc(3, 4));

            calc = (x, y) => x * y;
            Assert.AreEqual(12, calc(3, 4));
        }

        [TestMethod]
        public void FuncLambda()
        {
            Func<int, int, int> calc = (x, y) => { return x + y; };

            calc += (x, y) => x * y;

            Assert.AreEqual(12, calc(3, 4));

        }

    }
}
