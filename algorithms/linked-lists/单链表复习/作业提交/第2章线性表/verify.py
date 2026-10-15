"""Run compiled submission programs against samples and array-model cases."""
from pathlib import Path
import random
import subprocess

BASE = Path(__file__).resolve().parent / 'build'
COUNT = 0

def check(number, data, expected):
    global COUNT
    result = subprocess.run([str(BASE / f'q{number}.exe')], input=data,
                            text=True, encoding='utf-8', capture_output=True, timeout=3, check=True)
    assert result.stdout == expected + '\n', (number, data, result.stdout, expected)
    COUNT += 1

def line(values):
    return ' '.join(map(str, values))

check(3, '3 5\n1 2 3\n4 5 6 7 8\n', '1，4，2，5，3，6，7，8')
check(3, '5，6，\n1，2，3，4，5\n6，7，8，9，10，11\n', '1，6，2，7，3，8，4，9，5，10，11')
check(3, '2,1,\n-3,4\n7\n', '-3，7，4')
check(4, '1 3 5 7 7 9 10 12 -1\n3 9 -1\n', '1 3 9 10 12')
check(5, '1 3 4 5 6 9 -1\n2 3 7 8 12 -1\n', '1 2 3 3 4 5 6 7 8 9 12')
check(6, '1 2 2 3\n', '1 2 3')

rng = random.Random(12208)
for _ in range(100):
    a = [rng.randrange(-20, 21) for _ in range(rng.randrange(20))]
    b = [rng.randrange(-20, 21) for _ in range(rng.randrange(20))]
    common = min(len(a), len(b))
    merged = [v for pair in zip(a, b) for v in pair] + a[common:] + b[common:]
    check(3, f'{len(a)} {len(b)}\n{line(a)}\n{line(b)}\n', '，'.join(map(str, merged)))
    a = sorted(v for v in a if v != -1)
    b = sorted(v for v in b if v != -1)
    low, high = rng.randrange(-25, 26), rng.randrange(-25, 26)
    check(4, f'{line(a + [-1])}\n{low} {high} -1\n',
          line([v for v in a if not low < v < high]))
    check(5, f'{line(a + [-1])}\n{line(b + [-1])}\n', line(sorted(a + b)))
    values = sorted(a + b + [-1, -1])
    check(6, line(values), line(sorted(set(values))))

for number in (3, 4, 5, 6):
    data = {3: '0 0\n', 4: '-1\n0 1 -1\n', 5: '-1\n-1\n', 6: ''}[number]
    check(number, data, '')
check(6, '7 7 7 7\n', '7')
print(f'PASS: {COUNT} sample, boundary and model checks')
