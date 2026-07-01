public class NonDuplicateNumberInstances {
    public int moveElements(int[] arr) {
        if (arr == null || arr.length == 0) {
            return 0;
        }

        // Initialize the index of the next non-duplicate element. This variable will
        // keep track of the position where the next unique element should be placed.
        int nextNonDuplicate = 1;

        // Iterate through the array starting from the second element
        for (int i = 1; i < arr.length; i++) {
            // Check if the current element is different from the previous non-duplicate
            // element
            if (arr[nextNonDuplicate - 1] != arr[i]) {
                // If different, copy the current element to the nextNonDuplicate position
                arr[nextNonDuplicate] = arr[i];
                // Increment the index of the next non-duplicate element
                nextNonDuplicate++;
            }
        }

        // Return the length of the modified array (number of non-duplicate elements)
        return nextNonDuplicate;
    }
}
