#include <cstdlib>
#include <iostream>
#include <sstream>
#include <chrono>
#include <functional>
#include <array>
#include <memory>
#include <vector>

#include "BaseArray.h"
#include "Integer.h"
#include "Float.h"

using std::cout;
using std::endl;
using std::function;
using std::string;

#define ENABLE_TESTS

////////////////////////////////////////////////////////////////////////////////
// Performance Tests
////////////////////////////////////////////////////////////////////////////////

auto test_basearray_creation(unsigned long count)
{
    using DS::Numbers::BaseArray;
    for (auto i = 0ul; i < count; ++i) {
#ifdef ENABLE_TESTS
        {
            BaseArray a0b1(count % 1000);BaseArray a0b2(count % 1000);BaseArray a0b3(count % 1000);BaseArray a0b4(count % 1000);
            BaseArray a1b1(count % 1000);BaseArray a1b2(count % 1000);BaseArray a1b3(count % 1000);BaseArray a1b4(count % 1000);
            BaseArray a2b1(count % 1000);BaseArray a2b2(count % 1000);BaseArray a2b3(count % 1000);BaseArray a2b4(count % 1000);
            BaseArray a3b1(count % 1000);BaseArray a3b2(count % 1000);BaseArray a3b3(count % 1000);BaseArray a3b4(count % 1000);
            BaseArray a4b1(count % 1000);BaseArray a4b2(count % 1000);BaseArray a4b3(count % 1000);BaseArray a4b4(count % 1000);
            BaseArray a5b1(count % 1000);BaseArray a5b2(count % 1000);BaseArray a5b3(count % 1000);BaseArray a5b4(count % 1000);
            BaseArray a6b1(count % 1000);BaseArray a6b2(count % 1000);BaseArray a6b3(count % 1000);BaseArray a6b4(count % 1000);
            BaseArray a7b1(count % 1000);BaseArray a7b2(count % 1000);BaseArray a7b3(count % 1000);BaseArray a7b4(count % 1000);
            BaseArray a8b1(count % 1000);BaseArray a8b2(count % 1000);BaseArray a8b3(count % 1000);BaseArray a8b4(count % 1000);
            BaseArray a9b1(count % 1000);BaseArray a9b2(count % 1000);BaseArray a9b3(count % 1000);BaseArray a9b4(count % 1000);
            BaseArray aab1(count % 1000);BaseArray aab2(count % 1000);BaseArray aab3(count % 1000);BaseArray aab4(count % 1000);
            BaseArray abb1(count % 1000);BaseArray abb2(count % 1000);BaseArray abb3(count % 1000);BaseArray abb4(count % 1000);
            BaseArray acb1(count % 1000);BaseArray acb2(count % 1000);BaseArray acb3(count % 1000);BaseArray acb4(count % 1000);
            BaseArray adb1(count % 1000);BaseArray adb2(count % 1000);BaseArray adb3(count % 1000);BaseArray adb4(count % 1000);
        }
        {
            BaseArray a0b1(count % 1000);BaseArray a0b2(count % 1000);BaseArray a0b3(count % 1000);BaseArray a0b4(count % 1000);
            BaseArray a1b1(count % 1000);BaseArray a1b2(count % 1000);BaseArray a1b3(count % 1000);BaseArray a1b4(count % 1000);
            BaseArray a2b1(count % 1000);BaseArray a2b2(count % 1000);BaseArray a2b3(count % 1000);BaseArray a2b4(count % 1000);
            BaseArray a3b1(count % 1000);BaseArray a3b2(count % 1000);BaseArray a3b3(count % 1000);BaseArray a3b4(count % 1000);
            BaseArray a4b1(count % 1000);BaseArray a4b2(count % 1000);BaseArray a4b3(count % 1000);BaseArray a4b4(count % 1000);
            BaseArray a5b1(count % 1000);BaseArray a5b2(count % 1000);BaseArray a5b3(count % 1000);BaseArray a5b4(count % 1000);
            BaseArray a6b1(count % 1000);BaseArray a6b2(count % 1000);BaseArray a6b3(count % 1000);BaseArray a6b4(count % 1000);
            BaseArray a7b1(count % 1000);BaseArray a7b2(count % 1000);BaseArray a7b3(count % 1000);BaseArray a7b4(count % 1000);
            BaseArray a8b1(count % 1000);BaseArray a8b2(count % 1000);BaseArray a8b3(count % 1000);BaseArray a8b4(count % 1000);
            BaseArray a9b1(count % 1000);BaseArray a9b2(count % 1000);BaseArray a9b3(count % 1000);BaseArray a9b4(count % 1000);
            BaseArray aab1(count % 1000);BaseArray aab2(count % 1000);BaseArray aab3(count % 1000);BaseArray aab4(count % 1000);
            BaseArray abb1(count % 1000);BaseArray abb2(count % 1000);BaseArray abb3(count % 1000);BaseArray abb4(count % 1000);
            BaseArray acb1(count % 1000);BaseArray acb2(count % 1000);BaseArray acb3(count % 1000);BaseArray acb4(count % 1000);
            BaseArray adb1(count % 1000);BaseArray adb2(count % 1000);BaseArray adb3(count % 1000);BaseArray adb4(count % 1000);
        }
#endif
    }
}

