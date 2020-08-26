//
// Created by Marco Gatti on 10/01/2020.
//

#ifndef INC_829895_SPARSEMATRIX_H
#define INC_829895_SPARSEMATRIX_H

#include <iostream>
#include <cassert>
#include <algorithm>
#include <iterator>
#include <cstddef>

template<typename T, typename C>
class SparseMatrix {
public:
    typedef unsigned int size_type;
    typedef T value_type_t;
private:

    size_type _rows;
    size_type _columns;
    value_type_t *_v;
    size_type _v_size;
    size_type *_col_index;
    size_type *_row_index;
    value_type_t D;
    C is_different;

    /**
     * Private method for modifying an element in the array, whose value is different from the default
     * @param value
     * @param row
     * @param column
     */
    void set(const value_type_t &value, const size_type row, const size_type column) {
        size_type start;
        size_type end;
        int index = -1;
        start = _row_index[row - 1];
        if (row == _rows) {
            end = _v_size;
        } else {
            end = _row_index[row];
        }
        for (size_type i = start; i < end; ++i) {
            if (_col_index[i] == column - 1) {
                index = i;
            }
        }
        _v[index] = value;
    }

public:

    /**
     * Creates a new array with the required default parameter
     * @param valueDefault
     */
    explicit SparseMatrix(const value_type_t &valueDefault) : D(valueDefault), _rows(0), _columns(0), _v_size(0),
                                                              _v(nullptr), _col_index(nullptr), _row_index(nullptr) {
#ifndef NDEBUG
        std::cout << "explicit SparseMatrix(value_type_t valueDefault)" << std::endl;
#endif
    }

    /**
     * Creates a new array with the required default parameter and memory limits such as number rows and number columns
     * @param rows
     * @param columns
     * @param valueDefault
     */
    SparseMatrix(const size_type rows, const size_type columns, const value_type_t &valueDefault) : _rows(0), _columns(0),
                                                                                                    D(valueDefault),
                                                                                                    _v_size(0),
                                                                                                    _v(nullptr),
                                                                                                    _col_index(nullptr),
                                                                                                    _row_index(nullptr) {
        assert(rows > 0 && columns > 0);
        _rows = rows;
        _columns = columns;
        try {
            _row_index = new size_type[_rows];
            for (int i = 0; i < _rows; ++i) {
                _row_index[i] = 0;
            }
        } catch (...) {
            delete[] _row_index;
            _row_index = nullptr;
            throw;
        }


#ifndef NDEBUG
        std::cout << "SparseMatrix(size_type rows, size_type columns, value_type_t valueDefault)" << std::endl;
#endif
    }

    /**
     * Copy constructor
     * @param other SparseMatrix
     */
    SparseMatrix(const SparseMatrix &other) : _rows(0), _columns(0), D(other.D), _v_size(0),
                                              _v(nullptr), _col_index(nullptr), _row_index(nullptr) {
        if (other._v_size > 0) {
            try {

                _v = new value_type_t[other._v_size];
                _col_index = new size_type[other._v_size];

                for (size_type i = 0; i < other._v_size; ++i) {
                    _v[i] = other._v[i];
                    _col_index[i] = other._col_index[i];
                }

            } catch (...) {
                delete[] _v;
                delete[] _col_index;
                _v = nullptr;
                _col_index = nullptr;
                throw;
            }
        }
        if (other._rows > 0) {
            try {
                _row_index = new size_type[other._rows];
                for (size_type i = 0; i < other._rows; ++i) {
                    _row_index[i] = other._row_index[i];
                }
            } catch (...) {
                delete[] _row_index;
                delete[] _v;
                delete[] _col_index; //These last two deletions are safe because either the objects could contain memory that leave an inconsistent state or point to nullptr
                _row_index = nullptr;
                _v = nullptr;
                _col_index = nullptr;
                throw;
            }
        }
        _rows = other._rows;
        _columns = other._columns;
        _v_size = other._v_size;
#ifndef NDEBUG
        std::cout << "SparseMatrix(const SparseMatrix &other)" << std::endl;
#endif

    }

