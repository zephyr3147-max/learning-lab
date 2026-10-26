#define main palindrome_program_main
#include "../考试背诵版/回文字符串_顺序栈.c"
#undef main
#include <assert.h>

int main(void)
{
    SqStack S;
    char ch = '?';
    InitStack(&S);
    assert(S.top == -1);
    assert(Pop(&S, &ch) == 0);
    assert(ch == '?');
    for (int i = 0; i < MAX_SIZE; i++)
    {
        assert(Push(&S, (char)('a' + i % 26)) == 1);
    }
    assert(Push(&S, 'x') == 0);
    assert(S.top == MAX_SIZE - 1);
    for (int i = MAX_SIZE - 1; i >= 0; i--)
    {
        assert(Pop(&S, &ch) == 1);
        assert(ch == (char)('a' + i % 26));
    }
    assert(S.top == -1);
    assert(Pop(&S, &ch) == 0);
    assert(IsPalindrome("") == 1);
    assert(IsPalindrome("level") == 1);
    assert(IsPalindrome("abca") == 0);
    puts("All stack operation checks passed.");
    return 0;
}
