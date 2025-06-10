@echo off
REM 发布脚本 - 打包游戏和所有必要的SDL2依赖

REM 创建发布目录
mkdir release_v1.0.0
echo 正在创建发布目录...

REM 复制可执行文件
copy cmake-build-release\DLNU_CPP_CourseDesign.exe release_v1.0.0\
echo 已复制游戏可执行文件...

REM 复制SDL2相关DLL
REM 使用项目中已有的SDL2库
set SDL2_PATH=lib\dep\plugins\SDL2\lib\x64
copy "%SDL2_PATH%\SDL2.dll" release_v1.0.0\
copy "%SDL2_PATH%\SDL2_image.dll" release_v1.0.0\
copy "%SDL2_PATH%\SDL2_ttf.dll" release_v1.0.0\
copy "%SDL2_PATH%\SDL2_mixer.dll" release_v1.0.0\
echo 已复制SDL2核心DLL...

REM 复制可选依赖的DLL
set SDL2_OPT_PATH=lib\dep\plugins\SDL2\lib\x64\optional
copy "%SDL2_OPT_PATH%\libogg-0.dll" release_v1.0.0\
copy "%SDL2_OPT_PATH%\libopus-0.dll" release_v1.0.0\
copy "%SDL2_OPT_PATH%\libopusfile-0.dll" release_v1.0.0\
copy "%SDL2_OPT_PATH%\libwebp-7.dll" release_v1.0.0\
echo 已复制SDL2可选依赖DLL...

REM 复制游戏资源文件
mkdir release_v1.0.0\asset
xcopy /E /I asset release_v1.0.0\asset
echo 已复制游戏资源文件...

REM 复制README和VERSION文件
copy README.md release_v1.0.0\
copy VERSION.md release_v1.0.0\
echo 已复制文档文件...

REM 创建一个简单的启动说明
echo # 大鱼吃小鱼游戏 v1.0.0 > release_v1.0.0\readme.txt
echo. >> release_v1.0.0\readme.txt
echo 直接双击DLNU_CPP_CourseDesign.exe即可运行游戏 >> release_v1.0.0\readme.txt
echo 游戏控制：方向键控制鱼的移动 >> release_v1.0.0\readme.txt
echo. >> release_v1.0.0\readme.txt
echo 本发布版本已包含所有必要的SDL2库文件，无需额外安装 >> release_v1.0.0\readme.txt

REM 创建ZIP压缩包
powershell Compress-Archive -Path release_v1.0.0\* -DestinationPath 大鱼吃小鱼_v1.0.0.zip -Force
echo 已创建发布ZIP包...

echo 发布打包完成!
