package main

import (
	"testing"

	"gotest.tools/assert"
)

func TestRegular(t *testing.T) {
	result := solution([]int{7, 2, 5, 0, 1})
	assert.Assert(t, result == 3, result)

	assert.Assert(t, solution([]int{7, 2, 5, 0, 1}) == 3)

	assert.Assert(t, solution([]int{3, 4, -1, 1}) == 2)

	assert.Assert(t, solution([]int{1, 2, 0}) == 3)

	assert.Assert(t, solution([]int{1, 2, 4, 0}) == 3)

	assert.Assert(t, solution([]int{1}) == 2)

	assert.Assert(t, solution([]int{0}) == 1)

	assert.Assert(t, solution([]int{-1}) == 1)

	assert.Assert(t, solution([]int{3, 7, 9, 55, 57, 1, 2}) == 4)

	assert.Assert(t, solution([]int{-3, -2}) == 1)
}