    /**
     * Assignment operator
     * @param SparseMatrix to the right
     * @return Copied SparseMatrix
     */
    SparseMatrix &operator=(const SparseMatrix &rhs) {
        if (this != &rhs) {

            SparseMatrix tmp(rhs);

            std::swap(this->_rows, tmp._rows);
            std::swap(this->_columns, tmp._columns);
            std::swap(this->_v, tmp._v);
            std::swap(this->_v_size, tmp._v_size);
            std::swap(this->_col_index, tmp._col_index);
            std::swap(this->_row_index, tmp._row_index);
            std::swap(this->D, tmp.D);

        }
#ifndef NDEBUG
        std::cout << "SparseMatrix &operator=(const SparseMatrix &rhs)" << std::endl;
#endif
        return *this;
    }

    /**
     * Destructor
     */
    ~SparseMatrix() {
        delete[] _v;
        delete[] _col_index;
        delete[] _row_index;
        _v = nullptr;
        _col_index = nullptr;
        _row_index = nullptr;
        _rows = 0;
        _columns = 0;
        _v_size = 0;

#ifndef NDEBUG
        std::cout << "~SparseMatrix()" << std::endl;
#endif
    }

    /**
     * Constructor for matrix from another of a different type that accepts a type conversion with static_cast
     * @tparam Q type of the other matrix
     * @tparam E other matrix comparison function
     * @param other Q value matrix and E comparison
     */
    template<typename Q, typename E>
    explicit
    SparseMatrix(const SparseMatrix<Q, E> &other):  _rows(0), _columns(0), _v_size(0), _v(nullptr), _col_index(nullptr),
                                                    _row_index(nullptr){
        if (other.size_element() > 0) {
            try {

                _v = new value_type_t[other.size_element()];
                _col_index = new size_type[other.size_element()];

                for (size_type i = 0; i < other.size_element(); ++i) {
                    _v[i] = static_cast<T>(other.v(i));
                    _col_index[i] = other.col_index(i);
                }

            } catch (...) {
                delete[] _v;
                delete[] _col_index;
                _v = nullptr;
                _col_index = nullptr;
                throw;
            }
        }
        if (other.rows() > 0) {
            try {
                _row_index = new size_type[other.rows()];
                for (size_type i = 0; i < other.rows(); ++i) {
                    _row_index[i] = other.row_index(i);
                }
            } catch (...) {
                delete[] _row_index;
                delete[] _v;
                delete[] _col_index; //These last two deletions are safe because either the objects could contain memory that leave an inconsistent state or point to nullptr
                _row_index = nullptr;
                _v = nullptr;
                _col_index = nullptr;
                throw;
            }
            _rows = other.rows();
            _columns = other.columns();
            _v_size = other.size_element();
            D = static_cast<T>(other.default_value());
#ifndef NDEBUG
            std::cout << "SparseMatrix(const SparseMatrix &other)" << std::endl;
#endif

        }
    }

    /**
     * Adds an element to the array
     * @param value
     * @param row start from 1
     * @param column start from 1
     */
    void add(const value_type_t &value, const size_type row, const size_type column) {
        assert(column > 0 && row > 0 && column <= _columns && row <= _rows && is_different(D, value));
        value_type_t matrix_at = operator()(row, column);
        if (is_different(matrix_at, D)) {
            set(value, row, column);
        } else {
            value_type_t *tmp_v = nullptr;
            size_type *tmp_c = nullptr;
            size_type *tmp_r = nullptr;
            try {

                tmp_v = new value_type_t[_v_size + 1];
                tmp_c = new size_type[_v_size + 1];
                tmp_r = new size_type[_rows];

                for (int j = 0; j < row; ++j) {
                    tmp_r[j] = _row_index[j];
                }

                for (int l = row; l < _rows; ++l) {
                    tmp_r[l] = (_row_index[l] + 1);
                }
                if (_v != nullptr) {
                    size_type i;
                    for (i = 0; i < _row_index[row - 1]; ++i) {
                        tmp_v[i] = _v[i];
                        tmp_c[i] = _col_index[i];
                    }
                    size_type end;
                    if (row == _rows) {
                        end = _v_size;
                    } else {
                        end = _row_index[row];
                    }
                    size_type j = _row_index[row - 1];
                    while (j < end && (column - 1) > _col_index[j]) {
                        tmp_v[j] = _v[j];
                        tmp_c[j] = _col_index[j];
                        j++;
                    }
                    tmp_v[j] = value;
                    tmp_c[j] = column - 1;
                    j++;
                    for (size_type k = j - 1; k < _v_size; ++k, ++j) {
                        tmp_v[j] = _v[k];
                        tmp_c[j] = _col_index[k];
                    }
                } else {
                    tmp_v[0] = value;
                    tmp_c[0] = column - 1;
                }
            } catch (...) {
                delete[] tmp_v;
                delete[] tmp_c;
                delete[] tmp_r;
                tmp_v = nullptr;
                tmp_c = nullptr;
                tmp_r = nullptr;
                throw;
            }

            std::swap(this->_v, tmp_v);
            std::swap(this->_row_index, tmp_r);
            std::swap(this->_col_index, tmp_c);
            delete[] tmp_v;
            delete[] tmp_r;
            delete[]  tmp_c;
            tmp_v = nullptr;
            tmp_r = nullptr;
            tmp_c = nullptr;
            _v_size++;
        }
    }

