// Algorithm: Fast I/O with Buffer
// Supports: Fast reading and writing of signed/unsigned integers and strings
// Complexity: O(1) amortized per character/integer
// Preconditions: Reads from standard input via fread into internal 64KB buffer

#include <bits/stdc++.h>
using namespace std;

namespace FastIO {
    static constexpr int BUF_SIZE = 1 << 16;
    static char in_buf[BUF_SIZE];
    static int in_head = 0, in_tail = 0;

    static char out_buf[BUF_SIZE];
    static int out_head = 0;

    inline char gc() {
        if (in_head == in_tail) {
            in_head = 0;
            in_tail = (int)fread(in_buf, 1, BUF_SIZE, stdin);
            if (in_head == in_tail) return EOF;
        }
        return in_buf[in_head++];
    }

    template <typename T>
    inline bool read_int(T& val) {
        char c = gc();
        val = 0;
        int sgn = 1;
        while (c != EOF && c <= ' ') c = gc();
        if (c == EOF) return false;
        if (c == '-') {
            sgn = -1;
            c = gc();
        }
        while (c >= '0' && c <= '9') {
            val = val * 10 + (c - '0');
            c = gc();
        }
        val *= sgn;
        return true;
    }

    inline void flush_out() {
        if (out_head > 0) {
            fwrite(out_buf, 1, out_head, stdout);
            out_head = 0;
        }
    }

    inline void pc(char c) {
        if (out_head == BUF_SIZE) flush_out();
        out_buf[out_head++] = c;
    }

    template <typename T>
    inline void write_int(T val, char endc = '\0') {
        if (val < 0) {
            pc('-');
            val = -val;
        }
        static char s[32];
        int top = 0;
        do {
            s[top++] = (char)('0' + (val % 10));
            val /= 10;
        } while (val > 0);
        while (top > 0) pc(s[--top]);
        if (endc != '\0') pc(endc);
    }

    struct Flusher {
        ~Flusher() { flush_out(); }
    } flusher;
}
