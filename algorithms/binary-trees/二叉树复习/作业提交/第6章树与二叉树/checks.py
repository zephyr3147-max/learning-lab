"""本地检查：样例、空树、单结点、重复值，以及随机小树的独立结果对照。"""
import heapq
import random
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parent
RNG = random.Random(12399)
COUNTS = {i: 0 for i in range(1, 10)}


def check(number, data, expected):
    exe = next((ROOT / "build").glob(f"{number:02}_*.exe"))
    result = subprocess.run(
        [str(exe)], input=data, text=True, capture_output=True, timeout=5
    )
    assert result.returncode == 0, (number, result.stderr)
    assert result.stdout.split() == expected.split(), (
        number, repr(data), repr(expected), repr(result.stdout)
    )
    COUNTS[number] += 1


def make_tree(values):
    if not values:
        return None
    split = RNG.randrange(len(values))
    return (values[0], make_tree(values[1:split + 1]), make_tree(values[split + 1:]))


def walk(t, order):
    if t is None:
        return []
    value, left, right = t
    if order == "pre":
        return [value] + walk(left, order) + walk(right, order)
    if order == "in":
        return walk(left, order) + [value] + walk(right, order)
    return walk(left, order) + walk(right, order) + [value]


def encode(t, empty):
    if t is None:
        return empty
    return str(t[0]) + encode(t[1], empty) + encode(t[2], empty)


def depth(t):
    return 0 if t is None else 1 + max(depth(t[1]), depth(t[2]))


def find(t, value):
    if t is None or t[0] == value:
        return t
    return find(t[1], value) or find(t[2], value)


def encode_int(t):
    if t is None:
        return "0 "
    return str(t[0]) + " " + encode_int(t[1]) + encode_int(t[2])


def mirror(t):
    return None if t is None else (t[0], mirror(t[2]), mirror(t[1]))


def delete(t, value):
    if t is None or t[0] == value:
        return None
    return (t[0], delete(t[1], value), delete(t[2], value))


check(1, "", "T")
check(3, "", "n")

for n in range(32):
    def pre_complete(i):
        if i > n:
            return []
        return [str(i)] + pre_complete(2 * i) + pre_complete(2 * i + 1)
    check(1, f"{n}\n" + " ".join(map(str, range(1, n + 1))),
          " ".join(pre_complete(1)))

check(2, "abdecfg\ndbeafcg\n", "debfgca")
check(4, "ABC**D**CE**F**\n", "C B D A E C F\nC B D A E C F")
check(5, "ab  c  \n", "acb\ncab")
check(5, "a, , \n", "a\na")
check(5, "a,b, , ,c, , \n", "acb\ncab")
check(6, "ABC##D##C#F##\nC\n", "ABD")
check(7, "7\n35 20 19 0 13 0 47\n13\n", "20")
check(8, "5\n2 4 0 0 0\n3 5 0 0 0\n3 1\n", "1")
check(9, "1 2 4\n", "10")

for n in range(27):
    unique = make_tree(list("abcdefghijklmnopqrstuvwxyz"[:n]))
    if n > 0:
        check(2, "".join(walk(unique, "pre")) + "\n" +
              "".join(walk(unique, "in")) + "\n",
              "".join(walk(unique, "post")))
    numeric = make_tree(list(range(1, n + 1)))
    target = RNG.randrange(1, n + 2)
    check(3, encode_int(numeric) + f"\n{target}\n", str(depth(find(numeric, target))))
    repeated = make_tree([RNG.choice("ABCD") for _ in range(n)])
    inorder = " ".join(walk(repeated, "in"))
    check(4, encode(repeated, "*") + "\n", inorder + "\n" + inorder)
    exchanged = mirror(repeated)
    check(5, encode(repeated, " ") + "\n",
          "".join(walk(exchanged, "pre")) + "\n" + "".join(walk(exchanged, "in")))
    check(5, ",".join(encode(repeated, " ")) + "\n",
          "".join(walk(exchanged, "pre")) + "\n" + "".join(walk(exchanged, "in")))
    to_delete = RNG.choice("ABCDE")
    check(6, encode(repeated, "#") + f"\n{to_delete}\n",
          "".join(walk(delete(repeated, to_delete), "pre")))

for n in range(1, 33):
    values = [0] + [3 * i + 7 for i in range(1, n + 1)]
    index = RNG.randrange(1, n + 1)
    check(7, str(n) + "\n" + " ".join(map(str, values[1:])) +
          f"\n{values[index]}\n", str(values[index // 2]))
    check(7, str(n) + "\n" + " ".join(map(str, values[1:])) +
          f"\n{values[1]}\n", "0")

for n in range(1, 27):
    tree = make_tree(list(range(1, n + 1)))
    left = [0] * (n + 1)
    right = [0] * (n + 1)
    def record(t):
        if t is not None:
            left[t[0]] = 0 if t[1] is None else t[1][0]
            right[t[0]] = 0 if t[2] is None else t[2][0]
            record(t[1])
            record(t[2])
    record(tree)
    for u, v in [(RNG.randrange(1, n + 1), 1), (1, 1), (1, n)]:
        subtree = find(tree, v)
        expected = u != v and u in walk(subtree, "pre")
        check(8, f"{n}\n" + " ".join(map(str, left[1:])) + "\n" +
              " ".join(map(str, right[1:])) + f"\n{u} {v}\n",
              "1" if expected else "0")

for n in range(1, 10):
    for _ in range(4):
        weights = [RNG.randrange(0, 10001) for _ in range(n)]
        heap = weights.copy()
        heapq.heapify(heap)
        total = 0
        while len(heap) > 1:
            merged = heapq.heappop(heap) + heapq.heappop(heap)
            total += merged
            heapq.heappush(heap, merged)
        check(9, " ".join(map(str, weights)) + "  \n999999\n", str(total))

for number, count in COUNTS.items():
    print(f"Problem {number}: {count} checks passed")
print(f"All {sum(COUNTS.values())} checks passed.")
