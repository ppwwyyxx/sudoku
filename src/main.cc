// File: main.cc
// Date: Sat Mar 30 11:14:54 2013 +0800
// Author: Yuxin Wu <ppwwyyxxc@gmail.com>

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <map>
#include <utility>
#include "matrix.hh"
#include "DL.hh"
using namespace std;

#define NUM 9
const int SQR = NUM * NUM;
const int SQRT = sqrt(NUM);

int main(int argc, char* argv[]) {
	if (argc != 3) {
		fprintf(stderr, "usage: %s <input filename> <output filename>", argv[0]);
		exit(1);
	}

	FILE* fin = fopen(argv[1], "r");
	int n = 0;
	Matrix orig(NUM, NUM);
	char* line = NULL;
	line = (char*) malloc (NUM + 1);
	size_t len = NUM;

	for (int i = 0; i < NUM; i ++) {
		getline(&line, &len, fin);
		for (int j = 0; j < NUM; j ++) {
			int x = line[j] - (NUM == 9 ? '0' : 'A' - 1);
			if ((line[j] == '-') || (line[j] == '.'))
				x = 0;
			orig[i][j] = x;
			if (x) n ++;
		}
	}
	free(line);
	fclose(fin);

	MatrixBase<bool> mat(SQR * 4, n + (SQR - n) * NUM);
	map<int, pair<int, int> > line_record;

	// add node[i][j] of value v to the cover matrix
#define add(i, j, v)\
	do {\
		mat[linecnt][i * NUM + j] = true;\
		mat[linecnt][SQR + i * NUM + v - 1] = true;\
		mat[linecnt][SQR * 2 + j * NUM + v - 1] = true;\
		mat[linecnt][SQR * 3 + NUM * ((i / SQRT) * SQRT + (j / SQRT)) + v - 1] = true;\
		line_record[linecnt] = make_pair(i * NUM + j, v);\
		linecnt ++;\
	} while (0)

	for (int linecnt = 0, i = 0; i < NUM; i ++)
		for (int j = 0; j < NUM; j ++) {
			if (orig[i][j])
				add(i, j, orig[i][j]);
			else
				for (int k = 1; k <= NUM; k ++)
					add(i, j, k);
		}
#undef add

	DL cover(&mat);
	vector<int> ans = cover.solve();
	for (vector<int>::iterator itr = ans.begin(); itr != ans.end(); itr ++) {
		int i = *itr;
		pair<int, int> res = line_record[i];
		orig[res.first / NUM][res.first % NUM] = res.second;
	}

	FILE* fout = fopen(argv[2], "w");
	for (int i = 0; i < NUM; i ++)
		for (int j = 0; j < NUM; j ++)
			fprintf(fout, "%c%s", (NUM == 9 ? orig[i][j] + '0' : orig[i][j] + 'A' - 1) , j == NUM - 1 ? "\n" : "");
	fclose(fout);
}
