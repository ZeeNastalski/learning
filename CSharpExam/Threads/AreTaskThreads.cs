using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Threads
{
    class AreTaskThreads
    {
        public static void Run()
        {
            for(int i=0; i<100; i++)
            {
                //Task t = Task.Run(() => Thread.Sleep(10000));
                new System.Threading.Thread(() => Thread.Sleep(10000)).Start();

                //the answer is no
            }

            Thread.Sleep(1000);
            Console.WriteLine("main thread finished sleeping");
        }
    }
}
