# AnimShareTest
本项目是测试 Animation Sharing Plugin的测试项目，项目中包含两张测试地图

* 地图1: Spawner创建固定数量的Character， Character动作蓝图用正常状态机实现，每2秒循环切换一次，顺序为 Idle->Walk->Run->Jump->Attack
* 地图2：初始化创建同地图1，不同之处在于动作状态机完全由AnimationSharingManager接管，蓝图不再配置动画蓝图，
所有配置见ASS_SetUp
