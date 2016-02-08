using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Threads
{
    class TaskWithContinuation
    {
        private static int TaskMethod()
        {
          
            throw new Exception("Piss off");

            #pragma warning disable 0162
            return 42;
        }

        public static void Run()
        {


            //Task<int> t = Task.Run(() => TaskMethod()  );
            Task<int> t = new Task<int>(() => TaskMethod() );
            t.Start();


            /*
            try {
                // Even if continuation is added after the task 
                // finishes execution, the continuation executes correctly.
                Console.WriteLine(t.Result);
            }catch(AggregateException e)
            {
                Console.WriteLine("Accessing result first throws exception.");
            }
            */


            t.ContinueWith((task) => {

                Console.WriteLine("OK");

            }, TaskContinuationOptions.OnlyOnRanToCompletion);



            Task contTask = t.ContinueWith((task) => {
               
                Console.WriteLine("ERROR");
                throw new Exception("Continuation says piss off too");

            }, TaskContinuationOptions.OnlyOnFaulted);





            try {

                Console.WriteLine(t.Result);

            }catch(AggregateException e)
            {
                Console.WriteLine("First task threw exception: " + e.InnerExceptions[0].Message);
            }



            try {
                contTask.Wait();
            }catch(AggregateException e)
            {
                Console.WriteLine("Continuation threw exception: " + e.InnerExceptions[0].Message);
                
            }
        }

    }
}