auto test_basearray_copying(unsigned long count)
{
    using DS::Numbers::BaseArray;
    BaseArray b(100);
    b.finalize();
    for (auto i = 0ul; i < count; ++i) {
#ifdef ENABLE_TESTS
        { BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }{ BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }
        { BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }{ BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }
        { BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }{ BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }
        { BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }{ BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }
        { BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }{ BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }
        { BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }{ BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }
        { BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }{ BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }
        { BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }{ BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }
        { BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }{ BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }
        { BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }{ BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }
        { BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }{ BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }
        { BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }{ BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }
        { BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }{ BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }
        { BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }{ BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }
        { BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }{ BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }
        { BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }{ BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }
        { BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }{ BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }
        { BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }{ BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }
        { BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }{ BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }
        { BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }{ BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }
        { BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }{ BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }
        { BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }{ BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }
        { BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }{ BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }
        { BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }{ BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }
        { BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }{ BaseArray c(b); BaseArray d(1); d = b; d = c; c = d; b = c; b = d; }

#endif
    }
    return b;
}

auto test_basearray_setting(unsigned long count)
{
    using DS::Numbers::BaseArray;
    //BaseArray ba(100);
    std::array<BaseArray, 1000> baa;
    for (auto& ba : baa)
        ba = BaseArray(100);
    unsigned long t = 1000;
    for (auto i = 0ul; i < count; ++i) {
#ifdef ENABLE_TESTS
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
        baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);baa[i%t].set(i,i%100);baa[i%999].set(i,i%99);baa[i%998].set(i,i%98);baa[i%997].set(i,i%97);
#endif
    }
}

auto test_basearray_getting(unsigned long count)
{
    using DS::Numbers::BaseArray;
    std::array<BaseArray, 1000> baa;
    for (auto& ba : baa)
        ba = BaseArray(100);
    BaseArray::unit_t a = 0;
    for (auto i = 0ul; i < count; ++i) {
#ifdef ENABLE_TESTS
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
        a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];a+=baa[i % 1000][i % 100];
#endif
    }
    return a;
}

auto test_integer(unsigned long count)
{
    using DS::Numbers::Integer;
    Integer m(0);
    for (auto index = 0ul; index < count/10000; ++index) {
#ifdef ENABLE_TESTS
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
#endif
    }
    cout << ((m == Integer(2)) ? "" : "               <red><b>**** Integer Result Incorrect! ****</b></red>\n");
}

auto test_float(unsigned long count)
{
    using DS::Numbers::Float;
    Float c;
    for (auto index = 0ul; index < count/1000; ++index) {
#ifdef ENABLE_TESTS
        Float f(12345.45678);
        f.sqrt();
        Float g = f;
        Float h(3456.0033);
        h.ln();
        h = h / g;
        c = h;
        h.sin();
        h.sqrt();
#endif
    }
    auto target = "(314956277*2^(384)+1538707376*2^(352)+989686057*2^(320)+3741943418*2^(288)+2329427682*2^(256)+2326218685*2^(224)+3335557927*2^(192)+1133823119*2^(160)+3715106361*2^(128)+2575701856*2^(96)+2251213430*2^(64)+2617781194*2^(32)+2682567656*2^(0)+0)*2^(-416)";
    std::stringstream s;
    c.output(s);
    cout << ((s.str() == target) ? "" : "               <red><b>**** Float Result Incorrect! ****</b></red>\n");
}

////////////////////////////////////////////////////////////////////////////////
// Setup
////////////////////////////////////////////////////////////////////////////////

auto time_fn(unsigned long count, function<void (unsigned long)> f)
{
    auto start = std::chrono::steady_clock::now();
    f(count);
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration<double, milli>(end-start).count() / 1000.0; // s
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
    if (percent < -10.0)
        percent_string = "<green><b>" + percent_string + "</b></green>";
    else if (percent > 10.0)
        percent_string = "<red><b>" + percent_string + "</b></red>";
    percent_string += "%";
    if (percent >= 0.0)
        percent_string = " " + percent_string;
    printf("    <blue>%15s</blue>:  %15ss    baseline: %12ss     Change: %-30s\n", name, str(res).c_str(), str(base).c_str(), percent_string.c_str());
    fflush(stdout);
}

int main(int argc, char* argv[])
{
    //printf("sizeof(Integer):       %lu\n", sizeof(DS::Numbers::Integer));
    //printf("sizeof(BaseArray):     %lu\n", sizeof(DS::Numbers::BaseArray));
    //printf("sizeof(SP):            %lu\n", sizeof(std::shared_ptr<std::vector<int>>));
    //printf("sizeof(vector):        %lu\n", sizeof(std::vector<int>));
    //printf("sizeof(std::array[8]): %lu\n", sizeof(std::array<char, 8>));
    //printf("sizeof(Float):     %lu\n", sizeof(DS::Numbers::Float));
    //printf("sizeof(bool):      %lu\n", sizeof(bool));
    //printf("sizeof(int):       %lu\n", sizeof(int));
    fflush(stdout);

    auto count = (unsigned long)(100000);
    if (argc > 1)
        count = atol(argv[1]);

    //printf("Running with count: %lu\n", count);

    output_test(time_fn(count, test_basearray_creation), 20.90, "test_creation");
    output_test(time_fn(count, test_basearray_copying),  20.05, "test_copying");
    output_test(time_fn(count, test_basearray_setting),  20.70, "test_setting");
    output_test(time_fn(count, test_basearray_getting),  20.09, "test_getting");
    output_test(time_fn(count, test_integer),            23.83, "test_integer");
    output_test(time_fn(count, test_float),              19.61, "test_float");

    return 0;
}
