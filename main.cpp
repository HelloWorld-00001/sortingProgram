#include <iostream>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int* readFile(ifstream& fread, int& n);
void WriteFile(ofstream& fwrite, int* a, int n);
void flashSort(int* a, int n, long long& comp);
void mergeSort(int* a, int l, int r, long long& comp);
bool checkStringNum(string a);
void cmd1(string mode, string algor, string inputFile, string paramet);
void cmd2(string mode, string algor, string size, string order, string paramet);
void cmd3(string mode, string algor, string size, string paramet);
void cmd4(string mode, string algor1, string algor2, string inputFile);
void cmd5(string mode, string algor1, string algor2, string size, string order);
//ham chay all case
void menuWithoutArgument();
/*	luoi nhap qua viet san lenh :)))
	cmd1 : a.exe -a flash-sort input.txt -both
	cmd2 : a.exe -a flash-sort 30000 -rand -both
	cmd3 : a.exe -a merge-sort 20000 -both
	cmd4 : a.exe -a flash-sort merge-sort input.txt
	cmd5 : a.exe -a merge-sort flash-sort 50000 -nsorted
*/

int main(int argc,char** argv)
{
	if (argc == 6) {
		string s[5];
		for (int i = 1;i <= 5;i++)
			s[i - 1] = (string)argv[i];
		if (checkStringNum(s[2])) 
			cmd2(s[0], s[1], s[2], s[3], s[4]);
		else
			cmd5(s[0], s[1], s[2], s[3], s[4]);
	}
	if (argc == 5) {
		string s[4];
		for (int i = 1;i <= 4;i++)
			s[i - 1] = (string)argv[i];
		if (checkStringNum(s[2])) 
			cmd3(s[0], s[1], s[2], s[3]);
		else {
			if (s[3] == "-both" || s[3] == "-comp" || s[3] == "-time") 
				cmd1(s[0], s[1], s[2], s[3]);
			else
				cmd4(s[0], s[1], s[2], s[3]);
		}
	}
	if (argc != 6 || argc != 5)
		cout << "ERROR INPUT!";

	return 0;
}




int findMax(int* a, int n)
{
	int max = a[0];
	for (int i = 0;i < n;i++)
		if (max < a[i])
			max = a[i];
	return max;
}
int findMin(int* a, int n)
{
	int min = a[0];
	for (int i = 0;i < n;i++)
		if (min > a[i])
			min = a[i];
	return min;
}
void swap(int& a, int& b)
{
	int x = a;
	a = b;
	b = x;
}
void flashSort(int a[], int n,long long& comp)
{
	comp = 0;
	int minVal = a[0];
	int max = 0;
	int m = int(0.45 * n);
	int* l = new int[m];
	for (int i = 0; i < m; i++)
		l[i] = 0;
	for (int i = 1;++comp && i < n; i++)
	{
		if (++comp && a[i] < minVal)
			minVal = a[i];
		if (++comp && a[i] > a[max])
			max = i;
	}
	if (++comp && a[max] == minVal)
		return;
	double c1 = (double)(m - 1) / (a[max] - minVal);
	for (int i = 0;++comp && i < n; i++)
	{
		int k = int(c1 * (a[i] - minVal));
		++l[k];
	}
	for (int i = 1;++comp && i < m; i++)
		l[i] += l[i - 1];
	swap(a[max], a[0]);
	int nmove = 0;
	int j = 0;
	int k = m - 1;
	int t = 0;
	int flash;
	while (++comp && nmove < n - 1)
	{
		while (++comp && j > l[k] - 1)
		{
			j++;
			k = int(c1 * (a[j] - minVal));
		}
		flash = a[j];
		if (++comp && k < 0) break;
		while (++comp && j != l[k])
		{
			k = int(c1 * (flash - minVal));
			int hold = a[t = --l[k]];
			a[t] = flash;
			flash = hold;
			++nmove;
		}
	}
	delete[] l;
	for (int i = 1;++comp && i < n; i++)
	{
		int v = i - 1;
		int key = a[i];
		while ((++comp && a[v] > key) && (++comp && v >= 0))
		{
			a[v + 1] = a[v];
			v--;
		}
		a[v + 1] = key;
	}
}

