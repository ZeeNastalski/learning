using System;
using System.Collections.Generic;
using System.Reflection;
using System.Text;

namespace ConsoleApp1
{
    public abstract class ZLEvent
    {       
        public string Version => Assembly.GetEntryAssembly().GetName().Version.ToString();

    }
}
