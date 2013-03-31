// File: DL.cc
// Date: Sun Mar 31 13:35:56 2013 +0800
// Author: Yuxin Wu <ppwwyyxxc@gmail.com>

#include <vector>
#include <iostream>
using namespace std;

#include "DL.hh"

void DL::init() {
	// initialize root
	root.l = &col[maxx - 1], root.r = col;

	// initialize col
	// link all the column horizontally with root as head,
	// if a column needn't to be covered anymore, it will be deleted
	//
	// link all the node vertically with col as head
	for (int i = 0; i < maxx; i ++) {
		col[i].col = i;		// for find min_column
		col[i].u = col[i].d = &col[i];
		if (!i)
			col[i].l = &root;
		else
			col[i].l = &col[i - 1];

		if (maxx - 1 == i)
			col[i].r = &root;
		else
			col[i].r = &col[i + 1];
	}

	// initialize row
	// link all the node in one row with row[] as head
	// horizontally, row[].u, row[].d don't matter
	Node* row = new Node[maxy];
	for (int j = 0; j < maxy; j ++)
		row[j].u = row[j].d = row[j].l = row[j].r = &row[j];

	// initialize nodes
	for (int cnt = 0, j = 0; j < maxy; j ++)
		for (int i = 0; i < maxx; i ++) {
			if (!mat->val[j][i])
				continue;
			// the for loop is increasing, explaining the following order to insert nodes
			nodes[cnt].col = i, nodes[cnt].row = j;
			nodes[cnt].u = col[i].u;
			nodes[cnt].d = &col[i];
			nodes[cnt].l = row[j].l;
			nodes[cnt].r = &row[j];

			// link node with col and row head
			col[i].u = col[i].u->d = row[j].l = row[j].l->r = &nodes[cnt];

			cnt ++;
			sum[i] ++;
		}

	// delete head, to make a circle list in every row.
	// head will cause trouble later when iterating
	for (int j = 0; j < maxy; j ++) {
		row[j].l->r = row[j].r;
		row[j].r->l = row[j].l;
	}
	delete[] row;
}

bool DL::search() {
	if (root.r == &root)
		return true;

	// find a column with least "1"s
	Node* min = root.r;
	for (Node* p = min->r; p != &root; p = p->r)
		if (sum[p->col] < sum[min->col])
			min = p;

	print_debug("find min colum: %d\n", min->col);
	cover(min);

	for (Node* p = min->d; p != min; p = p->d) {
		print_debug("push ans %d\n", p->row);
		ans.push_back(p->row);

		for (Node* q = p->r; q != p; q = q->r)
			cover(&col[q->col]);

		if (search())
			return true;

		print_debug("pop ans %d\n", p->row);
		ans.pop_back();

		for (Node* q = p->l; q != p; q = q->l)
			uncover(&col[q->col]);
	}
	uncover(min);
	return false;
}

void DL::cover(Node* s) {
	sassert(&col[s->col] == s);	 // this node must be a column node
	print_debug("cover column %d\n", s->col);
	s->l->r = s->r;
	s->r->l = s->l;
	for (Node* i = s->d; i != s; i = i->d)
		for (Node* j = i->r; j != i; j = j->r) {
			j->u->d = j->d;
			j->d->u = j->u;
			sum[j->col]--;
		}
}

void DL::uncover(Node* s) {
	sassert(&col[s->col] == s);  // this node must be a column node
	print_debug("uncover column %d\n", s->col);
	for (Node* i = s->u; i != s; i = i->u)
		for (Node* j = i->l; j != i; j = j->l) {
			j->u->d = j->d->u = j;
			sum[j->col] ++;
		}
	s->l->r = s->r->l = s;
}

vector<int> DL::solve() {
	ans.clear();
	init();
	if(!search())
		sassert(0);
	return ans;
}

