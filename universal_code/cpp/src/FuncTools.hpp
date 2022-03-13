#pragma once
#include <vector>
#include <cmath>

namespace functools
{

template<typename T>
std::vector<T> linspace(double min, double max, int n)
{
    std::vector<T> result;
    // vector iterator
    int iterator = 0;

    for (int i = 0; i <= n-2; i++)	
    {
        T temp = min + i*(max-min)/(std::floor((T)n) - 1);
        result.insert(result.begin() + iterator, temp);
        iterator += 1;
    }

    result.insert(result.begin() + iterator, max);
    return result;
};

template<typename T>
std::vector<T> zeros_1d(int n)
{
    std::vector<T> result(n, 0);
    return result;
};

template<typename T>
std::vector<T> ones_1d(int n)
{
    std::vector<T> result(n, 1);
    return result;
};

template <class T>
class Matrix
{
    public:
        Matrix( int rows, int cols, const T& initVal = T() );

        // Size and structure
        int NumRows() const                       { return m_rows; }
        int NumColumns() const                    { return m_cols; }
        int NumElements() const                   { return m_data.size(); }

        // Direct vector access and indexing
        operator const std::vector<T>& () const        { return m_data; }
        int Index( int row, int col ) const       { return row * m_cols + col; }

        // Get a single value
              T & Value( int row, int col )       { return m_data[Index(row,col)]; }
        const T & Value( int row, int col ) const { return m_data[Index(row,col)]; }
              T & operator[]( size_t idx )        { return m_data[idx]; }
        const T & operator[]( size_t idx ) const  { return m_data[idx]; }

        // Simple row or column slices
        std::vector<T> Row( int row, int colBegin = 0, int colEnd = -1 ) const;
        std::vector<T> Column( int row, int colBegin = 0, int colEnd = -1 ) const;

    private:
        std::vector<T> StridedSlice( int start, int length, int stride ) const;

        int m_rows;
        int m_cols;

        std::vector<T> m_data;
};

template <class T>
std::vector<T> Matrix<T>::StridedSlice( int start, int length, int stride ) const
{
    std::vector<T> result;
    result.reserve( length );
    const T *pos = &m_data[start];
    for( int i = 0; i < length; i++ ) {
        result.push_back(*pos);
        pos += stride;
    }
    return result;
};

template <class T>
Matrix<T>::Matrix( int rows, int cols, const T& initVal )
    : m_data( rows * cols, initVal )
    , m_rows( rows )
    , m_cols( cols )
{    
};

template <class T>
std::vector<T> Matrix<T>::Row( int row, int colBegin, int colEnd ) const
{
    if( colEnd < 0 ) colEnd = m_cols-1;
    if( colBegin <= colEnd )
        return StridedSlice( Index(row,colBegin), colEnd-colBegin+1, 1 );
    else
        return StridedSlice( Index(row,colBegin), colBegin-colEnd+1, -1 );
};

template <class T>
std::vector<T> Matrix<T>::Column( int col, int rowBegin, int rowEnd ) const
{
    if( rowEnd < 0 ) rowEnd = m_rows-1;
    if( rowBegin <= rowEnd )
        return StridedSlice( Index(rowBegin,col), rowEnd-rowBegin+1, m_cols );
    else
        return StridedSlice( Index(rowBegin,col), rowBegin-rowEnd+1, -m_cols );
};

template<typename T>
Matrix<T> zeros_2d(int rows, int cols)
{
    Matrix<T> result(rows, cols, 0);
    return result;
}

template<typename T>
Matrix<T> ones_2d(int rows, int cols)
{
    Matrix<T> result(rows, cols, 1);
    return result;
}

}