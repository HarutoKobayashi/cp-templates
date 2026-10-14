// --- BEGIN SOURCE: https://github.com/HarutoKobayashi/cp-templates/cpp/all-in-one.cpp ---
#ifdef DEFINED_ONLY_IN_LOCAL
#include <atcoder/modint>
#include <cpp-dump/cpp-dump.hpp>
namespace cpp_dump::_detail {
template <int m>
inline std::string
export_var(const atcoder::static_modint<m> &mint, const std::string &indent,
           std::size_t last_line_length, std::size_t current_depth,
           bool fail_on_newline, const export_command &command) {
    return export_var(mint.val(), indent, last_line_length, current_depth,
                      fail_on_newline, command);
}
template <int m>
inline std::string
export_var(const atcoder::dynamic_modint<m> &mint, const std::string &indent,
           std::size_t last_line_length, std::size_t current_depth,
           bool fail_on_newline, const export_command &command) {
    return export_var(mint.val(), indent, last_line_length, current_depth,
                      fail_on_newline, command);
}
} // namespace cpp_dump::_detail
#define debug(...) cpp_dump(__VA_ARGS__)
namespace cp = cpp_dump;
CPP_DUMP_SET_OPTION_GLOBAL(max_line_width, 80);
CPP_DUMP_SET_OPTION_GLOBAL(log_label_func, cp::log_label::filename());
CPP_DUMP_SET_OPTION_GLOBAL(enable_asterisk, true);
#else
#define debug(...)
#define CPP_DUMP_SET_OPTION(...)
#define CPP_DUMP_SET_OPTION_GLOBAL(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT(...)
#define CPP_DUMP_DEFINE_EXPORT_ENUM(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT_GENERIC(...)
#endif

#include <atcoder/all>
#include <bits/stdc++.h>
#include <cassert>

using namespace std;

// def
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define elif else if
#define ll long long
#define pb push_back
#define mp make_pair
#define LARGE_PRIME 999999999999999023ll
#define el '\n'
constexpr ll inf = 2e18;

// range
template <int MOD>
istream &operator>>(istream &is, atcoder::static_modint<MOD> &x) {
    long long v;
    is >> v;
    x = v;
    return is;
}
template <int MOD>
ostream &operator<<(ostream &os, const atcoder::static_modint<MOD> &x) {
    return os << x.val();
}
template <int id>
istream &operator>>(istream &is, atcoder::dynamic_modint<id> &x) {
    long long v;
    is >> v;
    x = v;
    return is;
}
template <int id>
ostream &operator<<(ostream &os, const atcoder::dynamic_modint<id> &x) {
    return os << x.val();
}

template <class T> auto range_arg(T x) {
    if constexpr (requires { x.val(); }) {
        return static_cast<int>(x.val());
    } else if constexpr (std::unsigned_integral<T> && !std::same_as<T, bool>) {
        return static_cast<std::make_signed_t<T>>(x);
    } else {
        return x;
    }
}

template <class T> struct Range {
    struct I {
        T x;
        T s;
        T operator*() const { return x; }
        bool operator!=(const I &r) const { return s > 0 ? x < r.x : x > r.x; }
        I &operator++() {
            x += s;
            return *this;
        }
    };
    T l;
    T r;
    T s;
    I begin() const { return {l, s}; }
    I end() const { return {r, s}; }
};
template <class A> auto range(A r) {
    auto rr = range_arg(r);
    using T = common_type_t<decltype(rr), int>;
    return Range<T>{0, rr, 1};
}
template <class A, class B> auto range(A l, B r) {
    auto left = range_arg(l);
    auto right = range_arg(r);
    using T = common_type_t<decltype(left), decltype(right), int>;
    return Range<T>{left, right, 1};
}
template <class A, class B, class C> auto range(A l, B r, C s) {
    auto left = range_arg(l);
    auto right = range_arg(r);
    auto ss = range_arg(s);
    using T = common_type_t<decltype(left), decltype(right), decltype(ss)>;
    assert(ss != 0);
    return Range<T>{left, right, ss};
}

template <class C> constexpr int len(const C &c) {
    return static_cast<int>(std::size(c));
}

template <class T>
concept StringLike = same_as<remove_cvref_t<T>, string> ||
                     same_as<remove_cvref_t<T>, string_view> ||
                     is_convertible_v<T, const char *>;

template <class T>
concept PrintableRange = ranges::range<T> && (!StringLike<T>);
template <class T> void print_one(const T &x) { cout << x; }
template <class T> void print_arg(const T &x, bool &first) {
    if constexpr (PrintableRange<T>) {
        for (const auto &e : x) {
            if (!first)
                cout << ' ';
            first = false;
            print_one(e);
        }
    } else {
        if (!first)
            cout << ' ';
        first = false;
        print_one(x);
    }
}
template <class T, class U> void print_arg(const pair<T, U> &p, bool &first) {
    print_arg(p.first, first);
    print_arg(p.second, first);
}
template <class... Args> void print(const Args &...args) {
    bool first = true;
    (print_arg(args, first), ...);
    cout << '\n';
}

#define kill(...)                                                              \
    do {                                                                       \
        print(__VA_ARGS__);                                                    \
        return 0;                                                              \
    } while (0)

// bisect
template <class T> int bisect_left(const vector<T> &a, const T &x) {
    return lower_bound(all(a), x) - a.begin();
}
template <class T> int bisect_right(const vector<T> &a, const T &x) {
    return upper_bound(all(a), x) - a.begin();
}

