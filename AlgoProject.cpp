#include<bits/stdc++.h>
#define maxsize 10

using namespace std;

//Graph
bool graph[maxsize][maxsize];

//Returns true if there is a possible subsetof size 'k' that can be a vertex cover.
bool isCover(int V, int k, int E)
{
	//Set has first 'k' bits high initially
	int set = (1 << k) - 1;
	int limit = (1 << V);

	//to mark the edges covered in each subset of size 'k'
	bool vis[maxsize][maxsize];

	while (set < limit)
	{
		//Reset visited array for every subset of vertices as 0.
		memset(vis, 0, sizeof vis);

		//set counter for number of edges covered from this subset of vertices to zero
		int cnt = 0;

		// selected vertex cover is the indices where 'set' has its bit high
		for (int j = 1, v = 1 ; j < limit ; j = j << 1, v++)
		{
			if (set & j)
			{
				// Mark all edges emerging out of this vertex visited
				for (int k = 1 ; k <= V ; k++)
				{
					if (graph[v][k] && !vis[v][k])
					{
						vis[v][k] = 1;
						vis[k][v] = 1;
						cnt++;
					}
				}
			}
		}
        cout<<cnt<<" ";
		// If the current subset covers all the edges
		if (cnt == E)
			return true;

		// Generate previous combination with k bits high set & -set = (1 << last bit high in set)
		int c = set & -set;
		int r = set + c;
		set = (((r^set) >> 2) / c) | r;
	}
	return false;
}

//Returns minimum size of the Vertex Cover Using binary Search
int findMinCover(int n, int m)
{
	int left = 1, right = n;
	while (right > left)
	{
        //mid = (left+right)+1
		int mid = (left + right) >> 1; 
        //if vertex cover does not exist of size mid then left = mid+1, 
        //checking vertex cover for larger mid
		if (isCover(n, mid, m) == false) 
			left = mid + 1;
        //if vertex cover exist of that mid,then righ = mid
        //checking vertex cover for a smaller mid
		else
			right = mid;
	}
    return left;
}

//Adding edges in the bidirected Graph
void addEdge(int u, int v)
{
	graph[u][v] = 1;
	graph[v][u] = 1; 
}


int main()
{
	int V = 6, E = 6;
	addEdge(1, 2);
	addEdge(2, 3);
	addEdge(1, 3);
	addEdge(1, 4);
	addEdge(1, 5);
	addEdge(1, 6);
	cout << endl<<"Minimum size of a vertex cover = "<< findMinCover(V, E) << endl;
	return 0;
}
 