#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <functional>
#include <array>
#include <memory>
#include <vector>
#include <cstdint>
#include <map>
#include <algorithm>
#include <exception>

#include "BaseArray.h"
#include "Integer.h"
#include "Float.h"

using std::cout;
using std::endl;
using std::function;
using std::string;
using std::vector;
using std::pair;

////////////////////////////////////////////////////////////////////////////////
// Result verification
////////////////////////////////////////////////////////////////////////////////

void verify_float_with_double(const DS::Numbers::Float& f, double target)
{
    double tmp = f.toDouble() / target;
    double ep = .00001;
    if (tmp < 1.0+ep && tmp > 1.0-ep)
        return;
    cout << "               <red><b>**** Float Result Incorrect! (" << f.toDouble() << " != " << target << ") ****</b></red>\n";
}

void verify_float_is_zero(const DS::Numbers::Float& f, double ep)
{
    double tmp = f.toDouble();
    if (tmp < ep && tmp > -ep)
        return;
    cout << "               <red><b>**** Float Result Incorrect! (" << f.toDouble() << " != 0) ****</b></red>\n";
}

////////////////////////////////////////////////////////////////////////////////
// Integer Performance Tests
////////////////////////////////////////////////////////////////////////////////

auto test_small_integer(unsigned long count)
{
    using DS::Numbers::Integer;
    Integer m(0);
    for (auto index = 0ul; index < count; ++index) {
        Integer m3(3), m4(4), m5(5), m6(6);
        m = (m3*m3 + m4*m4) / m3 + m6 + m6/m3;
        m = m*m + m + m;
        m = (m*m + m) / m;
        m = m-m/2;
    }
    cout << ((m == Integer(145)) ? "" : "               <red><b>**** Integer Result Incorrect! ****</b></red>\n");
}

auto test_integer(unsigned long count)
{
    using DS::Numbers::Integer;
    Integer m(0);
    for (auto index = 0ul; index < count; ++index) {
        {
            Integer i(3473); Integer j(125); Integer k(100);
            i.pow(k);
            i *= j;
            i = i / Integer(2);
            m = i / (i/Integer(2));
        }
        {
            Integer i(3473); Integer j(125); Integer k(100);
            i.pow(k);
            i *= j;
            i = i / Integer(2);
            m = i / (i/Integer(2));
        }
    }
    cout << ((m == Integer(2)) ? "" : "               <red><b>**** Integer Result Incorrect! ****</b></red>\n");
}

////////////////////////////////////////////////////////////////////////////////
// Float Performance Tests
////////////////////////////////////////////////////////////////////////////////

auto test_float_1(unsigned long count)
{
    using DS::Numbers::Float;
    Float res;
    for (auto index = 0ul; index < count; ++index) {
        Float f(12345.45678);
        f.sqrt();
        Float g = f;
        Float h(3456.0033);
        h.ln();
        h = h / g;
        h.sin();
        h.sqrt();
        res = h;
    }
    verify_float_with_double(res, .270676);
}

auto test_float_pisqrt(unsigned long count)
{
    using DS::Numbers::Float;
    Float two(2.0), one(1.0), zero(0.0), res;
    for (auto index = 0ul; index < count; ++index) {
        Float prev = zero;
        Float total = one;
        for (auto term = 0ul; term < 200; ++term) {
            Float tmp = sqrt(prev + two);
            prev = tmp;
            total *= tmp / two;
        }
        res = total;
    }
    res = (one / res) * two - Float::pi();
    verify_float_is_zero(res, 1.0e-30);
}

auto test_float_atan(unsigned long count)
{
    using DS::Numbers::Float;
    Float one(1.0), res;
    for (auto index = 0ul; index < count; ++index) {
        Float tmp = one;
        tmp.atan();
        res = tmp;
    }
    res = res*Float(4.0) - Float::pi();
    verify_float_is_zero(res, 1.0e-30);
}

auto test_float_exppi(unsigned long count)
{
    using DS::Numbers::Float;
    Float one(1.0), res;
    for (auto index = 0ul; index < count; ++index) {
        Float tmp = Float::pi();
        tmp.exp();
        res = tmp;
    }
    verify_float_with_double(res, 23.1407);
}

auto test_coscos(unsigned long count)
{
    using DS::Numbers::Float;
    Float one(1.0), res;
    for (auto index = 0ul; index < count; ++index) {
        Float tmp = one;
        tmp = cos(cos(cos(cos(cos(cos(cos(cos(cos(cos(cos(tmp)))))))))));
        tmp = cos(cos(cos(cos(cos(cos(cos(cos(cos(cos(cos(tmp)))))))))));
        tmp = cos(cos(cos(cos(cos(cos(cos(cos(cos(cos(cos(tmp)))))))))));
        tmp = cos(cos(cos(cos(cos(cos(cos(cos(cos(cos(cos(tmp)))))))))));
        tmp = cos(cos(cos(cos(cos(cos(cos(cos(cos(cos(cos(tmp)))))))))));
        tmp = cos(cos(cos(cos(cos(cos(cos(cos(cos(cos(cos(tmp)))))))))));
        tmp = cos(cos(cos(cos(cos(cos(cos(cos(cos(cos(cos(tmp)))))))))));
        res = tmp;
    }
    verify_float_with_double(res, 0.73908513321516067);
}

////////////////////////////////////////////////////////////////////////////////
// Setup
////////////////////////////////////////////////////////////////////////////////

auto time_fn(unsigned long count, function<void (unsigned long)> f, int times = 1)
{
    double res = 0;
    for (int t = times; t > 0; --t) {
        auto start = std::chrono::steady_clock::now();
        f(count);
        auto end = std::chrono::steady_clock::now();
        res += std::chrono::duration<double, milli>(end-start).count() / 1000.0; // s
    }
    return res / (double)times;
}

