# 大连民族大学 C++ 课程设计 API 文档

本文档详细说明了大连民族大学C++课程设计"大鱼吃小鱼"游戏项目中提供的两个主要API模块：`lx`和`lyt`。这两个模块分别提供了游戏中鱼类的行为管理和游戏引擎的基础功能。

## 目录

1. [LX API - 鱼类管理模块](#lx-api---鱼类管理模块)
   - [Fish - 鱼类基类](#fish---鱼类基类)
   - [AIFish - AI控制的鱼类](#aifish---ai控制的鱼类)
   - [PlayerFish - 玩家控制的鱼类](#playerfish---玩家控制的鱼类)
   - [ScoreManager - 分数管理器](#scoremanager---分数管理器)

2. [LYT API - 游戏引擎模块](#lyt-api---游戏引擎模块)
   - [Game - 游戏管理类](#game---游戏管理类)
   - [Window - 窗口管理](#window---窗口管理)
   - [Renderer - 渲染器](#renderer---渲染器)
   - [Controller - 控制器](#controller---控制器)
   - [Image - 图像管理](#image---图像管理)
   - [Text - 文本渲染](#text---文本渲染)
   - [Button - 按钮组件](#button---按钮组件)


## LX API - 鱼类管理模块

LX API 是由雷烜和汤觐瑄开发的鱼类管理模块，提供了游戏中与鱼类相关的所有类和功能。

### Fish - 鱼类基类

`Fish`类是所有鱼类的基类，定义了鱼的基本属性和接口。

#### 主要功能

- **构造与初始化**：通过指定渲染器、图像路径以及位置和大小来创建鱼对象
- **状态更新**：提供纯虚函数`update()`供子类实现鱼的移动和状态更新
- **渲染**：将鱼绘制到屏幕上
- **碰撞检测**：通过`getRect()`获取鱼的位置和大小信息
- **成长管理**：通过`grow()`方法让鱼变大

#### 主要方法

| 方法                                                                                        | 描述                 |
|-------------------------------------------------------------------------------------------|--------------------|
| `Fish(lyt::Renderer* renderer, const std::string& imagePath, int x, int y, int w, int h)` | 构造函数，初始化鱼的位置、大小和纹理 |
| `virtual ~Fish()`                                                                         | 析构函数，释放资源          |
| `virtual void update(int windowW, int windowH) = 0`                                       | 更新鱼的状态（纯虚函数）       |
| `virtual void render() const`                                                             | 渲染鱼到屏幕             |
| `virtual bool isAlive() const`                                                            | 判断鱼是否存活            |
| `virtual void grow(float scale)`                                                          | 让鱼变大               |
| `virtual SDL_Rect getRect() const`                                                        | 获取鱼的矩形区域           |
| `virtual float getSize() const`                                                           | 获取鱼的面积             |
| `void kill()`                                                                             | 杀死鱼                |

### AIFish - AI控制的鱼类

`AIFish`类继承自`Fish`类，实现了由随机控制的鱼类行为。

#### 主要功���

- **自动移动**：AI鱼能够自主在屏幕上移动
- **随机生成**：通过静态方法`createRandomFish()`可以生成随机方向的AI鱼
- **体积与类型**：支持通过`FishType`结构定义不同体积范围的鱼类类型

#### 主要方法

| 方法                                                                                                                                                             | 描述               |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------|------------------|
| `AIFish(lyt::Renderer* renderer, const std::string& imagePath, int x, int y, int w, int h)`                                                                    | 构造函数，初始化AI鱼对象    |
| `static AIFish createRandomFish(lyt::Renderer* renderer, const std::vector<FishType>& fishTypes, int windowW, int windowH, std::mt19937& gen, int playerSize)` | 创建随机鱼的静态方法       |
| `void update(int windowW, int windowH) override`                                                                                                               | 更新AI鱼的状态（覆盖基类方法） |

### PlayerFish - 玩家控制的鱼类

`PlayerFish`类继承自`Fish`类，实现了由玩家控制的鱼类行为。

#### 主要功能

- **玩家控制**：响应键盘或鼠标输入控制鱼的移动
- **吃鱼逻辑**：通过`tryEat()`方法判断是否可以吃掉AI鱼
- **位置重置**：提供方法重置玩家鱼的位置

#### 主要方法

| 方法                                                                                              | 描述                |
|-------------------------------------------------------------------------------------------------|-------------------|
| `PlayerFish(lyt::Renderer* renderer, const std::string& imagePath, int x, int y, int w, int h)` | 构造函数，初始化玩家鱼的位置和图片 |
| `void update(int windowW, int windowH) override`                                                | 更新玩家鱼的位置和状态       |
| `void handleInput(const lyt::Controller* controller)`                                           | 处理输入控制类键盘或鼠标）     |
| `bool tryEat(AIFish& ai, ScoreManager& scoreManager)`                                           | 尝试吃掉AI鱼，成功则加分     |
| `void resetPosition(int x, int y)`                                                              | 重置玩家鱼的位置          |

### ScoreManager - 分数管理器

`ScoreManager`类负责管理游戏中的分数系统。

#### 主要功能

- **分数记录**：记录游戏中的当前分数和最高分数
- **分数增加**：根据吃掉的鱼的大小增加分数
- **高分保存**：保存和加载最高分记录

#### 主要方法

| 方法                         | 描述               |
|----------------------------|------------------|
| `ScoreManager()`           | 构造函数，初始化分数并读取最高分 |
| `void add(int value)`      | 增加分数             |
| `int getScore() const`     | 获取当前分数           |
| `int getHighScore() const` | 获取最高分            |
| `void saveHighScore()`     | 保存最高分到文件         |
| `void reset()`             | 重置当前分数为0         |

## LYT API - 游戏引擎模块

LYT API 是由李岳烔开发的游戏引擎模块，提供了游戏开发所需的基础功能组件。

### Game - 游戏管理类

`Game`类是游戏引擎的核心类，负责管理游戏的主要功能和生命周期。

#### 主要功能

- **游戏初始化**：初始化SDL环境和游戏资源
- **游戏循环**：管理游戏的主循环，包括处理事件、更新状态和渲染画面
- **帧率控制**：控制游戏的运行帧率
- **资源管理**：管理游戏窗口和渲染器资源

#### 主要方法

| 方法                                                                                          | 描述            |
|---------------------------------------------------------------------------------------------|---------------|
| `Game()`                                                                                    | 默认构造函数        |
| `~Game()`                                                                                   | 析构函数，负责清理游戏资源 |
| `bool init(const std::string& title, int x, int y, int width, int height, bool fullscreen)` | 初始化游戏         |
| `void handleEvents()`                                                                       | 处理事件          |
| `void update()`                                                                             | 更新游戏状态        |
| `void render()`                                                                             | 渲染画面          |
| `void clean()`                                                                              | 清理资源          |
| `bool running() const`                                                                      | 获取游戏运行状态      |
| `Renderer* getRenderer() const`                                                             | 获取渲染器         |

### Window - 窗口管理

`Window`类负责管理游戏窗口的创建和操作。

#### 主要功能

- **窗口创建**：创建和初始化SDL窗口
- **事件处理**：处理与窗口相关的SDL事件
- **窗口配置**：设置窗口标题、图标和尺寸等属性

#### 主要方法

| 方法                                                        | 描述                     |
|-----------------------------------------------------------|------------------------|
| `Window()`                                                | 默认构造函数，创建空窗口对象         |
| `Window(SDL_Window* window)`                              | 使用现有SDL_Window指针构造窗口对象 |
| `Window(const std::string& title, int width, int height)` | ���用指定标题、宽度和高度创建窗口     |
| `~Window()`                                               | 析构函数，负责清理窗口资源          |
| `void handleEvents(SDL_Event& event)`                     | 处理窗口相关的SDL事件           |
| `SDL_Window* get() const`                                 | 获取SDL_Window指针         |
| `int width() const`                                       | 获取窗口宽度                 |
| `int height() const`                                      | 获取窗口高度                 |
| `void setIcon(const std::string& filePath)`               | 设置窗口图标                 |

### Renderer - 渲染器

`Renderer`类封装了SDL渲染功能渲染器提供绘制图像、形状和文本的方法。

#### 主要功能

- **渲染管理**：负责处理SDL渲染相关操作
- **纹理处理**：加载和管理纹理资源
- **绘制操作**：提供各种绘制方法将内容呈现到屏幕

#### 主要方法

| 方法                                                                                                                                             | 描述                          |
|------------------------------------------------------------------------------------------------------------------------------------------------|-----------------------------|
| `Renderer()`                                                                                                                                   | 默认构造函数，创建空渲染器对象             |
| `Renderer(SDL_Renderer* renderer)`                                                                                                             | 使用已存在的SDL_Renderer指针构造渲染器对象 |
| `Renderer(const Window* window, bool vsync)`                                                                                                   | 从窗口创建渲染器，可指定是否启用垂直同步        |
| `~Renderer()`                                                                                                                                  | 析构函数，清理渲染器资源                |
| `void clear()`                                                                                                                                 | 清除渲染目标                      |
| `void present() const`                                                                                                                         | 将渲染内容呈现到屏幕                  |
| `int copy(SDL_Texture* texture, const SDL_Rect* src, const SDL_Rect* dst, double angle, const SDL_Point* center, SDL_RendererFlip flip) const` | 将纹理复制到渲染目标，支持旋转和翻转          |
| `SDL_Renderer* get() const`                                                                                                                    | 获取SDL_Renderer指针            |
| `SDL_Texture* loadTexture(const std::string& filePath) const`                                                                                  | 从文件加载纹理                     |

### Controller - 控制器

`Controller`类管理用户输入，包括键盘、鼠标和游戏手柄事件的处理。

#### 主要功能

- **输入事件处理**：处理键盘和鼠标的各种输入事件
- **状态跟踪**维护键盘按键的按下状态
- **鼠标坐标**：提供获取和更新鼠标坐标的功能

#### 主要方法

| 方法                                                             | 描述            |
|----------------------------------------------------------------|---------------|
| `Controller()`                                                 | 默认构造函数        |
| `~Controller()`                                                | 析构函数          |
| `void event(SDL_Event& event, int& x, int& y)`                 | 处理输入事件，更新鼠标坐标 |
| `void KeyboardPress(const SDL_Event& event, int& x, int& y)`   | 处理键盘按下事件      |
| `void KeyboardRelease(const SDL_Event& event, int& x, int& y)` | 处理键盘释放事件      |
| `void MousePress(const SDL_Event& event)`                      | 处理鼠标按下事件      |
| `void MouseRelease(const SDL_Event& event)`                    | 处理鼠标释放事件      |
| `void MouseMove(const SDL_Event& event, int& x, int& y)`       | 处理鼠标移动事件，更新坐标 |
| `bool isKeyPressed(SDL_Scancode scancode) const`               | 检查指定按键是否被按下   |

### Image - 图像管理

`Image`类负责加载、管理和渲染图像资源。

#### 主要功能

- **图像加载**：从文件加载图像并创建纹理
- **图像控制**：控制图像的位置、大小和渲染方式
- **透明度管理**：支持设置图像的透明度和混合模式

#### 主要方法

| 方法                                                                                           | 描述                 |
|----------------------------------------------------------------------------------------------|--------------------|
| `Image()`                                                                                    | 默认构造函数             |
| `~Image()`                                                                                   | 析构函数，负责清理图像资源      |
| `void draw()`                                                                                | 绘制图像到屏幕            |
| `void setImage(const std::string& filePath, Renderer* renderer, int x, int y, int w, int h)` | 设置图像的文件路径、渲染器和位置大小 |
| `void setPosition(int x, int y)`                                                             | 设置图像位置             |
| `void setSize(int w, int h)`                                                                 | 设置图像大小             |
| `void setColor(SDL_Color color)`                                                             | 设置图像颜色             |
| `void setAlpha(Uint8 alpha)`                                                                 | 设置图像透明度            |
| `SDL_Rect getRect() const`                                                                   | 获取图像矩形区域           |

### Text - 文本渲染

`Text`类提供文本渲染功能，支持不同字体和样式的文本显示。

#### 主要功能

- **文本渲染**：将文本内的渲染为可显示的纹理
- **字体管理**：支持加载和使用不同的TTF字体
- **样式调整**：控制文本颜色、透明度和混合模式

#### 主要方法

| 方法                                                                                                                   | 描述               |
|----------------------------------------------------------------------------------------------------------------------|------------------|
| `Text()`                                                                                                             | 默认构造函数           |
| `~Text()`                                                                                                            | 析构函数，负责清理文本资源    |
| `void draw()`                                                                                                        | 绘制文本到屏幕          |
| `void setText(const std::string& text, const std::string& fontPath, int fontSize, Renderer* renderer, int x, int y)` | 设置文本内容、字体、渲染器和位置 |
| `void setPosition(int x, int y)`                                                                                     | 设置文本位置           |
| `void setColor(SDL_Color color)`                                                                                     | 设置文本颜色           |
| `void setAlpha(Uint8 alpha)`                                                                                         | 设置文本透明度          |
| `void setBlendMode(SDL_BlendMode mode)`                                                                              | 设置混合模式           |
| `SDL_Texture* getTexture() const`                                                                                    | 获取文本纹理           |
| `SDL_Rect getRect() const`                                                                                           | 获取文本显示区域         |

### Button - 按钮组件

`Button`类实现了可交互的按钮UI组件。

#### 主要功能

- **按钮样式**：支持纯色按钮和图片按钮两种样式
- **事件响应**：处理鼠标点击、释放和悬停等事件
- **状态管理**：管理按钮的点击、按下和释放状态
- **文本显示**：支持在按钮上显示文本内容

#### 主要方法

| 方法                                                                                 | 描述               |
|------------------------------------------------------------------------------------|------------------|
| `Button()`                                                                         | 默认构造函数           |
| `~Button()`                                                                        | 析构函数             |
| `bool isButtonClicked() const`                                                     | 检查按钮是否被点击（鼠标按下）  |
| `bool isButtonReleased() const`                                                    | 检查按钮是否被释放（鼠标抬起）  |
| `bool isButtonPressed() const`                                                     | 检查按钮是否被按住        |
| `void draw()`                                                                      | 绘制纯色按钮（带圆角的矩形）   |
| `void drawwithImage()`                                                             | 绘制图片按钮           |
| `void handleEvent(const SDL_Event &event)`                                         | 处理按钮事件，更新按钮状态    |
| `void setButton(int x, int y, int w, int h, SDL_Color color)`                      | 设置按钮属性（位置、大小、颜色） |
| `void setButtonText(const std::string& text, TTF_Font* font, SDL_Color textColor)` | 设置按钮文本内容和样式      |
| `void setButtonImage(const std::string& filePath, Renderer* renderer)`             | 设置按钮图片           |
## 使用示例

以下是使用API创建简单游戏场景的示例代码：

```cpp
#include "lx_api.h"
#include "lyt_api.h"

int main(int argc, char* argv[]) {
    // 创建游戏实例
    lyt::Game game;
    
    // 初始化游戏窗口
    game.init("大鱼吃小鱼", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
    
    // 获取渲染器
    lyt::Renderer* renderer = game.getRenderer();
    
    // 创建玩家鱼
    lx::PlayerFish player(renderer, "asset/images/player_1_left_0.png", 400, 300, 50, 30);
    
    // 创建分数管理器
    lx::ScoreManager scoreManager;
    
    // 游戏主循环
    while (game.running()) {
        // 处理事件
        game.handleEvents();
        
        // 更新游戏状态
        game.update();
        
        // 渲染画面
        game.render();
    }
    
    // 清理资源
    game.clean();
    
    return 0;
}
```

## 结语

本API文档提供了大连民族大学C++课程设计"大鱼吃小鱼"游戏项目中`lx`和`lyt`两个API模块的概览和使用方法。通过合理使用这些API，可以轻松开发出功能完善的游戏应用。

如有任何问题或建议，请联系API开发者：
- LX API (鱼类管理模块): 雷烜 & 汤觐瑄
- LYT API (游戏引擎模块): 李岳烔
