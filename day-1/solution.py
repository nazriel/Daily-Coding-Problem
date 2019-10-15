#!/usr/bin/env python3

import unittest

def does_adds_up(numbers_list: list, sum: int) -> bool:
    """
    Check whenever any two numbers provided in numbers_list adds up to sum.
    """

    subs = set()

    # O(n)
    for number in numbers_list:
        if number in subs: # O(1)
            return True
        subs.add(sum - number) # O(1)

    return False


class TestDoesAddsUp(unittest.TestCase):
    def test_positive(self):
        self.assertTrue(does_adds_up([10, 15, 3, 7], 17))
        self.assertTrue(does_adds_up([3, 4, 9, 12], 7))
        self.assertTrue(does_adds_up([4, 4], 8))
        self.assertTrue(does_adds_up([1, 2, 5], 3))

    def test_negative(self):
        self.assertFalse(does_adds_up([10, 15, 3, 7], 5))
        self.assertFalse(does_adds_up([3, 4, 9, 12], 4))
        self.assertFalse(does_adds_up([4, 4], 3))
        self.assertFalse(does_adds_up([1, 2, 5], 1))

    def test_corner_cases(self):
        self.assertFalse(does_adds_up([], 5))
        self.assertFalse(does_adds_up([1, 2], 0))
        self.assertFalse(does_adds_up([99, -1], -1))
        self.assertTrue(does_adds_up([-2, -1], -3))

    def test_wrong_args(self):
        with self.assertRaises(TypeError):
            does_adds_up([-2, -1], "ff")
            does_adds_up(1, 9)


if __name__ == '__main__':
    unittest.main()
