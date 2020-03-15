using System;
using System.Collections.Generic;
using System.IO;
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
        public class ZLPathProvider : IRootPathProvider
        {
            public string GetRootPath()
            {
                return Path.GetFullPath(@"c:\Games");
            }
        }

        ZLPathProvider pathProvider = new ZLPathProvider();
        protected override IRootPathProvider RootPathProvider
        {
            get
            {
                return pathProvider;
            }
        }

        protected override void ConfigureConventions(NancyConventions nancyConventions)
        {
            
            nancyConventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("", @"/../games"));
            nancyConventions.StaticContentsConventions.Add(StaticContentConventionBuilder.AddDirectory("games", @"/../zerolatency/launcher/games"));
            base.ConfigureConventions(nancyConventions);
        }
    }

    public class MainModule : NancyModule
    {
        public MainModule()
        {
            Get("/hello", args =>
            {
                return "Hello World";
            });
        }
    }


    class Program
    {
        static void Main(string[] args)
        {
            HostConfiguration config = new HostConfiguration();
            config.UrlReservations.CreateAutomatically = true;
            config.AllowChunkedEncoding = false;
            string uri = "http://localhost:8666";
            string uri2 = "http://localhost:8667";

            var host = new NancyHost(config, new Uri(uri));
            var host2 = new NancyHost(config, new Uri(uri2));

            host.Start();
            host2.Start();

            Console.WriteLine($"Running on {uri}");
            Console.ReadLine();

            host.Stop();
            host2.Stop();
        }
    }
}
