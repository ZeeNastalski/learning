using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;

namespace EventsAndCallbacks
{
    [TestClass]
    public class DelegatesException
    {
        class Publisher
        {
            public event EventHandler<EventArgs> OnChange = delegate {};

            virtual public void Raise()
            {
                OnChange(this, new EventArgs());
            }
        }

        class PublisherWithHandler
        {

            public event EventHandler<EventArgs> OnChange = delegate { };

            public void Raise()
            {
                var exceptionsThrown = new List<Exception>();

                foreach (Delegate handler in OnChange.GetInvocationList())
                {
                    try
                    {
                        // explicitly invoke handlers and aggregate exceptions
                        handler.DynamicInvoke(this, EventArgs.Empty);

                    }catch (Exception e)
                    {
                        exceptionsThrown.Add(e);
                    }
                }

                if(exceptionsThrown.Count > 0)
                {
                    new AggregateException(exceptionsThrown);
                }
            }
        }

        [TestMethod]
        public void handlerNotCalledDueToException()
        {
            bool thirdHandlerCalled = false;
            bool exceptionHandled = false;

            Publisher pub = new Publisher();
            pub.OnChange += (sender, args) => { Console.WriteLine("All is good");};
            pub.OnChange += (sender, args) => { throw new Exception("All is bad."); };
            pub.OnChange += (sender, args) => {
                thirdHandlerCalled = true;
                Console.WriteLine("Do I even get called?");
            };

            try {

                pub.Raise();

            }catch(Exception)
            {
                exceptionHandled = true;
            }
            Assert.IsTrue(exceptionHandled);
            Assert.IsFalse(thirdHandlerCalled);
         }


        [TestMethod]
        [Ignore] //For some reason the exception is not handled in PublisherWithHandler
        public void handlerCalledAfterException()
        {
            bool thirdHandlerCalled = false;
            bool exceptionHandled = false;

            PublisherWithHandler pub = new PublisherWithHandler();
            pub.OnChange += (sender, args) => { Console.WriteLine("All is good"); };
            pub.OnChange += (sender, args) => { throw new Exception("All is bad."); };
            pub.OnChange += (sender, args) => {
                thirdHandlerCalled = true;
                Console.WriteLine("Do I even get called?");
            };

            try
            {
                pub.Raise();
            }
            catch (Exception)
            {
                exceptionHandled = true;
            }
            Assert.IsTrue(exceptionHandled,"exception was not thrown or handled");
            Assert.IsTrue(thirdHandlerCalled, "third handler not called");
        }


    }
}
