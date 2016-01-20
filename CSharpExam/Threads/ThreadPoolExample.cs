using System;
using System.Threading;

namespace Threads
{
    class ThreadPoolExample
    {
        public static void Run()
        {
            for (int i = 0; i < 3; i++)
            {
                ThreadPool.QueueUserWorkItem(ThreadProc);
            }


            Console.WriteLine("Main Thread doing something. Thread id: {0}", Thread.CurrentThread.ManagedThreadId);
            Thread.Sleep(1000);

            //how do I join the threads?
            Console.ReadKey();
            
        }


        public static void ThreadProc(Object state)
        {            
            Console.WriteLine("Hello from thread. Thread id: {0}",
                 Thread.CurrentThread.ManagedThreadId);
        }
    }
}
