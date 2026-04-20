READ me.md
# 空洞骑士融合游戏

一个基于C++和状态机架构开发的横版动作游戏原型，融合了《空洞骑士》的核心玩法与其他游戏的创意元素，探索不同游戏机制的碰撞与结合。

## 项目简介

本项目是一个实验性质的2D横版动作游戏，从《空洞骑士》等经典游戏中汲取灵感，尝试将快节奏的战斗、复杂的平台跳跃与角色成长系统融为一体。游戏采用自定义游戏引擎，运用有限状态机（FSM）来管理玩家和敌人的行为逻辑，提供了流畅的操作反馈和丰富的战斗体验。

## 主要特性

- **核心玩法系统**：实现了玩家角色的移动、跳跃、攻击等核心动作，拥有完整的动画状态机控制。
- **战斗机制**：包含近战攻击、子弹时间等特殊机制，设计了多样化的敌人AI行为。
- **碰撞检测系统**：完整的碰撞管理机制，支持多层级碰撞层判定。
- **资源管理**：通过资源管理器统一加载和管理游戏中的贴图、音频等资源。
- **状态机架构**：玩家和敌人均通过状态节点控制行为，便于扩展新的动作和AI逻辑。
- **简单易用的构建**：基于Visual Studio 2022的项目配置，开箱即用。

## 技术栈

- **编程语言**：C++17
- **开发环境**：Visual Studio 2022
- **图形库**：基于Windows GDI / 自定义渲染管线（根据项目实际依赖调整）
- **项目结构**：使用`.sln`解决方案文件和`.vcxproj`工程文件管理代码。

## 快速开始

### 环境要求

- Windows操作系统
- Visual Studio 2022（或更高版本），安装“使用C++的桌面开发”工作负载

### 克隆仓库

```bash
git clone https://github.com/YIJIA257/-.git
打开项目
双击项目根目录下的kongdongqishi.sln文件，使用Visual Studio打开解决方案。

编译与运行
在Visual Studio中，选择Debug或Release配置。

按F5或点击“本地Windows调试器”按钮，编译并运行游戏。

注意：如果资源文件（如图片、音频）缺失，请检查kongdongqishi/resources目录是否包含必要的游戏资源，并根据实际文件路径调整代码中的资源加载逻辑。
├── kongdongqishi.sln          # Visual Studio 解决方案文件
├── kongdongqishi/             # 项目主目录
│   ├── resources/             # 游戏资源文件（图片、音频等）
│   └── *.vcxproj*             # 项目配置文件
├── main.cpp                   # 程序入口
├── player.cpp / player.h      # 玩家角色逻辑
├── enemy.cpp / enemy.h        # 敌人角色逻辑
├── sword.cpp / sword.h        # 武器系统
├── animation.h                # 动画系统
├── atlas.h                    # 贴图图集管理
├── collision_manager.cpp/h    # 碰撞检测管理器
├── state_machine.cpp/h        # 状态机核心逻辑
├── state_node.h               # 状态节点基类
├── player_state_nodes.cpp/h   # 玩家状态节点（站立、移动、攻击等）
├── enemy_state_nodes.cpp/h    # 敌人状态节点（巡逻、追击、攻击等）
├── resources_manager.cpp/h    # 资源加载管理器
├── bullet_time_manager.cpp/h  # 子弹时间特效管理器
├── character.cpp/h            # 角色基类
└── util.h / vector2.h         # 工具函数与数学库
