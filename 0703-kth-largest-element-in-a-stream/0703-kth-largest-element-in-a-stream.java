import java.util.PriorityQueue;

class KthLargest {
    private PriorityQueue<Integer> minHeap;
    private int k;

    public KthLargest(int k, int[] nums) {
        this.k = k;
        this.minHeap = new PriorityQueue<>();
        
        for (int num : nums) {
            add(num);
        }
    }
    
    public int add(int val) {
        minHeap.add(val);
        
        // Retain only the k largest elements in the heap
        if (minHeap.size() > k) {
            minHeap.poll();
        }
        
        return minHeap.peek();
    }
}