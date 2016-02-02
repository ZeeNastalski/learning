using System;
using System.Collections.Concurrent;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Threads
{
    class BlockingCollectionExample
    {
        public static void Run()
        {
            int size = 10;
            BlockingCollection<int> col = new BlockingCollection<int>(size/3);

            Task read = Task.Run(() => 
            {
                while(true)
                {
                    if (col.Count == 0 && col.IsAddingCompleted)
                    {
                        break;
                    }

                    Console.WriteLine(col.Take() + " " + col.Count);                      
                }
            });


            Task write = Task.Run(() => 
            {
                foreach(int i in Enumerable.Range(1, size))
                {
                    Console.WriteLine("adding " + i);
                    col.Add(i);
                }

                col.CompleteAdding();
            });

            write.Wait();
            read.Wait();
        }
    }
}