// math
/**
 * @see https://trap.jp/post/2728/
 */
unsigned long long isqrt_aux(int c, unsigned long long n) {
    if (c == 0) {
        return 1;
    } else {
        int k = (c - 1) / 2;
        unsigned long long a = isqrt_aux(c / 2, n >> (2 * k + 2));
        return (a << k) + (n >> (k + 2)) / a;
    }
}
/**
 * @see https://trap.jp/post/2728/
 */
ll isqrt(unsigned long long n) {
    if (n == 0) {
        return 0;
    } else {
        unsigned long long a = isqrt_aux((63 - __builtin_clzll(n)) / 2, n);
        return n <= a * a - 1 ? a - 1 : a;
    }
}
ll capped_lcm(ll a, ll b, ll Y = inf) {
    if (a == 0 or b == 0) {
        return 0ll;
    }
    assert(a >= 0 and b >= 0);
    if (a >= Y)
        return Y;

    ll g = std::gcd(a, b);

    __int128 x = (__int128)(a / g) * b;

    if (x >= Y)
        return Y;
    return (ll)x;
}

ll cdiv(ll a, ll b) {
    ll q = a / b;
    if (a % b != 0 && ((a < 0) == (b < 0)))
        ++q;
    return q;
}
// power
template <class T> struct is_modint : false_type {};
template <int m> struct is_modint<atcoder::static_modint<m>> : true_type {};
template <int id> struct is_modint<atcoder::dynamic_modint<id>> : true_type {};
template <class T>
inline constexpr bool is_modint_v = is_modint<remove_cvref_t<T>>::value;
template <class T> ll integer_value(T x) {
    if constexpr (is_modint_v<T>) {
        return x.val();
    } else {
        return static_cast<ll>(x);
    }
}
template <class A, class N> ll power(A a, N n) {
    ll e0 = integer_value(n);

    if constexpr (is_modint_v<A>) {
        if (e0 < 0) {
            a = a.inv();
        }
        unsigned long long e = e0 < 0
                                   ? 0ULL - static_cast<unsigned long long>(e0)
                                   : static_cast<unsigned long long>(e0);
        A res = 1;
        while (e > 0) {
            if (e & 1) {
                res *= a;
            }

            a *= a;
            e >>= 1;
        }
        return res.val();
    } else {
        ll x = integer_value(a);
        assert(e0 >= 0);
        unsigned long long e = e0;
        ll res = 1;
        while (e > 0) {
            if (e & 1) {
                res *= x;
            }
            x *= x;
            e >>= 1;
        }
        return res;
    }
}
template <class A, class N, class M> ll power(A a_, N n_, M mod_) {
    ll a = integer_value(a_);
    ll n = integer_value(n_);
    ll mod = integer_value(mod_);

    assert(mod > 0);
    return atcoder::pow_mod(a, n, mod);
}

// max, min, sum
template <std::ranges::input_range R, class Key = std::identity>
auto amax(R &&r, Key key = {}) {
    using V = std::ranges::range_value_t<R>;
    auto it = std::ranges::begin(r);
    const auto last = std::ranges::end(r);
    if (it == last) {
        throw std::invalid_argument("amax() arg is an empty range");
    }
    V best = *it;
    using K = std::remove_cvref_t<std::invoke_result_t<Key &, decltype(*it)>>;
    K best_key = std::invoke(key, *it);
    for (++it; it != last; ++it) {
        K k = std::invoke(key, *it);

        if (best_key < k) {
            best = *it;
            best_key = std::move(k);
        }
    }
    return best;
}
template <std::ranges::input_range R, class Key = std::identity>
auto amin(R &&r, Key key = {}) {
    using V = std::ranges::range_value_t<R>;
    auto it = std::ranges::begin(r);
    const auto last = std::ranges::end(r);
    if (it == last) {
        throw std::invalid_argument("amin() arg is an empty range");
    }
    V best = *it;
    using K = std::remove_cvref_t<std::invoke_result_t<Key &, decltype(*it)>>;
    K best_key = std::invoke(key, *it);
    for (++it; it != last; ++it) {
        K k = std::invoke(key, *it);
        if (k < best_key) {
            best = *it;
            best_key = std::move(k);
        }
    }
    return best;
}
template <std::ranges::input_range R, class Init = int>
auto asum(R &&r, Init init = {}) {
    using V = std::ranges::range_value_t<R>;
    using T = std::common_type_t<V, Init>;
    T ans = static_cast<T>(init);
    for (auto &&x : r)
        ans += x;
    return ans;
}

// string
char lower(char c) { return char(tolower((unsigned char)c)); }
string lower(string s) {
    for (char &c : s) {
        c = lower(c);
    }
    return s;
}
char upper(char c) { return char(toupper((unsigned char)c)); }
string upper(string s) {
    for (char &c : s) {
        c = upper(c);
    }
    return s;
}
/**
 * @brief 数字文字を対応する整数値に変換する。
 *
 * 例: '0' -> 0, '9' -> 9
 *
 * @param c 数字文字。
 * @return c - '0'。
 */
int ctoi(char c) { return c - '0'; }
int ord(char c) { return static_cast<unsigned char>(c); }
char chr(int x) { return static_cast<char>(x); }

