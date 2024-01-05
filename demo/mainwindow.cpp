#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QIcon>
#include <QLineEdit>
#include <QPixmap>

#include "roler/widgets/autoclosemessagebox.h"
#include "roler/widgets/lengthhintlineedit.h"
#include "roler/widgets/paginationwidget.h"
#include "roler/widgets/passwordlineedit.h"
#include "roler/widgets/synccheckbox.h"
#include "roler/widgets/tagwidget.h"

using namespace roler;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::init() {
    m_widgets_menu = ui->menubar->addMenu("Widgets");

    initPasswordLineEdit();
    initTagWidget();
    initSyncCheckBox();
    initPagingWidget();
    initLengthHintLineEdit();
    initAutoCloseMessageBox();
}

void MainWindow::initPasswordLineEdit() {
    PasswordLineEdit *lineEdit = new PasswordLineEdit(this);
    QWidget *widget = new QWidget(this);
    widget->setLayout(new QHBoxLayout);
    widget->layout()->addWidget(lineEdit);
    int index = ui->stackedWidget->addWidget(widget);

    auto *action = m_widgets_menu->addAction("PasswordLineEdit");
    connect(action, &QAction::triggered, this, [this, index]() { ui->stackedWidget->setCurrentIndex(index); });
}

void MainWindow::initTagWidget() {
    TagWidget *tagWidget = new TagWidget(this);
    int index = ui->stackedWidget->addWidget(tagWidget);
    auto *action = m_widgets_menu->addAction("TagWidget");
    connect(action, &QAction::triggered, this, [this, index]() { ui->stackedWidget->setCurrentIndex(index); });
}

void MainWindow::initSyncCheckBox() {
    SyncCheckBox *scb = new SyncCheckBox(this);
    scb->setText("SyncCheckBox");
    QWidget *widget = new QWidget(this);
    QVBoxLayout *v_layout = new QVBoxLayout(widget);
    QHBoxLayout *h_layout = new QHBoxLayout;
    for (int i = 0; i < 5; i++) {
        QCheckBox *cb = new QCheckBox(widget);
        cb->setText(QString::number(i + 1));
        h_layout->addWidget(cb);
        scb->addChildCheckBox(cb);
    }
    v_layout->addWidget(scb);
    v_layout->addLayout(h_layout);
    int index = ui->stackedWidget->addWidget(widget);
    auto *action = m_widgets_menu->addAction("SyncCheckBox");
    connect(action, &QAction::triggered, this, [this, index]() { ui->stackedWidget->setCurrentIndex(index); });
}

void MainWindow::initPagingWidget() {}

void MainWindow::initLengthHintLineEdit() {
    LengthHintLineEdit *line_edit = new LengthHintLineEdit(this);

    QWidget *widget = new QWidget(this);
    widget->setLayout(new QHBoxLayout);
    widget->layout()->addWidget(line_edit);
    int index = ui->stackedWidget->addWidget(widget);
    auto *action = m_widgets_menu->addAction("LengthHintLineEdit");
    connect(action, &QAction::triggered, this, [this, index]() { ui->stackedWidget->setCurrentIndex(index); });
}

void MainWindow::initAutoCloseMessageBox() {
    QMenu *menu = m_widgets_menu->addMenu("AutoCloseMessageBox");

    auto *action_show = menu->addAction("Show");
    auto *action_exec = menu->addAction("Exec");
    connect(action_show, &QAction::triggered, this, [this]() {
        AutoCloseMessageBox *msgbox =
            new AutoCloseMessageBox(QMessageBox::Information, "Title", "Contents Text", QMessageBox::Ok);
        msgbox->setAttribute(Qt::WA_DeleteOnClose);
        msgbox->showWithAutoClose(2000);
    });
    connect(action_exec, &QAction::triggered, this, [this]() {
        AutoCloseMessageBox *msgbox =
            new AutoCloseMessageBox(QMessageBox::Information, "Title", "Contents Text", QMessageBox::Ok);
        msgbox->setAttribute(Qt::WA_DeleteOnClose);
        msgbox->execWithAutoClose(2000);
    });
}
