#include <iostream>
#include "SparseMatrix.h"

/**
 * global function that returns the number of elements in array M that respect P
 * @tparam T, value type contained in M
 * @tparam C, M comparison operator
 * @tparam PR, type of the predicate functor
 * @param M, the sparse matrix
 * @param P,the predicate functor
 * @return The number of elements in array M that respect P
 */
template<typename T, typename C, typename PR>
int evaluate(const SparseMatrix<T, C> &M, const PR &P) {
    int count = 0;
    for (unsigned int i = 1; i <= M.rows(); ++i) {
        for (unsigned int j = 1; j <= M.columns(); ++j) {
            if (P(M(i, j))) {
                count++;
            }
        }

    }
    return count;
}

struct is_different_int {
    bool operator()(int a, int b) const {
        return a != b;
    }
};

struct is_different_char {
    bool operator()(char a, char b) const {
        return a != b;
    }
};

struct is_different_std_string {
    bool operator()(const std::string &a, const std::string &b) const {
        return a != b;
    }
};
struct eq_ele{
    bool operator()(const SparseMatrix<int, is_different_int>::iterator::element e1, const SparseMatrix<int, is_different_int>::iterator::element e2){
        return e1._element_value == e2._element_value;
    }
};

bool eq_ele2(const SparseMatrix<int, is_different_int>::iterator::element e1, const SparseMatrix<int, is_different_int>::iterator::element e2){
    return e1._element_value == e2._element_value;
}
void evaluate_test();

void constructor_test() {
    SparseMatrix<int, is_different_int> s1(0);
    s1.debug();
    SparseMatrix<char, is_different_char> s2('a');
    s2.debug();
    SparseMatrix<std::string, is_different_std_string> s3("This test >> 42");
    s3.debug();
    SparseMatrix<int, is_different_int> s4(4, 6, 0);
    s4.debug();
    SparseMatrix<char, is_different_char> s5(100, 20, 'a');
    s5.debug();
    SparseMatrix<std::string, is_different_std_string> s6(10, 10, "This test >> 42");
    s6.debug();
    SparseMatrix<int, is_different_int> s7 = s4;
    s7.debug();
    SparseMatrix<char, is_different_char> s8 = s5;
    s8.debug();
    SparseMatrix<std::string, is_different_std_string> s9 = s6;
    s9.debug();
    SparseMatrix<int, is_different_int> s10(5);
    s10 = s4;
    s10.debug();
    SparseMatrix<char, is_different_char> s11('c');
    s11 = s5;
    s11.debug();
    SparseMatrix<std::string, is_different_std_string> s12("this is magic moment");
    s12 = s6;
    s12.debug();
    SparseMatrix<int, is_different_int> s13(s11);
    s13.debug();
    SparseMatrix<int, is_different_int> s14(5);
    s14.debug();
    SparseMatrix<char, is_different_char> s15('b');
    s15.debug();
    SparseMatrix<std::string, is_different_std_string> s16("Magic moment");
    s16.debug();
    s14 = s1;
    s14.debug();
    s15 = s2;
    s15.debug();
    s16 = s3;
    s16.debug();

}


void add_test_get() {
    SparseMatrix<int, is_different_int> s1(3, 3, 0);
    SparseMatrix<char, is_different_char> s2(100, 20, 'a');
    SparseMatrix<std::string, is_different_std_string> s3(10, 10, "Hello");
    int i = 1;
    s1.add(i, 2, 3);
    char j = 'c';
    s2.add(j, 50, 2);
    std::string l = "many";
    s3.add(l, 10, 10);
    std::cout << s3(10, 10);
    s1.debug();
    s2.debug();
    s3.debug();
    std::cout << s3(10, 10) << std::endl;

    int u = 1;
    for (unsigned int k = 1; k < 4; ++k) {
        for (unsigned int m = 1; m < 4; ++m) {
            s1.add(u, k, m);
            s1.debug();
            ++u;
        }
    }

    s1.debug();
    std::cout << std::endl;
    for (unsigned int k = 1; k < 4; ++k) {
        std::cout << std::endl;
        for (unsigned int m = 1; m < 4; ++m) {
            std::cout << s1(k, m) << " ";
        }
    }
    std::cout << std::endl;

    char y = 'l';
    for (unsigned int k = 50; k <= 100; ++k) {
        for (unsigned int m = 1; m <= 20; ++m) {
            s2.add(y, k, m);
        }
    }
    for (unsigned int k = 1; k <= 100; ++k) {
        std::cout << std::endl;
        for (unsigned int m = 1; m <= 20; ++m) {
            std::cout << s2(k, m) << " ";
        }
    }
    std::cout << std::endl;

    std::string r = "world";
    for (unsigned int k = 1; k <= 10; ++k) {
        for (unsigned int m = 1; m <= 10; ++m) {
            if (m % 2 == 0) {
                s3.add(r, k, m);
            }
        }
    }
    for (unsigned int k = 1; k <= 10; ++k) {
        std::cout << std::endl;
        for (unsigned int m = 1; m <= 10; ++m) {
            std::cout << s3(k, m) << " ";
        }
    }
    std::cout << std::endl;


}


