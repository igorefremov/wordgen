// Copyright (c) 2018 Igor Efremov
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software"), to deal 
// in the Software without restriction, including without limitation the rights 
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
// copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all 
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
// SOFTWARE.

#include <stdint.h>
#include <stdio.h>
#include <string.h>

static int16_t const _word_terminator = -1;
static char const _charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890";
static int const _max_length = 4;

static int _last_charset_index;

static int increment_word(int16_t * const word, int const index, int const length) {
    if(index == length) {
        return 0;
    }

    if(word[index] == _last_charset_index) {
        if(!increment_word(word, index + 1, length)) {
            return 0;
        }
        word[index] = 0;
    } else {
        // This works for both the (word[index] == _word_terminator) and (word[index] < _last_char_index) 
        // cases because _word_terminator is -1
        word[index] = word[index] + 1;
    }

    return 1;
}

static void print_word(int16_t * const word, int const length) {
    for(int i = 0; (i < length) && (word[i] != -1); fputc(_charset[word[i++]], stdout));
    fputc('\n', stdout);
    return;
}

int main(int nargs, char **argv) {
    _last_charset_index = strlen(_charset) - 1;
    if(_last_charset_index < 1) {
        fprintf(stderr, "invalid charset\n");
        return 1;
    }

    int16_t word[_max_length];

    for(int i = 0; i < _max_length; word[i++] = _word_terminator);
    for(; increment_word(word, 0, _max_length); print_word(word, _max_length));

    return 0;
}