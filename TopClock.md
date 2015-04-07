# 小时钟 主页 #
## 简述 ##
> 小时钟 是一个以GPL协议发布的免费软件。她可以在您的手机屏幕上方以LED数码管的效果显示时间。她曾经叫做“状态栏时钟（ClockOnTop）”，从那个时候起她就已经被很多ROM所集成。她的大小不超过20K，您可以把它放在手机的任何位置而不必担心消耗许多存储空间。您可以通过命令行参数选择12小时制或是24小时制显示，并选择显示的颜色。如果不指定颜色她将自动选择您的手机主题里指定的颜色。

## 变更履历 ##
> 前往[小时钟 变更履历](TopClockHistory.md)

## 下载 ##
> 前往[小时钟 下载页](http://code.google.com/p/huangda1982/downloads/list?q=label:TopClock)

## 命令行参数说明 ##
  * _-hide_
> > 启动时不显示窗口，默认为显示窗口。
  * _-12_
> > 以十二小时制显示时间，默认以二十四小时制显示。
  * _-color #XXXXXX_
> > 以#XXXXXX格式指定RGB颜色值，默认为自动颜色。

## 命令行参数举例 ##
  1. 55#"\Program Files\TopClock\TopClock" -12
  1. 62#"\Program Files\TopClock\TopClock" -color #0000ff -hide