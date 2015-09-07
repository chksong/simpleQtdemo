#include "dialog.h"
#include "ui_dialog.h"

#pragma comment(lib, "user32.lib")

#include <QDesktopServices>
#include <QUrl>

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QTime>


#include <QDebug>
//#include "qxtglobalshortcut5/gui/qxtglobalshortcut.h

#include <Windows.h>
HHOOK key_keep = NULL ;

LRESULT CALLBACK Hotkey_Filter(int code, WPARAM wparam, LPARAM lparam);

#define KEY_BOARD_KEYUP 0x80000000

Dialog  *pMainDlg = NULL ;


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->pushButton_search,&QPushButton::clicked,this,&Dialog::explore_web);

    ui->webView->load(QUrl("http://m.chinaso.com"));

    QIcon * icon= new QIcon(":/111.png") ;
    setWindowIcon(*icon);

    m_trayIcon = new QSystemTrayIcon(this) ;
    m_trayIcon->setIcon(*icon);
    m_trayIcon->show();


    QAction *act_quit = new QAction(this) ;
    act_quit->setText("quit");
    connect(act_quit, &QAction::triggered, this,&Dialog::close) ;

    QAction *act_show = new QAction(this) ;
    act_show->setText(QString("显示窗口"));
    connect(act_show ,&QAction::triggered , this ,&Dialog::show) ;

    QMenu  *menu = new QMenu(this) ;
    menu->addAction(act_show) ;
    menu->addAction(act_quit) ;
    m_trayIcon->setContextMenu(menu);


    connect(ui->btHide ,&QPushButton::clicked, this ,&Dialog::hide) ;


//    QxtGlobalShortcut *shortcut = new QxtGlobalShortcut(this);
//    shortcut->setShortcut(QKeySequence("Shift+1"));
//    connect(shortcut, &QxtGlobalShortcut::activated,
//        [=]() {qDebug() << "shortcut activated";});


    // 退出在最后窗口关闭点击关闭时程序不关闭
 //   QApplication::setQuitOnLastWindowClosed(false) ;
    key_keep = NULL ;

    pMainDlg = this ;

    register_key_hook() ;
}

Dialog::~Dialog()
{
    unregister_key_hook();
    delete ui;
}

void Dialog::explore_web()
{
    QDesktopServices::openUrl(QUrl("http://m.chinaso.com/")) ;
}

void Dialog::explore() {
  //  QT::sender()
}




void Dialog::unregister_key_hook()
{
    if(key_keep)
         UnhookWindowsHookEx(key_keep);

    key_keep = NULL;
}

LRESULT CALLBACK KeyboardProc(int code, WPARAM wparam, LPARAM lparam)
{
//    ITEM_FUNC array[] =
//    {
//          VK_LEFT ,   &Dialog::select_next_card,0,
//          VK_RIGHT,   &Dialog::select_next_card,1,

//          VK_NUMPAD0, &Dialog::select_main_card,0,
//          VK_NUMPAD1, &Dialog::select_main_card,1,
//          VK_NUMPAD2, &Dialog::select_main_card,2,
//          VK_NUMPAD3, &Dialog::select_main_card,3,
//          VK_NUMPAD4, &Dialog::select_main_card,4,

//          '0',&MainWidget::select_main_card,0,
//          '1',&MainWidget::select_main_card,1,
//          '2',&MainWidget::select_main_card,2,
//          '3',&MainWidget::select_main_card,3,
//          '4',&MainWidget::select_main_card,4
//    };
//    if(lparam & KEY_BOARD_KEYUP)
//    {
//        int size = sizeof(array)/sizeof(array[0]);
//        for(int i = 0;i < size;i++)
//        {
//            if(wparam == array[i].code)
//            {
//                _main_win->excute_function(array[i].pFun,array[i].param);
//            }
//       }
//
//    }

    if ( lparam & KEY_BOARD_KEYUP) {
        qDebug() << "****" << rand();
    }

    return CallNextHookEx(0, code, wparam, lparam);
}

//钩子 回调函数
void Dialog::HotKeyFunc(int ) {

      qDebug() << "****" << rand();

     if (  this->isHidden() ) {
         this->show();
     }
     else  {
         this->hide();
     }


}


void Dialog::register_key_hook()
{
//   if(key_keep)return;
//      key_keep = SetWindowsHookEx(WH_KEYBOARD,KeyboardProc,NULL,GetCurrentThreadId());
    //安装低级键盘钩子
  // key_keep=  SetWindowsHookEx(WH_KEYBOARD_LL, Hotkey_Filter,GetModuleHandle(TEXT("HookDll")),GetCurrentThreadId());
     key_keep=  SetWindowsHookEx(WH_KEYBOARD_LL, Hotkey_Filter,NULL ,NULL);
   if (NULL == key_keep)
   {
      qDebug() << "install hotkook is error" ;
   }

   qDebug() << "install hotkook is " ;
}




LRESULT CALLBACK Hotkey_Filter(int nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *Key_Info = (KBDLLHOOKSTRUCT*)lParam;
    if (HC_ACTION == nCode)
    {
        if (WM_KEYDOWN == wParam /*|| WM_SYSKEYDOWN*/)  //如果按键为按下状态
        {
           // qDebug() << "****" << rand();
            if  (Key_Info->vkCode == VK_LWIN || Key_Info->vkCode == VK_RWIN )    //屏敝 WIN(左右) 键
            {
                pMainDlg->HotKeyFunc(0);
                return TRUE ;
            }

//            if (Key_Info->vkCode == 0x4D && ((GetKeyState(VK_LWIN) & 0x8000) ||
//                                            (GetKeyState(VK_RWIN) & 0x8000))) //屏敝 WIN+D 组合键(左右)
//            {
//                return TRUE;
//            }

//            if (Key_Info->vkCode == 0x44 && ((GetKeyState(VK_LWIN) & 0x8000) ||
//                                             (GetKeyState(VK_RWIN) & 0x8000)))  //屏敝 WIN+M 组合键(左右)
//            {
//                return TRUE;
//            }

//            if (Key_Info->vkCode == 0x1b && GetKeyState(VK_CONTROL) & 0x8000) //屏敝 CTRL + ESC 组合键
//            {
//                return TRUE;
//            }

//            if (Key_Info->vkCode == VK_TAB && Key_Info->flags & LLKHF_ALTDOWN) //屏敝 ATL + TAB 组合键
//            {
//                return TRUE;
//            }

//             if (Key_Info->vkCode == VK_ESCAPE && Key_Info->flags & LLKHF_ALTDOWN) //屏敝 ATL + ESC 组合键
//            {
//                 return TRUE;
//            }

        }
    }

    return CallNextHookEx(key_keep, nCode, wParam, lParam); //回调
}

// BOOL Hotkey_Install(DWORD ThreadID)
// {
//    h_HotKey = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)Hotkey_Filter, //安装低级键盘钩子

//    GetModuleHandle("hotkey"), ThreadID);
//    if (NULL == h_HotKey)
//    {

//        MessageBox(NULL, "安装钩子出错 !", "error", MB_ICONSTOP);
//        return FALSE;
//    }
//   return TRUE;
//}

//BOOL Hotkey_UnInstall()
//{
//    UnhookWindowsHookEx(h_HotKey); //卸载钩子
//    return TRUE;
//}
