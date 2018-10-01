#include<bits/stdc++.h>
#include<fstream>
using namespace std;

int n,m,k;
int curr_var_no = 0;
vector< vector<bool> > adj;
vector< vector<int> > adj_list;

ifstream fin;
ofstream fout;

void take_input(){
	fin >> n >> m >> k;

	vector<bool> row(n+1,0);
	vector<int> empty;
	for(int i=0;i<=n;i++) adj.push_back(row), adj_list.push_back(empty);

	for(int i=0;i<m;i++){
		int u,v;
		fin >> u >> v;
		adj[u][v] = 1;
		adj[v][u] = 1;
		adj_list[u].push_back(v);
		adj_list[v].push_back(u);
	}
}
// Total number of variables = n*k + m*k + n*k*k
// Total number of clauses = n + (nC2-m)*k + (m+3mk) + (k*k + 3*n*k*k)
void init(){
	int no_var = n*k + m*k + n*k*(k-1);
	int no_clauses = n + (n*(n-1)*k)/2 - m*k + m + 3*m*k + k*(k-1) + 3*n*k*(k-1);
	fout << "p cnf " << no_var << ' ' << no_clauses <<'\n';
}

void vertex_fn(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=k;j++){
			int no = (i-1)*k + j;
			fout << no << ' ';
		}
		fout<<"0\n";
	}
}

inline int vertex_var_no(int i, int j){
	return (i-1)*k + j;
}

inline bool random_proc(){
	int a = rand() % 100;
	if(a < 5) return true;
	return false;
}

void subgraph_fn(){
	for(int i=1;i<=k;i++){
		for(int j=i+1;j<=k;j++){
			if(i == j) continue;
			string clause1, clause2;
			int curr_var_no_tmp = curr_var_no;
			for(int p=1;p<=n;p++){
				clause1 += to_string(++curr_var_no_tmp);
				clause1 += ' ';
				clause2 += to_string(++curr_var_no_tmp);
				clause2 += ' ';
			}
			fout << clause1 << "0\n";
			fout << clause2 << "0\n";

			for(int p=1;p<=n;p++){
				
				// clause += to_string(++curr_var_no);
				// clause += ' ';
				++curr_var_no;
				
				int pi = vertex_var_no(p,i);
				int pj = vertex_var_no(p,j);

				fout << -curr_var_no << ' ' <<  pi << " 0\n";
				fout << -curr_var_no << ' ' << -pj << " 0\n";
				if(random_proc())
				fout <<  curr_var_no << ' ' << -pi << ' ' << pj << " 0\n";

				++curr_var_no;

				pi = vertex_var_no(p,j);
				pj = vertex_var_no(p,i);

				fout << -curr_var_no << ' ' <<  pi << " 0\n";
				fout << -curr_var_no << ' ' << -pj << " 0\n";
				if(random_proc())
				fout <<  curr_var_no << ' ' << -pi << ' ' << pj << " 0\n";
			}
		}
	}
}

void add_edge_clause(int i, int j){
	string clause;
	vector<string> cl;
	int curr_var_no_tmp = curr_var_no;
	for(int l=1;l<=k;l++){
		clause += to_string(++curr_var_no_tmp);
		clause += ' ';
	}
	fout << clause << "0\n";
	for(int l=1;l<=k;l++){
		++curr_var_no;

		int il = vertex_var_no(i,l);
		int jl = vertex_var_no(j,l);
		
		fout << -curr_var_no << ' ' << il << " 0\n";
		fout << -curr_var_no << ' ' << jl << " 0\n";
		if(random_proc())
		fout << curr_var_no << ' ' << -il << ' ' << -jl << " 0\n";

	}
}


void add_no_edge_clause(int i, int j){
	for(int l=1;l<=k;l++){
		int il = vertex_var_no(i,l);
		int jl = vertex_var_no(j,l);
		fout << -il << ' ' << -jl <<" 0\n";
	}
}

void edge_fn(){
	
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){

			if(adj[i][j]) add_edge_clause(i,j);
			else add_no_edge_clause(i,j);
		}
	}
}
int total = 0;

void lets_do_it(){
	vector<int> deg(n+1,0);
	vector<bool> vis(n+1,0);
	vector<bool> vis_local(n+1,0);
	set< pair<int,int> > se;
	for(int i=1;i<=n;i++){
		deg[i] = adj_list[i].size();
		se.insert({deg[i], i});
	}
	int subgraph_index = 0;

	while(!se.empty()){
		if(subgraph_index==k){
			break;
		}

		auto z = *se.begin();
		se.erase(se.begin());
		int curr_vertex = z.second;

		if(vis[curr_vertex] == 1) continue;
		subgraph_index++;
		vis[curr_vertex] = 1;

		fout << vertex_var_no(curr_vertex, subgraph_index) << " 0\n";
		total++;

		for(int i=1;i<=n;i++) vis_local[i] = 0;
		vis_local[curr_vertex] = 1;
		for(auto y : adj_list[curr_vertex]){
			vis[y] = 1;
			vis_local[y] = 1;
		}

		for(int i=1;i<=n;i++){
			if(vis_local[i]) continue;
			fout << -vertex_var_no(i, subgraph_index) << " 0\n";
			total++;
		}
	}
}

int main(int argc, char const *argv[]){
	if(argc < 2){
		cout<<"Input File Error\n";
		return 0;
	}
	srand(time(NULL));
	string inputFile = argv[1];
	inputFile += ".graph";
	string ouputFile = argv[1];
	ouputFile += ".satinput"; 

	fin = ifstream(inputFile);
	fout = ofstream(ouputFile);

	take_input();
	init();

	curr_var_no += n*k;

	lets_do_it();
	vertex_fn();
	subgraph_fn();
	edge_fn();

	cout << total << endl;

	fin.close();
	fout.close();
	return 0;
}