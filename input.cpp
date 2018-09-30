#include<bits/stdc++.h>
#include<fstream>
using namespace std;

int n,m,k;
int curr_var_no = 0;
vector< vector<bool> > adj;
ifstream fin;
ofstream fout;

void take_input(){
	fin >> n >> m >> k;

	vector<bool> row(n+1,0);
	for(int i=0;i<=n;i++) adj.push_back(row);

	for(int i=0;i<m;i++){
		int u,v;
		fin >> u >> v;
		adj[u][v] = 1;
		adj[v][u] = 1;
	}
}
// Total number of variables = n*k + m*k + n*k*k
// Total number of clauses = n + (nC2-m)*k + (m+3mk) + (k*k + 3*n*k*k)
void init(){
	int no_var = n*k + m*k + n*k*k;
	int no_clauses = n + (n*(n-1)*k)/2 - m*k + m + 3*m*k + k*(k-1) + 3*n*k*(k-1);
	fout << "p cnf " << no_var << ' ' << no_clauses <<'\n';
}

void vertex_fn(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=k;j++){
			int no = (i-1)*k + j;
			curr_var_no++;
			fout << no << ' ';
		}
		fout<<"0\n";
	}
}
inline int vertex_var_no(int i, int j){
	return (i-1)*k + j;
}

void subgraph_fn(){
	for(int i=1;i<=k;i++){
		for(int j=1;j<=k;j++){
			if(i == j) continue;
			string clause;
			for(int p=1;p<=n;p++){
				
				clause += to_string(++curr_var_no);
				clause += ' ';
				
				int pi = vertex_var_no(p,i);
				int pj = vertex_var_no(p,j);

				fout << '-' << curr_var_no << ' ' << pi << "0\n";
				fout << '-' << curr_var_no << ' ' << '-' << pj << "0\n";
				fout << curr_var_no << ' ' << '-' << pi << ' ' << pj << "0\n";
			}
			fout << clause << "0\n";
		}
	}
}

void add_edge_clause(int i, int j){
	string clause;
	for(int l=1;l<=k;l++){
		
		clause += to_string(++curr_var_no);
		clause += ' ';

		int il = vertex_var_no(i,l);
		int jl = vertex_var_no(j,l);
		
		fout << '-' << curr_var_no << ' ' << il << "0\n";
		fout << '-' << curr_var_no << ' ' << jl << "0\n";
		fout <<        curr_var_no << " -" << il << " -" << jl << "0\n";

	}
	fout << clause << "0\n";
}

void add_no_edge_clause(int i, int j){
	for(int l=1;l<=k;l++){
		int il = vertex_var_no(i,l);
		int jl = vertex_var_no(j,l);
		fout << '-' << il << ' ' << '-' << jl <<"0\n";
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

int main(int argc, char const *argv[]){
	if(argc < 2){
		cout<<"Input File Error\n";
		return 0;
	}
	string inputFile = argv[1];
	inputFile += ".graph";
	string ouputFile = argv[1];
	ouputFile += ".satinput"; 

	fin = ifstream(inputFile);
	fout = ofstream(ouputFile);
	cout << "here\n";

	take_input();
	cout << n << ' ' << m << ' ' << k << '\n';
	init();

	vertex_fn();
	cout << curr_var_no << '\n';
	subgraph_fn();
	cout << curr_var_no << '\n';
	edge_fn();
	cout << curr_var_no << '\n';

	fin.close();
	fout.close();
	return 0;
}