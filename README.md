Arise: Automatically Extract Records In Search Engine
---
Arise组件可以***全自动***抽取目前主流搜索引擎（百度、谷歌、Bing、Yahoo、Sogou、haosou、Sina、s.weibo、Youdao、Goso、盘古等）结果页面数据记录的三个元信息（标题、URL、摘要）。

Arise由C++编写，由Cmake构建工程，支持Linux和windows平台。


build
---
```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```


how to use
---
#### 1. 可执行程序
使用 --help 打印用法

可执行程序包含四个参数：

第一个参数为运行程序exe

第二个参数为待抽取搜索结果页面文件存储路径

第三个参数为是否修补网页标签的bool值，0不修补，1修补，其他整数对应不修补

第四个参数为抽取结果文件的存储路径


#### 2. libarise.a
同样可以生成lib供调用


test result
---
precision/recall more than **95%**.

time consuming 10ms/page.




 


