import java.util.ArrayDeque;
import java.util.Queue;

class MyStack {
    private Queue<Integer> queue;

    public MyStack() {
        queue = new ArrayDeque<>();
    }
    
    // Push element x onto stack.
    public void push(int x) {
        queue.add(x);
        int size = queue.size();
        
        // Rotate the previous elements behind the newly inserted element
        for (int i = 0; i < size - 1; i++) {
            queue.add(queue.poll());
        }
    }
    
    // Removes the element on the top of the stack and returns it.
    public int pop() {
        return queue.poll();
    }
    
    // Get the top element.
    public int top() {
        return queue.peek();
    }
    
    // Returns whether the stack is empty.
    public boolean empty() {
        return queue.isEmpty();
    }
}