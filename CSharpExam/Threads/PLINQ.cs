using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Threads
{
    class PLINQ
    {
        public static void Run()
        {
            var numbers = Enumerable.Range(0, 20);
            try
            {


                // unordered result, 
                // var parallelResult = numbers.AsParallel().Where(i => i % 2 == 0).ToArray();
                
                // ordered
                var parallelResult = numbers.AsParallel().AsOrdered().Where(i => i % 2 == 0).ToArray();          

                foreach (int i in parallelResult) Console.WriteLine(i);

                

            }catch (AggregateException e)
            {
                Console.WriteLine("There where {0} exceptions",
                                    e.InnerExceptions.Count);
            }
        }
    }
}
