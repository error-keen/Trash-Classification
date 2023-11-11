## 1. 项目流程和规划：

本项目的整体思路就是，软硬结合，Jetson Nano负责图像识别和处理部分，识别完产生结果，通过串口通信将结果传给STM32F103C8T6，然后STM32再根据结果通过PWM信号控制舵机转动。之所以这样做是因为我STM32通信部分的代码在别的项目中用过，基本都是通用的，稍微改一下，直接将程序烧到32上就可以用了。

下面会详细介绍一下硬件方面和软件方面。



## 2. 硬件方面：

**开发板**：Jetson Nano

功能：Jetson Nano是一款体积小巧、功能强大的人工智能嵌入式开发板,具备的性能和能效可以运行现代AI 工作负载，并行运行多个神经网络，以及同时处理来自多个高清传感器的数据。本项目是在百度飞桨上训练大量垃圾图形识别，训练完模型之后，基于Jetson Nano在Paddle Inference上进行推理部署。

![image-20231109205019499](https://github.com/error-keen/data-structure/blob/main/img/trash1.jpg)

**STM32舵机驱动**：STM32F103C8T6

功能：STM32F103C8T6是一款单片机芯片，由意法半导体Stmicroelectronics设计。STM32F103C8T6广泛应用于电子设备中，具有复杂控制和算法的处理器，如工控系统、机器人和马达控制等。它的主要功能包括模拟数字转换（ADC）、定时器和中断控制器（TIM）、串行通信接口（USART）等功能。此外，它还拥有许多具有创新性和高性能的特性，如高速I/O端口、嵌入式硬件分支预测等。它是一款成本低、功能强大的单片机。本项目以STM32F103C8T6作为主控芯片，Jetson Nano识别完产生结果，通过串口通信将结果传给STM32F103C8T6，然后再根据结果通过PWM信号控制舵机转动。

![STM32](https://github.com/error-keen/data-structure/blob/main/img/trash2.jpg)

**超声波传感器**：HC-SR04

功能：检测垃圾满载。

**摄像头**：接口是usb的摄像头都可以，像素越好识别的效果应该会更好一点，当然影响因素有很多，比如灯光，摄像头角度，或者图像处理的模型等等都会影响识别的结果。

**舵机**：两个DS3120，一个270度，另外一个90度以上都可以。

**伸缩电机**：压缩易拉罐。



## 3. 软件方面：

预测部署模型：在百度飞浆上训练自己的模型，基于训练得到的权重导出 inference 模型。

Paddle Inference推理部署：Paddle Inference 是飞桨的原生推理库， 作用于服务器端和云端，提供高性能的推理能力。 由于能力直接基于飞桨的训练算子，因此Paddle Inference 可以通用支持飞桨训练出的所有模型。Paddle Inference 功能特性丰富，性能优异，针对不同平台不同的应用场景进行了深度的适配优化，做到高吞吐、低时延，保证了飞桨模型在服务器端即训即用，快速部署。

python3.6:准备预测部署程序，摄像头的处理，图像处理，开机一键启动，视频播放，界面UI设计，处理后结果通信传给STM32等等都是通过python控制的。

C语言：此部分是需要烧到STM32F103C8T6上的代码，先在自己电脑上使用Kill5运行和调试一下代码，没问题就烧到32上就行了，如果后面实物做出来发现舵机的角度转动不对，及时调整此部分的代码，我不再过多叙述，因为此部分代码我在很多项目都使用过，没有太大问题，就调整一下控制舵机转动的代码就可以了。

以上对各个版本要求很严格，比如numpy必须用1.16版本，python必须用3.6版本，如果python版本过高或者过低，推荐使用Anaconda升级或者降级python的版本。



## 4. 具体的操作步骤：

1. 配置Jetson Nano的基础环境：参考一下连接的文章，再强调一遍注意numpy，python，以及Jetson Nano的版本，PaddlePaddle的版本必须严格一一对应。

   [【从踩坑到入门】基于Jetson Nano的深度学习模型部署教程 - 飞桨AI Studio星河社区 (baidu.com)](https://aistudio.baidu.com/projectdetail/3451173)

   

   ubuntu安装Anaconda：推荐文章https://blog.csdn.net/KRISNAT/article/details/124041869

2. 按照以上的文章，Jetson Nano的基础配置好了之后，即python版本，numpy版本，以及PaddlePaddle安装完之后，如果说你们想直接用我部署好的模型和代码，就不需要往下看了，直接把我的代码传到Jetson Nano上就可以用了。

3. 如果想自己重新拍照，训练模型，参考以下文章，这个文章是我在百度飞浆上发布的项目，我的训练过程以及步骤我在这篇文章上都进行了详细的说明。

   [Detection训练pp-yolo_垃圾识别_getson nano部署 - 飞桨AI Studio星河社区 (baidu.com)](https://aistudio.baidu.com/projectdetail/6686744?sUid=4562752&shared=1&ts=1697711405564)

4. 这一步是我对以上文章简单的说明，第一步我推荐标注工具labelme 下载与使用csdn那篇文章，只需要看到生成每张图片的.json文件就行了，后面不需要管，标注照片时，需要两个文件夹，一个为\_img文件，放置图片，另一个为\_json文件，放置每张图片对应生成的.json文件,这两个文件就是数据集，然后fork一下我的飞浆的这个项目，运行进入，然后将这两个文件的压缩文件传到根目录上，第三步我上面有详细的说明，根据自己的需求修改配置文件，大概就是这样，按照我飞浆上的项目一步一步运行就可以了。

   ![image-20231111100944784](https://github.com/error-keen/data-structure/blob/main/img/trash3.png)

5. 数据集不能太小，太小的话会报错，如果没问题的话，就可以导出推理模型，里面有这四个文件infer_cfg.yml，model.pdiparams，model.pdiparams.info，model.pdmodel，这四个文件其中有一个没用到，不过问题不大。

6. 将上面的包含着四个文件的文件夹替换掉我的model文件里的ppyolo_tiny_650e_coco_t文件就可以了，最后在终端上运行trash_identification.py就可以了，或者写一个shell程序，设置一下开机自动启动，都可以。

7. ![image-20231111215707643](https://github.com/error-keen/data-structure/blob/main/img/trash4.png)

   这三个文件，model和trash_ identification.py是传到Jetson Nano上的，运行trash_ identification.py就可以启动了，串口控制PWM驱动舵机文件是烧到STM32上的，如果要用自己的模型，替换掉model文件里的ppyolo_tiny_650e_coco_t就可以了。

8. 本来我想把所有的资料都传github上面，但是资料内存太大，更详细的资料我放百度网盘上了。

   链接：https://pan.baidu.com/s/1m1zpZeXbX7SPq4eEsRqQig 
   提取码：0ray

   

   ## 5.总结

   ​        这个项目将近做了两个月，我起初也是为了参加工训赛的，不过我收获很多知识，一开始我是用的树莓派进行部署，使用深度学习框架TensorFlow（使用MobileNetV1网络），机器学习框架XGBoost（使用XGBoost分类器）做这个项目的，而且我平时树莓派用的比较多，更熟悉一点，真的整整折磨了我快一个多月，遇到了很多很多问题，比如numpy的版本和python的版本，我在树莓派上安装Anaconda，弄了将近一个星期才安装好，然后降级python和numpy的版本，安装TensorFlow这个库也遇到了一堆问题，版本对应问题解决了，但怎么都安装不上去，最后安装上去了也运行不了，真给我搞崩溃了，遇到一堆又一堆的问题，最后能运行了，但树莓派的计算性能不仅弱爆了，运行速度比蜗牛都慢。

   ​       最后我换方案了，用jetson nano，使用Paddle Inference推理部署，其他的不说，Anaconda一会就安装好了，然后python和numpy的版本问题也迎刃而解，基本一天就部署好运行成功了，不过后面也没时间了，我界面都没有做，开机一键启动只能说勉勉强强，

   ​        最后两个星期才开始搭建实物，画电路板，焊电路板，搭建完，调试STM32那部分的代码，最后勉勉强强拿了一个省二，界面吃大亏了，压缩比赛前还没问题，结果比赛的时候崩了，唉，真的心累，暑假两个月时间，家都没回，电赛完接着就是工训赛，结果也不是很好，我当时一直在想，要是这两个月好好学习计算机专业知识不参加比赛肯定会收获很多，不过回想起这段经历，过程虽然很艰难，但确实收获了很多不一样的东西，满满的回忆。
