# Learning Lab · 学习与实践记录

长期记录 C++ 练习、单片机代码、算法题、demo，以及学习过程中的思路、踩坑和心得。

已有练习的分类、文件来源和使用注意事项见 [历史代码归档](IMPORTS.md)。

## 分区

| 目录 | 用途 |
| --- | --- |
| [cpp](cpp/) | C++ 语法、标准库、面向对象及其他练习 |
| [embedded](embedded/) | 单片机、外设、通信协议及嵌入式项目 |
| [algorithms](algorithms/) | 算法题、数据结构与解题复盘 |
| [demos](demos/) | 小项目、功能验证和实验 demo |
| [templates](templates/) | 通用学习记录模板 |

## 如何记录

各分区中使用 `YYYY-MM-DD-主题/` 创建练习目录，把代码和 `README.md` 放在一起。较大的项目可以持续更新同一个目录，在 README 中按日期补充进展。

例如 `cpp/2026-10-05-vector-practice/` 可包含 `main.cpp` 和 `README.md`。这只是命名示例，并非已完成的学习内容。

复制 [学习记录模板](templates/study-note.md) 为练习的 README，填写目标、运行方法、结果和心得。

## 提交习惯

完成一次练习后：

```sh
git add cpp/2026-10-05-vector-practice
git commit -m "study(cpp): vector 练习与心得"
git push
```

将路径和提交说明替换为本次实际内容。推荐格式：`study(分区): 内容`、`fix(分区): 修正问题`、`docs: 补充心得`。

## 学习索引

| 日期 | 分区 | 主题 | 记录 |
| --- | --- | --- | --- |
| 2026-09-01 | C++ | 基础语法 | [练习代码](cpp/basics/2026-09-01/) |
| 2026-09-02 | 算法 | 冒泡排序 | [练习代码](algorithms/sorting/2026-09-02/) |
| 2026-09-04 | C++ | 结构体数组 | [练习代码](cpp/structs/2026-09-04/) |
| 2026-09-14 | 算法 | 数组操作 | [练习代码](algorithms/arrays/2026-09-14/) |
| 2026-09-20 | 算法 | 顺序表 | [练习代码](algorithms/sequential-lists/2026-09-20/) |
| 2026-09-22 | 算法 | 单链表 | [练习代码](algorithms/linked-lists/2026-09-22/) |

每次学习后新增一行，链接到对应练习目录。
