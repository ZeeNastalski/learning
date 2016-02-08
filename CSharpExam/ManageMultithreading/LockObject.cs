using System;

using System.Threading.Tasks;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace ManageMultithreading
{
    [TestClass]
    public class LockObject
    {



        [TestMethod]
        public void NoLocking()
        {
            int n = 0;

            Task up = Task.Run(() => {
                for (int i = 0; i < 1000000; i++) n++;
            });

            for (int i = 0; i < 1000000; i++) n--;

            up.Wait();

            Console.WriteLine(n);
            Assert.AreNotEqual(0, n);
        }




        [TestMethod]
        public void LocObject()
        {
            int n = 0;
            object _lock = new object();

            Task up = Task.Run(() => {
                for (int i = 0; i < 1000000; i++)
                {
                    lock (_lock)
                    {
                        n++;
                    }
                }
            });

            for (int i = 0; i < 1000000; i++)
            {
                lock (_lock)
                {
                    n--;
                }
            }

            up.Wait();

            Console.WriteLine(n);
            Assert.AreEqual(0, n);
        }



  

    }
}