    /**
     * Prints the state of the array for debugging
     */
    void debug() {
        std::cout << "_rows: " << _rows;
        std::cout << " _columns: " << _columns;
        std::cout << " D: " << D;
        std::cout << " _v_size: " << _v_size;
        std::cout << std::endl;
        std::cout << "_col_index: ";
        if (_col_index != nullptr) {
            for (int i = 0; i < _v_size; ++i) {
                std::cout << _col_index[i];
            }
        } else {
            std::cout << "nullptr";
        }
        std::cout << std::endl;
        std::cout << "_row_index: ";
        if (_row_index != nullptr) {
            for (int i = 0; i < _rows; ++i) {
                std::cout << _row_index[i];
            }
        } else {
            std::cout << "nullptr";
        }
        std::cout << std::endl;
        std::cout << "_v: ";
        if (_v != nullptr) {
            for (int i = 0; i < _v_size; ++i) {
                std::cout << _v[i];
            }
        } else {
            std::cout << "nullptr";
        }
        std::cout << std::endl;
    }

    /**
     * It is used to take an item in row "row" and column "column"
     * @param row start from 1
     * @param column start from 1
     * @return Element in row "row" and column "column"
     */
    const value_type_t &operator()(const size_type row, const size_type column) const {
        assert(column > 0 && row > 0 && column <= _columns && row <= _rows);
        if (_v_size > 0) {
            size_type start;
            size_type end;
            int index;
            index = -1;
            start = _row_index[row - 1];
            if (row == _rows) {
                end = _v_size;
            } else {
                end = _row_index[row];
            }
            for (size_type i = start; i < end; ++i) {
                if (_col_index[i] == (column - 1)) {
                    index = i;
                }
            }
            if (index >= 0) {
                return _v[index];
            } else {
                return D;
            }
        }
        return D;
    }

    /**
     * Getter rows
     * @return The number of rows
     */
    size_type rows() const {
        return _rows;
    }

    /**
     * Getter columns
     * @return The number of columns
     */
    size_type columns() const {
        return _columns;
    }

    /**
     * Getter size
     * @return The number of elements inserted
     */
    size_type size_element() const {
        return _v_size;
    }

    /**
     * Getter default value
     * @return The default value
     */
    const value_type_t &default_value() const {
        return D;
    }

    /**
     * Defines the size of the matrix if it has not yet been defined
     * @param rows
     * @param columns
     */
    void set_dimension(const size_type rows, const size_type columns) {
        assert(_rows == 0 && _columns == 0);
        SparseMatrix tmp(rows, columns, D);
        std::swap(_rows, tmp._rows);
        std::swap(_columns, tmp._columns);
        std::swap(_row_index, tmp._row_index);
    }

    /**
     * Getter for value
     * @param i
     * @return The i-th value
     */
    const value_type_t &v(const size_type i) const {
        assert(i < _v_size);
        return _v[i];
    }

    /**
     * Getter for columns
     * @param i
     * @return The i-th value
     */
    const size_type &col_index(const size_type i) const {
        assert(i < _v_size);
        return _col_index[i];
    }

    /**
     * Getter for row index
     * @param i
     * @return The i-th value
     */
    const size_type &row_index(const size_type i) const {
        assert(i < _rows);
        return _row_index[i];
    }

    class const_iterator;

    class iterator {
        friend class SparseMatrix;

    public:
        struct element {
            value_type_t &_element_value;
            const size_type _element_row;
            const size_type _element_column;

            element(value_type_t &elementValue, const size_type elementRow, const size_type elementColumn)
                    : _element_value(elementValue), _element_row(elementRow), _element_column(elementColumn) {}

