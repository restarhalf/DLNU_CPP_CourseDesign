# API 文档

## Button.h

### `lyt::Button` 类

按钮类，负责处理交互式按钮的显示和事件响应，支持纯色按钮和图片按钮两种样式。

#### 成员函数

| 函数签名 | 描述 |
|----------|------|
| `bool isButtonClicked() const` | 检查按钮是否被点击（鼠标按下） |
| `bool isButtonReleased() const` | 检查按钮是否被释放（鼠标抬起） |
| `bool isButtonPressed() const` | 检查按钮是否被按住 |
| `void draw()` | 绘制纯色按钮（带圆角的纯色矩形） |
| `void drawwithImage()` | 绘制图片按钮（根据状态调整透明度） |
| `void handleEvent(const SDL_Event &event)` | 处理按钮事件（鼠标点击/移动） |
| `void setButton(int x, int y, int w, int h, SDL_Color color)` | 设置纯色按钮属性（坐标+尺寸） |
| `void setButton(SDL_Rect rect, SDL_Color color)` | 设置纯色按钮属性（SDL_Rect结构） |
| `void setButtonwithImage(SDL_Rect rect)` | 设置图片按钮尺寸 |
| `void setText(const std::string &text, TTF_Font *font, SDL_Color color, Renderer *renderer, SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND, Uint8 alpha = 255)` | 设置按钮文本（自动缩放居中） |
| `void setButtonwithImage(const std::string &filePath, Renderer *renderer, SDL_Rect rect, SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND, Uint8 alpha = 255)` | 设置图片按钮属性 |

#### 成员变量
无公共成员变量

---

## Controller.h

### `lyt::Controller` 类

控制器类，负责处理键盘和鼠标的输入控制。

#### 成员函数

| 函数签名 | 描述 |
|----------|------|
| `Controller()` | 构造函数 |
| `~Controller()` | 析构函数 |
| `void event(SDL_Event& event, int& x, int& y)` | 处理所有输入事件 |
| `void KeyboardPress(const SDL_Event& event, int& x, int& y)` | 处理键盘按下事件 |
| `void KeyboardRelease(const SDL_Event& event, int& x, int& y)` | 处理键盘释放事件 |
| `void MousePress(const SDL_Event& event)` | 处理鼠标按下事件 |
| `void MouseRelease(const SDL_Event& event)` | 处理鼠标释放事件 |
| `void MouseMove(const SDL_Event& event, int& x, int& y)` | 处理鼠标移动事件 |

#### 成员变量
无公共成员变量

---

## Game.h

### `lyt::Game` 类

游戏类，负责管理游戏的主要功能和生命周期。

#### 成员函数

| 函数签名 | 描述 |
|----------|------|
| `Game()` | 构造函数 |
| `~Game()` | 析构函数 |
| `bool init(std::string title, int width, int height, int flags)` | 初始化游戏环境 |
| `void handleEvent(SDL_Event& event, int& x, int& y)` | 处理游戏事件 |
| `void clean()` | 清理游戏资源 |
| `void update() const` | 更新游戏状态 |
| `void render() const` | 渲染游戏画面 |
| `Renderer* getRenderer() const` | 获取渲染器指针 |
| `Window* getWindow() const` | 获取窗口指针 |
| `void setRenderer(Renderer* renderer)` | 设置渲染器 |
| `void setWindow(Window* window)` | 设置窗口 |
| `bool running() const` | 检查游戏是否运行 |
| `void frameStart()` | 开始帧计时 |
| `void frameEnd()` | 结束帧计时（帧率控制） |
| `void setFps(float fps)` | 设置目标帧率 |

#### 成员变量
无公共成员变量

---

## Image.h

### `lyt::Image` 类

图像类，负责处理图片资源的加载、显示和管理。

#### 成员函数

| 函数签名 | 描述 |
|----------|------|
| `Image()` | 构造函数 |
| `~Image()` | 析构函数 |
| `void draw()` | 绘制图像 |
| `void setImage(const std::string& filePath, Renderer* renderer, SDL_Rect rect, SDL_BlendMode blendMode, Uint8 alpha)` | 设置图像属性并加载图像 |
| `SDL_Rect getRect() const` | 获取图像矩形区域 |
| `void setRect(const SDL_Rect& rect)` | 设置图像矩形区域 |
| `SDL_Color getColor() const` | 获取图像颜色 |
| `void setColor(const SDL_Color& color)` | 设置图像颜色 |
| `std::string getFilepath() const` | 获取图像文件路径 |
| `void setFilepath(const std::string& file_path)` | 设置图像文件路径 |
| `Renderer* getRenderer() const` | 获取渲染器指针 |
| `void setRenderer(Renderer* renderer)` | 设置渲染器 |
| `SDL_BlendMode getBlendmode() const` | 获取混合模式 |
| `void setBlendmode(SDL_BlendMode blend_mode)` | 设置混合模式 |
| `Uint8 getAlpha() const` | 获取透明度 |
| `void setAlpha(Uint8 alpha)` | 设置透明度 |