void iterator_test() {
    SparseMatrix<int, is_different_int> s1(3, 3, 0);
    SparseMatrix<char, is_different_char> s2(100, 20, 'a');
    SparseMatrix<std::string, is_different_std_string> s3(10, 10, "Hello");

    int u = 1;
    for (unsigned int k = 1; k < 4; ++k) {
        for (unsigned int m = 1; m < 4; ++m) {
            s1.add(u, k, m);
            ++u;
        }
    }

    char y = 'l';
    for (unsigned int k = 1; k <= 50; ++k) {
        for (unsigned int m = 1; m <= 20; ++m) {
            s2.add(y, k, m);
        }
    }

    std::string r = "fantastic world";
    for (unsigned int k = 1; k <= 10; ++k) {
        for (unsigned int m = 1; m <= 10; ++m) {
            if (m % 2 == 0) {
                s3.add(r, k, m);
            }
        }
    }

    SparseMatrix<int, is_different_int>::iterator is1, es1;
    is1 = s1.begin();
    es1 = s1.end();
    SparseMatrix<int, is_different_int>::iterator::element e1 = *is1;
    e1._element_value = 6;
    std::cout << "value: " << e1._element_value << " row: " << e1._element_row
              << " column: " << e1._element_column;
    std::cout << std::endl;

    while (is1 != es1) {
        std::cout << "value: " << is1.operator*()._element_value
                  << " row: " << is1.operator*()._element_row
                  << " column: " << is1.operator*()._element_column;
        std::cout << std::endl;
        is1++;
    }

    SparseMatrix<char, is_different_char>::iterator is2, es2;
    is2 = s2.begin();
    es2 = s2.end();
    while (is2 != es2) {
        std::cout << "value: " << is2.operator*()._element_value << " row: " << is2.operator*()._element_row
                  << " column: " << is2.operator*()._element_column;
        std::cout << std::endl;
        ++is2;
    }

    SparseMatrix<std::string, is_different_std_string>::iterator is3, es3;
    is3 = s3.begin();
    es3 = s3.end();
    SparseMatrix<std::string, is_different_std_string>::iterator::element e3 = *(is3.operator->());
    e3._element_value = "string_1";
    while (is3 != es3) {
        std::cout << "value: " << is3.operator*()._element_value << " row: " << is3.operator*()._element_row
                  << " column: " << is3.operator*()._element_column;
        std::cout << std::endl;
        is3++;
    }

    is1 = s1.begin();
    es1 = s1.end();
    is1.operator->()->_element_value = 3;
    std::cout << is1.operator->()->_element_value;
    is1.operator*()._element_value = 5;
    std::cout << std::endl;

    while (is1 != es1) {
        std::cout << "value: " << is1.operator->()->_element_value << " row: " << is1.operator->()->_element_row
                  << " column: " << is1.operator->()->_element_column;
        std::cout << std::endl;
        ++is1;
    }
    is2 = s2.begin();
    es2 = s2.end();
    while (is2 != es2) {
        std::cout << "value: " << is2.operator->()->_element_value << " row: " << is2.operator->()->_element_row
                  << " column: " << is2.operator->()->_element_column;
        std::cout << std::endl;
        ++is2;
    }

    is3 = s3.begin();
    es3 = s3.end();
    is3.operator*()._element_value = "string_2";
    is3.operator->()->_element_value = "string_2";
    while (is3 != es3) {
        std::cout << "value: " << is3.operator->()->_element_value << " row: " << is3.operator->()->_element_row
                  << " column: " << is3.operator->()->_element_column;
        std::cout << std::endl;
        ++is3;
    }

    SparseMatrix<int, is_different_int>::const_iterator isc1, esc1;
    isc1 = s1.begin();
    esc1 = s1.end();
    SparseMatrix<int, is_different_int>::const_iterator::element e2 = *isc1;
    std::cout << "value: " << e2._element_value << " row: " << e2._element_row
              << " column: " << e2._element_column;
    std::cout << std::endl;

    while (isc1 != esc1) {
        std::cout << "value: " << isc1.operator*()._element_value << " row: " << isc1.operator*()._element_row
                  << " column: " << isc1.operator*()._element_column;
        std::cout << std::endl;
        isc1++;
    }
    isc1 = s1.begin();
    esc1 = s1.end();
    std::cout << std::endl;

    while (isc1 != esc1) {
        std::cout << "value: " << isc1.operator->()->_element_value << " row: " << isc1.operator->()->_element_row
                  << " column: " << isc1.operator->()->_element_column;
        std::cout << std::endl;
        ++isc1;
    }
    SparseMatrix<char, is_different_char>::const_iterator isc2, esc2;
    isc2 = s2.begin();
    esc2 = s2.end();
    std::cout << std::endl;
    while (isc2 != esc2) {
        std::cout << "value: " << isc2.operator*()._element_value << " row: " << isc2.operator*()._element_row
                  << " column: " << isc2.operator*()._element_column;
        std::cout << std::endl;
        ++isc2;
    }
    isc2 = s2.begin();
    esc2 = s2.end();
    while (isc2 != esc2) {
        std::cout << "value: " << isc2.operator->()->_element_value << " row: " << isc2.operator->()->_element_row
                  << " column: " << isc2.operator->()->_element_column;
        std::cout << std::endl;
        ++isc2;
    }

    SparseMatrix<std::string, is_different_std_string>::const_iterator isc3, esc3;
    isc3 = s3.begin();
    esc3 = s3.end();
    while (isc3 != esc3) {
        std::cout << "value: " << isc3.operator*()._element_value << " row: " << isc3.operator*()._element_row
                  << " column: " << isc3.operator*()._element_column;
        std::cout << std::endl;
        isc3++;
    }

    isc3 = s3.begin();
    esc3 = s3.end();
    while (isc3 != esc3) {
        std::cout << "value: " << isc3.operator->()->_element_value << " row: " << isc3.operator->()->_element_row
                  << " column: " << isc3.operator->()->_element_column;
        std::cout << std::endl;
        ++isc3;
    }
    SparseMatrix<int, is_different_int> s4(s2);

    SparseMatrix<int, is_different_int>::const_iterator isc4, esc4;
    isc4 = s4.begin();
    esc4 = s4.end();
    std::cout << std::endl;

    while (isc4 != esc4) {
        std::cout << "value: " << isc4.operator*()._element_value << " row: " << isc4.operator*()._element_row
                  << " column: " << isc4.operator*()._element_column;
        std::cout << std::endl;
        ++isc4;
    }
    isc4 = s4.begin();
    esc4 = s4.end();
    std::cout << std::endl;

    while (isc4 != esc4) {
        std::cout << "value: " << isc4.operator->()->_element_value << " row: " << isc4.operator->()->_element_row
                  << " column: " << isc4.operator->()->_element_column;
        std::cout << std::endl;
        ++isc4;
    }

    SparseMatrix<std::string, is_different_std_string>::iterator is5, es5;
    is5 = s3.begin();
    es5 = s3.end();
    SparseMatrix<std::string, is_different_std_string>::const_iterator isc6, esc6;
    isc6 = s3.begin();
    esc6 = s3.end();

    is3 = is5;
    es3 = es5;
    while (is3 != es3) {
        std::cout << "value: " << is3.operator->()->_element_value << " row: " << is3.operator->()->_element_row
                  << " column: " << is3.operator->()->_element_column;
        std::cout << std::endl;
        ++is3;
    }
    is5 = s3.begin();
    es5 = s3.end();
    is3 = is5;
    es3 = es5;
    while (is3 != es3) {
        std::cout << "value: " << is3.operator*()._element_value << " row: " << is3.operator*()._element_row
                  << " column: " << is3.operator*()._element_column;
        std::cout << std::endl;
        is3++;
    }
    isc3 = isc6;
    esc3 = esc6;
    while (isc3 != esc3) {
        std::cout << "value: " << isc3.operator->()->_element_value << " row: " << isc3.operator->()->_element_row
                  << " column: " << isc3.operator->()->_element_column;
        std::cout << std::endl;
        ++isc3;
    }
    isc6 = s3.begin();
    esc6 = s3.end();
    isc3 = isc6;
    esc3 = esc6;
    while (isc3 != esc3) {
        std::cout << "value: " << isc3.operator*()._element_value << " row: " << isc3.operator*()._element_row
                  << " column: " << isc3.operator*()._element_column;
        std::cout << std::endl;
        isc3++;
    }
    is5 = s3.begin();
    es5 = s3.end();
    isc3 = is5;
    esc3 = es5;
    while (isc3 != esc3) {
        std::cout << "value: " << isc3.operator->()->_element_value << " row: " << isc3.operator->()->_element_row
                  << " column: " << isc3.operator->()->_element_column;
        std::cout << std::endl;
        ++isc3;
    }
    is5 = s3.begin();
    es5 = s3.end();
    isc3 = is5;
    esc3 = es5;

    while (isc3 != esc3) {
        std::cout << "value: " << isc3.operator*()._element_value << " row: " << isc3.operator*()._element_row
                  << " column: " << isc3.operator*()._element_column;
        std::cout << std::endl;
        isc3++;
    }

    std::cout << std::equal(s1.begin(), s1.end(), s1.begin(), eq_ele());
    std::cout << std::equal(s1.begin(), s1.end(), s1.begin(), eq_ele2);

}


