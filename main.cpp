#include "dialog.h"
#include <QApplication>
#include <QSystemSemaphore>
#include <QDebug>
#include <QSharedMemory>
#include <QMessageBox>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    //进程间互斥， 只能打开一个程序
    // 确保只运行一次
      QSystemSemaphore sema("chinasoTool",1,QSystemSemaphore::Open);
      sema.acquire();// 在临界区操作共享内存 SharedMemory
      QSharedMemory mem("SystemObject_chinaso");// 全局对象名
      if (!mem.create(1))// 如果全局对象以存在则退出
       {
  //        QMessageBox::information(0, MESSAGEBOXTXT,"An instance has already been running.");
          sema.release();// 如果是 Unix 系统，会自动释放。
          return 0;
      }
      sema.release();// 临界区




    QApplication a(argc, argv);
	
	QDesktopWidget* desktop = QApplication::desktop();


    Dialog w;

	w.move((desktop->width() - w.width()) / 2, (desktop->height() / 16));
 //   w.show();

    return a.exec();
}
