// File: DL.hh
// Date: Sat Mar 30 11:21:29 2013 +0800
// Author: Yuxin Wu <ppwwyyxxc@gmail.com>

#ifndef __HEAD__DL
#define __HEAD__DL

#include <vector>
#include "matrix.hh"

class Node {
	public:
		Node *u, *d, *l, *r;
		int col, row;
};

// Exact Cover Class Using Dancing Links
class DL {
	public:
		DL(MatrixBase<bool>* m) :
			mat(m) {
			maxx = m->w;
			maxy = m->h;
			nodes = new Node[maxx * maxy];
			col = new Node[maxx];
			sum = new int[maxx]();
		};

		~DL(){
			delete[] nodes;
			delete[] col;
			delete[] sum;
		}

		void init();

		std::vector<int> solve();

		bool search();

		void cover(Node*);

		void uncover(Node*);


	private:
		MatrixBase<bool>* mat;
		int maxx, maxy;
		Node* nodes;
		Node* col;
		Node root;
		int* sum;
		std::vector<int> ans;
};

#endif //HEAD
