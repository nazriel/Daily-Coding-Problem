#define BOOST_TEST_MODULE day2
#include <boost/test/included/unit_test.hpp>
#include <vector>
#include <cstdint>
#include <unordered_map>

namespace std
{
    ostream &operator <<(ostream &os, const vector<uint32_t> &v)
    {
        os << " { ";
        if (v.size() > 1)
        {
            copy(v.begin(), v.end() - 1, ostream_iterator<uint32_t>(os, ", "));
        }
        if (v.size() >= 1)
        {
            os << v.back();
        }
        os << " } ";
        return os;
    }

    template<typename K, typename V>
    ostream &operator <<(ostream& os, const unordered_map<K, V>& m)
    {
        os << " { ";
        for (const auto& r : m) {
            os << "{ \"" << r.first << "\": " << r.second << " }, ";
        }
        os << " } ";

        return os;
    }
}

// TODO: check against overflows - each number can be up to uint32_t,
// yet we hold sums as uint32_t as well - easy to overflow.

// time: O(n^2)
// space: O(n)
std::vector<std::uint32_t> solution1(const std::vector<std::uint32_t>& input)
{
    // O(n)
    std::vector<std::uint32_t> res(input.size());

    // O(n)
    for (std::size_t i = 0; i < input.size(); i++)
    {
        res[i] = input.size() > 1 ? 1 : 0;

        // O(n)
        for (std::size_t j = 0; j < input.size(); j++)
        {
            if (j == i)
            {
                continue;
            }
            res[i] *= input[j];
        }
    }

    return res;
}

// time: O(2n)
// space: O(n)
// downsides: uses division
std::vector<std::uint32_t> solution2(const std::vector<std::uint32_t>& input)
{
    std::uint32_t prod = input.size() > 1 ? 1 : 0;

    // t: O(n)
    bool zeroFound = false;
    for (std::size_t i = 0; i < input.size(); i++)
    {
        if (input[i] != 0)
        {
            prod *= input[i];
        }
        else
        {
            zeroFound = true;
        }
    }

    // s: O(n)
    std::vector<std::uint32_t> res(input.size());

    // t: O(n)
    for (std::size_t i = 0; i < input.size(); i++)
    {
        if (input[i] != 0 && !zeroFound)
        {
            res[i] = prod / input[i];
        }
        else if (input[i] != 0 && zeroFound)
        {
            res[i] = 0;
        }
        else
        {
            res[i] = prod;
        }
    }

    return res;
}

// time: O(2n)
// space: O(3n) - can be reducded to o(2n) by reusing one of the tmp vectors (although will make code way less readable).
std::vector<std::uint32_t> solution3(const std::vector<std::uint32_t>& input)
{
    std::uint32_t lhsSum = input.size() > 1 ? 1 : 0;
    std::uint32_t rhsSum = input.size() > 1 ? 1 : 0;

    // s: o(2n)
    std::vector<std::uint32_t> lhsV(input.size());
    std::vector<std::uint32_t> rhsV(input.size());

    // t: o(n)
    for (std::size_t i = 0; i < input.size(); i++)
    {
        lhsSum *= input[i];
        rhsSum *= input[input.size() - i - 1];

        lhsV[i] = lhsSum;
        rhsV[input.size() - i - 1] = rhsSum;
    }

    // s: o(n)
    std::vector<std::uint32_t> res(input.size());
    // t: o(n)
    for (std::size_t i = 0; i < input.size(); i++)
    {
        auto lhs = lhsV.size() > 1 ? 1 : 0;
        if (i > 0)
            lhs = lhsV[i - 1];

        auto rhs = rhsV.size() > 1 ? 1 : 0;
        if (i + 1 < rhsV.size())
            rhs = rhsV[i + 1];

        res[i] = lhs * rhs;
    }

    return res;
}

auto solution = solution3;

BOOST_AUTO_TEST_CASE( possitive )
{
    std::vector<std::uint32_t> lhs, rhs;

    lhs = solution({1, 2, 3, 4, 5});
    rhs = {120, 60, 40, 30, 24};
    BOOST_CHECK_EQUAL(lhs, rhs);

    lhs = solution({3, 2, 1});
    rhs = {2, 3, 6};
    BOOST_CHECK_EQUAL(lhs, rhs);

    lhs = solution({3, 0, 2});
    rhs = {0, 6, 0};
    BOOST_CHECK_EQUAL(lhs, rhs);
}

BOOST_AUTO_TEST_CASE_EXPECTED_FAILURES( negative, 2 )
BOOST_AUTO_TEST_CASE( negative )
{
    std::vector<std::uint32_t> lhs, rhs;

    lhs = solution({1, 2, 3, 4, 5});
    rhs = {120, 60, 40, 30, 25};
    BOOST_CHECK_EQUAL(lhs, rhs);

    lhs = solution({3, 2, 1});
    rhs = {2, 3, 7};
    BOOST_CHECK_EQUAL(lhs, rhs);
}

BOOST_AUTO_TEST_CASE( corner )
{
    std::vector<std::uint32_t> lhs, rhs;

    lhs = solution({});
    rhs = {};
    BOOST_CHECK_EQUAL(lhs, rhs);

    lhs = solution({3});
    rhs = {0};
    BOOST_CHECK_EQUAL(lhs, rhs);

    lhs = solution({0});
    rhs = {0};
    BOOST_CHECK_EQUAL(lhs, rhs);
}
