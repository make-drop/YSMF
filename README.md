# SparseMatrix
Sparse matrix template library in c++
# Description

 In this project, the data structure known as the Yale Sparse Matrix was used.
 
 In addition, two template were considered for generic development. A type T, for the data contained in the matrix, and a functor C to compare values. In the matrix you can insert data of type T. If no data has been entered in a certain position then a default value is considered. The default value has to be provided when building the object.
 

 Actually, the array stores only the data entered other than the default value. It is assumed that the values contained in it are few and to speed up the access, it is preferred a static approach with fixed size arrays rather than a dynamic one made for example with a list. We consider below the variables used:
* _rows: the number of rows in the matrix;
* _columns: the number of columns in the matrix;
* _v: this vector contains all input data of type T (other than the default value) in the array;
* _v_size: the number of inserted elements of data type T;
* _column_index: maintains the column in which the element is inserted;
* _row_index: is recursively defined and has a fixed length equal to the number of rows: the first element is zero, while the n+1 element is the the sum of the nth element and the number of values contained in the nth row;
* D: the default value (type T);
* C: the functor for the comparison between two types of data T.

The matrix can be constructed by passing only the default value without the number of rows and columns. In this case, the matrix (of zero dimension) is in fact existing but without elements and without the possibility of inserting them; so, subsequently, only for the matrices that do not yet have a dimension, the number of rows and columns can be defined (necessarily greater than zero)

The constructor of a matrix on type T from a matrix on type Q was also written, and convertibility checking was delegated to the compiler.

# Usage

For the compilation there is the Makefile. SparseMatrix.h provides the complete code implementation. The main.cpp provides tests with different usage examples.

# Please contact me
Please contact me if you have any concerns or can help me improve the documentation. Thanks!
