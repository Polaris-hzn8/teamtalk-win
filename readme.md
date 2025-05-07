# teamtalk-win

---

本项目为teamtalk的windows客户端，由C++语言开发

项目目录结构：

1. 3rdParty：第三方开源工具
   - include：头文件 google、sqlite3
   - src：源文件 cxImage、http、json、libogg、libsecurity、libspeex、protobuff、yaolog
2. commonlib：各个项目共享的静态库文件
3. solution：工程文件
4. inlude：项目头文件
5. core：项目源文件，包括duilib、network、utility
6. src：项目源文件，包括duilibex、gifsmiley、modules、teamtalk
7. package：项目打包目录
   - data：软件运行的基本数据
   - gui：界面布局控件控制
   - users：用户目录
   - teamtalk：程序进程本体位置
     - speexdec.exe：语音处理
     - teamtalk.exe：应用主体
     - Duilib.dll
     - GifSmiley.dll
     - httpclient.dll
     - libogg.dll
     - Modules.dll
     - network.dll
     - sqliet3.dll
     - utility.dll

