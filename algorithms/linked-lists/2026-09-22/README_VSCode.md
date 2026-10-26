# 在 VS Code 中使用 26_9_22

打开文件夹 `E:\code\c++ learn\26_9_22`，不要只打开单独的 `test.c`。

## 编译与运行

1. 修改代码后保存。Ctrl+Shift+B 编译整个项目，使用 Debug / x64 配置。
2. Ctrl+Shift+P 打开命令面板，输入“运行任务”或 `Tasks: Run Task`，选择 `Run project (build first)`。
3. 点击下方终端，输入 `1 2 3 4 5` 并按 Enter。程序会打印链表测试结果。
4. Ctrl+F5 使用项目的 launch 配置运行，不在断点暂停。

如果需要强制重新编译，在运行任务菜单选择 `Rebuild project (Debug x64)`。编译失败时先修复错误，不要继续执行旧程序。

## 断点调试

1. 打开 test.c，在 `LinkList L = SListInit();` 这一行行号左边点击，设置红色断点。
2. Ctrl+Shift+D 打开运行和调试，选择 `26_9_22: Debug (MSVC x64)`，按 F5。
3. 到断点暂停时，黄色箭头表示下一条要执行的语句。按 F10 执行一行，之后在左侧变量中查看 L。
4. 要观察函数内部，可以在 SList.c 的函数体中设置断点，也可以在调用处按 F11 进入函数。Shift+F11 跳出函数。
5. 按 F5 继续；执行到输入时，在底部终端输入五个整数。Shift+F5 停止调试。

变量尚未初始化时看到的值没有意义，要执行赋值语句后再看。函数调用堆栈可以查看当前函数由谁调用。

## 新建文件与项目成员

在资源管理器中右键项目文件夹，新建 `helper.c` 或 `helper.h`，然后保存。

此项目由 .vcxproj 决定编译哪些文件。新建源文件后，在 VS Code 打开 `26_9_22.vcxproj`，找到包含下面两项的 ItemGroup：

```xml
<ClCompile Include="SList.c" />
<ClCompile Include="test.c" />
```

在同一组中加入 `<ClCompile Include="helper.c" />`。新头文件可以在包含 SList.h 的组中加入 `<ClInclude Include="helper.h" />`。路径相对于项目目录，子文件夹使用相对路径。保存后 Ctrl+Shift+B 编译整个项目。不需要把头文件写成 ClCompile。

同一个可执行程序只保留一个 main。单独的学习练习应放在另一个项目中，不能把两个含 main 的源文件一起加入这个项目。

## 编码与输出

原 test.c 使用 GBK，本项目的源码默认按 GBK 保存，新终端也设为代码页 936，用于正确显示中文。若旧终端仍乱码，关闭旧终端并创建新终端。项目编译任务会先设为 UTF-8 以读取中文工具路径，完成后恢复代码页 936。

UTF-8 文件可以通过右下角编码菜单“通过编码重新打开”选择 UTF-8。不要随意批量转换现有源码编码。

最终程序是 `x64\Debug\26_9_22.exe`。编译由 `.vscode/tasks.json` 调用 MSBuild；调试由 `.vscode/launch.json` 启动这个固定程序，不依赖当前打开哪个源文件。

已验证完整重新编译成功，输入 1–5 后输出链表 1->2->3->4->5，删除后为 2->3->4，程序退出码为 0。断点暂停尚未通过界面实测。
