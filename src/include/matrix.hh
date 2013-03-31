// File: matrix.hh
// Date: Sat Mar 30 10:15:40 2013 +0800
// Author: Yuxin Wu <ppwwyyxxc@gmail.com>

#ifndef __HEAD__MATRIX
#define __HEAD__MATRIX
#include "debugutils.hh"

// basic 2-d array
template <typename T>
class MatrixBase {
	public:
		T **val;
		int w, h;

		MatrixBase(int m_w, int m_h):
			w(m_w), h(m_h) {
				val = new T* [h];
				for (int i = 0; i < h; i ++)
					val[i] = new T[w]();
		}

		MatrixBase(int m_w, int m_h, T** v)
			:w(m_w), h(m_h) {
			val = new T* [h];
			int rowlen = w * sizeof(T);

			for (int i = 0; i < h; i++) {
				val[i] = new T [w]();
				if (v)
					memcpy(val[i], v[i], rowlen);
			}
		}

		~MatrixBase() {
			for (int i = 0; i < h; i++)
				delete [] val[i];
			delete [] val;
		}

		// get the ith row
		T*& operator [] (int i) {
			sassert((0 <= i) && (i <= h));
			return val[i];
		}

		/*
		 *const T*& operator [] (int i) const {
		 *    sassert((0 <= i) && (i <= h));
		 *    return val[i];
		 *}
		 */
};

typedef MatrixBase<int> Matrix;

#endif //HEAD
