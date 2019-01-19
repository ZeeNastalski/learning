using System;
using System.Threading;
using Serilog;
using Serilog.Events;
using Serilog.Formatting.Compact;

namespace ConsoleApp1
{
    class Program
    {
        static void Main(string[] args)
        {
            var formatter = new CompactJsonFormatter();
            
            Log.Logger = new LoggerConfiguration()
                //.WriteTo.Console()
                .WriteTo.File(new CompactJsonFormatter(), "myapp.json")
                .CreateLogger();
                

            LogEvent(new ZLSampleEvent()
            {
                PlayerName = "Jack",
                PlayerScore = 666,
                DoubleArray = new[] {0.1, 0.2, 0.3},
                Subobject = new ZLSubObject()
                {
                    IsIncluded = true
                }
            });

            Thread.Sleep(1000);
        }


        public static void LogEvent(ZLEvent myEvent)
        {
            string format = "{@" + myEvent.GetType().Name +"}";
            Log.Logger.Information(format, myEvent);
        }
    }



}
