# teamtalk-win

---

本项目为teamtalk的windows客户端，由C++语言开发

目录结构：

1. 3rdParty：
    - include：
    - src：

2. bin-teamtalk：
    - data：
    - gui：
    - users：

3. core：
    - DuiLib：
    - network：
    - utility：

4. include：
    - DuilibEx
    - GifSmiley
    - Modules
    - network
    - ProtocolBuffer
    - utility

5. src：
    - DuiLibEx
    - GifSmiley
    - Modules
        - Base
        - Database
        - Emotion
        - FileTransfer
        - GroupList
        - HttpPool
        - Login
        - Message
        - Misc
        - P2PCmd
        - res
        - ScreenCapture
        - Session
        - SysConfig
        - TcpClient
        - UserList

    - teamtalk
        - res
        - UI

6. tools：
    - depends
    - docs
    - protobuf-2.6.1


```
teamtalk-win:.
├─3rdParty
│  ├─include
│  │  ├─google
│  │  └─sqlite3
│  └─src
│      ├─cxImage
│      ├─http
│      ├─json
│      ├─libogg
│      ├─libspeex
│      └─yaolog
├─bin
│  └─teamtalk
│      ├─data
│      │  ├─avatar
│      │  ├─Emotion
│      │  ├─icons
│      │  ├─module
│      │  └─Sound
│      ├─gui
│      │  ├─CreateDiscussionGrpDialog
│      │  ├─EmotionDialog
│      │  ├─FileTransferDialog
│      │  ├─FloatDialog
│      │  ├─LoginDialog
│      │  ├─MainDialog
│      │  ├─menu
│      │  ├─ScreenCapture
│      │  ├─SessionDialog
│      │  └─SysConfigDialog
│      ├─Release
│      ├─Debug
│      └─users
├─core
│  ├─DuiLib
│  │  ├─Control
│  │  ├─Core
│  │  ├─Layout
│  │  └─Utils
│  ├─network
│  └─utility
├─include
│  ├─DuilibEx
│  ├─GifSmiley
│  ├─Modules
│  ├─network
│  ├─ProtocolBuffer
│  └─utility
├─solution
├─src
│  ├─DuiLibEx
│  ├─GifSmiley
│  ├─Modules
│  │  ├─Base
│  │  ├─Database
│  │  ├─Emotion
│  │  ├─FileTransfer
│  │  ├─GroupList
│  │  ├─HttpPool
│  │  ├─Login
│  │  ├─Message
│  │  ├─Misc
│  │  ├─P2PCmd
│  │  ├─res
│  │  ├─ScreenCapture
│  │  ├─Session
│  │  ├─SysConfig
│  │  ├─TcpClient
│  │  └─UserList
│  └─teamtalk
│      ├─res
│      └─UI
└─tools
    ├─depends
    ├─docs
    └─protobuf-2.6.1
```

