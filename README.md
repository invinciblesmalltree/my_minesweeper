# MyMinesweeper

此程序是南京邮电大学程序设计实践课程的作品

## 项目简介

这是一个基于 Qt6 的游戏，实现了基本的扫雷功能，包括左键点击翻开格子，右键标记格子，左右键快速翻开周围的格子等功能。

字体来自「一款开放世界冒险 RPG 游戏：原神」。

## TL;DR

点击开始游戏，选择难度后即可开始游戏。游戏中左键点击翻开格子，右键标记格子，左右键快速翻开周围的格子。翻开所有非雷格子即可获胜。翻开雷格子即为失败。获胜后可以输入名字记录成绩。

AI 玩家可以自动开始玩游戏。

排行榜使用 SQLite 数据库存储，可以查看所有玩家的历史游戏记录。数据库存储在 `db/record_data.db` 中。

具体的游戏规则请查阅游戏内的“玩法说明”。

## 项目结构

- `src/`：源代码
- `include/`：头文件
- `db/`：数据库文件
- `images/`：资源文件
- `README.md`：项目说明文档
- `LICENSE`：开源协议
- `resources.qrc`：资源文件
- `main.cpp`：主函数
- `main_menu.cpp`：主菜单界面
- `difficulty_menu.cpp`：难度选择界面
- `custom_ui.cpp`：自定义难度界面
- `game_ui.cpp`：游戏界面
- `gameover_win_ui.cpp`：游戏胜利记录名字界面
- `ai_player.cpp`：AI 玩家
- `restart_ui.cpp`：重新开始游戏界面
- `ranking_table_ui.cpp`：排行榜界面
- `record_dao.cpp`：数据库操作
- `instructions_ui.cpp`：玩法说明界面
- `about_ui.cpp`：关于界面