#### 成员变量
无公共成员变量

---

## Music.h

### `Music` 类

音乐类，负责处理背景音乐的播放和控制。

#### 成员函数

| 函数签名 | 描述 |
|----------|------|
| `Music()` | 构造函数 |
| `~Music()` | 析构函数 |
| `void playMusic(const std::string& filePath)` | 播放音乐文件 |
| `void stopMusic()` | 停止当前播放的音乐 |

#### 成员变量
无公共成员变量

---

## Renderer.h

### `lyt::Renderer` 类

渲染器类，负责处理SDL渲染相关操作。

#### 成员函数

| 函数签名 | 描述 |
|----------|------|
| `Renderer()` | 默认构造函数 |
| `explicit Renderer(SDL_Renderer *renderer)` | 使用现有SDL_Renderer构造 |
| `explicit Renderer(const Window *window, bool vsync)` | 从窗口创建渲染器 |
| `~Renderer()` | 析构函数 |
| `void clear() const` | 清除渲染目标 |
| `void present() const` | 呈现渲染内容到屏幕 |
| `int copy(SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dst) const` | 复制纹理到渲染目标 |
| `SDL_Renderer *get() const` | 获取SDL_Renderer指针 |

#### 成员变量
无公共成员变量

---

## Text.h

### `lyt::Text` 类

文本类，负责处理文字的渲染和显示。

#### 成员函数

| 函数签名 | 描述 |
|----------|------|
| `Text()` | 构造函数 |
| `~Text()` | 析构函数 |
| `SDL_Texture *getTexture() const` | 获取文本纹理 |
| `void setTexture(SDL_Texture *texture)` | 设置文本纹理 |
| `SDL_Rect getRect() const` | 获取文本显示区域 |
| `void setRect(const SDL_Rect &rect)` | 设置文本显示区域 |
| `SDL_Color getColor() const` | 获取文本颜色 |
| `void setColor(const SDL_Color &color)` | 设置文本颜色 |
| `TTF_Font *getFont() const` | 获取字体 |
| `void setFont(TTF_Font *font)` | 设置字体 |
| `SDL_Surface *getSurface() const` | 获取文本表面 |
| `void setSurface(SDL_Surface *surface)` | 设置文本表面 |
| `SDL_BlendMode getBlendmode() const` | 获取混合模式 |
| `void setBlendmode(SDL_BlendMode BlendMode)` | 设置混合模式 |
| `std::string getText() const` | 获取文本内容 |
| `void setText(const std::string &text)` | 设置文本内容 |
| `void setAll(Renderer *render, SDL_Rect rect, SDL_Color color, TTF_Font *font, SDL_BlendMode blendMode, const std::string &text)` | 设置所有文本属性 |
| `void flush()` | 刷新文本纹理 |
| `void draw()` | 绘制文本 |

#### 成员变量
无公共成员变量

---

## Window.h

### `lyt::Window` 类

窗口类，负责管理SDL窗口的创建、销毁和事件处理。

#### 成员函数

| 函数签名 | 描述 |
|----------|------|
| `Window()` | 默认构造函数 |
| `Window(SDL_Window *window)` | 使用现有SDL_Window构造 |
| `Window(const std::string &title, int width, int height)` | 创建指定参数的窗口 |
| `~Window()` | 析构函数 |
| `void handleEvents(SDL_Event &event)` | 处理窗口事件 |
| `SDL_Window *get() const` | 获取SDL_Window指针 |
| `int width() const` | 获取窗口宽度 |
| `int height() const` | 获取窗口高度 |
| `void setIcon(const std::string &filePath)` | 设置窗口图标 |
| `void getSize(int &width, int &height) const` | 获取窗口尺寸 |
| `void fullscreen(bool fullScreen)` | 设置全屏模式 |
| `void hide(bool isHide)` | 设置窗口隐藏/显示 |

#### 成员变量
无公共成员变量