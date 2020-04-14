#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define MAXN 502
#define INF 65537
using namespace std;

typedef struct edge {
	int left,right;
	int weight;
}E;

E edge[m];
int f[MAXN],rec,sum;

bool cmp(const E& a,const E& b) {
	return a.weight < b.weight;
}

int find(int x) {
	if(x!=f[x]) return f[x] = find(f[x]);
	else return x;
}

bool Union(int x,int y) {
	int fx = find(x);
	int fy = find(y);
	if(fx!=fy) {
		f[fx] = fy;
		rec++;
		return true;
	}
	return false;
}

int main()
{
	int m,n,left,right,weight;
	cin >> n >> m;
	for(int i=0;i<m;i++) {
		cin >> left >> right >> weight;
		edge[i].left = left;
		edge[i].right = right;
		edge[i].weight = weight;
	}
	sort(edge,edge+m,cmp);
	for(int i=0;i<m;i++) {
		if(rec < n-1) if(Union(edge[i].left,edge[i].right)) sum += edge[i].weight;
		else break;
	} 
	return 0;
}