// io
void setup() {
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    cout << fixed << setprecision(15);
}
template <class T> void getvec(vector<T> &n) {
    for (int i = 0; i < int(n.size()); i++)
        cin >> n[i];
}
template <class T, class K> void getvec(vector<T> &n, vector<K> &m) {
    for (int i = 0; i < int(n.size()); i++)
        cin >> n[i] >> m[i];
}
template <class... Ts> void read(Ts &...xs) { (cin >> ... >> xs); }
#define getints(...)                                                           \
    ll __VA_ARGS__;                                                            \
    read(__VA_ARGS__)

/**
 * @brief 非負の剰余を返す。
 * @pre m > 0
 */
template <class T> T mod(T a, T m) {
    T r = a % m;

    if (r < 0)
        r += m;

    return r;
}

// python-like deque
template <class T, class Allocator = std::allocator<T>>
class dq : public std::deque<T, Allocator> {
    using Base = std::deque<T, Allocator>;

  public:
    using Base::Base;

    void append(const T &x) { this->push_back(x); }
    void append(T &&x) { this->push_back(std::move(x)); }
    void appendleft(const T &x) { this->push_front(x); }
    void appendleft(T &&x) { this->push_front(std::move(x)); }

    T pop_back() {
        if (this->empty()) {
            throw std::out_of_range("mydeque::pop_back(): empty deque");
        }

        T value = std::move(this->back());
        Base::pop_back();

        return value;
    }

    T pop_front() {
        if (this->empty()) {
            throw std::out_of_range("mydeque::pop_front(): empty deque");
        }

        T value = std::move(this->front());
        Base::pop_front();

        return value;
    }
    T pop() { return pop_back(); }
    T popleft() { return pop_front(); }
};

template <class Container> auto to_vector(const Container &c) {
    using T = typename Container::value_type;
    return vector<T>(c.begin(), c.end());
}
// bit
template <class T> int bit_count(T x) {
    static_assert(std::is_integral_v<T>);
    static_assert(!std::is_same_v<std::remove_cv_t<T>, bool>);
    using U = std::make_unsigned_t<T>;
    U u;
    if constexpr (std::is_signed_v<T>) {
        u = (x < 0) ? U(0) - static_cast<U>(x) : static_cast<U>(x);
    } else {
        u = x;
    }
    return std::popcount(u);
}
template <class T> int bit_length(T x) {
    static_assert(std::is_integral_v<T>);
    using U = std::make_unsigned_t<T>;

    U u = static_cast<U>(x);
    if constexpr (std::is_signed_v<T>) {
        if (x < 0)
            u = U(0) - u;
    }

    int res = 0;
    while (u) {
        ++res;
        u >>= 1;
    }
    return res;
}

// combinations
using mint = atcoder::modint;
template <class mint> struct Comb {
    vector<mint> fac;
    vector<mint> finv;
    Comb(int n) : fac(n + 1), finv(n + 1) {
        fac[0] = 1;
        for (int i = 1; i <= n; i++) {
            fac[i] = fac[i - 1] * i;
        }
        finv[n] = fac[n].inv();
        for (int i = n; i >= 1; i--) {
            finv[i - 1] = finv[i] * i;
        }
    }
    mint factorial(int n) const { return fac[n]; }
    mint inv_factorial(int n) const { return finv[n]; }
    mint inv(int n) const {
        assert(n >= 1);
        return fac[n - 1] * finv[n];
    }
    mint comb(int n, int r) const {
        if (r < 0 || r > n)
            return 0;
        return fac[n] * finv[r] * finv[n - r];
    }
    mint perm(int n, int r) const {
        if (r < 0 || r > n)
            return 0;
        return fac[n] * finv[n - r];
    }
};

using i128 = __int128;
using ull = uint64_t;
using u128 = __uint128_t;

vector<ll> all_primes_le_(ll limit) {

    if (limit < 2)
        return {};
    if (limit == 2)
        return {2};

    size_t n_odds = static_cast<size_t>((limit - 3) / 2 + 1);
    vector<unsigned char> sieve(n_odds, 1);

    ll r = static_cast<ll>(isqrt(static_cast<unsigned long long>(limit)));

    if (r >= 3) {
        size_t last_i_to_check = static_cast<size_t>((r - 3) / 2);

        for (size_t i = 0; i <= last_i_to_check; ++i) {
            if (!sieve[i])
                continue;

            ll p = 2 * static_cast<ll>(i) + 3;
            size_t start = static_cast<size_t>((p * p - 3) / 2);

            for (size_t j = start; j < n_odds; j += static_cast<size_t>(p)) {
                sieve[j] = 0;
            }
        }
    }

    vector<ll> primes;
    primes.push_back(2);

    for (size_t i = 0; i < n_odds; ++i) {
        if (sieve[i]) {
            primes.push_back(2 * static_cast<ll>(i) + 3);
        }
    }

    return primes;
}

vector<ll> all_primes_in_(ll L, ll R) {

    if (R <= 2)
        return {};

    if (L < 0) {
        throw invalid_argument("L must be non-negative.");
    }

    if (L >= R)
        return {};

    size_t n = static_cast<size_t>(R - L);
    vector<unsigned char> is_prime(n, 1);

    if (L == 0) {
        if (n >= 1)
            is_prime[0] = 0;
        if (n >= 2)
            is_prime[1] = 0;
    } else if (L == 1) {
        is_prime[0] = 0;
    }

    ll limit = static_cast<ll>(isqrt(static_cast<unsigned long long>(R - 1)));

    auto base_primes = all_primes_le_(limit);

    for (ll p : base_primes) {
        ll pp = p * p;

        if (pp >= R)
            break;

        ll start = ((L + p - 1) / p) * p;
        if (start < pp)
            start = pp;

        for (ll x = start; x < R; x += p) {
            is_prime[static_cast<size_t>(x - L)] = 0;
        }
    }

    vector<ll> primes;

    for (size_t i = 0; i < n; ++i) {
        if (is_prime[i]) {
            primes.push_back(L + static_cast<ll>(i));
        }
    }

    return primes;
}

