# teamtalk-win

---

本项目为teamtalk的win客户端，由C++语言开发

### 目录结构

1. 3rdParty：libsecurity、httpclient、libogg、libspeex、speexdec、cxImage、json、protobuff、yaolog
2. import_lib：依赖的各个项目导出库
3. include：头文件
4. src：源文件，duilibex、gifsmiley、modules、teamtalk、duilib、network、utility
5. pack：软件打包
   - data：资源文件
   - gui：布局界面控件
   - module：软件主体
     - ttlogconfig.ini：日志设置
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

### 解决方案

teamtalk解决方案包含以下项目：

1. 3rdParty：

   - httpclient：程序中集成的http请求库，

     登录前程序会先连接服务器的login_server以获得后续需要登录的msg_server的ip地址和端口号等信息，这里使用的是http协议，

     同时聊天过程中收发的聊天图片与图片服务器msfs也使用http协议来收发这些图片；

   - libogg：语音库用来解析声音文件，pc客户端会收到来自移动端的语音消息，相比较传统的 `.wav、.mp3、.wma`，`.ogg` 格式的不仅音质高，而且音频文件的体积小，腾讯的QQ游戏英雄杀中的语音也是使用这个格式的。

   - libspeex：音频压缩库

   - speexdec：和ogg格式相关的编码和解码器；

2. TTClient：

   - Duilib：开源界面库该界面库模仿web开发中的布局技术，使用xml文件来布局win界面，并且在主窗口上绘制所有子控件，即所谓的directUI技术
   - GifSmiley：是程序中用来解析和显示Gif格式的图片的库，以支持Gif图片的动画效果；
   - Modules：项目中的各个主要的业务模块
   - teamtalk：是主程序入口工程
   - network：TCP网络通信库，客户端与服务器使用的是同套TCP网络通信库，只不过服务器运行在Linux下，其核心的IO复用模型是epoll，而客户端使用的IO复用模型是select；
   - utility：工具类工程，如sqlite的包装接口、md5工具类等。

除了上面这些库以外，项目中还使用到了sqlite库、谷歌protobuf库、C++跨平台日志库yaolog等（可打印出网络通信中的字节流的二进制形式）。

关于yaolog可参考：http://blog.csdn.net/gemo/article/details/8499692

### 目标分层架构

1. 用户界面层（UI Layer）：
   - Windows客户端采用图形用户界面（GUI）来与用户交互，提供了各种界面元素和交互功能，包括聊天窗口、联系人列表、群组列表、设置界面等。
   - 用户界面层负责接收用户的输入操作，显示界面元素，并将用户的操作转发给业务逻辑层进行处理。
2. 业务逻辑层（Business Logic Layer）：
   - 业务逻辑层负责处理用户的操作和事件，包括用户登录、消息发送、联系人管理、群组管理等业务逻辑。
   - 它与服务器端进行通信，发送请求并接收响应，实现与服务器的数据交互。
   - 业务逻辑层还负责处理用户状态的管理，包括在线状态、离线状态、忙碌状态等。
3. 网络通信层（Network Communication Layer）：
   - 网络通信层负责与服务器进行网络通信，发送和接收数据。
   - 它使用TCP/IP协议栈进行数据传输，并与服务器端的网络通信模块进行交互。
   - 网络通信层处理与服务器的连接建立、断开、数据传输等相关操作。
4. 数据持久化层（Data Persistence Layer）：
   - 数据持久化层负责将客户端的数据进行持久化存储，包括用户的个人信息、聊天记录、联系人列表等。
   - 它使用数据库或文件系统等方式来进行数据的读写操作，以保证数据的安全性和可靠性。
5. 辅助模块（Auxiliary Modules）：
   - 客户端包含一些辅助模块，如音视频模块、文件传输模块等。
   - 音视频模块负责处理音视频通话的建立和管理，包括音频采集、编解码、网络传输等。
   - 文件传输模块负责处理文件的上传、下载和共享，实现文件的传输功能。

总体而言，TeamTalk Windows客户端的架构采用了分层的设计，将不同的功能模块分解为不同的层级，实现了界面、业务逻辑、网络通信和数据持久化的分离。这样的架构设计使得代码的组织更加清晰，模块之间的耦合度较低，便于维护和扩展。

### 系统功能架构

程序有以下几类线程：

1. 网络事件检测线程：接收和发送网络数据包；
   - 通过提前注册的会话反应函数，来进行数据的回调，并根据serviceID来调用相应模块中的与cmdID对应的业务函数。
   - 客户端各业务被拆分成多个模块，登录、会话、文件传输，服务端数据包传递过来时会选择对应的模块进行相应的逻辑处理。
   - 基础模块和界面模块之间的数据流，则通过观察者模式，来进行通知对应界面的视图变化。
2. HTTP任务处理线程：处理http相关操作；其中有个线程池，默认线程数量为1
3. 普通任务处理线程：处理一般性任务如登录等；
4. 主线程\UI线程：界面相关逻辑处理，
   - 负责界面消息循环，处理用户交互：
   - 在UI线程中有个代理窗口的窗口过程函数，利用win32的消息队列，使用窗口处理函数来统一接口，负责处理客户端后台业务与界面的数据传递。
   - 核心是利用PostMessage向代理线程中投递事件，事件消息参数携带任务信息。





