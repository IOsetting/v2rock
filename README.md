# v2rock
GUI tool for v2ray  
针对Ubuntu发行版的v2ray工具软件. 适用于使用订阅地址的v2ray管理. 

## 环境要求

### 操作系统要求  
此软件可以运行于以下发行版的64位版本.  
* Ubuntu 20.04 Focal
* Ubuntu 18.04 Bionic
* Ubuntu 16.04 Xenial
* Debian 10 Buster
* Debian 8 Jessie


### 安装v2ray
此软件本身不携带v2ray, 需要您自行安装, 参考[v2ray Github项目地址](https://github.com/v2ray/v2ray-core), [v2ray官网](https://www.v2ray.com/).

**网络安装**  

执行官网提供的shell脚本  
```shell
bash <(curl -L -s https://install.direct/go.sh)
```

**本地安装**  

在网络环境不好的地方, 网络安装可能会失败, 需要作如下处理:  
1. 从 [install.direct](https://install.direct/go.sh)下载go.sh脚本
1. 从[官网Release](https://github.com/v2ray/v2ray-core/releases), [Github Dist](https://github.com/v2ray/dist/)下载预编译的压缩包, 对应Ubuntu 64位, 应当下载文件名为 v2ray-linux-64.zip 的文件.
1. 在本地执行下面的命令安装, 版本为所使用的预编译压缩包的版本
```
./go.sh --version v1.13 --local /path/to/v2ray.zip
```

### 浏览器代理插件

推荐使用 SwitchyOmega 插件, [SwitchyOmega Github项目地址](https://github.com/FelisCatus/SwitchyOmega). 此插件支持Firefox和Chrome, 使用方便, 可以完美配合各种协议的代理.  

## 安装

下载对应发行版的deb文件到本地, 用dpkg安装, 安装需要sudo权限
```shell
sudo dpkg -i v2rock_x.x.x-x_xxxxx_xxxxx.deb
```
如果提示有未安装的依赖, 再运行下面的命令修复依赖关系
```shell
sudo apt install -f
```
如果需要查看deb安装包的内容, 可以使用
```shell
dpkg -c v2rock_x.x.x-x_xxxxx_xxxxx.deb
```

## 使用

### 配置
安装成功后, 在软件列表中可以找到v2rock, 或者按下`super`键(`win`键)后输入v2rock,会出现v2rock的图标, 点击运行. v2rock第一次运行会在 ~/.config/v2rock/ 下初始化配置文件. 您需要点击`settings`按钮, 在`general`标签下配置以下参数  

* Subscribe URL: 请填写服务商提供的订阅地址
* V2Ray Executable Path: v2ray的可执行文件地址, 默认安装是/usr/bin/v2ray/v2ray, 如果没动过就不需要修改.
* SOCKS5 Proxy 勾选表示启用本地SOCKS5代理
* HTTP Proxy 勾选表示启用本地HTTP代理, HTTP和SOCKS5代理至少要选中一个
* SOCKS Proxy Listen: SOCKS5代理监听的本地IP, 默认使用127.0.0.1为仅接收本机代理请求, 如使用0.0.0.0, 则可以接受任意来源代理请求
* SOCKS Proxy Port: 默认为1080, 如果改成别的端口需要注意不要和其他的应用冲突, 另外不能小于1024, 因为小于1024的都属于系统保留端口, 需要sudo 权限
* HTTP Proxy Listen: HTTP代理监听的本地IP, 说明同上
* HTTP Proxy Port: 默认为1081, 说明同上, 注意与SOCKS5的端口值不能相同


### 导入
在配置完订阅地址后, 点击`Import`按钮导入, 如果导入不成功, 可以用浏览器试试订阅地址是否能直接访问, 如果访问不了, 说明地址无法访问, 需要联系订阅地址提供方解决.  

### 测试
暂时只提供ping测试, 在上一步成功导入节点后, 在列表中左键单击选中节点, 再点击`Test`按钮, 就可以测试当前选中节点的ping, 从下方日志窗口可以看到节点的ping结果.  
在测试过程中, 如果节点无法访问, 日志窗口长时间无输出, 可以点击`Stop`按钮停止.

### 选择节点
在列表中双击节点, 右侧会出现`√`字符, 此节点即被选中

### 启动
点击`Start`按钮, 就会使用选中的节点启动v2ray进程. 在日志窗口中会有对应日志输出.  
在浏览器中配置socks5代理, 或者通过SwitchyOmega插件配置socks5代理, 地址为127.0.0.1, 端口为刚才在Settings中填写的端口, 就可以使用了.

### 停止
点击`Stop`按钮, 就会停止当前的v2ray进程. 点击`Quit`按钮退出应用, 也会停止当前的v2ray进程(如果有已经启动的v2ray).

## 卸载
卸载可以使用dpkg命令  
```shell
sudo dpkg --purge v2rock
```
如果需要清除配置文件, 需要删除 `~/.config/v2ray` 目录
```shell
rm -rf ~/.config/v2rock
```

## 从源代码编译
安装依赖  
```shell
sudo apt install build-essential qt5-default libssl-dev qt5keychain-dev
```
Git导出  
```shell
git clone https://github.com/IOsetting/v2rock.git
```
执行编译
```shell
cd v2rock
qmake && make -j4
```
在v2rock/v2rock目录下会生成v2rock二进制文件


