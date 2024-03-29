#include "pch.h"
#include <iostream> 
#include <fstream> 
#include <string> 
using namespace std;
// размер слова 
const int n = 30;
struct replace
{
	char name1[4];
	char name2[4];
};
// копирование 
void strcpy1(char a[n], char b[n])
{
	int i = 0;
	while ((a[i] = b[i]) != '\0')
		++i;
}
// проверка, строка s является подстрокой p 
// ЕА предикат
bool strstr1(char s[n], char p[n])
{
	bool b = false;
	for (int i = 0; i < strlen(p) - strlen(s) + 1 && !b; ++i)
	{
		bool d = true;
		for (int j = 0; j < strlen(s) && d; ++j)
			if (s[j] != p[i + j])
				d = false;
		b = d;
	}
	return b;
}
// поместить подстроку s в строку p 
// возвращает позицию, начиная с которой подстрока s входит в p
int strstr2(char s[n], char p[n])
{
	int i, j;
	int pos = -1;
	bool t = false;
	for (i = 0; i < strlen(p) - strlen(s) + 1 && !t; ++i)
	{
		bool r = true;
		for (j = 0; j < strlen(s) && r; ++j)
			if (s[j] != p[i + j])
				r = false;
		t = r;
	}
	if (t)
		pos = i - 1;
	else
		pos = -1;
	return pos;
}
//добавление y в конец x
void conc(char x[n], char y[n])
{
	int i = strlen(x);
	int j = 0;
	while ((x[i] = y[j]) != '\0')
	{	++i;++j;	}
}

// удаление подслова 
void del(char x[n], int pos, int len)
{
	if (pos > strlen(x) - len)
	{
		cout << "impossible!" << endl;
		exit(-1);
	}
	int j = pos;
	int i = pos + len;
	while ((x[j] = x[i]) != '\0')
	{	i++; j++;	}
}

// insert string y[n] to string x[n] 
// with position pos in x[n] 
void insert(char y[n], int pos, char x[n])
{
	if (pos == strlen(x))
	{
		conc(x, y); exit(-1);
	}

	if ((pos > strlen(x)) || (pos < 0))
	{
		cout << " impossible!! ";
		exit(-1);
	}

	char z[n], m[n];
	int i = 0;
	int j = pos;
	while ((z[i] = x[j]) != '\0')
	{
		++i;
		++j;
	}
	strcpy1(m, y);
	conc(m, z);
	i = pos;
	j = 0;
	while ((x[i] = m[j]) != '\0')
	{
		++i;
		++j;
	}
}
// замены 
void insert(replace arr[], char word[], ofstream& out, int& it, string buf)
{
	int i = 0, k;
	while (i!=1)// так как у нас две замены 0 и 1 в "b.txt"
	{
		if (strstr2(arr[i].name1, word) == -1)//подслово ab не встретилось в word 
			++i;// то смотрим следующее подслово (ac)

		if (strstr2(arr[i].name1, word) != -1)
		{
			k = strstr2(arr[i].name1, word);
			out <<it<<' '<< word << " -> ";
			del(word, k, strlen(arr[i].name1));
			insert(arr[i].name2, k, word);
			buf = word;
			out << buf << endl;
			i = 0;	
			++it;
		}
	}
}

int main()
{
	ifstream in1("a.txt");
	ifstream in2("b.txt");
	ofstream out("result.txt");
	replace arr[10]; // массив замен 
	for (int i = 0; !in2.eof(); ++i)
	{
		in2 >> arr[i].name1;
		in2 >> arr[i].name2;
	}
	char word[n]; // введеное слово 
	in1 >> word;
	out << "Begining word = " << word << endl << endl;
	int it = 1;
	string buf;
	insert(arr, word, out, it, buf);// производим замены 
	out << endl << "Final word = " << word << endl;
	in1.close();
	in2.close();
	out.close();
	system ("pause");
	return 0;
}