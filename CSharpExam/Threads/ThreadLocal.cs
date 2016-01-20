using System;
using System.Threading;

namespace Threads
{
    class ThreadLocalExample
    {

        public static ThreadLocal<int> _field =
            new ThreadLocal<int>(() =>
            {
                return Thread.CurrentThread.ManagedThreadId;
            });
            


        public static void Run(string[] args)
        {

            new Thread(() =>
            {
                for (int x = 0; x < _field.Value; x++)
                {
                    Console.WriteLine("Thread A({0}): {1}", _field.Value, x);
                }

            }).Start();



            new Thread(() =>
            {
                for (int x = 0; x < _field.Value; x++)
                {
                    Console.WriteLine("Thread B({0}): {1}", _field.Value, x);
                }

            }).Start();


            Console.ReadKey();



        }
    }
}
