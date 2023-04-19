#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mhash.h>

 char get_next_char(char a, const char *alphabet, size_t alphabet_len) {
    if(a == alphabet[alphabet_len]) {
        return 0;
    }
    size_t aidx = a - alphabet[0];
    aidx++;
    if(aidx == alphabet_len) {
        return 0;
    }
    return alphabet[aidx];
}

size_t generate_next_word(char *current_word, size_t word_len, const char *alphabet, size_t alphabet_len) {
    for(size_t i = 1;i<=word_len;i++) {
        char next = get_next_char(current_word[word_len - i], alphabet, alphabet_len);
        if(next != 0) {
            current_word[word_len - i] = next;
            for(size_t j = word_len - i + 1;j<word_len;j++) {
                current_word[j] = alphabet[0];
            }
            return word_len;
        }
    }

    // Extend word
    word_len++;
    for(size_t i = 0;i<word_len;i++) {
        current_word[i] = alphabet[0];
    }
    current_word[word_len] = 0;

    return word_len;
}

void md5_printf(unsigned char* hash) {
        printf("%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X",
               hash[0], hash[1], hash[2], hash[3], hash[4], hash[5], hash[6], hash[7],
               hash[8], hash[9], hash[10], hash[11], hash[12], hash[13], hash[14], hash[15]);
}

char *allocate_alphabet() {
    char *result = calloc(0x7F - 0x20 + 1, 1);
    for(unsigned char i = 0x20;i<0x7F;i++) {
        int idx = i - 0x20;
        result[idx] = (char ) i;
    }
    return result;
}

int main() {
    char *word = calloc(33, 1);
    char *full_alphabet = allocate_alphabet();
    word[0] = full_alphabet[0];

    MHASH td;
    size_t word_len = strlen(word);
    while (word_len < 33) {
        td = mhash_init(MHASH_MD5);
        if (td == MHASH_FAILED) exit(1);
        word_len = generate_next_word(word, word_len, full_alphabet, strlen(full_alphabet));
        mhash(td, word, word_len);
        unsigned char hash[16];
        mhash_deinit(td, hash);
        printf("%s\t", word);
        md5_printf(hash);
        printf("\n");
    }
    free(word);
    return 0;
}