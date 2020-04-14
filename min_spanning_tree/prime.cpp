#include <cstdio>
#include <cstring>
#include <iostream>
#define MAXN 502
#define INF 65537
using namespace std;

int t,n;
int cost[MAXN];
int map[MAXN][MAXN];
bool vis[MAXN];

int prime(int cur) {
	int sum = 0;
	int min_len;
	int min_index;
	vis[cur] = true;
	for(int i=0;i<n;i++) cost[i] = map[cur][i];
	for(int i=0;i<n-1;i++) {
		min_index = -1;
		min_len = INF;
		for(int i=0;i<n;i++) {
			if(!vis[i]&&cost[i]<min_len) {
				min_len = cost[i];
				min_index = i;
			}
		}
		vis[min_index] = true;
		sum += min_len;
		for(int i=0;i<n;i++) if(!vis[i]&&(map[min_index][i]<cost[i])) cost[i] = map[min_index][i];
	}
	return sum;
}

int main()
{
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		for(int i=0;i<n;i++) cost[i] = INF;
		memset(vis,false,n*sizeof(bool));
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++) {
				scanf("%d",&map[i][j]);
			}
		}
		printf("%d\n",prime(0));
	}
	return 0;
}
