using System.Threading;

namespace Threads
{
    class StartingThread
    {
        static bool stop = false;

        public static void ThreadMethod(object o)
        {
            int number = (int)o;

            while(!stop)
            {
                System.Console.WriteLine("Thread printing " + number);
                Thread.Sleep(0);
            }
                
        }


        public static void Run(string[] args)
        {
            // ThreadStart is a wrapper on the thread method
            // hread t = new Thread(new ThreadStart(ThreadMethod));

            // ParameterizedThreadStart allows for a start method to have one arg of type object

            Thread t = new Thread(new ParameterizedThreadStart(ThreadMethod));
            
            //t.IsBackground = true;
            t.Start(10);

            System.Console.ReadKey();
            stop = true;
            t.Join();

        }

    }
}
