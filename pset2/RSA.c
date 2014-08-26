// devigenere vigenere.c

int main()
{
    // Generate two Prime numbers p & q     e.g. p = 61 and q = 53

    // Multiply p & q and store in n        e.g. n = 61 \times 53 = 3233
    
    // calculate (p-1)*(q-1) store in m     e.g. m = (61 - 1)(53 - 1) = 3120
    
    /** Generate e such that 1 < e < m 
      * {e should be prime}
      * {e should be coprime of m} 
      * { m should not be divisible by e}   e.g. e = 17
      */
    
    // calculate d in such a way that  (d * e) % m == 1     e.g. d = 2753
    
    // Encrypt using formula cm = m ^ e % n                 e.g. cm = 65 ^ 17 % 3233 = 2790 

    
    // Decript mc = c ^ d % n                               e.g. mc = 2790 ^ 2753 % 3233 = 65 
}
