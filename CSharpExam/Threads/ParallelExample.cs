using System;
using System.Threading;
using System.Threading.Tasks;

namespace Threads
{
    class ParallelExample
    {
        public static void Run()
        {

                ParallelLoopResult result = 
                    Parallel.For(0, 10, (int i, ParallelLoopState state) =>
                {
                    if(i==8)
                    {
                        state.Break();
                    }

                    Console.WriteLine("going to sleep " + i);
                    Thread.Sleep(1000);
                    Console.WriteLine("waking up " + i);
                });
        }
    }
}
