# Ternary Huffman Encoding Using Priority Query

A modified Huffman algorithm is implemented for compressing sequences of characters from an alphabet of size n, where the characters
occur with known frequencies f1, f2, …, fn. The algorithm encodes each character with a variable-length code word over the values 0, 1, 2 such that no code word is a prefix of another code word and so as to obtain the maximum possible compression.

## Time Complexity

To count the frequency of each character in the alphabet, count sort is used which takes O (N). Priority Queue operations take O (log N) time and these are called in a loop for n/2 characters. Therefore, the overall time complexity would be O (N log N).

# Correctness Proof

The detailed proof is given the Proof.pdf file.

# Directory Structure

<pre>
📦Huffman-Encoding-Using-Priority-Queue
 ┣ 📜CMakeLists.txt
 ┣ 📜main.cpp
 ┣ 📜Proof.pdf
 ┗ 📜README.md
</pre>
