/**
 * Note: Requires C++11
**/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/** DEBUG OPERATIONS **/
bool use_color = false;

void enable_debug_colouring() {
    use_color = true;
}

template<class... T>
void _print_debug(int line_num, T const&... data) {
    if (use_color) {
        std::cout << "\033[1;31m";
    }
    std::cout << "DEBUG LINE " << line_num << ": ";
    using expander = int[];
    (void) expander{0, (void(std::cout << data << ", "), 0)...};
    std::cout << "\b \b\b \b" << std::endl;
    if (use_color) {
        std::cout << "\033[0m";
    }
}

template<class... T>
void println(T const&... data) {
    using expander = int[];
    (void) expander{0, (void(std::cout << data), 0)...};
    std::cout << std::endl;
}

template<class... T>
void printlni(T const&... data) {
    std::cout << "> ";
    using expander = int[];
    (void) expander{0, (void(std::cout << data), 0)...};
    std::cout << std::endl;
}
/** END DEBUG OPERATIONS **/


/** DICT OPERATIONS **/
template<typename key_type, typename val_type>
class dict_keys {
private:
    typename std::map<key_type, val_type>::iterator ibegin;
    typename std::map<key_type, val_type>::iterator icurrent;
    typename std::map<key_type, val_type>::iterator iend;
public:
    dict_keys(std::map<key_type, val_type>* map) {
        ibegin = map->begin();
        icurrent = map->begin();
        iend = map->end();
    }

    key_type& operator[](int i) const {
        typename std::map<key_type, val_type>::iterator temp = ibegin;
        std:advance(temp, i);
        return temp->first;
    }

    dict_keys<key_type, val_type>& begin() {return *this;}
    dict_keys<key_type, val_type>& end() {return *this;}

    bool operator==(const dict_keys<key_type, val_type>& x) {
        return icurrent == iend;
    }

    bool operator!=(const dict_keys<key_type, val_type>& x) {
        return icurrent != iend;
    }

    dict_keys<key_type, val_type>& operator++() {
        std::advance(icurrent, 1);
        return *this;
    }

    typename std::map<key_type, val_type>::iterator get_index() {
        return icurrent;
    }

    key_type operator*() const {return icurrent->first;}
};

template<typename key_type, typename val_type>
class dict_values {
private:
    typename std::map<key_type, val_type>::iterator ibegin;
    typename std::map<key_type, val_type>::iterator icurrent;
    typename std::map<key_type, val_type>::iterator iend;
public:
    dict_values(std::map<key_type, val_type>* map) {
        ibegin = map->begin();
        icurrent = map->begin();
        iend = map->end();
    }

    key_type& operator[](int i) const {
        typename std::map<key_type, val_type>::iterator temp = ibegin;
        std:advance(temp, i);
        return temp->second;
    }

    dict_values<key_type, val_type>& begin() {return *this;}
    dict_values<key_type, val_type>& end() {return *this;}

    bool operator==(const dict_values<key_type, val_type>& x) {
        return icurrent == iend;
    }

    bool operator!=(const dict_values<key_type, val_type>& x) {
        return icurrent != iend;
    }

    dict_values<key_type, val_type>& operator++() {
        std::advance(icurrent, 1);
        return *this;
    }

    typename std::map<key_type, val_type>::iterator get_index() {
        return icurrent;
    }

    key_type operator*() const {return icurrent->second;}
};

template<typename val_type>
class dict_proxy {
private:
    val_type* _mem_loc;
public:
    dict_proxy(val_type* mem_loc) {
        _mem_loc = mem_loc;
    }

    void operator=(val_type val) {
        *_mem_loc = val;
    }

    operator val_type() const {
        return *_mem_loc;     
    }
};

template<typename key_type, typename val_type>
class dict {
private:
    std::map<key_type, val_type> map;
public:
    dict() {};

    int len() {
        return map.size();
    }

    void clear() {
        map.clear();
    }

    val_type pop(key_type key) {
        val_type ret = map[key];
        map.erase(key);
        return ret;
    }

    std::pair<val_type, key_type> popitem() {
        auto titr = map.end();
        std::advance(titr, -1);
        key_type key;
        val_type val;
        std::tie(key, val) = *titr;
        map.erase(key);
        return std::make_pair(key, val);
    }

    dict_keys<key_type, val_type> keys() {
        return dict_keys<key_type, val_type>(&map);
    }

    dict_values<key_type, val_type> values() {
        return dict_values<key_type, val_type>(&map);
    }

    typename std::map<key_type, val_type>::iterator get_key_iterator(key_type key) {
        return map.find(key);
    }

    bool is_key(key_type key) {
        return map.count(key) == 1 ? true : false;
    }

    void set(key_type key, val_type val) {
        map[key] = val;
    }

    dict_proxy<val_type> operator[](key_type key) {
        return dict_proxy<val_type>(&map[key]);
    }
};

template<typename val_type>
std::ostream& operator<<(std::ostream& os, const dict_proxy<val_type>& x) {
    return os << val_type(x);
}
/** END DICT OPERATIONS **/


/** MATRIX OPERATIONS **/
template<typename type, class... T>
type* load(T const&... dims) {
    int size = 1;
    using expander = int[];
    (void) expander{0, (void(size *= dims), 0)...};
    auto ptr = (type*) malloc(size*sizeof(type));

    for (int i = 0; i < size; i++) {
        std::cin >> ptr[i];
    }

    return ptr;
}

