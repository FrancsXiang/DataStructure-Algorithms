#include <iostream>
#include <queue>
#define N 10000
#define INF 0xffffff
using namespace std;
typedef pair<int,int> PII;

struct cmp {
	bool operator() (const PII &a,const PII &b) { //first为顶点号,second为到此点最短距离
		return a.second > b.second;
	}
};

priority_queue<PII,vector<PII>,cmp> que;

void bestFirstSearch(int cur,int n,vector<vector<PII>>& edge, int* dist) {
	for(int i=0;i<n;i++) dist[i] = INF;
	dist[cur] = 0;
	que.push({cur,0});
	while(!que.empty()) {
		auto item = que.top();
		que.pop();
		int start = item.first;
		int end,val; 
		for(int i=0;i<edge[start].size();i++) {
			end = edge[start][i].first;
			val = edge[start][i].second;
			if(val + dist[start] < dist[end]) que.push({end,dist[end] = val + dist[start]});
		}
	}
}


int main()
{
	int start,end,val,cur,n,m;
	cout << "input the number of vertexes and edges respectively:" << endl;
	cin >> n >> m;
	int dist[n];
	vector<vector<PII>> edge(n);//first为顶点号,second为边权
	cout << "input the edge(start,end,val):" << endl;
	for(int i=0;i<m;i++) {
		cin >> start >> end >> val;
		edge[start].push_back({end,val});
		edge[end].push_back({start,val});
	} 
	cout << "input the start vertex:" << endl;
	cin >> cur;
	bestFirstSearch(cur,n,edge,dist);
	cout << "Start from vertex: " << cur << endl;
	for(int i=0;i<n;i++) cout << "dist " << i << " :" << dist[i] << endl; 
	return 0;
}