template<typename T>
auto str(const T& data) {
    std::stringstream s;
    s << data;
    return s.str();
}

auto output_test(double res, double base, const char* name)
{
    double percent = ((double)((int)(1000.0*((res-base)/base))))/10.0;
    string percent_string = str(percent);
    if (percent < -9.99)
        percent_string = "<green><b>" + percent_string + "</b></green>";
    else if (percent > 9.99)
        percent_string = "<red><b>" + percent_string + "</b></red>";
    percent_string += "%";
    if (percent >= 0.0)
        percent_string = " " + percent_string;
    string new_name = str(name) + ":";
    printf("<blue>%-20s</blue>  %10ss    Change: %-30s\n", new_name.c_str(), str(res).c_str(), percent_string.c_str());
    fflush(stdout);
}

template<typename Iterator, typename String>
auto join(Iterator iter_start, Iterator iter_end, String s)
{
    string res;
    if (iter_start != iter_end) {
        res = *iter_start;
        ++iter_start;
    }
    for (Iterator iter = iter_start; iter != iter_end; ++iter)
        res += s + *iter; 
    return res;
}

template<typename T>
ostream& operator<< (ostream& out, vector<T> v)
{
    const int break_size = 3;
    string inside;
    if (v.size() <= break_size)
        inside = join(v.begin(), v.end(), ", ");
    else
        inside = "\n    " + join(v.begin(), v.end(), ",\n    ") + "\n";
    out << "[" << inside << "]";
    return out;
}

vector<string> get_args(int argc, char** argv)
{
    vector<string> args;
    std::for_each(argv + 1, argv + argc, [&args](auto arg) { args.push_back(string(arg)); } );
    return args;
}

class invalid_parameters : std::exception {};

unsigned long calibrate10s(function<void(unsigned long)> f)
{
    double time;
    unsigned long count = 1;
    while (1) {
        time = time_fn(count, f);
        if (time > .1)
            break;
        count *= 10;
    }
    if (time > 2.0)
        throw "Error: time > 2.0 in calibrate10s";
    return (unsigned long)((10.0/time) * (double)count);
}

auto calibrate10s_avg4(function<void(unsigned long)> f)
{
    return (calibrate10s(f) + calibrate10s(f) + calibrate10s(f)) / 3;
}

#define PRINT_SIZE(type) (printf("  %-25s %lu\n", #type, sizeof(type)));
#define ADD_TEST(test) { #test, test }

int main(int argc, char* argv[])
{
    //printf("Sizes:\n");
    //PRINT_SIZE(DS::Numbers::BaseArray);
    //PRINT_SIZE(DS::Numbers::Integer);
    //PRINT_SIZE(DS::Numbers::Float);
    //cout << "  UNIT_T_BITS:              " << UNIT_T_BITS << endl;
    //fflush(stdout);

    DS::Numbers::Float::pi();
    
    using tests_t = vector<pair<string, function<void(unsigned long)>>>;
    tests_t tests = {
        ADD_TEST(test_integer),
        ADD_TEST(test_small_integer),
        ADD_TEST(test_float_1),
        ADD_TEST(test_float_pisqrt),
        ADD_TEST(test_float_atan),
        ADD_TEST(test_float_exppi),
        ADD_TEST(test_coscos)
    };

    vector<string> args = get_args(argc, argv);

    map<string, unsigned long> calibrations;
    map<string, double> baselines;
    for (auto test : tests) {
        calibrations[test.first] = 1;
        baselines[test.first]    = 0;
    }

    ifstream in("baselines.in");
    if (in.good()) {
        while (1) {
            string name;
            double baseline;
            unsigned long count;
            in >> name >> count >> baseline;
            if (in.eof())
                break;
            baselines[name] = baseline;
            calibrations[name] = count;
        }
    }

    try {
        if (args.size() == 0)
            throw invalid_parameters();
        //// Baselining
        //// This will determine iteration counts necessary to make each test
        //// fit within 10s.  Then it will run each test a number of times and
        //// will record the average run time as the baseline.
        else if (args.size() >= 1 && args.size() <= 2 && args[0] == "baseline") {
            if (args.size() == 2) {
                auto p = find_if(begin(tests), end(tests), [&args](const auto& elem){ return elem.first == args[1]; });
                if (p == end(tests))
                    throw invalid_parameters();
                unsigned long count = calibrate10s_avg4((*p).second);
                cout << (*p).first << " " << count << " " << time_fn(count, (*p).second, 4) << endl;
            }
            else {
                for (auto& p : tests) {
                    unsigned long count = calibrate10s_avg4(p.second);
                    cout << p.first << " " << count << " " << time_fn(count, p.second, 4) << endl;
                }
            }
        }
        //// Performance tests
        //// This will run the tests and output performance comparisons against
        //// the baselines
        else if (args.size() >= 1 && args.size() <= 3 && args[0] == "run") {
            if (args.size() == 2) {
                auto p = find_if(begin(tests), end(tests), [&args](const auto& elem){ return elem.first == args[1]; });
                if (p == end(tests))
                    throw invalid_parameters();
                output_test(time_fn(calibrations[args[1]], (*p).second), baselines[(*p).first], (*p).first.c_str());
            }
            else {
                for (auto& p : tests)
                    output_test(time_fn(calibrations[p.first], p.second), baselines[p.first], p.first.c_str());
            }
        }
        //// Invalid arguments
        else
            throw invalid_parameters();
    }
    catch (invalid_parameters) {
        cout << "Usage:" << endl;
        cout << "    perftest calibrate [test name]" << endl;
        cout << "    perftest baseline  [test name]" << endl;
        cout << "    perftest run       [test name]" << endl;
    }
    return 0;
}
