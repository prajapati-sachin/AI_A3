#include<bits/stdc++.h>
#include<fstream>
using namespace std;

int n,m,k;
ifstream fin;
ofstream fout;

int main(int argc, char const *argv[]){
	if(argc < 2){
		cout<<"Input File Error\n";
		return 0;
	}
	string inputFile = argv[1];						inputFile +=".satoutput";
	string inputFile1 = argv[1];					inputFile1 += ".graph";
	string ouputFile = argv[1];						ouputFile += ".subgraphs";

	fin = ifstream(inputFile1);
	fin >> n >> m >> k;
	vector< vector<int> > subgraph;
	vector<int> empty;
	for(int i=0;i<=k;i++)
		subgraph.push_back(empty);

	fin.close();

	fin = ifstream(inputFile);
	fout = ofstream(ouputFile);

	string sat;

	fin >> sat;
	if(sat != "SAT"){
		fout << "0\n";
		goto ending;
	}

	int curr, sign;
	
	while(1){
		fin >> curr;
		if(curr == 0) break;

		sign = (curr > 0) ? 1 : -1;
		curr = abs(curr);
		if(curr > n*k || sign == -1) continue;

		curr--;
		int j = (curr%k) + 1;
		int i = curr/k + 1;

		subgraph[j].push_back(i);
	}

	for(int i=1;i<=k;i++){
		fout << "#" << i << ' ' << subgraph[i].size() << '\n';
		for(auto z : subgraph[i])
			fout << z << ' ';
		fout << '\n';
	}

	ending:
	fin.close();
	fout.close();
	return 0;
}