            ~element() {}

        };

    private:
        value_type_t *_v_it;
        size_type *_col_it;
        size_type *_row_it;
        size_type _r_size;
        size_type _index;
        size_type _limit;
        element *_e;


        iterator(value_type_t *v_it, size_type *row_it, size_type *col_it, const size_type r_size, const size_type index,
                 const size_type limit) : _v_it(v_it), _row_it(row_it), _col_it(col_it), _r_size(r_size), _index(index),
                                          _limit(limit),
                                          _e(nullptr) {
            make_element();
        }

        void make_element() {
            if (_index < _limit) {
                const size_type c = (*_col_it) + 1;
                size_type r = 0;
                size_type i;
                for (i = 0; i < _r_size - 1; ++i) {
                    if (*(_row_it + i) <= _index && _index < *(_row_it + i + 1)) {
                        r = i + 1;
                    }
                }
                if (i == _r_size - 1 && r == 0) {
                    r = i + 1;
                }
                if (_e != nullptr) {
                    delete _e;
                    _e = nullptr;
                }
                try {
                    _e = new element(*_v_it, r, c);
                } catch (...) {
                    delete _e;
                    _e = nullptr;
                    throw;

                }
            }
        }

    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef element value_type;
        typedef ptrdiff_t difference_type;
        typedef element *pointer;
        typedef element &reference;

        iterator() : _v_it(nullptr), _col_it(nullptr), _row_it(nullptr), _r_size(0), _index(0), _limit(0),
                     _e(nullptr) {}

        iterator(const iterator &other) : _v_it(other._v_it), _col_it(other._col_it), _row_it(other._row_it),
                                          _r_size(other._r_size), _index(other._index), _limit(other._limit),
                                          _e(nullptr) {
            if (other._e != nullptr) {
                _e = new element(other._e->_element_value, other._e->_element_row, other._e->_element_column);
            }
        }

        iterator &operator=(const iterator &rhs) {
            if (this != &rhs) {
                iterator tmp(rhs);
                std::swap(_v_it, tmp._v_it);
                std::swap(_col_it, tmp._col_it);
                std::swap(_row_it, tmp._row_it);
                std::swap(_index, tmp._index);
                std::swap(_r_size, tmp._r_size);
                std::swap(_limit, tmp._limit);
                std::swap(_e, tmp._e);
            }
            return *this;
        }

        ~iterator() {
            delete _e;
            _e = nullptr;
        }

        reference operator*() const {
            return *_e;
        }

        pointer operator->() const {

            return _e;

        }

        iterator operator++(int) {
            const iterator tmp(*this);
            ++_v_it;
            ++_col_it;
            ++_index;
            make_element();
            return tmp;
        }

        iterator &operator++() {
            ++_v_it;
            ++_col_it;
            ++_index;
            make_element();
            return *this;
        }


        bool operator==(const iterator &other) const {
            return (_v_it == other._v_it && _col_it == other._col_it && _row_it == other._row_it);
        }

        bool operator!=(const iterator &other) const {
            return (_v_it != other._v_it || _col_it != other._col_it || _row_it != other._row_it);
        }

        friend class const_iterator;

        bool operator==(const const_iterator &other) const {
            return (_v_it == other._v_it && _col_it == other._col_it && _row_it == other._row_it);
        }

        bool operator!=(const const_iterator &other) const {
            return (_v_it != other._v_it || _col_it != other._col_it || _row_it != other._row_it);
        }
    };

    iterator begin() {
        return iterator(_v, _row_index, _col_index, _rows, 0, _v_size);
    }

    iterator end() {
        return iterator(_v + _v_size, _row_index, _col_index + _v_size, _rows, _v_size, _v_size);
    }


    class const_iterator {
        friend class SparseMatrix;

    public:
        struct element {
            const value_type_t &_element_value;
            const size_type _element_row;
            const size_type _element_column;

            element(const value_type_t &elementValue, const size_type elementRow, const size_type elementColumn)
                    : _element_value(elementValue), _element_row(elementRow), _element_column(elementColumn) {}

            ~element() {}

        };

    private:
        value_type_t *_v_it;
        size_type *_col_it;
        size_type *_row_it;
        size_type _r_size;
        size_type _index;
        size_type _limit;
        element *_e;

