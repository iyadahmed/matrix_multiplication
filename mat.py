from typing import Sequence, Tuple


class Matrix2D:
    def __init__(self, num_rows: int, num_cols: int):
        self._num_rows = num_rows
        self._row_stride = self._num_cols = num_cols

        self._data = [0.0] * num_rows * num_cols

    def num_rows(self):
        return self._num_rows

    def num_cols(self):
        return self._num_cols

    def _calc_offset(self, i: int, j: int):
        assert 0 <= i < self._num_rows
        assert 0 <= j < self._num_cols

        return i * self._row_stride + j

    def __getitem__(self, index: Tuple[int, int]):
        return self._data[self._calc_offset(index[0], index[1])]

    def __setitem__(self, index: Tuple[int, int], value):
        self._data[self._calc_offset(index[0], index[1])] = value

    def get_row(self, row_index: int):
        offset = row_index * self._row_stride
        return self._data[offset : offset + self._row_stride]

    def get_column(self, column_index: int):
        return self._data[column_index :: self._row_stride]

    def print(self):
        for i in range(self._num_rows):
            print(self.get_row(i))


def dot(a: Sequence, b: Sequence):
    assert len(a) == len(b)
    return sum(a_e * b_e for a_e, b_e in zip(a, b))


def mat_mul(A: Matrix2D, B: Matrix2D):
    assert A.num_cols() == B.num_rows()

    result = Matrix2D(A.num_rows(), B.num_cols())

    for i in range(A.num_rows()):
        for j in range(B.num_cols()):
            row = A.get_row(i)
            col = B.get_column(j)
            result[i, j] = dot(row, col)

    return result


A = Matrix2D(3, 1)

A[0, 0] = -1
A[1, 0] = 0
A[2, 0] = 2

B = Matrix2D(1, 3)

B[0, 0] = 6
B[0, 1] = -2
B[0, 2] = -5

mat_mul(A, B).print()
