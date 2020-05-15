#include <bits/stdc++.h>
using namespace std;

struct DNA {
	string str;
	long measure = 0;

};


int main() {
	int n;
	char ch = '0';
	cin >> n;

	string * str = new string[n];
	ch = cin.get();
	for (int i = 0; i < n; i++) {
		while (ch = cin.get()) {
			switch (ch)
			{
			case '0':
				str[i].append(1, '0');
				break;
			case '1':
				str[i].append(1, '1');
				break;
			case '2':
			case 'A':
			case 'B':
			case 'C':
				str[i].append(1, '2');
				break;
			case '3':
			case 'D':
			case 'E':
			case 'F':
				str[i].append(1, '3');
				break;
			case '4':
			case 'G':
			case 'H':
			case 'I':
				str[i].append(1, '4');
				break;
			case '5':
			case 'J':
			case 'K':
			case 'L':
				str[i].append(1, '5');
				break;
			case '6':
			case 'M':
			case 'N':
			case 'O':
				str[i].append(1, '6');
				break;
			case '7':
			case 'P':
			case 'R':
			case 'S':
				str[i].append(1, '7');
				break;
			case '8':
			case 'T':
			case 'U':
			case 'V':
				str[i].append(1, '8');
				break;
			case '9':
			case 'W':
			case 'X':
			case 'Y':
				str[i].append(1, '9');
				break;
			default:
				break;
			}
			if (ch == '\n') break;
			if (str[i].length() == 3) {
				str[i].append(1, '-');
			}
		}
	}

	
	DNA * dna = new DNA[n];
	DNA dnaTemp;
	for (int i = 0; i < n; i++) {
		dna[i].str = str[i];
	}

	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (dna[j].str > dna[j + 1].str) {
				dnaTemp = dna[j];
				dna[j] = dna[j + 1];
				dna[j + 1] = dnaTemp;
			}
		}
	}
	int jumpFlag = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (dna[i].str == dna[j].str) {
				dna[i].measure++;
				dna[j].measure = -100000;
				jumpFlag++;
			}
			else break;
		}
		i += jumpFlag;
		jumpFlag = 0;
	}

	for (int i = 0; i < n; i++) {
		if (dna[i].measure > 0) {
			cout << dna[i].str << " " << dna[i].measure + 1 << endl;
		}
	}
	//system("pause");
	return 0;
}