void merge(int* a, int l, int m, int r, long long& comp)
{
	int i = 0, j = 0, k = l;
	int part1 = m - l + 1;
	int part2 = r - m;

	int* L, * R;
	L = new int[part1];
	R = new int[part2];

	int h = 0, c = 0;
	while (true) {
		if (++comp && h < part1)
			L[h] = a[l + h];
		if (++comp && h < part2)
			R[h] = a[m + 1 + h];
		if (++comp && h == part1)
			c++;
		if (++comp && h == part2)
			c++;
		if (++comp && c == 2)break;
		h++;
	}

	while ((++comp && i < part1) && (++comp && j < part2))
	{
		if (++comp && L[i] <= R[j])
		{
			a[k] = L[i];
			i++;
		}
		else
		{
			a[k] = R[j];
			j++;
		}
		k++;
	}

	while (++comp && i < part1)
		a[k++] = L[i++];

	while (++comp && j < part2)
		a[k++] = R[j++];
}
void mergeSort(int* a, int l, int r, long long& comp)
{
	if (++comp && l < r) {
		int mid = l + (r - l) / 2;
		mergeSort(a, l, mid, comp);
		mergeSort(a, mid + 1, r, comp);
		merge(a, l, mid, r, comp);
	}
}
void out(int* a, int n)
{
	for (int i = 0;i < n;i++)
		cout << a[i] << " ";
	cout << "\n-----------------------------------------------\n";
}

void GenerateRandomData(int a[], int n)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % n;
	}
}

// increase function
void GenerateSortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
}

// discrease
void GenerateReverseData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = n - 1 - i;
	}
}

// pretty sort
void GenerateNearlySortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		int r1 = rand() % n;
		int r2 = rand() % n;
		swap(a[r1], a[r2]);
	}
}

void GenerateData(int a[], int n, int dataType)
{
	switch (dataType)
	{
	case 0:	// random
		GenerateRandomData(a, n);
		break;
	case 1:	// sorted
		GenerateSortedData(a, n);
		break;
	case 2:	// high to low
		GenerateReverseData(a, n);
		break;
	case 3:	// nearly sort
		GenerateNearlySortedData(a, n);
		break;
	default:
		printf("Error: unknown data type!\n");
	}
}

bool checkStringNum(string a)
{
	for (int i = 0;i < a.length();i++)
		if (a[i] > '9' || a[i] < '0')
			return false;
	return true;
}
void WriteFile(ofstream& fwrite, int* a, int n)
{
	fwrite << n << '\n';
	for (int i = 0;i < n;i++)
		fwrite << a[i] << ' ';
}

int* readFile(ifstream& fread, int& n)
{
	int* a;
	fread >> n;
	a = new int[n];
	for (int i = 0;i < n;i++)
		fread >> a[i];
	return a;
}

