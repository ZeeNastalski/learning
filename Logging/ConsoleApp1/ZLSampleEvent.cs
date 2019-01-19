using System;
using System.Collections.Generic;
using System.Dynamic;
using System.Text;

namespace ConsoleApp1
{
    public class ZLSampleEvent : ZLEvent
    {
        public string PlayerName { get; set; }

        public int PlayerScore  { get; set; }

        public double[] DoubleArray { get; set; }

        public ZLSubObject Subobject { get; set; }
    }
}