void getter_setter_test() {
    SparseMatrix<int, is_different_int> s1(0);
    SparseMatrix<char, is_different_char> s2('a');
    SparseMatrix<std::string, is_different_std_string> s3("magicString");
    std::cout << "rows: " << s1.rows() << " columns: " << s1.columns() << " elements: " << s1.size_element() << " D: "
              << s1.default_value() << std::endl;
    s1.set_dimension(5, 5);
    std::cout << "rows: " << s1.rows() << " columns: " << s1.columns() << " elements: " << s1.size_element() << " D: "
              << s1.default_value() << std::endl;
    s1.debug();
    std::cout << "rows: " << s2.rows() << " columns: " << s2.columns() << " elements: " << s2.size_element() << " D: "
              << s2.default_value() << std::endl;
    s2.set_dimension(7, 1);
    std::cout << "rows: " << s2.rows() << " columns: " << s2.columns() << " elements: " << s2.size_element() << " D: "
              << s2.default_value() << std::endl;
    s2.debug();
    std::cout << "rows: " << s3.rows() << " columns: " << s3.columns() << " elements: " << s3.size_element() << " D: "
              << s3.default_value() << std::endl;
    s3.set_dimension(4, 100);
    std::cout << "rows: " << s3.rows() << " columns: " << s3.columns() << " elements: " << s3.size_element() << " D: "
              << s3.default_value() << std::endl;
    s3.debug();

}

