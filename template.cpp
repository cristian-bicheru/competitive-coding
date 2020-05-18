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

// println
template<class... T>
void PLN(T const&... data) {
    using expander = int[];
    (void) expander{0, (void(std::cout << data), 0)...};
    std::cout << std::endl;
}

// printlni
template<class... T>
void PLNI(T const&... data) {
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
void _MTR(type* m, type val, int c, int I, int J, std::vector<bool>* transposed, bool first) {
    if (!(*transposed)[c]) {
        int i, j, nc, nval;
        i = c/J;
        j = c-i*J;
        nc = I*j+i;
        nval = *(m+c);

        if (first) {
            _MTR<type>(m, nval, nc, I, J, transposed, false);
        } else {
            *(m+c) = val;
            (*transposed)[c] = true;
            _MTR<type>(m, nval, nc, I, J, transposed, false);
        }
    }
}

template<typename type>
void MT(type* m, int I, int J) {
    std::vector<bool> transposed(I*J, false);
    int c, nc;
    type temp;

    for (int i = 0; i < I; i++) {
        for (int j = 0; j < J; j++) {
            c = J*i+j;
            if (!transposed[c]) {
                _MTR<type>(m, temp, c, I, J, &transposed, true);
            }
        }
    }
}

template<typename type>
void MREV(type* m, int I, int J) {
    for (int i = 0; i < I; i++) {
        for (int j = 0; j < (J+1)/2; j++) {
            std::swap(m[J*i+j], m[J*i+(J-j-1)]);
        }
    }
}

template<typename type>
void MR90(type* m, int I, int J) {
    MT(m, I, J);
    MREV(m, J, I);
}

template<typename type1, typename type2>
int BFINDT(type1 m, type2 val, int len) {
    int i = len/2;
    type2 temp;

    while (true) {
        temp = m[i];
        if (temp == val) {
            return i;
        } else {
            if (i == 0 || i == len) {
                return -1;
            }
        }

        if (temp > val) {
            i /= 2;
        } else {
            i *= 2;
            if (i >= len) {
                i = len-1;
            }
        }
    }
}
/** END MATRIX OPERATIONS **/


/** SHORTHAND MACROS**/
#define GEPS(class) (std::numeric_limits<class>::epsilon()) // get
#define GMIN(class) (std::numeric_limits<class>::min())     // arbitrary
#define GMAX(class) (std::numeric_limits<class>::max())     // type
#define GNMAX(class) (-std::numeric_limits<class>::max())   // constants
#define PDB(...) _print_debug(__LINE__, __VA_ARGS__)  // print debug
#define FOR(var,a,b) for (int var = a; var < b; var++) // for
#define FORi(var,arr) for (auto var : arr) // for iterator
#define DA(m) FORi(x,m){std::cout<<x<<" "}; std::cout<<"\b "<<std::endl; // dump array
#define DM(m,I,J) FOR(i,0,I){FOR(j,0,J){std::cout<<m[i*J+j]<<" ";};std::cout<<"\b"<<std::endl;}; // dump matrix
#define LM(m, dims, type) type* m;std::vector<type> dims;std::tie(m, dims)=input_load<type>(); // load matrix
#define SV(v) std::sort(v.begin(), v.end()) // sort vector
#define RSV(v) std::sort(v.rbegin(), v.rend()) // sort vector in reverse order
#define MAX(x, y) ((x) >= (y) ? (x) : (y))
#define MIN(x, y) ((x) <= (y) ? (x) : (y))
#define SWAP(x, y) (std::swap(x, y))
#define PB push_back
#define MP std::make_pair
#define vi std::vector<int>
#define vc std::vector<char>
#define pi std::pair<int, int>
#define ll long long
#define f float
#define d double
#define ld long double
#define u uint64_t
#define CPI ld(3.14159265358979323846264338)
#define CE ld(2.71828182845904523536028747)
#define FIND(vec, val) (std::find(vec.begin(), vec.end(), val)-vec.begin())
#define BFIND(vec, val) (BFINDT<decltype(vec), decltype(val)>(vec, val, vec.size()))
/** END SHORTHAND MACROS**/


/** TESTS **/
void test_macros() {
    f epsf = GEPS(f);
    d epsd = GMAX(d);
    ld epsld = GMIN(ld);
    int eps = GNMAX(int);
}

void debug_tests() {
    PLN();
    PLN("|| Debug Tests ||");
    PDB(1, 2, "test");
    enable_debug_colouring();
    PDB(1.f, 2.0, "test");
    PLN("|| End Debug Tests ||");
    PLN();
}

void matrix_tests() {
    PLN();
    PLN("|| Matrix Tests ||");
    PLN("Enter 2D Matrix:");
    LM(m, dims, int);
    PLNI("Matrix:");
    DM(m, dims[0], dims[1]);
    PLNI("Matrix Transpose:");
    MT<int>(m, dims[0], dims[1]);
    DM(m, dims[1], dims[0]);
    PLNI("Matrix Row Reversal:");
    MT<int>(m, dims[1], dims[0]);
    MREV(m, dims[0], dims[1]);
    DM(m, dims[0], dims[1]);
    PLNI("Matrix Rot90:");
    MREV(m, dims[0], dims[1]);
    MR90(m, dims[0], dims[1]);
    DM(m, dims[1], dims[0]);
    PLN("|| End Matrix Tests ||");
    PLN();
}

void vector_tests() {
    PLN();
    PLN("|| Vector Tests ||");
    vi test_vec;
    FOR(i, 0, 10) {
        test_vec.PB(i);
    }
    SV(test_vec);
    PLN(FIND(test_vec, 4));
    PLN(BFIND(test_vec, 4));
    PLN("|| End Vector Tests ||");
    PLN();
}

void dict_tests() {
    PLN();
    PLN("|| Dict Tests ||");
    dict<std::string, std::string> tdict;
    PLNI("Assigning Key/Value Pairs...");
    tdict["test"] = "hi";
    tdict["test1"] = "hi1";
    tdict["test2"] = "hi2";
    PLNI("Print dict[\"test\"]:");
    PLN(tdict["test"]);
    PLNI("Assign To Variable And Print:");
    std::string t = tdict["test"];
    PLN(t);
    PLNI("Get Dict Keys Iterator...");
    auto keys = tdict.keys();
    PLNI("Iterating Over Keys:");
    for (auto key : keys) {
        PLN(key);
    }
    PLNI("Get Dict Values Iterator...");
    auto vals = tdict.values();
    PLNI("Iterating Over Values:");
    for (auto val : vals) {
        PLN(val);
    }
    PLNI("Pop From Dict With Key:");
    PLN(tdict.pop("test"));
    PLNI("Pop From End Of Dict:");
    auto temp  = tdict.popitem();
    PLN('(', std::get<0>(temp), ", ", std::get<1>(temp), ")");
    PLN("|| End Dict Tests ||");
    PLN();
}

int main() {
    debug_tests();
    matrix_tests();
    dict_tests();
    vector_tests();
}
/** END TESTS **/