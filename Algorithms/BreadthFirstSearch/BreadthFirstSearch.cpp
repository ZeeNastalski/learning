#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>

using namespace std;


class UndirectedGraph
{
private:
	int V;
	vector<list<int>> adj; //vector of adjacencies (lists)

public:
	UndirectedGraph(int V)
	{
		this->V = V;
		adj = vector<list<int>>(V, list<int>());
	}

	void addEdge(int v, int w)
	{
		adj[v].push_back(w);
		adj[w].push_back(v);
	}

};

int main() {
	
	int T = 0;
	cin >> T;
	
	for (int i = 0; i < T; i++) {
		
		int N = 0;
		int M = 0;
		cin >> N;
		cin >> M;

		UndirectedGraph graph(N);
		for (int j = 0; j < M; j++)
		{
			int a, b;
			cin >> a;
			cin >> b;
			
			// graph supports vertices starting from 0 
			// but the problem statement they start from 1 			
			graph.addEdge(a-1, b-1);
		}

		int start;
		cin >> start;

	}




	return 0;
}