struct PrimeTools {
    static PrimeTools setup_primes() {
        return PrimeTools(all_primes_le_(10000));
    }

    /**
     * @brief n の素因数を重複ありで全列挙する。
     *
     * 例:
     * 20 -> [2, 2, 5]
     */
    vector<ll> factorize(ll n) const {
        vector<ll> out;
        factorize_impl(n, out);
        sort(all(out));
        return out;
    }

    vector<ll> &factorize(ll n, vector<ll> &out) const {
        factorize_impl(n, out);
        sort(out.begin(), out.end());
        return out;
    }

    /**
     * @brief n の素因数分解を {素数: 指数} 形式で返す。
     *
     * 例:
     * 20 -> {{2, 2}, {5, 1}}
     */
    map<ll, int> pf(ll n) const {
        auto fs = factorize(n);

        sort(fs.begin(), fs.end());

        map<ll, int> res;

        for (ll p : fs) {
            ++res[p];
        }

        return res;
    }

    /**
     * @brief 素因数分解から約数を全列挙する。
     *
     * 例:
     * {{2, 2}, {5, 1}}
     * ->
     * [1, 2, 4, 5, 10, 20]
     */
    vector<ll> divisors_from_pf(const map<ll, int> &pf,
                                bool need_sort = true) const {
        vector<ll> divs = {1};

        for (auto [p, a] : pf) {
            vector<ll> base = divs;

            ll mul = 1;

            for (int e = 0; e < a; ++e) {
                mul *= p;

                for (ll d : base) {
                    divs.push_back(d * mul);
                }
            }
        }

        if (need_sort) {
            sort(divs.begin(), divs.end());
        }

        return divs;
    }

  private:
    vector<ll> small_primes_;

    // Miller-Rabin
    static constexpr array<ll, 7> MR_BASES = {
        2LL, 325LL, 9375LL, 28178LL, 450775LL, 9780504LL, 1795265022LL,
    };

    // Pollard-Rho
    static constexpr array<pair<ll, ll>, 10> PR_SEEDS = {{
        {2, 1},
        {2, 3},
        {2, 5},
        {2, 7},
        {2, 11},
        {3, 1},
        {5, 1},
        {7, 1},
        {11, 1},
        {13, 1},
    }};

