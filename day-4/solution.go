package main

func abs(n int) int {
	if n < 0 {
		return -n
	}

	return n
}

func swipeNegatives(inputs []int) []int {
	j := 0
	// O(n)
	for i, number := range inputs {
		if number <= 0 {
			inputs[j], inputs[i] = inputs[i], inputs[j]
			j++
		}
	}

	return inputs[j:]
}

func markVistited(inputs []int) {
	// O(n)
	for i, number := range inputs {
		if abs(number)-1 < len(inputs) {
			if inputs[abs(inputs[i])-1] > 0 {
				inputs[abs(inputs[i])-1] = -inputs[abs(inputs[i])-1]
			}
		}
	}
}

// T: O(3n) in total -> O(n)
// S: O(1)
func solution(inputs []int) int {
	inputs = swipeNegatives(inputs) // input is sliced so Space complexity stays intact
	markVistited(inputs)

	// O(n)
	for i, n := range inputs {
		if n > 0 {
			return i + 1
		}
	}

	return len(inputs) + 1
}

func main() {
}
