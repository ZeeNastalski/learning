using System.Threading;

namespace Threads
{
    class Program
    {

        public static void ThreadMethod()
        {
            for(int i = 0; i<10; i++)
            {
                System.Console.WriteLine("Thread " + i);
                Thread.Sleep(0);
            }
                
        }


        static void Main(string[] args)
        {
            Thread t = new Thread(new ThreadStart(ThreadMethod));
            t.Start();

            for(int i=0; i<10; i++)
            {
                System.Console.WriteLine("Main thread " + i);
                Thread.Sleep(0);
            }
        }

    }
}