    explicit PrimeTools(vector<ll> small_primes)
        : small_primes_(std::move(small_primes)) {}
    static ll mul_mod(ll a, ll b, ll m) {
        return static_cast<ll>(static_cast<i128>(a) * b % m);
    }
    static ll pow_mod(ll a, ll e, ll m) {
        ll res = 1 % m;
        a %= m;
        while (e > 0) {
            if (e & 1) {
                res = mul_mod(res, a, m);
            }
            a = mul_mod(a, a, m);
            e >>= 1;
        }
        return res;
    }
    // Miller-Rabin
    bool is_prime_64(ll n) const {
        if (n < 2) {
            return false;
        }
        for (int i = 0; i < 12; ++i) {
            ll p = small_primes_[i];
            if (n % p == 0) {
                return n == p;
            }
        }
        ll d = n - 1;
        int s = 0;
        while (d % 2 == 0) {
            d /= 2;
            ++s;
        }
        for (ll a : MR_BASES) {
            if (a % n == 0) {
                return true;
            }
            ll x = pow_mod(a, d, n);
            if (x == 1 || x == n - 1) {
                continue;
            }
            bool passed = false;
            for (int i = 0; i < s - 1; ++i) {
                x = mul_mod(x, x, n);
                if (x == n - 1) {
                    passed = true;
                    break;
                }
            }
            if (!passed) {
                return false;
            }
        }
        return true;
    }
    static ll f_brent(ll x, ll c, ll m) { return (mul_mod(x, x, m) + c) % m; }
    ll pollard_rho_brent(ll n) const {
        if (n % 2 == 0) {
            return 2;
        }
        if (n % 3 == 0) {
            return 3;
        }
        for (auto [x0, c] : PR_SEEDS) {
            ll y = x0;
            ll r = 1;
            ll q = 1;
            ll g = 1;
            ll x = 0;
            ll ys = 0;
            while (g == 1) {
                x = y;
                for (ll i = 0; i < r; ++i) {
                    y = f_brent(y, c, n);
                }
                ll k = 0;
                while (k < r && g == 1) {
                    ys = y;
                    constexpr ll M = 128;
                    ll cnt = min(M, r - k);
                    for (ll i = 0; i < cnt; ++i) {
                        y = f_brent(y, c, n);
                        q = mul_mod(q, mod(x - y, n), n);
                    }
                    g = gcd(q, n);
                    k += M;
                }
                r <<= 1;
            }
            if (g == n) {
                g = 1;
                while (g == 1) {
                    ys = f_brent(ys, c, n);
                    g = gcd(abs(x - ys), n);
                }
            }
            if (1 < g && g < n) {
                return g;
            }
        }
        ll i = 5;
        while (i <= n / i) {
            if (n % i == 0) {
                return i;
            }
            if (n % (i + 2) == 0) {
                return i + 2;
            }
            i += 6;
        }
        return n;
    }
    void factorize_impl(ll n, vector<ll> &out) const {
        if (n < 0) {
            out.push_back(-1);
            n = -n;
        }
        if (n == 0 || n == 1) {
            return;
        }
        for (ll p : small_primes_) {
            if (p > n / p) {
                break;
            }
            if (n % p == 0) {
                while (n % p == 0) {
                    n /= p;
                    out.push_back(p);
                }
            }
        }
        if (n == 1) {
            return;
        }
        if (is_prime_64(n)) {
            out.push_back(n);
            return;
        }
        ll d = pollard_rho_brent(n);
        if (d == n) {
            out.push_back(n);
        } else {
            factorize_impl(d, out);
            factorize_impl(n / d, out);
        }
    }
};
template <class T, T (*op)(T, T)> struct SparseTable {
    int n;
    vector<int> lg;
    vector<vector<T>> st;

    SparseTable(const vector<T> &a) : n(a.size()) {
        lg.resize(n + 1);
        for (int i = 2; i <= n; ++i) {
            lg[i] = lg[i >> 1] + 1;
        }

        int K = lg[n] + 1;
        st.resize(K);
        st[0] = a;

        for (int k = 1; k < K; ++k) {
            st[k].resize(n - (1 << k) + 1);
            for (int i = 0; i + (1 << k) <= n; ++i) {
                st[k][i] = op(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    T query(int l, int r) const {
        int k = lg[r - l];
        return op(st[k][l], st[k][r - (1 << k)]);
    }
};
// tour
/** @brief 木の DFS 行きがけ順（preorder）と、各部分木に対応する区間を求める。
 * Returns:
 * order : 行きがけ順に並べた頂点番号
 * tin   : tin[v] は order 中での v の位置
 * tout  : v の部分木は order[tin[v]:tout[v]] に対応
 * par   : v の親。root の親は -1
 * dep   : root からの深さ
 * size  : v を根とする部分木の頂点数
 * Complexity: O(n)
 **/
tuple<vector<int>, vector<int>, vector<int>, vector<int>, vector<int>,
      vector<int>>
euler_tour(ll n, const vector<vector<ll>> &graph, int root = 0) {
    vector<int> par(n, -1);
    vector<int> dep(n, 0);
    vector<int> order;
    order.reserve(n);

    vector<int> st = {root};

    while (!st.empty()) {
        int v = st.back();
        st.pop_back();

        order.push_back(v);
        int p = par[v];

        for (int u : graph[v]) {
            if (u == p)
                continue;

            par[u] = v;
            dep[u] = dep[v] + 1;
            st.push_back(u);
        }
    }

    vector<int> tin(n);
    for (int i = 0; i < n; ++i) {
        tin[order[i]] = i;
    }

    vector<int> size(n, 1);
    for (auto it = order.rbegin(); it != order.rend(); ++it) {
        int v = *it;
        if (par[v] >= 0) {
            size[par[v]] += size[v];
        }
    }

    vector<int> tout(n);
    for (int v = 0; v < n; ++v) {
        tout[v] = tin[v] + size[v];
    }

    return {order, tin, tout, par, dep, size};
}
/** LCA 用の長さ 2n-1 の Euler Tour を作る。
 * Returns:
 * tour  : Euler Tour の頂点列。長さ 2n-1
 * first : first[v] は tour 中に v が最初に現れる位置
 * dep   : root からの深さ
 * Complexity: O(n)
 **/
tuple<vector<int>, vector<int>, vector<int>>
euler_tour_lca(int n, const vector<vector<int>> &graph, int root = 0) {
    vector<int> par(n, -1);
    vector<int> dep(n, 0);
    vector<int> first(n);

    vector<int> tour;
    tour.reserve(2 * n - 1);

    vector<int> st = {root};

    while (!st.empty()) {
        int v = st.back();
        st.pop_back();

        if (v >= 0) {
            first[v] = (int)tour.size();
            tour.push_back(v);

            int p = par[v];

            for (auto it = graph[v].rbegin(); it != graph[v].rend(); ++it) {
                int u = *it;
                if (u == p)
                    continue;

                par[u] = v;
                dep[u] = dep[v] + 1;

                st.push_back(~v);
                st.push_back(u);
            }
        } else {
            tour.push_back(~v);
        }
    }

    return {tour, first, dep};
}

// grid utils
vector<pair<int, int>> move4 = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
};
vector<pair<int, int>> move8 = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
};
struct Edge {
    int to;
    long long cost;
};

// heap
namespace heapq {
namespace detail {
template <class T> void siftdown(vector<T> &h, int start, int pos) {
    T x = std::move(h[pos]);

    while (pos > start) {
        int par = (pos - 1) / 2;

        if (!(x < h[par]))
            break;

        h[pos] = std::move(h[par]);
        pos = par;
    }

    h[pos] = std::move(x);
}

template <class T> void siftup(vector<T> &h, int pos) {
    int n = (int)h.size();
    int start = pos;

    T x = std::move(h[pos]);

    int child = 2 * pos + 1;

    while (child < n) {
        int right = child + 1;

        // 小さい方の子を選ぶ
        if (right < n && !(h[child] < h[right])) {
            child = right;
        }

        h[pos] = std::move(h[child]);
        pos = child;
        child = 2 * pos + 1;
    }

    h[pos] = std::move(x);
    siftdown(h, start, pos);
}

} // namespace detail
template <class T> void heapify(vector<T> &h) {
    for (int i = (int)h.size() / 2 - 1; i >= 0; --i) {
        detail::siftup(h, i);
    }
}
template <class T> void heappush(vector<T> &h, T x) {
    h.push_back(std::move(x));
    detail::siftdown(h, 0, (int)h.size() - 1);
}
template <class T> T heappop(vector<T> &h) {
    if (h.empty()) {
        throw out_of_range("heappop from empty heap");
    }
    T last = std::move(h.back());
    h.pop_back();
    if (h.empty()) {
        return last;
    }
    T res = std::move(h[0]);
    h[0] = std::move(last);
    detail::siftup(h, 0);
    return res;
}

} // namespace heapq
using namespace heapq;

// dijkstra
vector<ll> dijkstra(ll start, const vector<vector<array<ll, 2>>> &graph) {
    vector<ll> dist(graph.size(), inf);
    dist[start] = 0;
    vector<bool> finished(graph.size(), false);

    vector<array<ll, 2>> q;
    heappush(q, {0, start});
    while (not q.empty()) {
        auto [_, cur] = heappop(q);
        if (finished[cur]) {
            continue;
        }

        finished[cur] = true;
        for (auto [nex, cost] : graph[cur]) {
            if (dist[cur] + cost < dist[nex]) {
                dist[nex] = dist[cur] + cost;
                heappush(q, {dist[nex], nex});
            }
        }
    }

    return dist;
}
vector<vector<ll>> warshall_floyd(ll N,
                                  const vector<vector<array<ll, 2>>> &graph) {
    vector<vector<ll>> dist(N, vector<ll>(N, inf));

    for (int i : range(N))
        dist[i][i] = 0;
    for (int u : range(N))
        for (auto [v, cost] : graph[u])
            if (cost < dist[u][v])
                dist[u][v] = cost;

    for (int k : range(N))
        for (int i : range(N)) {
            auto dik = dist[i][k];
            if (dik == inf)
                continue;
            for (int j : range(N)) {
                if (dist[k][j] < inf) {
                    auto nd = dik + dist[k][j];
                    if (nd < dist[i][j])
                        dist[i][j] = nd;
                }
            }
        }
    return dist;
}

// struct Node {
//     map<ll, ll> nexts;
//     vector<ll> end_here;
//     ll node_idx;
// };

using std::views::keys;
using std::views::values;

mt19937_64 rng(random_device{}());
ll randint(ll l, ll r) { return uniform_int_distribution<ll>(l, r)(rng); }

/** @brief ax + by = gcd(a, b) を満たす x, y を求める。 O(ln max(|a|, |b|))
 * * a, b >= 0 かつ (a, b) != (0, 0)
 * * |a|, |b| <= 10^18 ならば、|x|, |y| <= 10^18 となる。
 **/
ll extgcd(ll a, ll b, ll &x, ll &y) {
    assert(a >= 0 and b >= 0);
    assert(not(a == 0 and b == 0));
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    ll g = extgcd(b, a % b, y, x);
    y -= (a / b) * x;

    return g;
}

/** @brief potential付き union-find.
 * Args:
 * op: ポテンシャルを合成する関数。e.g., op(a,b) = a + b
 * inv: ポテンシャルの向きを反転する関数。e.g., inv(a) = -a
 * id: 単位元。e.g., id = 0;
 * **/
template <typename T> class potentialized_unionfind {
    // Copyright (c) 2024 0214sh7
    // https://github.com/0214sh7/library/
  private:
    std::vector<int> par, rank, size_;
    std::vector<T> pot;

    std::function<T(T, T)> op_;
    std::function<T(T)> inv_;
    T id_;

  public:
    void init(int N, std::function<T(T, T)> op, std::function<T(T)> inv, T id) {
        op_ = op;
        inv_ = inv;
        id_ = id;
        par.assign(N, 0);
        rank.assign(N, 0);
        size_.assign(N, 1);
        pot.assign(N, id);
        for (int i = 0; i < N; i++) {
            par[i] = i;
        }
    }

    potentialized_unionfind(int N, std::function<T(T, T)> op,
                            std::function<T(T)> inv, T id) {
        init(N, op, inv, id);
    }

    int leader(int k) {
        if (par[k] == k) {
            return k;
        }
        int r = leader(par[k]);
        pot[k] = op_(pot[par[k]], pot[k]);
        par[k] = r;
        return par[k];
    }

    bool same(int p, int q) { return leader(p) == leader(q); }

    int size(int k) { return size_[leader(k)]; }

    /** @brief pot(Q) - pot(P) = d
     * とできる（か、既になっている）のであれば merge し、true を返す
     **/
    bool merge(int p, int q, T d) {
        // pot(Q)-pot(P)=dを満たす
        d = op_(potential(p), d);
        d = op_(d, inv_(potential(q)));
        p = leader(p);
        q = leader(q);
        if (p == q) {
            T X = diff(p, q);
            return (d == X);
        }
        if (rank[p] < rank[q]) {
            std::swap(p, q);
            d = inv_(d);
        }
        par[q] = p;
        if (rank[p] == rank[q])
            rank[p]++;
        size_[p] += size_[q];
        size_[q] = 0;
        pot[q] = d;
        return true;
    }

    T potential(int k) {
        leader(k);
        return pot[k];
    }

    T diff(int p, int q) { return op_(inv_(potential(p)), potential(q)); }
};
/**
 * @brief カルテシアンツリー
 * @tparam T 値の型
 * @tparam Compare 優先順位を定める比較関数（デフォルトは less<T>）
 *
 * @param a 元の配列
 *
 * Members:
 * par[i] : 頂点 i の親
 * l[i]   : 頂点 i の左の子
 * r[i]   : 頂点 i の右の子
 * root   : 根の頂点番号
 *
 * 存在しない頂点番号は -1 とする。
 * 空配列の場合、root = -1 となる。
 * 同値の場合は添字の小さい頂点を優先する。
 *
 * @note 頂点番号は元の配列の添字に対応する。
 */
template <class T, class Compare = less<T>> struct CartesianTree {
    int n, root;
    vector<int> par, l, r;

    CartesianTree(const vector<T> &a)
        : n(a.size()), root(-1), par(n, -1), l(n, -1), r(n, -1) {

        Compare cmp;
        vector<int> st;

        for (int i = 0; i < n; i++) {
            int last = -1;

            while (!st.empty() && cmp(a[i], a[st.back()])) {
                last = st.back();
                st.pop_back();
            }

            if (!st.empty()) {
                par[i] = st.back();
                r[st.back()] = i;
            }

            if (last != -1) {
                par[last] = i;
                l[i] = last;
            }

            st.push_back(i);
        }

        if (!st.empty())
            root = st.front();
    }
};

bool chmin(auto &a, const auto &b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}
bool chmax(auto &a, const auto &b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

namespace rolling_hash {

using ull = uint64_t;
using u128 = __uint128_t;

constexpr ull MOD = (1ULL << 61) - 1;

/**
 * @brief a + b mod MOD を返す。
 *
 * @pre 0 <= a, b < MOD
 */
ull add(ull a, ull b) {
    ull res = a + b;
    if (res >= MOD)
        res -= MOD;
    return res;
}

/**
 * @brief a - b mod MOD を返す。
 *
 * @pre 0 <= a, b < MOD
 */
ull sub(ull a, ull b) {
    if (a >= b)
        return a - b;
    return a + MOD - b;
}

/**
 * @brief a * b mod MOD を返す。
 */
ull mul(ull a, ull b) {
    u128 x = static_cast<u128>(a) * b;

    x = (x >> 61) + (x & MOD);

    if (x >= MOD)
        x -= MOD;

    return static_cast<ull>(x);
}

/**
 * @brief Rolling Hash で使用する base を返す。
 */
ull base() {
    static const ull b = [] {
        uint64_t seed = chrono::steady_clock::now().time_since_epoch().count();

        mt19937_64 rng(seed);

        return uniform_int_distribution<ull>(1ULL << 10, MOD - 2)(rng);
    }();

    return b;
}

/**
 * @brief base^i を管理するテーブル。
 *
 * 必要な長さまで自動的に拡張される。
 */
vector<ull> &powers() {
    static vector<ull> p = {1};
    return p;
}

/**
 * @brief base^n まで powers を拡張する。
 */
void ensure_power(size_t n) {
    auto &p = powers();

    while (p.size() <= n) {
        p.push_back(mul(p.back(), base()));
    }
}

/**
 * @brief base^n mod MOD を返す。
 */
ull pow_base(size_t n) {
    ensure_power(n);
    return powers()[n];
}

/**
 * @brief 文字をハッシュ用の整数に変換する。
 */
ull value(char c) { return static_cast<unsigned char>(c) + 1; }

/**
 * @brief 左の文字列と右の文字列のハッシュを連結する。
 *
 * left_hash が文字列 L のハッシュ、
 * right_hash が文字列 R のハッシュのとき、
 * L + R のハッシュを返す。
 *
 * @param left_hash L のハッシュ
 * @param right_hash R のハッシュ
 * @param right_len R の長さ
 */
ull concat(ull left_hash, ull right_hash, size_t right_len) {
    return add(mul(left_hash, pow_base(right_len)), right_hash);
}

/**
 * @brief 通常の Rolling Hash。
 *
 * 任意の部分文字列 s[l, r) のハッシュを O(1) で取得する。
 */
struct RollingHash {
    vector<ull> hash;

    RollingHash(string_view s) : hash(s.size() + 1) {

        ensure_power(s.size());

        for (size_t i = 0; i < s.size(); i++) {
            hash[i + 1] = add(mul(hash[i], base()), value(s[i]));
        }
    }

    /**
     * @brief s[l, r) のハッシュを返す。
     *
     * @complexity O(1)
     */
    ull get(size_t l, size_t r) const {
        return sub(hash[r], mul(hash[l], pow_base(r - l)));
    }
};

} // namespace rolling_hash

template <class T> struct CoordinateCompression {
    vector<T> xs;

    CoordinateCompression() {}

    CoordinateCompression(const vector<T> &a) {
        xs = a;
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
    }

    int encode(const T &x) const {
        return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
    }

    T decode(int i) const { return xs[i]; }

    vector<int> encode(const vector<T> &a) const {
        vector<int> res(a.size());
        for (int i = 0; i < (int)a.size(); i++) {
            res[i] = encode(a[i]);
        }
        return res;
    }

    vector<T> decode(const vector<int> &a) const {
        vector<T> res(a.size());
        for (int i = 0; i < (int)a.size(); i++) {
            res[i] = decode(a[i]);
        }
        return res;
    }

    int size() const { return xs.size(); }
};

template <class T, class U>
pair<vector<int>, vector<vector<int>>>
scc_id_and_dag(const vector<vector<T>> &graph, const vector<vector<U>> &sccs) {
    int n = graph.size();
    int k = sccs.size();

    // 頂点 -> SCC id
    vector<int> comp_id(n, -1);

    for (int cid = 0; cid < k; cid++) {
        for (int v : sccs[cid]) {
            if (!(0 <= v && v < n)) {
                throw invalid_argument("vertex in sccs is out of range");
            }
            if (comp_id[v] != -1) {
                throw invalid_argument("vertex appears in multiple SCCs");
            }

            comp_id[v] = cid;
        }
    }

    for (int v = 0; v < n; v++) {
        if (comp_id[v] == -1) {
            throw invalid_argument("some vertices are missing from sccs");
        }
    }

    // SCC を縮約した DAG
    vector<set<int>> dag_set(k);

    for (int v = 0; v < n; v++) {
        int cv = comp_id[v];

        for (int to : graph[v]) {
            int cu = comp_id[to];

            if (cv != cu) {
                dag_set[cv].insert(cu);
            }
        }
    }

    vector<vector<int>> dag(k);

    for (int i = 0; i < k; i++) {
        dag[i] = vector<int>(all(dag_set[i]));
    }

    return {comp_id, dag};
}

template <class T, class Coord = long long>
class StaticRectangleFillRectangleSum {
  private:
    struct Point {
        Coord x, y;
        T w;
    };

    struct PrefixQuery {
        Coord x, y;
        int id;
        int sign;
    };

    struct Query {
        Coord l, r, u, d;
    };

    vector<Point> points;
    vector<Query> queries;

    void add_point(Coord x, Coord y, const T &w) {
        points.push_back({x, y, w});
    }

  public:
    StaticRectangleFillRectangleSum() = default;

    void reserve(int n, int q) {
        points.reserve(4 * n);
        queries.reserve(q);
    }

    // [l, r) x [u, d) に w を加算
    // l <= r, u <= d
    void add_rectangle(Coord l, Coord r, Coord u, Coord d, const T &w) {
        add_point(l, u, w);
        add_point(r, u, -w);
        add_point(l, d, -w);
        add_point(r, d, w);
    }

    // [l, r) x [u, d) の和を求めるクエリを追加
    int add_query(Coord l, Coord r, Coord u, Coord d) {
        int id = (int)queries.size();
        queries.push_back({l, r, u, d});
        return id;
    }

    vector<T> solve() const {
        int Q = (int)queries.size();

        vector<PrefixQuery> pq;
        pq.reserve(4 * Q);

        for (int i = 0; i < Q; ++i) {
            auto [l, r, u, d] = queries[i];

            // F(r,d) - F(l,d) - F(r,u) + F(l,u)
            pq.push_back({r, d, i, +1});
            pq.push_back({l, d, i, -1});
            pq.push_back({r, u, i, -1});
            pq.push_back({l, u, i, +1});
        }

        vector<Point> ps = points;

        sort(ps.begin(), ps.end(),
             [](const Point &a, const Point &b) { return a.x < b.x; });

        sort(pq.begin(), pq.end(),
             [](const PrefixQuery &a, const PrefixQuery &b) {
                 return a.x < b.x;
             });

        vector<Coord> ys;
        ys.reserve(ps.size());

        for (const auto &p : ps) {
            ys.push_back(p.y);
        }

        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());

        int M = (int)ys.size();

        atcoder::fenwick_tree<T> fw00(M); // c
        atcoder::fenwick_tree<T> fw10(M); // c*a
        atcoder::fenwick_tree<T> fw01(M); // c*b
        atcoder::fenwick_tree<T> fw11(M); // c*a*b

        vector<T> ans(Q);

        int pi = 0;

        for (const auto &q : pq) {
            // a < q.x
            while (pi < (int)ps.size() && ps[pi].x < q.x) {
                const auto &p = ps[pi];

                int yid = lower_bound(ys.begin(), ys.end(), p.y) - ys.begin();

                T a = T(p.x);
                T b = T(p.y);
                T c = p.w;

                fw00.add(yid, c);
                fw10.add(yid, c * a);
                fw01.add(yid, c * b);
                fw11.add(yid, c * a * b);

                ++pi;
            }

            // b < q.y
            int yr = lower_bound(ys.begin(), ys.end(), q.y) - ys.begin();

            T s00 = fw00.sum(0, yr);
            T s10 = fw10.sum(0, yr);
            T s01 = fw01.sum(0, yr);
            T s11 = fw11.sum(0, yr);

            T X = T(q.x);
            T Y = T(q.y);

            T val = s00 * X * Y - s10 * Y - s01 * X + s11;

            if (q.sign == +1) {
                ans[q.id] += val;
            } else {
                ans[q.id] -= val;
            }
        }

        return ans;
    }
};
// --- END SOURCE: https://github.com/HarutoKobayashi/cp-templates/cpp/all-in-one.cpp ---

/* memo */
// ll composition(ll f, ll g) {return f+g;} // f \circ g
// mint::set_mod(998244353);
// PrimeTools pt = PrimeTools::setup_primes();
// Comb<mint> C(2 * power(10, 6) + 30ll);
// CoordinateCompression<ll> cc(A); // A は unique でなくても、unsorted でもよい
// cc.encode / cc.decode

int main() {
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    cout << fixed << setprecision(15);
}
