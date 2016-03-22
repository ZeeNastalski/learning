using System;
using System.Runtime.ExceptionServices;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Exceptions
{
    [TestClass]
    public class Exception
    {
        [TestMethod]
        [ExpectedException(typeof(FormatException))]
        public void ExceptionDispatchInfoExample()
        {
            ExceptionDispatchInfo possibleException = null;

            try
            {
                string s = "aaa";
                int.Parse(s);
            }
            catch (FormatException ex)
            {
                possibleException = ExceptionDispatchInfo.Capture(ex);
            }

            if (possibleException != null)
            {
                possibleException.Throw();
            }
            
        }
    }
}