void cmd1(string arg1, string arg2, string arg3, string arg4)
{
	ofstream fwrite;
	ifstream fread;
	int* a;
	int n;
	fread.open(arg3);
	a = readFile(fread, n);
	fread.close();
	long long comp1, comp2 = 0;
	clock_t start, end;
	int type;
	if (arg1 == "-a");
	if (arg1 == "-c");
	start = clock();

	if (arg2== "flash-sort") {
		cout << "Algorithm : Flash sort\n";
		flashSort(a, n, comp1);
		end = clock();
		type = 0;
	}
	if (arg2 == "merge-sort") {
		cout << "Algorithm : Merge sort\n";
		mergeSort(a, 0, n - 1, comp2);
		end = clock();
		type = 1;
	}
	cout << "Input file : " << arg3 << "\n";
	cout << "Input size : " << n << "\n";
	cout << "--------------------------------------\n";
	if (arg4 == "-time") {
		if (type == 0)
			cout << "Flash sort : " << fixed << double(end - start) / double(CLOCKS_PER_SEC) * 1000 << "\tmili seconds.\n";
		else
			cout << "Merge sort : " << fixed << double(end - start) / double(CLOCKS_PER_SEC) * 1000 << "\tmili seconds.\n";
	}
	if (arg4 == "-comp") {
		if (type == 0)
			cout << "Comparison : " << comp1 << "\n";
		else
			cout << "Comparison : " << comp2 << "\n";
	}
	if (arg4 == "-both") {
		if (type == 0) {
			cout << "Comparison : " << comp1 << "\n";
			cout << "Time : " << fixed << double(end - start) / double(CLOCKS_PER_SEC) * 1000 << "\tmili seconds.\n";
		}
		else {
			cout << "Time: " << fixed << double(end - start) / double(CLOCKS_PER_SEC) * 1000 << "\tmili seconds.\n";
			cout << "Comparison : " << comp2 << "\n";
		}
	}
	//ghi mang da sap xep vao file
	fwrite.open("output.txt");
	WriteFile(fwrite, a, n);
	fwrite.close();

}
void cmd2(string mode, string algor, string size, string order,string paramet)
{
	ofstream fwrite;
	int* a;
	int n = stoi(size);
	a = new int[n];
	long long comp1, comp2 = 0;
	clock_t start, end;
	string inputOrder;
	int type;
	if (mode == "-a")
		cout << "ALGORITHM MODE\n";
	if (mode == "-c")
		cout << "ALGORITHM MODE\n";
	if (order == "-rand") {
		GenerateRandomData(a, n);
		inputOrder = "Randomized data.\n";
	}
	if (order == "-nsorted") {
		GenerateNearlySortedData(a, n);
		inputOrder = " Nearly sorted data.\n";
	}
	if (order == "-sorted") {
		GenerateSortedData(a, n);
		inputOrder = "Sorted data.\n";
	}
	if (order == "-rev") {
		GenerateReverseData(a, n);
		inputOrder = "Reverse sorted data.\n";
	}

	//ghi du lieu dau vao vao file
	fwrite.open("input.txt");
	WriteFile(fwrite, a, n);
	fwrite.close();

	start = clock();
	if (algor == "flash-sort") {
		cout << "Algorithm : Flash sort\n";
		flashSort(a, n, comp1);
		end = clock();
		type = 0;
	}
	if (algor == "merge-sort") {
		cout << "Algorithm : Merge sort\n";
		mergeSort(a, 0, n - 1, comp2);
		end = clock();
		type = 1;
	}
	cout << "Input size : " << n << "\n";
	cout << "Input oder : " << inputOrder << "\n";
	cout << "--------------------------------------\n";
	if (paramet == "-time") {
		if (type == 0)
			cout << "Time : " << fixed << double(end - start) / double(CLOCKS_PER_SEC) * 1000 << "\tmili seconds.\n";
		else
			cout << "Time : " << fixed << double(end - start) / double(CLOCKS_PER_SEC) * 1000 << "\tmili seconds.\n";
	}
	if (paramet == "-comp") {
		if (type == 0)
			cout << "Comparison : " << comp1 << "\n";
		else
			cout << "Comparison : " << comp2 << "\n";
	}
	if (paramet == "-both") {
		if (type == 0) {
			cout << "Comparison : " << comp1 << "\n";
			cout << "Time : " << fixed << double(end - start) / double(CLOCKS_PER_SEC) * 1000 << "\tmili seconds.\n";
		}
		else {
			cout << "Time: " << fixed << double(end - start) / double(CLOCKS_PER_SEC) * 1000 << "\tmili seconds.\n";
			cout << "Comparison : " << comp2 << "\n";
		}
	}


}
void cmd3(string mode, string algor, string size, string paramet)
{
	ofstream fwrite;
	int* a;
	int n = stoi(size);
	a = new int[n];
	long long comp1, comp2 = 0;
	clock_t start, end;
	string inputOrder[4];
	int type;
	if (mode == "-a")
		cout << "ALGORITHM MODE\n";
	if (mode == "-c")
		cout << "ALGORITHM MODE\n";
	if (algor == "flash-sort") 
		cout << "Algorithm : Flash sort\n";
	if (algor == "merge-sort") 
		cout << "Algorithm : Merge sort\n";
	cout << "Input size : " << n << "\n\n";


	inputOrder[0] = "Randomized data.\n";
	inputOrder[3] = " Nearly sorted data.\n";
	inputOrder[1] = "Sorted data.\n";
	inputOrder[2] = "Reverse sorted data.\n";
	for (int i = 0;i < 4;i++) {
		cout << "Input order : " << inputOrder[i];
		cout << "--------------------------------------\n";
		GenerateData(a, n, i);
		//Ghi du lieu dau vao vao file
		stringstream s;
		s << i + 1;
		fwrite.open("input_" + s.str() + ".txt");
		fwrite << inputOrder[i] << "\n";
		WriteFile(fwrite, a, n);
		fwrite.close();
		cout << "\n";

		start = clock();
		if (algor == "flash-sort") {
			flashSort(a, n, comp1);
			end = clock();
			type = 0;
		}
		if (algor == "merge-sort") {
			mergeSort(a, 0, n - 1, comp2);
			end = clock();
			type = 1;
		}

		if (paramet == "-time") {
			if (type == 0)
				cout << "Time : " << fixed << double(end - start) / double(CLOCKS_PER_SEC) * 1000 << "\tmili seconds.\n";
			else
				cout << "Time : " << fixed << double(end - start) / double(CLOCKS_PER_SEC) * 1000 << "\tmili seconds.\n";
		}
		if (paramet == "-comp") {
			if (type == 0)
				cout << "Comparison : " << comp1 << "\n";
			else
				cout << "Comparison : " << comp2 << "\n";
		}
		if (paramet == "-both") {
			if (type == 0) {
				cout << "Comparison : " << comp1 << "\n";
				cout << "Time : " << fixed << double(end - start) / double(CLOCKS_PER_SEC) * 1000 << "\tmili seconds.\n";
			}
			else {
				cout << "Time: " << fixed << double(end - start) / double(CLOCKS_PER_SEC) * 1000 << "\tmili seconds.\n";
				cout << "Comparison : " << comp2 << "\n";
			}
		}
		
	}

	
}
void cmd4(string mode, string algor1, string algor2, string inputFile)
{
	ifstream fread;
	ofstream fwrite;
	int* a,*b;
	int n;
	fread.open(inputFile);
	a = readFile(fread, n);
	b = a;
	fread.close();
	long long comp1, comp2 = 0;
	clock_t start1, end1,start2,end2;

	if (mode == "-a")
		cout << "ALGORITHM MODE\n";
	if (mode == "-c")
		cout << "ALGORITHM MODE\n";
	start1 = clock();

	if (algor1 == "flash-sort") {
		cout << "Algorithm : Flash sort  |  ";
		flashSort(a, n, comp1);
		end1 = clock();
	}
	if (algor1 == "merge-sort") {
		cout << "Algorithm : Merge sort  |  ";
		mergeSort(a, 0, n - 1, comp2);
		end1 = clock();
	}
	start2 = clock();
	if (algor2 == "flash-sort") {
		cout << "Flash sort\n";
		flashSort(b, n, comp1);
		end2 = clock();
	}
	if (algor2 == "merge-sort") {
		cout << "Merge sort\n";
		mergeSort(b, 0, n - 1, comp2);
		end2 = clock();
	}
	cout << "Input file : " << inputFile << "\n";
	cout << "Input size : " << n << "\n";
	cout << "--------------------------------------\n";

	cout << "Running time : " << fixed << double(end1 - start1) / double(CLOCKS_PER_SEC) * 1000;
	cout << "  |  " << fixed << double(end2 - start2) / double(CLOCKS_PER_SEC) * 1000<<"\n";
	cout << "Comparisons : " << comp1 << "  |   " << comp2 << "\n";

	//ghi mang da sap xep vao file
	fwrite.open("output.txt");
	WriteFile(fwrite, a, n);
	fwrite.close();
}

