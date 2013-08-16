// File: main.cc
// Date: Fri Aug 16 21:24:44 2013 +0800
// Author: Yuxin Wu <ppwwyyxxc@gmail.com>

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <map>
#include <utility>
#include "utils.hh"
#include <sys/time.h>
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

	REP(i, NUM) {
		getline(&line, &len, fin);
		REP(j, NUM) {
			int x = line[j] - (NUM == 9 ? '0' : 'A' - 1);
			if ((line[j] == '-') || (line[j] == '.'))
				x = 0;
			orig[i][j] = x;
			if (x) n ++;
		}
	}
	free(line);
	fclose(fin);

	timeval start_time;
	gettimeofday(&start_time, nullptr);

	MatrixBase<bool> mat(SQR * 4, n + (SQR - n) * NUM);
	pair<int, int>* line_record = new pair<int, int>[mat.h]();

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
		REP(j, NUM) {
			if (orig[i][j])
				add(i, j, orig[i][j]);
			else
				for (int k = 1; k <= NUM; k ++)
					add(i, j, k);
		}
#undef add

	DL cover(&mat);
	auto ret = cover.solve();

	timeval end_time;
	gettimeofday(&end_time, nullptr);
	cout << end_time.tv_sec - start_time.tv_sec + (double)(end_time.tv_usec - start_time.tv_usec) / 1e6
		<< " seconds spent on calculation." << endl;

	FILE* fout = fopen(argv[2], "w");
	for (auto & ans: ret) {
		for (auto i : ans) {
			pair<int, int> res = line_record[i];
			orig[res.first / NUM][res.first % NUM] = res.second;
		}
		REP(i, NUM) REP(j, NUM)
			fprintf(fout, "%c%s", (NUM == 9 ? orig[i][j] + '0' : orig[i][j] + 'A' - 1) , j == NUM - 1 ? "\n" : "");
		fprintf(fout, "\n");
	}
	delete[] line_record;
	fclose(fout);

	cout << ret.size() << endl;
}
