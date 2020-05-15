#include <bits/stdc++.h>
using namespace std;

struct DNA {
	string str;
	long measure = 0;

	void calMeasure();
};
void DNA::calMeasure()
{
	for (int i = 0; i < this->str.length(); i++) {
		for (int j = i; j < this->str.length(); j++) {
			if (this->str.at(i) > this->str.at(j))
				this->measure++;
		}
	}
}
int main() {

	int n, m;
	cin >> n >> m;
	DNA * dna = new DNA[m];
	DNA dnaTemp;
	for (int i = 0; i < m; i++) {
		cin >> dna[i].str;
		dna[i].calMeasure();
	}
	
	for (int i = 0; i < m - 1; i++) {
		for (int j = 0; j < m -i - 1; j++) {
			if (dna[j].measure > dna[j + 1].measure) {
				dnaTemp = dna[j];
				dna[j] = dna[j + 1];
				dna[j + 1] = dnaTemp;
			}
		}
	}
	for (int i = 0; i < m; i++) {
		cout << dna[i].str << endl;
	}
	//system("pause");
	return 0;
}