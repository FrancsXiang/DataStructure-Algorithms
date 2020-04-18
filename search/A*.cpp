#include <iostream>
#include <set>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#define MAXN 50
#define NOISE 300
using namespace std;
typedef pair<int, int> PII;

int dx[3] = { -1,0,1 };
int dy[3] = { -1,0,1 };
int dist[MAXN][MAXN];

struct node {
	PII point;
	int cost;
	node(PII _point, int _cost) :point(_point), cost(_cost) {}
};

struct cmp {
	bool operator()(const node& a, const node& b) {
		return a.cost > b.cost;
	}
};

set<PII> obstacle, close, seen;
priority_queue<node, vector<node>, cmp> open;
unordered_map<PII, PII> parent;

int cheby_dist(int x1, int y1) {
	return max(abs(x1 - MAXN + 1), abs(y1 - MAXN + 1));
}

bool is_valid(int x, int y) {
	if (x < 0 || x >= MAXN || y < 0 || y >= MAXN || obstacle.count(PII(x, y)) || close.count(PII(x, y))) return false;
	else return true;
}

vector<PII> get_path(PII p) {
	vector<PII> res;
	while (true) {
		res.push_back(p);
		if (parent.count(p)) p = parent[p];
		else break;
	}
	reverse(res.begin(), res.end());
}

int main()
{
	srand(time(0));
	PII start(0, 0), dst(MAXN - 1, MAXN - 1);
	vector<PII> path;
	for (int i = 0; i < NOISE; i++) obstacle.insert(PII(rand() % MAXN, rand() % MAXN));
	dist[0][0] = 0;
	open.push(node(start, dist[0][0] + cheby_dist(0, 0)));
	seen.insert(start);
	while (!open.size()) {
		auto item = open.top();
		auto site = item.point;
		auto last_cost = item.cost;
		if (site == dst) {
			path = get_path(site);
			break;
		}
		open.pop();
		close.insert(site);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				int x = site.first + dx[i];
				int y = site.second + dy[i];
				if (is_valid(x, y)) {
					auto cur_cost = last_cost + 1;
					if (!seen.count(PII(x, y)) || cur_cost < dist[x][y]) {
						parent[PII(x, y)] = site;
						dist[x][y] = cur_cost;
						seen.insert(PII(x, y));
						open.push(node(PII(x, y), cur_cost + cheby_dist(x, y)));
					}
				}
			}
		}
	}
	if (path.size()) for (auto& it : path) cout << "(" << it.first << " " << it.second << " )" << endl;
	else cout << "no possible way existed!";
	return 0;
}
