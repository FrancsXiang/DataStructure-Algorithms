#include <iostream>
#include <stack>
#include <vector>
#define MAXN 100000
#define INF 0xfffffff
using namespace std;

typedef pair<int,int> PII;

typedef struct edgenode {
	int id;
	int cost;
	edgenode(int _v,int _cost):id(_v),cost(_cost) {}
}E;

int cnt;
int degree[MAXN];
int ev[MAXN];
int lv[MAXN]; 
stack<int> st,tmp;

int main()
{
	// vertex num begins with zero(start-0,end-n-1)
	int m,n,start,end,cost,cur,id;
	cin >> n >> m;
	vector<PII> res;
	vector<vector<E>> v(n);
	for(int i=0;i<m;i++) {
		cin >> start >> end >> cost;
		v[start].push_back(E(end,cost));
		degree[end]++;
	}
	st.push(0);
	while(!st.empty()) {
		cur = st.top();
		st.pop();
		tmp.push(cur);
		for(int i=0;i<v[cur].size();i++) {
			id = v[cur][i].id;
			cost = v[cur][i].cost;
			if(ev[id] < ev[cur] + cost) ev[id] = ev[cur] + cost;
			if(--degree[id] == 0) st.push(id),cnt++;
		}
	}
	for(int i=0;i<n;i++) ev[i] = INF;
	if(cnt == n - 1) {	
		lv[n-1] = ev[n-1];
		while(!tmp.empty()) {
			cur = tmp.top();
			tmp.pop();
			for(int i=0;i<v[cur].size();i++) {
				id = v[cur][i].id;
				cost = v[cur][i].cost;
				if(ev[cur] > ev[id] - cost) ev[cur] = ev[id] - cost;
			}
		}
		for(int i=0;i<n;i++) {
			for(int j=0;j<v[i].size();j++) {
				id = v[i][j].id;
				cost = v[i][j].cost;
				if(lv[i] == ev[id] - cost) res.push_back({i,id});
			}
		}
	}else 
		cout << "There exists a circle round!" << endl;
	return 0;	
}
