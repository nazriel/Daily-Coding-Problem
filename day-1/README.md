# Problem #1 [Easy]

## Problem description

```
This problem was recently asked by Google.

Given a list of numbers and a number k, return whether any two numbers from the list add up to k.

For example, given [10, 15, 3, 7] and k of 17, return true since 10 + 7 is 17.

Bonus: Can you do this in one pass?
```

## My solution

My idea was to simply go by each number in numbers list and check whenever it exists in a set that I defined earlier.

The mentioned set consists of numbers that are difference between expected sum and the given number that is being tested at given moment.

Use of set allows me to check for existance in O(1) time with rather cheap space complexity O(n).

## Step by step explanation

For `numbers_list = [3, 5, 9]` and `sum = 12`.

Go by each `number` in `numbers_list`.

For `number` being `3` check if it exists already in `set`.
If yes, it means there was a `number` before for which `sum - number` yielded `3`.
In our cases there wasn't such number yet, so we substract `number` (`3`) from `sum` (`12`) which gives `9` and save it in our set `subs.add(9)`.

Next is `5`. There is no `5` in set - so we continue with out `substract & continue` routine.

Next is `9`. In this case, our set contains `9` - which we added at the begging when processing `3`. This means that we can return with `True` since `9+3` == `12`.


## Time complexity

We are going by each number in the list of size N, and all performed operations, including substraction, comparision and set mutation are O(1), time complexity will be O(n) in worst case scenario.

## Space complexity

Set of substracted values is maintained during computation.
In worst case scenario all numbers will be substracted and added to the set.
Thus space complexity will be O(n) in worst case.
