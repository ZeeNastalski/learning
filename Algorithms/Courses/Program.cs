using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Courses
{
    class Program
    {
        public static List<string> getDirectFriendsForUser(string user) { return new List<string> { "A", "B", "C" }; }
        public static List<string> getAttendedCoursesForUser(string user) {

            if (user == "A") { return new List<string> { "1", "2" }; }
            if (user == "B") { return new List<string> { "3", "2" }; }
            if (user == "C") { return new List<string> { "3", "4" }; }

            return new List<string>();
        }



        public static void visitStudent(ref HashSet<string> visitedFriends, 
            ref Dictionary<string, int> courseOccurances, 
            string student, int level, int maxLevel)
        {

            visitedFriends.Add(student);

            foreach(string course in getAttendedCoursesForUser(student))
            {
                if(courseOccurances.ContainsKey(course))
                {
                    courseOccurances[course]++;
                }
                else
                {
                    courseOccurances[course] = 1;
                }
            }


            if (level <= maxLevel)
            {
                foreach (string friend in getDirectFriendsForUser(student))
                {
                    //recursive call to visit 2nd level connections
                    if (!visitedFriends.Contains(friend))
                    {
                        visitStudent(ref visitedFriends, ref courseOccurances, friend, level + 1, maxLevel);
                    }
                }
            }
        }


        public static List<string> getRankedCourses(string user)
        {
            List<string> courses = new List<string>();

            HashSet<string> visitedFriends = new HashSet<string>();
            visitedFriends.Add(user);

            Dictionary<string, int> courseOccurances = new Dictionary<string, int>();

            //iterate over direct connections
            foreach(string friend in getDirectFriendsForUser(user))
            {
                if (!visitedFriends.Contains(friend))
                {
                    visitStudent(ref visitedFriends, ref courseOccurances, friend, 1, 2);
                }
            }

            //sort courses by occurance
            List<KeyValuePair<string, int>> courseOccuranceList = courseOccurances.ToList();

            courseOccuranceList.Sort((a, b) =>
            {
                return b.Value.CompareTo(a.Value);
            });

            //filter courses
            HashSet<string> myCourses = new HashSet<string>(getAttendedCoursesForUser(user));
            foreach(var kvp in courseOccuranceList)
            {
                if(!myCourses.Contains(kvp.Key))
                {
                    courses.Add(kvp.Key);
                }            
            }

            return courses;

        }
        static void Main(string[] args)
        {
            List<string> courses = getRankedCourses("A");

        }
    }
}
