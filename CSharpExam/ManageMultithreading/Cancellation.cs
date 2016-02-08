using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Threading;

namespace ManageMultithreading
{
    [TestClass]
    public class Cancellation
    {

        [TestMethod]
        public void CancelingTask()
        {
            CancellationTokenSource cancelationTokenSource = new CancellationTokenSource();
            CancellationToken token = cancelationTokenSource.Token;

            Task task = Task.Run(() => {

                while (!token.IsCancellationRequested)
                {
                    Console.Write("*");
                    Thread.Sleep(500);
                }

                //token.ThrowIfCancellationRequested();
                throw new OperationCanceledException();

            }, token).ContinueWith( (t) =>
            {

                //t.Exception.Handle((e) => { Console.WriteLine(e.Message); return true; });
                Console.WriteLine("Continuation");
                 
            }, TaskContinuationOptions.OnlyOnCanceled);



            try
            {
                Thread.Sleep(3000);
                cancelationTokenSource.Cancel();

                task.Wait();
            }
            catch (AggregateException e)
            {
                Console.WriteLine("Handling aggr exception " + e.InnerExceptions[0].Message);
            }
        }

    }
}
