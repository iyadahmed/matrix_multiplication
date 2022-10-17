#pragma once

#include <cassert>

class ConstStridedView
{
private:
    const int length, stride;
    const float *data;

public:
    ConstStridedView(const float *data, int length, int stride) : length(length), stride(stride), data(data)
    {
    }

    const float &operator[](int index) const
    {
        return data[index * stride];
    }

    int get_length() const
    {
        return length;
    }

    float dot(const ConstStridedView &other) const
    {
        assert(length == other.length);

        float result = 0.0f;
        for (int i = 0; i < get_length(); i++)
        {
            result += (this->operator[](i) * other[i]);
        }
        return result;
    }
};

class Matrix4x4
{
private:
    const int num_rows = 4, num_cols = 4;
    const int &row_stride = num_cols;
    float data[4 * 4] = {};

    int calc_offset(int row_index, int col_index) const
    {
        return row_index * row_stride + col_index;
    }

public:
    float &element(int row_index, int col_index)
    {
        return data[calc_offset(row_index, col_index)];
    }

    ConstStridedView get_row(int row_index) const
    {
        return ConstStridedView(data + (row_index * row_stride), num_cols, 1);
    }

    ConstStridedView get_column(int col_index) const
    {
        return ConstStridedView(data + col_index, num_rows, row_stride);
    }

    void mat_mul(Matrix4x4 &out, const Matrix4x4 &other) const
    {
        for (int i = 0; i < this->num_rows; i++)
        {
            for (int j = 0; j < other.num_cols; j++)
            {
                ConstStridedView row = this->get_row(i);
                ConstStridedView col = other.get_column(j);

                float &out_elem = out.element(i, j);
                out_elem = row.dot(col);
            }
        }
    }
};