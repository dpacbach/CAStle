#include <cstdlib>
#include <iostream>
#include <sstream>
#include <chrono>
#include <functional>
#include <array>
#include <memory>
#include <vector>
#include <cstdint>

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
    count = (count == 0) ? 1 : count;
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
    count = (count == 0) ? 1 : count;
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
    count = (count == 0) ? 1 : count;
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
    count = (count == 0) ? 1 : count;
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
    count = count / 10000;
    count = (count == 0) ? 1 : count;
    for (auto index = 0ul; index < count; ++index) {
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

auto test_float_1(unsigned long count)
{
    using DS::Numbers::Float;
    Float res;
    count = count / 1000;
    count = (count == 0) ? 1 : count;
    for (auto index = 0ul; index < count; ++index) {
#ifdef ENABLE_TESTS
        Float f(12345.45678);
        f.sqrt();
        Float g = f;
        Float h(3456.0033);
        h.ln();
        h = h / g;
        h.sin();
        h.sqrt();
        res = h;
#endif
    }
    verify_float_with_double(res, .270676);
}

auto test_float_pisqrt(unsigned long count)
{
    using DS::Numbers::Float;
    Float two(2.0), one(1.0), zero(0.0), res;
    count = count / 7500;
    count = (count == 0) ? 1 : count;
    for (auto index = 0ul; index < count; ++index) {
#ifdef ENABLE_TESTS
        Float prev = zero;
        Float total = one;
        for (auto term = 0ul; term < 200; ++term) {
            Float tmp = sqrt(prev + two);
            prev = tmp;
            total *= tmp / two;
        }
        res = total;
#endif
    }
    res = (one / res) * two - Float::pi();
    verify_float_is_zero(res, 1.0e-30);
}

auto test_float_atan(unsigned long count)
{
    using DS::Numbers::Float;
    Float one(1.0), res;
    count = count / 800;
    count = (count == 0) ? 1 : count;
    for (auto index = 0ul; index < count; ++index) {
#ifdef ENABLE_TESTS
        Float tmp = one;
        tmp.atan();
        res = tmp;
#endif
    }
    res = res*Float(4.0) - Float::pi();
    verify_float_is_zero(res, 1.0e-30);
}

auto test_float_exppi(unsigned long count)
{
    using DS::Numbers::Float;
    Float one(1.0), res;
    count /= 3300;
    count = (count == 0) ? 1 : count;
    for (auto index = 0ul; index < count; ++index) {
#ifdef ENABLE_TESTS
        Float tmp = Float::pi();
        tmp.exp();
        res = tmp;
#endif
    }
    verify_float_with_double(res, 23.1407);
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
    printf("    <blue>%20s</blue>:  %15ss    baseline: %12ss     Change: %-30s\n", name, str(res).c_str(), str(base).c_str(), percent_string.c_str());
    fflush(stdout);
}

#define PRINT_SIZE(type) (printf("  %-28s %lu\n", #type, sizeof(type)));

int main(int argc, char* argv[])
{
    using DS::Numbers::Float;

    //PRINT_SIZE(uint_fast8_t);
    //PRINT_SIZE(uint_fast16_t);
    //PRINT_SIZE(uint_fast32_t);
    //PRINT_SIZE(uint_fast64_t);
    //PRINT_SIZE(uintmax_t);
    //PRINT_SIZE(__uint128_t);
    //PRINT_SIZE(DS::Numbers::BaseArray);
    //PRINT_SIZE(DS::Numbers::Integer);
    //PRINT_SIZE(DS::Numbers::Float);
    //PRINT_SIZE(double);
    //PRINT_SIZE(long double);
    //cout << "UNIT_T_MINUS1_LONG:       " << ((DS::Numbers::BaseArray::unit_t_long)(((DS::Numbers::BaseArray::unit_t)0)-1)) << endl;
    //cout << "UNIT_T_LONG_BITS_DIV_2:   " << UNIT_T_LONG_BITS_DIV_2 << endl;
    cout << "UNIT_T_BITS:              " << UNIT_T_BITS << endl;
    cout << "UNIT_T_LONG_BITS:         " << UNIT_T_LONG_BITS << endl;
    fflush(stdout);

    DS::Numbers::Float::pi();

    auto count = (unsigned long)(100000);
    if (argc > 1)
        count = atol(argv[1]);
    count--;count++;

    //count = 1;
    output_test(time_fn(count, test_basearray_creation), 20.90, "test_creation");
    output_test(time_fn(count, test_basearray_copying),  20.05, "test_copying");
    output_test(time_fn(count, test_basearray_setting),  20.70, "test_setting");
    output_test(time_fn(count, test_basearray_getting),  20.09, "test_getting");

    output_test(time_fn(count, test_integer),            23.83, "test_integer");
    output_test(time_fn(count, test_float_1),            20.52, "test_float_1");
    output_test(time_fn(count, test_float_pisqrt),       21.62, "test_float_pisqrt");
    output_test(time_fn(count, test_float_atan),         24.76, "test_float_atan");
    output_test(time_fn(count, test_float_exppi),        19.17, "test_float_exppi");

    return 0;
}
