using System;
using System.IO;
using System.Collections.Generic;


/*
* https://www.codeeval.com/open_challenges/119/
*/

public class Graph
{
    private Dictionary<string, List<string>> adjacency = new Dictionary<string, List<string>>();

    public void AddEdge(string from, string to)
    {
        if(!adjacency.ContainsKey(from))
        {
            adjacency.Add(from, new List<string>());
        }

        if(!adjacency.ContainsKey(to))
        {
            adjacency.Add(to, new List<string>());
        }

        adjacency[from].Add(to);
    }

    public List<string> Adjacent(string from)
    {
        return adjacency[from];
    }

}

class Program
{

    public static string TestChain(string chain)
    {
        Graph graph = new Graph();
        Dictionary<string, bool> visitedNodes = new Dictionary<string, bool>();

        try {
        
            // Construction
            string[] edges = chain.Split(';');
            foreach (string edge in edges)
            {
                string from = edge.Split('-')[0];
                string to = edge.Split('-')[1];

                visitedNodes[from] = false;
                visitedNodes[to] = false;

                graph.AddEdge(from, to);
            }


            // Traversal
            string nodeFrom = "BEGIN";

            while(nodeFrom != "END")
            {
                visitedNodes[nodeFrom] = true;
                List<string> adj = graph.Adjacent(nodeFrom);

                // Fork or detected
                if (adj.Count != 1) { return "BAD"; }

                string nodeTo = adj[0];

                if(visitedNodes.ContainsKey(nodeTo) && visitedNodes[nodeTo] == true)
                {
                    // loop detected
                    return "BAD";
                }

                nodeFrom = nodeTo;
            }

            visitedNodes["END"] = true;


            // Checking
            foreach(bool visited in visitedNodes.Values)
            {
                // not visited node detected
                if (!visited) return "BAD";
            }

            

        }catch(Exception)
        {
            //just in case
            return "BAD";                    
        }


        return "GOOD";

    }


    static void Main(string[] args)
    {
  
        using (StreamReader reader = File.OpenText(args[0]))
        {
            while(!reader.EndOfStream)
            {
                string line = reader.ReadLine();
                Console.WriteLine(TestChain(line));
            }
        }
        
    }

}