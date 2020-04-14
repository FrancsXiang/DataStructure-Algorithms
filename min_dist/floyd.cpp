#include <iostream>
#define MAXN 502
using namespace std;

int map[MAXN][MAXN];

int main()
{
	int n;
	cin >> n;
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cin >> map[i][j];//self2self == zero not INF
		}
	}
	for(int k=0;k<n;k++) {
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++) {
				map[i][j] = min(map[i][j],map[i][k]+map[k][j]);
			}
		}
	}
	return 0;
}
