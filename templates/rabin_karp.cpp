#include<bits/stdc++.h>
using namespace std;
#define ll long long
class RabinKarp {
public:
    const ll Radix1 = 31;
    const ll Mod1 = 1e9 + 7;
    const ll Radix2 = 37;
    const ll Mod2 = 1e9 + 9;

    vector<ll> pow1, pow2;

    // Precompute powers of radix up to maxLen
    void precomputePowers(int maxLen) {
        pow1.assign(maxLen + 1, 1);
        pow2.assign(maxLen + 1, 1);
        for (int i = 1; i <= maxLen; ++i) {
            pow1[i] = (pow1[i - 1] * Radix1) % Mod1;
            pow2[i] = (pow2[i - 1] * Radix2) % Mod2;
        }
    }

    // Compute hash pair for a string
    pair<ll, ll> computeHash(const string& s, int len) {
        ll h1 = 0, h2 = 0;
        for (int i = 0; i < len; ++i) {
            h1 = (h1 * Radix1 + (s[i] - 'a')) % Mod1;
            h2 = (h2 * Radix2 + (s[i] - 'a')) % Mod2;
        }
        return {h1, h2};
    }

    // Update rolling hash
    void rollHash(pair<ll, ll>& hash, char outChar, char inChar, int len) {

        //hash_i+1 = hash_i*maxweight - s[i]*(radix)^m + s[i+m]
        hash.first = ((hash.first - (outChar - 'a') * pow1[len - 1] % Mod1 + Mod1) * Radix1 + (inChar - 'a')) % Mod1;
        hash.second = ((hash.second - (outChar - 'a') * pow2[len - 1] % Mod2 + Mod2) * Radix2 + (inChar - 'a')) % Mod2;
    }

    // Main search function: returns first index of pattern in text or -1
    int search(const string& text, const string& pattern) {
        int n = text.size(), m = pattern.size();
        if (m > n) return -1;

        precomputePowers(m);
        pair<ll, ll> patternHash = computeHash(pattern, m);
        pair<ll, ll> currHash = computeHash(text, m);

        if (currHash == patternHash) return 0;

        for (int i = m; i < n; ++i) {
            rollHash(currHash, text[i - m], text[i], m);
            if (currHash == patternHash) return i - m + 1;
        }

        return -1;
    }
};

class Solution {
public:
    int strStr(string haystack, string needle) {
        RabinKarp rk;
        return rk.search(haystack, needle);
    }
};

