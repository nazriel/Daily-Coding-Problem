#define BOOST_TEST_MODULE day2
#include <boost/test/included/unit_test.hpp>
#include <vector>
#include <cstdint>

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
}

// time: O(n^2)
// space: O(n)
std::vector<std::uint32_t> solution1(const std::vector<std::uint32_t>& input)
{
    // O(n)
    auto res = std::vector<std::uint32_t>(input.size());

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
std::vector<std::uint32_t> solution(const std::vector<std::uint32_t>& input)
{
    // O(n)
    auto prod = input.size() > 1 ? 1 : 0;
    for (std::size_t i = 0; i < input.size(); i++)
    {
        prod *= input[i];
    }

    auto res = std::vector<std::uint32_t>(input.size());
    for (std::size_t i = 0; i < input.size(); i++)
    {
        res[i] = prod / input[i];
    }

    return res;
}

BOOST_AUTO_TEST_CASE( possitive )
{
    std::vector<std::uint32_t> lhs, rhs;

    lhs = solution({1, 2, 3, 4, 5});
    rhs = {120, 60, 40, 30, 24};
    BOOST_CHECK_EQUAL(lhs, rhs);

    lhs = solution({3, 2, 1});
    rhs = {2, 3, 6};
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
}
