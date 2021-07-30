# AnimShareTest
本项目是测试 Animation Sharing Plugin的测试项目，项目中包含两张测试地图  
使用版本：ue4.26.2

* 地图1: AnimNormalMap, Spawner创建固定数量的Character， Character动作蓝图用正常状态机实现，每2秒循环切换一次，顺序为 Idle->Walk->Run->Jump->Attack
* 地图2：AnimShareMap, 初始化创建同地图1，不同之处在于动作状态机完全由AnimationSharingManager接管，蓝图不再配置动画蓝图，
所有配置见ASS_SetUp
* BP_CharactersSpawner：负责Spawn Character, RowCount, ColumnCount用来控制当前Character数目。
* BP_ModularCharacter2继承自 AnimShareCharacter, 相关Significance实现在C++当中， 蓝图里 SignificanceThreholdsSetting是根据与Character的距离相关的配置。
* AnimationSharingSetup 也是在 BP_ModularCharacter2 中配置的。
