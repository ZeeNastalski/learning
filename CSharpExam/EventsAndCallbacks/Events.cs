using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace EventsAndCallbacks
{
    [TestClass]
    public class Events
    {
        class ActionPublisher
        {
            public Action OnChange { get; set; }

            public void Raise()
            {
                if(OnChange != null)
                {
                    OnChange();
                }
            }
        }


       
        class ActionEventPublisher
        {
            public event Action OnChange = delegate { };

            public void Raise()
            {                
                OnChange();                
            }
        }


        public class MyArgs : EventArgs
        {
            public string Value { get; set; }

            public MyArgs(string val) : base()
            {
                Value = val;
            }
        }

        class EventPublisher
        {
            public event EventHandler<MyArgs> OnChange = delegate { };

            public void Raise()
            {
                OnChange(this, new MyArgs("some args"));
            }
        }

        [TestMethod]
        public void ActionEvent()
        {
            bool actionOneCalled = false;
            bool actionTwoCalled = false;
            ActionPublisher p = new ActionPublisher();
            p.OnChange += () => { actionOneCalled = true; };
            p.OnChange += () => { actionTwoCalled = true; };

            p.Raise();

            Assert.IsTrue(actionOneCalled);
            Assert.IsTrue(actionTwoCalled);
        }


        [TestMethod]
        public void EventEvent()
        {
            bool actionOneCalled = false;
            bool actionTwoCalled = false;
            ActionEventPublisher p = new ActionEventPublisher();
            p.OnChange += () => { actionOneCalled = true; };
            p.OnChange += () => { actionTwoCalled = true; };

            p.Raise();

            Assert.IsTrue(actionOneCalled);
            Assert.IsTrue(actionTwoCalled);
        }

        public void handleEvent(Object sender, MyArgs args)
        {
            Console.WriteLine("Handler fired");
        }


        [TestMethod]
        public void EventHandler()
        {
            bool actionCalled = false;
            EventPublisher p = new EventPublisher();

            p.OnChange += (sender, args) =>
            {
                actionCalled = true;
            };

            p.OnChange += handleEvent;
            p.Raise();

            Assert.IsTrue(actionCalled);
        }




    }
}
