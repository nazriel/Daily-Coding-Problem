package main

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

func solution(inputs []int) int {
	inputs = swipeNegatives(inputs) // input is sliced so Space complexity stays intact
	return 0
}

func main() {
}
