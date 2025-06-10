# API 文档

## lx 命名空间

### `lx::Fish` 类

鱼类基类，提供鱼的基本属性和行为。

#### 成员函数

| 函数签名                                                            | 描述            |
|-----------------------------------------------------------------|---------------|
| `Fish(Renderer* renderer, int x, int y, int width, int height)` | 构造函数          |
| `virtual void update(int windowW, int windowH)`                 | 更新鱼的位置和状态     |
| `virtual void render()`                                         | 渲染鱼（绘制一个蓝色矩形） |
| `virtual bool tryEat(Fish& other)`                              | 尝试吃掉另一条鱼      |
| `bool isCollide(const Fish& other) const`                       | 检查与另一条鱼是否碰撞   |
| `int getSize() const`                                           | 获取鱼的大小        |
| `int getWidth() const`                                          | 获取鱼的宽度        |
| `int getHeight() const`                                         | 获取鱼的高度        |
| `SDL_Rect getRect() const`                                      | 获取鱼的矩形区域      |

---

### `lx::AIFish` 类

人工智能控制的鱼，继承自`Fish`。

#### 成员函数

| 函数签名                                                              | 描述             |
|-------------------------------------------------------------------|----------------|
| `AIFish(Renderer* renderer, int x, int y, int width, int height)` | 构造函数           |
| `void update(int windowW, int windowH) override`                  | 更新AI鱼的位置（水平移动） |
| `bool tryEat(Fish& other) override`                               | 尝试吃掉另一条鱼       |

---

### `lx::PlayerFish` 类

玩家控制的鱼，继承自`Fish`。

#### 成员函数

| 函数签名                                                                  | 描述              |
|-----------------------------------------------------------------------|-----------------|
| `PlayerFish(Renderer* renderer, int x, int y, int width, int height)` | 构造函数            |
| `void update(int windowW, int windowH) override`                      | 根据键盘输入更新玩家鱼的位置  |
| `bool tryEat(Fish& other) override`                                   | 尝试吃掉另一条鱼（可能被反吃） |
| `void moveUp(bool pressed)`                                           | 设置向上移动状态        |
| `void moveDown(bool pressed)`                                         | 设置向下移动状态        |
| `void moveLeft(bool pressed)`                                         | 设置向左移动状态        |
| `void moveRight(bool pressed)`                                        | 设置向右移动状态        |
| `bool isDead() const`                                                 | 检查玩家鱼是否死亡       |

---

## lyt 命名空间

### `lyt::Button` 类

交互式按钮，支持纯色按钮和图片按钮。

#### 成员函数

| 函数签名                                                                                      | 描述        |
|-------------------------------------------------------------------------------------------|-----------|
| `bool isButtonClicked() const`                                                            | 检查按钮是否被点击 |
| `void draw()`                                                                             | 绘制纯色按钮    |
| `void drawwithImage()`                                                                    | 绘制图片按钮    |
| `void handleEvent(const SDL_Event &event)`                                                | 处理按钮事件    |
| `void setButton(int x, int y, int w, int h, SDL_Color color)`                             | 设置纯色按钮属性  |
| `void setButtonwithImage(const std::string &filePath, Renderer *renderer, SDL_Rect rect)` | 设置图片按钮属性  |

---

### `lyt::Controller` 类

处理键盘和鼠标输入控制。

#### 成员函数

| 函数签名                                                         | 描述       |
|--------------------------------------------------------------|----------|
| `void event(SDL_Event& event, int& x, int& y)`               | 处理所有输入事件 |
| `void KeyboardPress(const SDL_Event& event, int& x, int& y)` | 处理键盘按下事件 |
| `void MouseMove(const SDL_Event& event, int& x, int& y)`     | 处理鼠标移动事件 |

---

### `lyt::Game` 类

管理游戏的主要功能和生命周期。

#### 成员函数

| 函数签名                                                             | 描述      |
|------------------------------------------------------------------|---------|
| `bool init(std::string title, int width, int height, int flags)` | 初始化游戏环境 |
| `void handleEvent(SDL_Event& event, int& x, int& y)`             | 处理游戏事件  |
| `void update() const`                                            | 更新游戏状态  |
| `void render() const`                                            | 渲染游戏画面  |
| `Renderer* getRenderer() const`                                  | 获取渲染器指针 |

---

### `lyt::Image` 类

处理图片资源的加载和显示。

#### 成员函数

| 函数签名                                                                            | 描述       |
|---------------------------------------------------------------------------------|----------|
| `void draw()`                                                                   | 绘制图像     |
| `void setImage(const std::string& filePath, Renderer* renderer, SDL_Rect rect)` | 设置并加载图像  |
| `SDL_Rect getRect() const`                                                      | 获取图像矩形区域 |

---

### `lyt::Music` 类

处理背景音乐的播放和控制。

#### 成员函数

| 函数签名                                          | 描述     |
|-----------------------------------------------|--------|
| `void playMusic(const std::string& filePath)` | 播放音乐文件 |
| `void stopMusic()`                            | 停止当前音乐 |

---

### `lyt::Renderer` 类

处理SDL渲染操作。

#### 成员函数

| 函数签名                                                                 | 描述        |
|----------------------------------------------------------------------|-----------|
| `void clear() const`                                                 | 清除渲染目标    |
| `void present() const`                                               | 呈现渲染内容    |
| `int copy(SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dst) const` | 复制纹理到渲染目标 |

---

### `lyt::Text` 类

处理文字的渲染和显示。

#### 成员函数

| 函数签名                                                                                                     | 描述       |
|----------------------------------------------------------------------------------------------------------|----------|
| `void draw()`                                                                                            | 绘制文本     |
| `void setAll(Renderer *render, SDL_Rect rect, SDL_Color color, TTF_Font *font, const std::string &text)` | 设置所有文本属性 |
| `void flush()`                                                                                           | 刷新文本纹理   |

---

### `lyt::Window` 类

管理SDL窗口的创建和事件处理。

#### 成员函数

| 函数签名                                                      | 描述     |
|-----------------------------------------------------------|--------|
| `Window(const std::string &title, int width, int height)` | 创建窗口   |
| `void handleEvents(SDL_Event &event)`                     | 处理窗口事件 |
| `int width() const`                                       | 获取窗口宽度 |
| `void fullscreen(bool fullScreen)`                        | 设置全屏模式 |