        const_iterator(value_type_t *v_it, size_type *row_it, size_type *col_it, const size_type r_size,
                       const size_type index, const size_type limit) : _v_it(v_it), _row_it(row_it), _col_it(col_it),
                                                                       _r_size(r_size), _index(index), _limit(limit),
                                                                       _e(nullptr) {
            make_element();
        }

        void make_element() {
            if (_index < _limit) {
                const size_type c = (*_col_it) + 1;
                size_type r = 0;
                size_type i;
                for (i = 0; i < _r_size - 1; ++i) {
                    if (*(_row_it + i) <= _index && _index < *(_row_it + i + 1)) {
                        r = i + 1;
                    }
                }
                if (i == _r_size - 1 && r == 0) {
                    r = i + 1;
                }
                if (_e != nullptr) {
                    delete _e;
                    _e = nullptr;
                }
                try {
                    _e = new element(*_v_it, r, c);
                } catch (...) {
                    delete _e;
                    _e = nullptr;
                    throw;

                }
            }
        }

    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef element value_type;
        typedef ptrdiff_t difference_type;
        typedef element *pointer;
        typedef element &reference;


        const_iterator() : _v_it(nullptr), _col_it(nullptr), _row_it(nullptr), _r_size(0), _index(0), _limit(0),
                           _e(nullptr) {}

        const_iterator(const const_iterator &other) : _v_it(other._v_it), _col_it(other._col_it),
                                                      _row_it(other._row_it), _r_size(other._r_size),
                                                      _index(other._index), _limit(other._limit), _e(nullptr) {
            if (other._e != nullptr) {
                _e = new element(other._e->_element_value, other._e->_element_row, other._e->_element_column);
            }
        }

        const_iterator &operator=(const const_iterator &rhs) {
            if (this != &rhs) {
                const_iterator tmp(rhs);
                std::swap(_v_it, tmp._v_it);
                std::swap(_col_it, tmp._col_it);
                std::swap(_row_it, tmp._row_it);
                std::swap(_index, tmp._index);
                std::swap(_r_size, tmp._r_size);
                std::swap(_limit, tmp._limit);
                std::swap(_e, tmp._e);
            }
            return *this;
        }

        ~const_iterator() {
            delete _e;
            _e = nullptr;
        }

        reference operator*() const {
            return *_e;
        }

        pointer operator->() const {
            return _e;
        }

        const_iterator operator++(int) {
            const const_iterator tmp(*this);
            ++_v_it;
            ++_col_it;
            ++_index;
            make_element();
            return tmp;
        }

        const_iterator &operator++() {
            ++_v_it;
            ++_col_it;
            ++_index;
            make_element();
            return *this;
        }


        bool operator==(const const_iterator &other) const {
            return (_v_it == other._v_it && _col_it == other._col_it && _row_it == other._row_it);
        }

        bool operator!=(const const_iterator &other) const {
            return (_v_it != other._v_it || _col_it != other._col_it || _row_it != other._row_it);

        }

        friend class iterator;

        bool operator==(const iterator &other) const {
            return (_v_it == other._v_it && _col_it == other._col_it && _row_it == other._row_it);
        }


        bool operator!=(const iterator &other) const {
            return (_v_it != other._v_it || _col_it != other._col_it || _row_it != other._row_it);
        }

        explicit const_iterator(const iterator &other) : _v_it(other._v_it), _col_it(other._col_it),
                                                         _row_it(other._row_it), _r_size(other._r_size),
                                                         _index(other._index), _limit(other._limit),
                                                         _e(nullptr) {
            if (other._e != nullptr) {
                _e = new element(other._e->_element_value, other._e->_element_row, other._e->_element_column);
            }
        }

        const_iterator &operator=(const iterator &rhs) {

            const_iterator tmp(rhs);
            std::swap(_v_it, tmp._v_it);
            std::swap(_col_it, tmp._col_it);
            std::swap(_row_it, tmp._row_it);
            std::swap(_index, tmp._index);
            std::swap(_r_size, tmp._r_size);
            std::swap(_limit, tmp._limit);
            std::swap(_e, tmp._e);
            return *this;
        }

    };

    const_iterator begin() const {
        return const_iterator(_v, _row_index, _col_index, _rows, 0, _v_size);
    }

    const_iterator end() const {
        return const_iterator(_v + _v_size, _row_index, _col_index + _v_size, _rows, _v_size, _v_size);
    }


};


#endif //INC_829895_SPARSEMATRIX_H

