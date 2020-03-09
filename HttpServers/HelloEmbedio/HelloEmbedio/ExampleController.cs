using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using EmbedIO;
using EmbedIO.Routing;
using EmbedIO.WebApi;

namespace HelloEmbedio
{
    public sealed class ExampleController : WebApiController
    {
        [Route(HttpVerbs.Get, "/hello")]
        public async Task<HelloMessage> SayHello([FormData] NameValueCollection data)
        {
            return await Task.FromResult(new HelloMessage());
        }
    }


    public class HelloMessage
    {
        public string Text => "Hello. I am your server";
    }


}
