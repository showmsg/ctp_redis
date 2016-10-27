ctp_Redis
=====

**注意:**
以后本系统将第一时间在[github](https://github.com/showmsg/ctp_redis)上更新，请大家关注此处。

### 依赖

ctp_redis依赖hiredis、xredis在使用xredis前需要安装hiredis库；
[xredis](https://git.oschina.net/showmsg/xrdis_rosolve) 使用了自己修改过的版本，RedisNode可配置;
默认安装即可;
```bash
make&sudo make install
```

### 编译

* 把amake和pump工具放到环境变量；
* 编译前需要先设置环境变量;

```bash
cat ~/.bash_profile
LD_LIBRARY_PATH=/lib:/usr/lib:/usr/local/lib:.
export LD_LIBRARY_PATH
C_INCLUDE_PATH=/usr/include:/usr/local/include:/usr/local/include:/usr/local/include/zookeeper
export C_INCLUDE_PATH

CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:/usr/include:/usr/local/include:/usr/local/include/hiredis:/usr/local/include/zookeeper:/usr/local/include/xredis
export CPLUS_INCLUDE_PATH
```
### 启动

```bash
# start market
./market
# start trade
./trade
# start plot
./plot GroupA 1
./plot GroupB 2
./plot GroupB 3
```

### 系统架构
![ctp_redis](https://github.com/showmsg/ctp_redis/tree/master/doc/plotDesign.png)

### 功能点

* 多环境支持;
* trade 报单接口, market 行情转换, plot 策略进程;
* plot [组别] [唯一标记],组别用于一个策略组的主备，一个组只有一个主，其它同步进行，只接受，不发送，
  在主进程宕掉后，其它进程竞争为主后进行发送；
* 唯一标识用于标识进程所在主机位置；
* 使用lrange使性能达到报单240000笔/秒；
* 支持配置多账号交易;
### TODO

* json和struct序列化互转实现;
* 策略前置、路由、主备与灾备考虑；
* 策略前端展现;

### 相关功能

<p>[Simnow](http://www.simnow.com.cn/)注册网站;
<p>[Redis](http://redis.io/)下载地址;

<p><p>作者:showmsg
<p>QQ群:12277157

<p><p>感谢:
<p>[xredis](https://github.com/0xsky/xredis)
<p>[ctpService](https://coding.net/u/laozhu_zzy)
<p>感谢其它C++开源常用库的贡献者!!!




			