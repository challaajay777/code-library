// Test suite for Strings and Text Algorithms
#include <bits/stdc++.h>
#include <cassert>
#include "Strings and Text Algorithms/string_hashing.cpp"
#include "Strings and Text Algorithms/kmp_prefix_function.cpp"
#include "Strings and Text Algorithms/z_algorithm.cpp"
#include "Strings and Text Algorithms/manacher_palindromes.cpp"
#include "Strings and Text Algorithms/trie.cpp"
#include "Strings and Text Algorithms/binary_trie.cpp"
#include "Strings and Text Algorithms/aho_corasick.cpp"
#include "Strings and Text Algorithms/suffix_automaton.cpp"

using namespace std;

void test_string_hash() {
    string s = "abcdeabcde";
    StringHash sh(s);
    auto h1 = sh.get_hash(0, 4); // "abcde"
    auto h2 = sh.get_hash(5, 9); // "abcde"
    assert(h1 == h2);

    auto h3 = sh.get_hash(1, 3); // "bcd"
    auto h4 = sh.get_hash(6, 8); // "bcd"
    assert(h3 == h4);
    assert(h1 != h3);
}

void test_kmp_and_z() {
    string text = "ababcabcabababd";
    string pat = "ababd";
    auto kmp_res = KMP::search(text, pat);
    assert(kmp_res.size() == 1 && kmp_res[0] == 10);

    auto z_res = ZAlgorithm::search(text, pat);
    assert(z_res.size() == 1 && z_res[0] == 10);

    assert(KMP::smallest_period("abcabcabc") == 3);
    assert(KMP::smallest_period("aaaa") == 1);
}

void test_manacher() {
    string s = "babad"; // "bab" or "aba"
    Manacher m(s);
    assert(m.is_palindrome(0, 2)); // "bab"
    assert(m.is_palindrome(1, 3)); // "aba"
    assert(!m.is_palindrome(0, 3)); // "baba"

    string even_pal = "cbbd";
    Manacher m2(even_pal);
    assert(m2.is_palindrome(1, 2)); // "bb"
}

void test_tries() {
    Trie trie;
    trie.insert("apple");
    trie.insert("app");
    assert(trie.count_word("apple") == 1);
    assert(trie.count_word("app") == 1);
    assert(trie.count_word("appl") == 0);
    assert(trie.count_prefix("app") == 2);
    assert(trie.count_prefix("b") == 0);

    BinaryTrie bt;
    bt.insert(3); // 011
    bt.insert(10); // 1010
    bt.insert(5); // 0101
    // Query max XOR with 6 (0110):
    // 6 ^ 3 = 5
    // 6 ^ 10 = 12
    // 6 ^ 5 = 3
    // Max XOR is 12
    assert(bt.query_max_xor(6) == 12);
}

void test_aho_corasick_and_sam() {
    AhoCorasick ac;
    int id1 = ac.insert("he");
    int id2 = ac.insert("she");
    int id3 = ac.insert("his");
    int id4 = ac.insert("hers");
    ac.build();

    string text = "ushers";
    auto occ = ac.count_occurrences(text);
    // In "ushers": "he" appears at index 2..3 (1 occurrence)
    assert(occ[id1] == 1);
    assert(occ[id2] == 1); // "she" at 1..3
    assert(occ[id3] == 0); // "his"
    assert(occ[id4] == 1); // "hers" at 2..5

    // Suffix Automaton
    string str = "ababa";
    SuffixAutomaton sam(str.size());
    for (char c : str) sam.extend(c);
    // Distinct substrings of "ababa":
    // len 1: a, b (2)
    // len 2: ab, ba (2)
    // len 3: aba, bab (2)
    // len 4: abab, baba (2)
    // len 5: ababa (1)
    // Total = 9
    assert(sam.count_distinct_substrings() == 9);
}

int main() {
    cout << "[TEST] Running test_strings suite...\n";
    test_string_hash();
    test_kmp_and_z();
    test_manacher();
    test_tries();
    test_aho_corasick_and_sam();
    cout << "[TEST] All 5 test sets in test_strings passed!\n";
    return 0;
}
