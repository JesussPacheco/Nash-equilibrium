#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>
#include<tuple>
using namespace std;
bool EliminationFilasPuras(vector<vector<pair<pair<int, int>, pair<int, int>>>>&a) {
	bool flag = true;
	for (int i = 0; i < a.size(); i++) { 

		for (int p = 0; p < a.size(); p++) {  //p=i;
			 flag = true;
			for (int j = 0; j < a[i].size(); j++) {
				if (a[i][j].first.first <= a[p][j].first.first) {
					flag = false;
					break;
				}
			}
			if (flag) {//si es que i dominda a ´p
				a.erase(a.begin() + p);
				return true;
			}
		}
	}
	return false;;
	
}
bool EliminationColumnasPuras(vector<vector<pair<pair<int, int>, pair<int, int>>>>&a) {
	bool flag = true;
	int ulti;
	for (int j = 0; j < a[0].size(); j++) {

		for (int p = 0; p < a[0].size(); p++) {  //p=i;
			 flag = true;
			for (int i = 0; i < a.size(); i++) {
				if (a[i][j].first.second<= a[i][p].first.second) {
					flag = false;
					break;
				} 
				 ulti = i;
			}
			if (flag) {//si es que i dominda a ´p
				for (int i = 0; i < a.size(); i++) {
					a[i].erase(a[i].begin() + p);
				}
				return true;
			}
		}
	}
	return false;
}
bool auxMixtas(vector <pair<int, int>>&div) {
	double prime;
	double second;
	
	while (true){
		prime = 0.5;
	    second = 0.5;
		bool flag = true;
		for (int z = 0; z < div.size()-1; z++) {
			if ((double)div[z].first*prime + (double)div[z+1].first*second<div[z].second) {
				return false;
			}
			if ((double)div[z].first*prime + (double)div[z].second*second == div[z].second) {
				prime += 0.1;
				second -= 0.1;
				break;
			}
			if (prime == 0.9) {
				flag = false;
				break;
			}
			z++;
		}
		if(flag)
		return true;
		else break;
}
	while (true) {
		prime = 0.5;
		second = 0.5;
		bool flag = true;
		for (int z = 0; z < div.size() - 1; z++) {
			if ((double)div[z].first*prime + (double)div[z+1].second*second<div[z].second) {
				return false;
			}
			if ((double)div[z].first*prime + (double)div[z+1].second*second == div[z].second) {
				prime -= 0.1;
				second += 0.1;
				break;
			}
			if (second == 0.9) {
				flag = false;
				break;
			}
		}
		if (flag)
			return true;
		else return false;
	}
}
bool EliminationColumnasMixtas(vector<vector<pair<pair<int, int>, pair<int, int>>>>&a) {
	if (a[0].size() < 3)return false;
	vector<int>dont;
	for (int i = 0; i < a.size(); i++) {//recorre columnas
		int not= -1;
		int nn;
		for (int j = 0; j < a[0].size(); j++) {//recorre filas
			int aux = not;
			not= max(a[i][j].first.second, not);
			if (not!= aux) {
				nn = j;
			}
		}
		dont.emplace_back(nn);
	}
	sort(dont.begin(), dont.end());
	for (int i = 0;i< a[0].size(); i++) {//determina al candidato a irse;
		int candit = a[0][i].second.second;
		if (!binary_search(dont.begin(), dont.end(), candit)) {
			bool capture = true;
			vector <pair<int, int>>div;
			for (int j = 0; j < a.size(); j++) {
				for (int k = 0; k < a[0].size(); k++) {
					if (k != candit) {
						div.push_back({ a[j][k].first.second, a[j][candit].first.second});
					}
				}
			}
			bool termi = auxMixtas(div);
			if (termi) {
				for (int i = 0; i < a.size(); i++) {
					a[i].erase(a[i].begin() + candit);
				}
				return true;
			}
			
		}
	}
	return false;
}
////////////////FILAS MIXTAS
bool EliminationFilasMixtas(vector<vector<pair<pair<int, int>, pair<int, int>>>>&a) {
	if (a.size() < 3)return false;
	vector<int>dont;
	for (int i = 0; i < a[0].size(); i++) {//recorre columnas
		int not= -1;
		int nn;
		for (int j = 0; j < a.size(); j++) {//recorre filas
			int aux = not;
			not= max(a[j][i].first.first, not);
			if (not!= aux) {
				nn = j;
			}
		}
		dont.emplace_back(nn);
	}
	sort(dont.begin(), dont.end());
	for (int i = 0; i< a.size(); i++) {//determina al candidato a irse;
		int candit = a[i][0].second.first;
		if (!binary_search(dont.begin(), dont.end(), candit)) {
			bool capture = true;
			vector <pair<int, int>>div;
			for (int j = 0; j < a[0].size(); j++) {
				for (int k = 0; k < a[j].size(); k++) {
					if (k != candit) {
						div.push_back({ a[k][j].first.first, a[candit][j].first.first });
					}
				}
			}
			bool termi = auxMixtas(div);
			if (termi) {
				a.erase(a.begin() + candit);
			}

		}
	}
	return false;
}



void Mostrar(vector<vector<pair<pair<int, int>, pair<int, int>>>>&a) {
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j< a[i].size(); j++) {
			cout << a[i][j].first.first << "," << a[i][j].first.second << " ";
		}
		cout << endl;
	}
	cout <<"\n";

}
int main() {
	int  n, m;
	cin >> n >> m;
	vector<vector<pair<pair<int,int>,pair<int ,int>>>>a(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int x, y;
			cin >> x >> y;
			a[i].push_back({ {x,y},{i,j} });
		}
	 }
	cout << "\n";
	Mostrar(a);
	cout << endl;
	bool an, bn, cn, dn;
	while (true) {
		an = EliminationColumnasPuras(a);
		if (an)Mostrar(a);
		 bn = EliminationFilasPuras(a);
		if (bn)Mostrar(a);
		cn = EliminationColumnasMixtas(a);
		if (cn) {
			Mostrar(a);
			an = EliminationColumnasPuras(a);
			if (an)Mostrar(a);
			bn = EliminationFilasPuras(a);
			if (bn)Mostrar(a);
		}
	 dn = EliminationFilasMixtas(a);
	 if (dn) {
		 Mostrar(a);
		 an = EliminationColumnasPuras(a);
		 if (an)Mostrar(a);
		 bn = EliminationFilasPuras(a);
		 if (bn)Mostrar(a);
	 }
		if (an == false && bn == false && cn == false && dn == false)break;
}

	cout << endl;
	return 0;
}
