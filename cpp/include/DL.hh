// File: DL.hh
// Date: Fri Aug 16 18:05:38 2013 +0800


#ifndef __HEAD__DL
#define __HEAD__DL

#include <vector>
#include "matrix.hh"


// Exact Cover Class Using Dancing Links
class DL {
	struct Node {
		Node *u, *d, *l, *r;
		int col, row;
	};

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

		std::vector<std::vector<int>> solve();

		void search();

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
		std::vector<std::vector<int>> ret;
};

#endif //HEAD