int main() {

    constructor_test();
    add_test_get();
    iterator_test();
    getter_setter_test();
    evaluate_test();
    return 0;
}

struct eql_int {
    int i;

    explicit eql_int(const int i) : i(i) {}

    bool operator()(const int a) const {
        return a == i;
    }
};

struct eql_char {
    char i;

    explicit eql_char(const char i) : i(i) {}

    bool operator()(const char a) const {
        return a == i;
    }
};

struct eql_string {
    std::string i;

    explicit eql_string(const std::string &i) : i(i) {}

    bool operator()(const std::string &a) const {
        return a == i;
    }
};

struct neql_string {
    std::string i;

    explicit neql_string(const std::string &i) : i(i) {}

    bool operator()(const std::string &a) const {
        return a != i;
    }
};

struct greater_int {
    int i;

    explicit greater_int(const int i) : i(i) {}

    bool operator()(const int a) const {
        return a > i;
    }
};

struct lenght_string_is_5 {

    bool operator()(const std::string &a) const {
        return a.length() == 5;
    }
};

void evaluate_test() {
    SparseMatrix<int, is_different_int> s1(3, 3, 0);
    SparseMatrix<char, is_different_char> s2(100, 20, 'a');
    SparseMatrix<std::string, is_different_std_string> s3(10, 10, "Hello");

    eql_int ei(0);
    std::cout << evaluate(s1, ei) << std::endl;
    eql_char ea('a');
    std::cout << evaluate(s2, ea) << std::endl;
    eql_string es("Hello");
    std::cout << evaluate(s3, es) << std::endl;
    neql_string nes("life");
    std::cout << evaluate(s3, nes) << std::endl;

    int u = 1;
    for (unsigned int k = 1; k < 4; ++k) {
        for (unsigned int m = 1; m < 4; ++m) {
            s1.add(u, k, m);
            ++u;
        }
    }

    greater_int gi(5);
    std::cout << evaluate(s1, gi) << std::endl;

    lenght_string_is_5 ls5;
    std::cout << evaluate(s3, ls5) << std::endl;

}

