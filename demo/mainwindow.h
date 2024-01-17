#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void init();
    void initModelTest();
    void initPasswordLineEdit();
    void initTagWidget();
    void initSyncCheckBox();
    void initPagingWidget();
    void initLengthHintLineEdit();
    void initAutoCloseMessageBox();

private:
    Ui::MainWindow *ui;
    QMenu *m_widgets_menu;
};
#endif  // MAINWINDOW_H