template<typename type>
type* load_from_vector(std::vector<int> *dims) {
    int size = 1;
    for (auto x : *dims) {
        size *= x;
    }

    auto ptr = (type*) malloc(size*sizeof(type));

    for (int i = 0; i < size; i++) {
        std::cin >> ptr[i];
    }

    return ptr;
}

template<typename type>
std::pair<type*, std::vector<int>> input_load() {
    std::vector<int> dims;
    std::string line;
    int t;
    std::getline(std::cin, line);
    std::stringstream sline(line);
    while (sline >> t) {
        dims.push_back(t);
    }

    return std::make_pair(load_from_vector<type>(&dims), dims);
}

template<typename type>
void transpose_recursive(type* m, type val, int c, int I, int J, std::vector<bool>* transposed, bool first) {
    if (!(*transposed)[c]) {
        int i, j, nc, nval;
        i = c/J;
        j = c-i*J;
        nc = I*j+i;
        nval = *(m+c);

        if (first) {
            transpose_recursive<type>(m, nval, nc, I, J, transposed, false);
        } else {
            *(m+c) = val;
            (*transposed)[c] = true;
            transpose_recursive<type>(m, nval, nc, I, J, transposed, false);
        }
    }
}

template<typename type>
void transpose_inplace(type* m, int I, int J) {
    std::vector<bool> transposed(I*J, false);
    int c, nc;
    type temp;

    for (int i = 0; i < I; i++) {
        for (int j = 0; j < J; j++) {
            c = J*i+j;
            if (!transposed[c]) {
                transpose_recursive<type>(m, temp, c, I, J, &transposed, true);
            }
        }
    }
}

template<typename type>
void reverse_rows_inplace(type* m, int I, int J) {
    for (int i = 0; i < I; i++) {
        for (int j = 0; j < (J+1)/2; j++) {
            std::swap(m[J*i+j], m[J*i+(J-j-1)]);
        }
    }
}

template<typename type>
void rot90_inplace(type* m, int I, int J) {
    transpose_inplace(m, I, J);
    reverse_rows_inplace(m, J, I);
}
/** END MATRIX OPERATIONS **/


/** SHORTHAND MACROS**/
#define get_eps(class) (std::numeric_limits<class>::epsilon())
#define get_min(class) (std::numeric_limits<class>::min())
#define get_max(class) (std::numeric_limits<class>::max())
#define get_nmax(class) (-std::numeric_limits<class>::max())
#define print_debug(...) _print_debug(__LINE__, __VA_ARGS__)
#define FOR(var,a,b) for (int var = a; var < b; var++)
#define FORi(var,arr) for (auto var : arr)
#define dump_array(m) FORi(x,m){std::cout<<x<<" "}; std::cout<<"\b "<<std::endl;
#define dump_matrix(m,I,J) FOR(i,0,I){FOR(j,0,J){std::cout<<m[i*J+j]<<" ";};std::cout<<"\b"<<std::endl;};
#define load_matrix(m, dims, type) type* m;std::vector<type> dims;std::tie(m, dims)=input_load<type>();
/** END SHORTHAND MACROS**/


/** TESTS **/
void test_macros() {
    float epsf = get_eps(float);
    double epsd = get_max(double);
    long double epsld = get_min(long double);
    int eps = get_nmax(int);

}

void debug_tests() {
    println();
    println("|| Debug Tests ||");
    print_debug(1, 2, "test");
    enable_debug_colouring();
    print_debug(1.f, 2.0, "test");
    println("|| End Debug Tests ||");
    println();
}

void matrix_tests() {
    println();
    println("|| Matrix Tests ||");
    printlni("Enter 2D Matrix:");
    load_matrix(m, dims, int);
    printlni("Matrix:");
    dump_matrix(m, dims[0], dims[1]);
    printlni("Matrix Transpose:");
    transpose_inplace<int>(m, dims[0], dims[1]);
    dump_matrix(m, dims[1], dims[0]);
    printlni("Matrix Row Reversal:");
    transpose_inplace<int>(m, dims[1], dims[0]);
    reverse_rows_inplace(m, dims[0], dims[1]);
    dump_matrix(m, dims[0], dims[1]);
    printlni("Matrix Rot90:");
    reverse_rows_inplace(m, dims[0], dims[1]);
    rot90_inplace(m, dims[0], dims[1]);
    dump_matrix(m, dims[1], dims[0]);
    println("|| End Matrix Tests ||");
    println();
}

void dict_tests() {
    println();
    println("|| Dict Tests ||");
    dict<std::string, std::string> tdict;
    printlni("Assigning Key/Value Pairs...");
    tdict["test"] = "hi";
    tdict["test1"] = "hi1";
    tdict["test2"] = "hi2";
    printlni("Print dict[\"test\"]:");
    println(tdict["test"]);
    printlni("Assign To Variable And Print:");
    std::string t = tdict["test"];
    println(t);
    printlni("Get Dict Keys Iterator...");
    auto keys = tdict.keys();
    printlni("Iterating Over Keys:");
    for (auto key : keys) {
        println(key);
    }
    printlni("Get Dict Values Iterator...");
    auto vals = tdict.values();
    printlni("Iterating Over Values:");
    for (auto val : vals) {
        println(val);
    }
    printlni("Pop From Dict With Key:");
    println(tdict.pop("test"));
    printlni("Pop From End Of Dict:");
    auto temp  = tdict.popitem();
    println('(', std::get<0>(temp), ", ", std::get<1>(temp), ")");
    println("|| End Dict Tests ||");
    println();
}

int main() {
    debug_tests();
    matrix_tests();
    dict_tests();
}
/** END TESTS **/