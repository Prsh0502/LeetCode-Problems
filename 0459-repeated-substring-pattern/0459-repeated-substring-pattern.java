class Solution {
    public boolean repeatedSubstringPattern(String s) {
        int n = s.length();

        for (int len = 1; len <= n / 2; len++) {

            // Substring length must divide
            // the complete string length
            if (n % len != 0) {
                continue;
            }

            boolean valid = true;

            // Compare with the first substring
            for (int i = len; i < n; i++) {
                if (s.charAt(i) != s.charAt(i % len)) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                return true;
            }
        }

        return false;
    }
}