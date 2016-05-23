using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CodilityBinaryGap
{

    class Solution
    {
        public int solution(int N)
        {

            bool inTheGap = false;
            int currentGapSize = 0;
            int maxGapSize = 0;
            while (N > 0)
            {
                if (N % 2 == 1)
                {
                    if(inTheGap)
                    {
                        if (currentGapSize > maxGapSize) maxGapSize = currentGapSize;
                        currentGapSize = 0;                        
                    }
                    else
                    {
                        inTheGap = true;
                        currentGapSize = 0;
                    }
                    
                }
                else
                {
                    if (inTheGap)
                    {
                        currentGapSize++;
                    }
                }

                N = N / 2;
            }

            return maxGapSize;
        }
    }




    class Program
    {
        static void Main(string[] args)
        {
            Solution s = new Solution();
            System.Diagnostics.Debug.Assert(s.solution(1041)==5);
            System.Diagnostics.Debug.Assert(s.solution(20) == 1);
            System.Diagnostics.Debug.Assert(s.solution(9) == 2);
            System.Diagnostics.Debug.Assert(s.solution(0) == 0);
            System.Diagnostics.Debug.Assert(s.solution(2147483647) == 0);
            
        }
    }


}
