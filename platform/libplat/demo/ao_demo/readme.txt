ao模块的调用示例，提供了ao模块接口的调用方法。
demo的输入参数：ak_ao_demo [采样率] [播放文件全路径] [音量]

例如输入：ak_ao_demo 8000 /mnt/a.pcm 7

测试者调用ao demo播放pcm文件，可以通过喇叭或者耳机听播放的音频是否正常。

注意：
1、要注意保存路径最后必须带“/”；
2、测试此demo时需要先kill掉anyka_ipc；
3、如果需要播放的pcm文件a.pcm是放置在/tmp/目录下，a.pcm不要使用太大的文件，否则可能会因为内存不足而无法运行；