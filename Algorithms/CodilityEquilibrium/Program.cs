using System;
using System.Diagnostics;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;



namespace CodilityEquilibrium
{



    class Solution
    {
        public int solution(int[] A)
        {           

            if (A.Length == 0) return -1;

            long sum = 0;
            foreach (int a in A) { sum += a; }

            long left = 0;
            long right = sum;

            for (int i = 0; i < A.Length; i++)
            {
                if (i > 0) { left = left + A[i - 1]; }

                right = right - A[i];

                if (right == left) return i;
            }

            return 0;


        }
    }


    public class Program
    {
        static void Main(string[] args)
        {
            Solution s = new Solution();
            

            Debug.Assert( s.solution(new int[] { 1, 2, 3 } ) == 0 );

        }
    }
}
