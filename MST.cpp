
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator> 

using namespace std;

const int N = 1000;
int n, m;
vector <pair <int, pair <int, int>>> g;
vector <pair <int, int>> MST;
int parent[N];

int min_e[N];
int sel_e[N]; 
vector <pair<int, int> > V[N]; 
const int INF = 2 * 1000 * 1000 * 1000 + 5; 
bool used[N];

int root(int a){ 
	if (parent[a] == a)
		return a;
	parent[a] = root(parent[a]);
	return root(parent[a]);
}

void SetParents(int a, int b){ 
	parent[root(a)] = root(b);
}

void Kruskal(){
	sort(g.begin(), g.end());
	MST.clear();
	for (int i = 0; i<n; i++)
		parent[i] = i;
	for (int i = 0; i<m; i++){
		int f = g[i].second.first;
		int t = g[i].second.second;
		if (root(f) != root(t)){
			MST.push_back(g[i].second);
			SetParents(f, t);
		}
	}
}

bool Prim(){
	fill_n(min_e, n, INF);
	fill_n(sel_e, n, -1); 
	fill_n(used, n, false); 
	min_e[0] = 0;
	for (int i = 0; i<n; i++) {
		int v = -1;
		for (int j = 0; j<n; j++)
			if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
				v = j;

		if (min_e[v] == INF)
			return false;

		used[v] = true;
		if (sel_e[v] != -1)
			MST.push_back(make_pair(sel_e[v], v));

		for (int j = 0; j<(int)V[v].size(); j++)
			if (V[v][j].second < min_e[V[v][j].first]) {
				min_e[V[v][j].first] = V[v][j].second;
				sel_e[V[v][j].first] = v;
			}
	}
	return true;
}

int main() {
	int flag;
	cout << "Method? \n 1: Prim \n 2: Kruskal \n";
	cin >> flag;
	cout << "Number Of Vertexes?" << endl;
	cin >> n;
	cout << "NUmber of Edges?" << endl;
	cin >> m;
	if (flag == 2)
	{
		g.clear();
		cout << "For Each Edge Give First & Second Vertexes & Edge's Weight In Order: " << endl;
		for (int i = 0; i < m; i++){
			cout << "Edge " << i << endl;
			int f, t, w;
			cin >> f >> t >> w;
			g.push_back(make_pair(w, make_pair(f, t)));
		}
		Kruskal();

		for (int i = 0; i != MST.size(); i++){
			cout << "Edge:" << MST[i].first << ' ' << MST[i].second << endl;
		}
	}
	if (flag == 1)
	{
		cout << "For Each Edge Give First & Second Vertexes & Edge's Weight In Order: " << endl;
		for (int i = 0; i < m; i++){
			cout << "Edge " << i << endl;
			int a, b, w;
			cin >> a >> b >> w;
			V[a - 1].push_back(make_pair(b - 1, w));
			V[b - 1].push_back(make_pair(a - 1, w));
		}
		if (Prim() == false)
			cout << "No MST!\n";
		else
			for (int i = 0; i != MST.size(); i++){
				cout << "Edge:" << MST[i].first + 1 << ' ' << MST[i].second + 1<< endl;
			}
	}
	system("pause");
}