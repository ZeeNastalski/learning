using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Nancy;
using Nancy.Conventions;
using Nancy.Hosting.Self;

namespace NancySelfHosted
{

    public class ApplicationBootstrapper : DefaultNancyBootstrapper
    {
        protected override void ConfigureConventions(NancyConventions nancyConventions)
        {
            nancyConventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("static", @"d:/tmp/html"));
            base.ConfigureConventions(nancyConventions);
        }
    }

    public class MainModule : NancyModule
    {
        public MainModule()
        {
            Get("/",  args => { return "Hello World"; });
        }
    }


    class Program
    {

        static void Main(string[] args)
        {
            HostConfiguration config = new HostConfiguration();
            config.UrlReservations.CreateAutomatically = true;
            string uri = "http://localhost:8666";

            var host = new NancyHost(config, new Uri(uri));
            
            host.Start();
            Console.WriteLine($"Running on {uri}");
            Console.ReadLine();
            host.Stop();
        }
    }
}
