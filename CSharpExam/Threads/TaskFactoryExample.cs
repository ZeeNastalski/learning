using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Threads
{
    class TaskFactoryExample
    {
        public static void Run()
        {
            Console.WriteLine("Main thread id: " + System.Threading.Thread.CurrentThread.ManagedThreadId);
            Task<Int32[]> parent = Task.Run(() =>
            {
                var result = new Int32[3];

                TaskFactory tf = new TaskFactory(TaskCreationOptions.AttachedToParent,
                    TaskContinuationOptions.ExecuteSynchronously);

                tf.StartNew(() =>
                {
                    result[0] = 0;
                    Console.WriteLine("Child task id: " + System.Threading.Thread.CurrentThread.ManagedThreadId);
                });
                tf.StartNew(() =>
                {
                    result[1] = 1;
                    Console.WriteLine("Child task id: " + System.Threading.Thread.CurrentThread.ManagedThreadId);
                });
                tf.StartNew(() =>
                {
                    result[2] = 2;
                    Console.WriteLine("Child task id: " + System.Threading.Thread.CurrentThread.ManagedThreadId);
                });

                return result;

            });

            Task finalTask = parent.ContinueWith((parentTask) =>
            {
                Console.WriteLine("Continuation " + System.Threading.Thread.CurrentThread.ManagedThreadId);
                foreach(int i in parentTask.Result)
                {
                    Console.WriteLine(i);
                }
            });


        }
    }
}