void cmd5(string mode, string algor1, string algor2, string size, string order)
{
	ofstream fwrite;
	int* a, * b;
	int n = stoi(size);
	a = new int[n];
	long long comp1, comp2 = 0;
	clock_t start1, end1, start2, end2;
	string inputOrder;


	if (mode == "-a")
		cout << "ALGORITHM MODE\n";
	if (mode == "-c")
		cout << "ALGORITHM MODE\n";
	
	if (algor1 == "flash-sort") 
		cout << "Algorithm : Flash sort  |  ";
	if (algor1 == "merge-sort") 
		cout << "Algorithm : Merge sort  |  ";
	if (algor2 == "flash-sort") 
		cout << "Flash sort\n";
	if (algor2 == "merge-sort") 
		cout << "Merge sort\n";

	if (order == "-rand") {
		GenerateRandomData(a, n);
		inputOrder = "Randomized data.\n";
	}
	if (order == "-nsorted") {
		GenerateNearlySortedData(a, n);
		inputOrder = " Nearly sorted data.\n";
	}
	if (order == "-sorted") {
		GenerateSortedData(a, n);
		inputOrder = "Sorted data.\n";
	}
	if (order == "-rev") {
		GenerateReverseData(a, n);
		inputOrder = "Reverse sorted data.\n";
	}
	b = a;

	//ghi mang dau vao da tao 
	fwrite.open("input.txt");
	WriteFile(fwrite, a, n);
	fwrite.close();

	cout << "Input order : " << inputOrder << "\n";
	cout << "Input size : " << n << "\n";
	cout << "--------------------------------------\n";

	start1 = clock();
	if (algor1 == "flash-sort") {
		flashSort(a, n, comp1);
		end1 = clock();
	}
	if (algor1 == "merge-sort") {
		mergeSort(a, 0, n - 1, comp2);
		end1 = clock();
	}

	start2 = clock();
	if (algor2 == "flash-sort") {
		flashSort(b, n, comp1);
		end2 = clock();
	}
	if (algor2 == "merge-sort") {
		mergeSort(b, 0, n - 1, comp2);
		end2 = clock();
	}

	cout << "Running time : " << fixed << double(end1 - start1) / double(CLOCKS_PER_SEC) * 1000;
	cout << "  |  " << fixed << double(end2 - start2) / double(CLOCKS_PER_SEC) * 1000 << "\n";
	cout << "Comparisons : " << comp1 << "  |   " << comp2 << "\n";
}

// Ham chay all case
void menuWithoutArgument()
{
	clock_t s1, s2, s;
	int type = 5, sort = 2;
	long long comp1, comp2 = 0;
	int t[6] = { 10000,30000,50000,100000,300000,500000 };
	for (int i = 0;i < type;i++)
		for (int j = 0;j < 6;j++)
			for (int z = 0;z < sort;z++) {
				int* a = new int[t[j]];
				GenerateData(a, t[j], i);
				s1 = clock();
				cout << "----------With type " << i << " and size " << t[j] << " :\n";
				if (z == 0) {
					flashSort(a, t[j], comp1);
					s2 = clock();
					cout << "Flash sort : " << fixed << double(s2 - s1) / double(CLOCKS_PER_SEC) * 1000 << "\tmili seconds.\n";
					cout << "Comparison : " << comp1 << "\n";
				}
				else
				{
					mergeSort(a, 0, t[j] - 1, comp2);
					s2 = clock();
					cout << "Merge sort : " << fixed << double(s2 - s1) / double(CLOCKS_PER_SEC) * 1000 << "\tmili seconds.\n";
					cout << "Comparison : " << comp2 << "\n";
				}
				cout << "\n____________________________________________________________\n\n";
			}
}