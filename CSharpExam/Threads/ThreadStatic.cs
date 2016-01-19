using System;
using System.Threading;

namespace Threads
{
    class ThreadStatic
    {
        [ThreadStatic]
        private static int countner;

        public static void Run(string[] args)
        {
            new System.Threading.Thread(() =>
               {
                   for(int i=0; i<10; i++)
                   {
                       countner++;
                       Console.WriteLine("Thread A couter=" + countner);                  

                   }
               }).Start();


            new System.Threading.Thread(() =>
            {
                for (int i = 0; i < 10; i++)
                {
                    countner++;
                    Console.WriteLine("Thread B couter=" + countner);

                }
            }).Start();


            Console.ReadKey();
        }
    }
}
