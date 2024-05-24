RakSAMP-CSE 中国特供版使用说明
=======

RakSAMP-CSE 是为SAMP量身定制的一款既可以以服务器也可以以客户端模式运行的SAMP假端

当前版本: v0.8.6-CES for SAMP-0.3.7.  
原作者：jlfm, bartekdvd, P3ti.  
特别鸣谢： balika011, .silent, n3ptun0. 
二次创作：FranciumKIKI，T-FascalXX

- 一、中国特供版(CSE)与标准版有什么区别？
- 答：在使用上基本没有任何区别，只是进行了部分汉化以及性能优化.

- 二、中国特供版的作者是谁？
- 答：用“作者”一词恐怕不太恰当，我们只是对标准版进行了二次开发，称不上“作者”

--

## 客户端模式
**客户端模式下可用的假端运行模式**

* 0 = RCON模式,
* 1 = 冻结模式(不能出生),
* 2 = 稻草人模式(一直保持在出生点位置不懂),
* 3 = 常规模式(可以在任意一个位置保持不动),
* 4 = 步行跟在一个玩家屁股后面,
* 5 = 开车赶在一个玩家屁股后面.

**客户端模式下可用的指令**

* !exit or !quit: 退出客户端
* !reconnect: 重新连接客户端
* !reload: 重新加载配置文件.
* !runmode: 设置当前客户端运行模式.
* !stats: shows raknet statistics.
* !players: 展示玩家列表.
* !npcs: 展示NPC列表.
* !login: 登录RCON.
* !rcon: 发送一条RCON命令.
* !goto: 传送至一名玩家的附近.
* !gotocp: 传送至当前检查点.
* !autogotocp: toggle automatic checkpoint teleporter.
* !imitate: change imitate name.
* !vlist: 展示载具列表.
* !vdeath: 给服务器发送一条车辆被摧毁的假信息.
* !fu: 发送一个连接超时的假包给服务器.
* !spawn: 使你假端所控制的玩家出生.
* !pickup: 发送一条捡起物品的假消息给服务器（需要指定物品id）.
* !class: 选择玩家类.
* !menusel: 向服务器发送一条信息用于模拟玩家点击GTA游戏菜单
* !kill: 给服务器发送一条玩家被杀死的假消息.
* !lag: toggle server lagger.
* !spam: toggle reconnect spammer.
* !joinflood: toggle join flooder.
* !chatflood: toggle chat flooder.
* !classflood: toggle class selection flooder.
* !bulletflood: flood the server with bullet sync packets to the players' positions.
* !weapon: 设置您的假段所控制的玩家手中的当前武器.
* !selplayer: 设置您的假段所控制的玩家跟随另一名玩家.
* !selveh: 设置您的假端正在驾驶的载具.
* !pos: 将您的假段所控制的玩家传送至一处坐标点.
* !follow: sets the following offset.
* !pulsator: pulse health & armor.
* !change_server: connect to another server without restarting RakSAMPClient.
* !change_name: change the fake player's name and reconnect/rejoin the game.
* !dialogresponse: 向服务器发送一条信息用于模拟玩家点击Dialog.  (需要指定Dialog-id)
* !logstatus: show log status.
* !log: toggle logging objects/pickups/textlabels/textdraws.
* !teleport: 展示传送点菜单.
* !scmevent: 给服务器发送一条SCM事件.
* !fakekick: send vehicle enter notification with invalid vehicle id to get kicked.
* !seltd: 向服务器发送一条信息用于模拟玩家点击TextDraw.（需指定TextDraw-id）
* !sendrates: show sendrates.

**这些东西我认为仅靠简单的几句话是难以描述清楚的，所以您最好亲自去试一试每一条指令，我想这能够加深您对这些指令的理解**

--

## 服务端模式
你可以为服务端制作Lua脚本

**服务端中的一些参数限制：**

* 最大玩家数量：1000.
* 最大载具数量：2000.
* 最大脚本数量：32.
  

**服务端中的一些可用的脚本事件：**

* onScriptStart
* onScriptExit
* onNewQuery
* onNewConnection
* onPlayerJoin
* onPlayerDisconnect
* onPlayerRequestClass
* onPlayerSpawn
* onPlayerDeath
* onPlayerDamageVehicle
* onPlayerWantsEnterVehicle
* onPlayerLeaveVehicle
* onPlayerMessage
* onPlayerCommand
* onPlayerWeaponShot
* onPlayerEnterCheckpoint
* onPlayerLeaveCheckpoint
* onPlayerClickMap
* onDialogResponse
* onPlayerInteriorChange
* onScmEvent
  

**客户端中可用的脚本函数**

* outputConsole
* setGameModeText
* setMapName
* setWebURL
* isPlayerConnected
* getPlayerName
* getPlayerPos
* setPlayerPos
* setPlayerPosFindZ
* getPlayerInterior
* setPlayerInterior
* getPlayerScore
* setPlayerScore
* getPlayerIP
* getPlayerPing
* getPlayerVehicleID
* sendPlayerMessage
* sendPlayerChatMessage
* sendPlayerChatMessageToAll
* setPlayerRotation
* setPlayerCameraPos
* setPlayerCameraLookAt
* setCameraBehindPlayer
* givePlayerMoney
* resetPlayerMoney
* setPlayerHealth
* setPlayerArmour
* addStaticVehicle
* createVehicle
* removeVehicle
* repairVehicle
* setVehicleHealth
* giveWeapon
* setWeaponAmmo
* clearPlayerWeapons
* playAudioStreamForPlayer
* stopAudioStreamForPlayer
* sendDeathMessage
* sendDeathMessageForPlayer
* setGravity
* setPlayerGravity
* setPlayerCheckpoint
* disablePlayerCheckpoint
* gameTextForAll
* gameTextForPlayer
* showPlayerDialog
* broadcastScmEvent
