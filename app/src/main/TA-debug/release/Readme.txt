TA签名打包准备材料：
1.combine.o TA编译产物
	=>放在指定目录
2.manifest.txt TA基本配置信息
	=>放在指定目录

3.configs.xml打包产物（服务器端打包后下发到本地）
	=>可以指定文件路径
4.TA开发者私钥
	=>可以指定路径
6.rsa_public_key.pem文件
	=>放在当前目录（固定文件）


打包执行命令需要四个参数：
	1.combine.o、manifest.txt文件所在目录
	2.生成产物路径
	3.开发者私钥路径
	4.configs.xml文件打包产物路径
示例：python signtool_v3.py 1 2 ./input ./output “” “” “” ./config/Config ./ta_cert/ta_key.pem