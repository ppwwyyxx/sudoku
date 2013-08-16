//File: DancingLinks.java
//Date: Fri Aug 16 21:47:40 2013 +0800
//Author: Yuxin Wu <ppwwyyxxc@gmail.com>

import java.util.List;
import java.util.ArrayList;

public class DancingLinks {

	class Node {
		public Node u, d, l, r;
		int col, row;
	}

	private Matrix mat;
	private int maxx, maxy;
	private Node[] nodes;
	private Node[] col;
	private int[] sum;
	private Node root = new Node();
	List<Integer> ans = new ArrayList<Integer>();
	List<List<Integer>> ret = new ArrayList<List<Integer>>();


	public DancingLinks(Matrix m) {
		mat = m;
		maxx = m.M;
		maxy = m.N;
		nodes = new Node[maxx * maxy];
		for (int i = 0; i < maxx * maxy; i ++) nodes[i] = new Node();
		col = new Node[maxx];
		for (int i = 0; i < maxx; i ++) col[i] = new Node();
		sum = new int[maxx];
	}

	public void init() {
		// initialize root
		root.l = col[maxx - 1];
		root.r = col[0];

		// initialize col
		// link all the column horizontally with root as head,
		// if a column needn't to be covered anymore, it will be deleted
		//
		// link all the node vertically with col as head
		for (int i = 0; i < maxx; i ++) {
			col[i].col = i;
			col[i].u = col[i].d = col[i];
			if (i == 0)
				col[i].l = root;
			else
				col[i].l = col[i - 1];

			if (i == maxx - 1)
				col[i].r = root;
			else
				col[i].r = col[i + 1];
		}

		// initialize row
		// link all the node in one row with row[] as head
		// horizontally, row[].u, row[].d don't matter
		Node[] row = new Node[maxy];
		for (int i = 0; i < maxy; i ++) row[i] = new Node();
		for (int i = 0; i < maxy; i ++)
			row[i].u = row[i].d = row[i].l = row[i].r = row[i];

		// initialize nodes
		for (int cnt = 0, j = 0; j < maxy; j ++)
			for (int i = 0; i < maxx; i ++) {
				if (!mat.data[j][i]) continue;
				// the for loop is increasing, explaining the following order to insert nodes
				nodes[cnt].col = i;
				nodes[cnt].row = j;
				nodes[cnt].u = col[i].u;
				nodes[cnt].d = col[i];
				nodes[cnt].l = row[j].l;
				nodes[cnt].r = row[j];

				// link node with col and row head
				col[i].u = col[i].u.d = row[j].l = row[j].l.r = nodes[cnt];

				cnt ++;
				sum[i] ++;
			}

		// delete head, to make a circle list in every row.
		// head will cause trouble later when iterating
		for (int j = 0; j < maxy; j ++) {
			row[j].l.r = row[j].r;
			row[j].r.l = row[j].l;
		}
	}

	public void search() {
		if (root.r == root) {
			ret.add(new ArrayList<Integer>(ans));
			return;
		}

		// find a column with least "1"s
		Node min = root.r;
		for (Node p = min.r; p != root; p = p.r)
			if (sum[p.col] < sum[min.col])
				min = p;

		cover(min);

		for (Node p = min.d; p != min; p = p.d) {
			ans.add(p.row);

			for (Node q = p.r; q != p; q = q.r)
				cover(col[q.col]);

			search();
			ans.remove(ans.size() - 1);

			for (Node q = p.l; q != p; q = q.l)
				uncover(col[q.col]);
		}
		uncover(min);
		return;
	}

	void cover(Node s) {
		assert col[s.col] == s;
		s.l.r = s.r;
		s.r.l = s.l;
		for (Node i = s.d; i != s; i = i.d)
			for (Node j = i.r; j != i; j = j.r) {
				j.u.d = j.d;
				j.d.u = j.u;
				sum[j.col] --;
			}
	}

	void uncover(Node s) {
		assert col[s.col] == s;
		for (Node i = s.u; i != s; i = i.u)
			for (Node j = i.l; j != i; j = j.l) {
				j.u.d = j.d.u = j;
				sum[j.col] ++;
			}
		s.l.r = s.r.l = s;
	}

	public List<List<Integer>> solve() {
		init();
		search();
		return ret;
	}
}
