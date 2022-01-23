# YSMF: Yale Sparse Matrix Format for C++

A C++ implementation of the Yale Sparse Matrix Format, for templated sparse matrices.

# Usage

## Import the library

Use:

`#include "SparseMatrix.h"`

Note: the library is compatible with _iostream_. Use the following import to use _iostream_ functions:

`#include <iostream>`

## Constructor

Create a new matrix called matrix_name, which:
* contains objects of type T;
* uses the functor C to compare two objects 
of type T;
* uses the object D as default value.   

Note: the function pointed to by C must return **TRUE** if two objects of type T are different, **FALSE** otherwise.

`SparseMatrix<T, C> matrix_name(D);`

Construct a matrix with objects of type T from a matrix of objects of type Q:

`SparseMatrix<T, C> matrix_name_T(matrix_name_Q);`

## Set the matrix size to (m, n)

`matrix_name.set_dimension(m, n);`

## Add an object to the matrix at position (i, j)

`matrix_name.add(object, i, j);`

Note: the object must be of type T

## Get the object at position (i, j)

`matrix_name(i, j);`

## Using iterators


```
SparseMatrix<T, C>::iterator s, e;
s = matrix_name.begin();
e = matrix_name.end();

while (s != e) {
        std::cout << "value: " << s.operator*()._element_value
                  << " row: " << s.operator*()._element_row
                  << " column: " << s.operator*()._element_column;
        std::cout << std::endl;
        s++;
    }
```

Iterators that do not allow editing of objects can also be used:

 `SparseMatrix<T, C>::const_iterator sc, ec;`


# Please contact me
Please contact me if you have any concerns or can help me improve the documentation. Thanks!
