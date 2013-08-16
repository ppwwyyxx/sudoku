//File: Matrix.java
//Date: Fri Aug 16 18:38:01 2013 +0800
//Author: Yuxin Wu <ppwwyyxxc@gmail.com>

public class Matrix {
	final int M;
	final int N;
	public boolean[][] data;

	public Matrix(int M, int N) {
		this.M = M;
		this.N = N;
		data = new boolean[N][M];
	}

	public Matrix(boolean[][] data) {
		N = data.length;
		M = data[0].length;
		this.data = new boolean[N][M];
		for (int i = 0; i < N; i ++)
			for (int j = 0; j < M; j ++)
				this.data[i][j] = data[i][j];
	}

	public void add(int linecnt, int i, int j, int v) {
		int SQR = M / 4;
		int NUM = (int)Math.sqrt(SQR);
		int SQRT = (int)Math.sqrt(NUM);
		data[linecnt][i * NUM + j] = true;
		data[linecnt][SQR + i * NUM + v - 1] = true;
		data[linecnt][SQR * 2 + j * NUM + v - 1] = true;
		data[linecnt][SQR * 3 + NUM * ((i / SQRT) * SQRT + (j / SQRT)) + v - 1] = true;
	}
}

