# simpleQtdemo
a simple qt demo (  QWebView  ,QSystemTrayIcon) and how hook hot key in window os

使用QT5.5.0 编写， 一开始使用Qtcreater编写，发布到生产环境有问题
考虑xp系统以及 32 bit系统 ，下载Qt 5.5.0 for Windows 32-bit 

后来转为 使用Visual stdio开发环境 （通过Visual Studio Add-in 1.2.4 for Qt5 插件桥接

1）出现的问题 
xxxxxx.exe is not a valid Win32 application 
解决办法 http://stackoverflow.com/questions/11305633/xxxxxx-exe-is-not-a-valid-win32-application


2）心得将 plugins\platforms的目录 拷贝到可执行文件的目录下
