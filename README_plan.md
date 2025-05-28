# Ocean Survival (大鱼吃小鱼) 项目计划

## 一、项目概述
- **项目类型**: 2D休闲生存游戏
- **开发周期**: 3周
- **代码规模**: 约2000行C++代码
- **目标平台**: Windows
- **技术栈**: 
  - C++20标准
  - SDL2
  - SDL_image
  - SDL_ttf
  - SDL_mixer

## 二、核心游戏机制
1. 玩家控制鱼的游动（WSAD）
2. 吃掉比自己小的鱼来成长
3. 避免被更大的鱼吃掉
4. 体积随积累得分而增长

## 三、功能需求
### 核心功能
- 鱼的移动控制
- 其他鱼类（食物和敌鱼）的生成与碰撞检测
- 鱼身增长机制
- 边界障碍物碰撞检测
- 分数计算与显示

### 扩展功能
- 障碍物生成
- 多级难度（目标分数差异）
- 特殊鱼类（加速/减速/加分）
- 游戏暂停/结束
- 最高分纪录显示

## 四、技术设计
### 类结构设计
```cpp
class GameState {
    // 游戏状态管理
};

class PlayerFish {
    // 玩家控制的鱼
};

class AIFish {
    // 不受玩家控制的鱼类
};

class InputHandler {
    // 键盘输入处理
};
```

### 关键数据结构
1. 二维数组表示游戏地图
2. 结构体存储游戏状态：
```cpp
struct GameStatus {
    int score;
    float size;
    float moveSpeed;
};
```

## 五、开发阶段划分
### 第1阶段：基础搭建（3天）
- 交付物：
  - 可运行的最小框架（显示窗口+空游戏循环）
  - 实体管理系统原型
  - 美术资源清单

### 第2阶段：核心玩法（5天）
- 玩家控制实现
- AI鱼行为状态机设计
- 碰撞检测性能优化

### 第3阶段：系统完善（4天）
### 第4阶段：测试与报告（3天）

## 六、详细分工方案
### 后端开发（游戏逻辑）
**关键代码**：
```cpp
class GameState {
    std::vector<std::unique_ptr<Entity>> entities;
    
    void serialize(std::ofstream& saveFile) {
        // 存档序列化
    }
};
```

### 前端开发（渲染优化）
**SDL2渲染示例**：
```cpp
// 使用纹理图集
SDL_Rect frameRect = { frameIndex * 64, 0, 64, 64 };
SDL_RenderCopyEx(renderer, spritesheet, &frameRect, &destRect, angle, nullptr, flip);
```

### 算法设计（核心系统）
**动态难度调整**：
```cpp
float calcSpawnRate() {
    return baseRate + playerSize * 0.1f;
}
```

### UI系统
**进度条绘制**：
```cpp
class UIManager {
    void drawBar(SDL_Renderer* r, float percent, SDL_Color c) {
        // 绘制动态进度条
    }
};
```

### 测试开发
**单元测试示例**：
```cpp
TEST_CASE("Player growth") {
    PlayerFish p;
    p.grow(0.5f);
    REQUIRE(p.getSize() == 1.5f);
}
```