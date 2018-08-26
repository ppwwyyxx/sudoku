//File: Sudoku.java
//Date: Fri Aug 16 21:47:42 2013 +0800


import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class Sudoku {
	private static final int NUM = 9;
	private static int exists_cnt = 0;

	public static void main(String[] args) throws FileNotFoundException, IOException {
		if (args.length != 2) {
			System.err.println("usage: java Sudoku <input filename> <output filename>");
			return;
		}

		int[][] orig = new int[NUM][NUM];

		BufferedReader fin = new BufferedReader(new FileReader(args[0]));
		for (int i = 0; i < NUM; i ++) {
			String text = fin.readLine();
			for (int j = 0; j < NUM; j ++) {
				int x = Integer.parseInt(text.substring(j, j + 1));
				orig[i][j] = x;
				if (x != 0) exists_cnt ++;
			}
		}
		fin.close();

		long start_time = System.currentTimeMillis();

		Matrix mat = new Matrix(NUM * NUM * 4, exists_cnt + (NUM * NUM - exists_cnt) * NUM);
		List<Pair<Integer, Integer>> line_record = new ArrayList<Pair<Integer, Integer>>();

		for (int linecnt = 0, i = 0; i < NUM; i ++) {
			for (int j = 0; j < NUM; j ++) {
				if (orig[i][j] != 0) {
					mat.add(linecnt, i, j, orig[i][j]);
					line_record.add(new Pair<Integer, Integer>(i * NUM + j, orig[i][j]));
					linecnt ++;
				} else {
					for (int k = 1; k <= NUM; k ++) {
						mat.add(linecnt, i, j, k);
						line_record.add(new Pair<Integer, Integer>(i * NUM + j, k));
						linecnt ++;
					}
				}
			}
		}

		DancingLinks cover = new DancingLinks(mat);
		List<List<Integer>> ret = cover.solve();
		long end_time = System.currentTimeMillis();
		System.out.println(Double.toString((end_time - start_time) / 1000) + " seconds spent on calculation.");

		/*
		 *PrintWriter fout = new PrintWriter(new FileWriter(args[1]));
		 *for (List<Integer> ans : ret) {
		 *    for (Integer i : ans) {
		 *        Pair<Integer, Integer> res = line_record.get(i);
		 *        orig[res.first / NUM][res.first % NUM] = res.second;
		 *    }
		 *    for (int i = 0; i < NUM; i ++)
		 *        for (int j = 0; j < NUM; j ++) {
		 *            fout.print(orig[i][j]);
		 *            fout.print( j == NUM - 1 ? "\n" : "");
		 *        }
		 *    fout.println();
		 *}
		 *fout.close();
		 */

		System.out.print(ret.size());
		System.out.println(" results.");
	}
}
