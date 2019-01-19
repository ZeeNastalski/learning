using System;
using System.Threading;
using Serilog;
using Serilog.Events;
using Serilog.Formatting.Compact;
using Serilog.Formatting.Json;

namespace ConsoleApp1
{
    class Program
    {
        static void Main(string[] args)
        {
            var formatter = new CompactJsonFormatter();
            
            Log.Logger = new LoggerConfiguration()
                //.WriteTo.Console()
                .WriteTo.File(new CompactJsonFormatter(new JsonValueFormatter(typeTagName: null)), @"c:\ZeroLatency\Logging\myapp.json", fileSizeLimitBytes: 1L*1024, rollOnFileSizeLimit: true, retainedFileCountLimit: 5, rollingInterval: RollingInterval.Day)
                .WriteTo.Console(new CompactJsonFormatter(new JsonValueFormatter(typeTagName: null)))
                .CreateLogger();

            for (int i = 0; i < 10 * 10; i++)
            {
                Thread.Sleep(1100);
                LogEvent(new ZLSampleEvent()
                {
                    PlayerName = "Michael",
                    PlayerScore = 666,
                    DoubleArray = new[] {0.1, 0.2, 0.3},
                    Subobject = new ZLSubObject()
                    {
                        IsIncluded = true
                    }
                });
            }

            Thread.Sleep(1000);
        }


        public static void LogEvent(ZLEvent myEvent)
        {
            string format = "{@" + myEvent.GetType().Name +"}";
            Log.Logger.Information(format, myEvent);
        }


    }



}
