using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CodilityPermMissingElem
{

    class Solution
    {
        public int solution(int[] A)
        {            
            ulong sum = ((uint)A.Length + 1) * ((uint)A.Length + 2) / 2;

            foreach (int x in A) { sum = sum - (uint)x; }

            return (int)sum;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Solution s = new Solution();
            s.solution(new int[] { 1, 2, 3, 5 });
        }
    }
}
