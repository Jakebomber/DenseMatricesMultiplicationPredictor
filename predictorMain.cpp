#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> matricesDimensionsData;
vector<string> matricesBrackets;
int p = 0,*q;
map<int, map<int, int> > a;

bool cmp(char a, char b) {
	return a > b;
}

void displayResult() {
	cout << endl << matricesBrackets[0];
	for (int i = 1; i < *q; i++) {
		cout << "A" << i << matricesBrackets[i];
	}
	cout << endl;
}

long long int predict(vector<int> mdd, int i_start, int i_end,int status) {
	if (a[i_start][i_end] != 0)return a[i_start][i_end];
	if (i_start == i_end) return 0;
	int p_min = 0;
	long long int min = INT_MAX, temp = 0;
	for (int i = i_start; i < i_end; i++) {
		temp = predict(mdd, i_start, i,1) + predict(mdd, i + 1, i_end,1) + (mdd)[i_start - 1] * (mdd)[i] * (mdd)[i_end];
		if(status==0)cout << temp << endl;
		if (temp < min) {
			min = temp;
			p_min = i;
		}
	}
	matricesBrackets[i_start - 1] += "(";
	matricesBrackets[p_min] += ")(";
	matricesBrackets[i_end] += ")";
	a[i_start][i_end] = min;
	return min;
}

int main() {
	//mtg:matrices group file
	FILE* s1;
	q = new int();
	freopen_s(&s1,"data.mtg", "r", stdin);
	if (s1 == NULL) {
		cout << "文件打开失败！" << endl;
		return 0;
	}
	int n;
	while (cin >> n)matricesDimensionsData.push_back(n), matricesBrackets.push_back("");
	for (auto x : matricesDimensionsData)cout << x << endl;
	cout << predict(matricesDimensionsData, 1, matricesDimensionsData.size() - 1,0);
	*q = matricesDimensionsData.size();

	for (int i = 1; i < matricesBrackets.size(); i++) {
		int ll = 0, rr = 0, l = 0, r = 0;
		for (auto x : matricesBrackets[i - 1]) {
			if (x == '(')ll++;
			else rr++;
		}
		for (auto x : matricesBrackets[i]) {
			if (x == '(')l++;
			else r++;
		}
		if (ll <= r) {
			r -= ll;
			ll = 0;
		}
		else {
			ll -= r;
			r = 0;
		}
		matricesBrackets[i - 1] = "";
		for (int j = 0; j < rr; j++) {
			matricesBrackets[i - 1] += ')';
		}
		for (int j = 0; j < ll; j++) {
			matricesBrackets[i - 1] += '(';
		}
		matricesBrackets[i] = "";
		for (int j = 0; j < r; j++) {
			matricesBrackets[i] += ')';
		}
		for (int j = 0; j < l; j++) {
			matricesBrackets[i] += '(';
		}
		displayResult();
	}

	//for (auto &x : matricesBrackets) {
	//	sort(x.begin(), x.end(),cmp);
	//}

	delete q;
	fclose(s1);
}