// File: matrix.hh
// Date: Fri Aug 16 18:45:40 2013 +0800


#ifndef __HEAD__MATRIX
#define __HEAD__MATRIX

#include "debugutils.hh"

// basic 2-d array
template <typename T>
class MatrixBase {
	public:
		T **val;
		int w, h;

		MatrixBase(int _w, int _h):
			w(_w), h(_h) {
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
