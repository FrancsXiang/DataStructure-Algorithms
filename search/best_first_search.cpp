#include <iostream>
#include <cstring>
#include <queue>
#define N 10000
#define INF 0xffffff
using namespace std;
typedef pair<int,int> PII;

struct cmp {
	bool operator() (const PII &a,const PII &b) { 
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
		vis[start] = true; 
		for(int i=0;i<edge[start].size();i++) {
			end = edge[start][i].first;
			if(vis[end]) continue;
			val = edge[start][i].second;
			if(val + dist[start] < dist[end]) que.push({end,dist[end] = val + dist[start]});
		}
	}
}


int main()
{
	int start,end,val,cur,n,m;
	cin >> n >> m;
	int dist[n];
	bool vis[n];
	memset(vis,false,sizeof(vis));
	vector<vector<PII>> edge(n);
	for(int i=0;i<m;i++) {
		cin >> start >> end >> val;
		edge[start].push_back({end,val});
		edge[end].push_back({start,val});
	} 
	cin >> cur;
	bestFirstSearch(cur,n,edge,dist);
	cout << "Start from vertex: " << cur << endl;
	for(int i=0;i<n;i++) cout << "dist " << i << " :" << dist[i] << endl; 
	return 0;
}

