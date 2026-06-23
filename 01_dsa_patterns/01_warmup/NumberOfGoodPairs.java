public class NumberOfGoodPairs {
    public int numGoodPairs(int[] nums) {
        int[] counts = new int[101]; // 1 <= nums[i] <= 100 so that's why using array otheriwse use hashmap
        int pairCount = 0;
        for (int n : nums) {
            pairCount += counts[n]++; // Adds current count to pairs, THEN increments the count.
        }
        return pairCount;
    }
}
