#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QIcon>
#include <QLineEdit>
#include <QPixmap>

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
    initPasswordLineEdit();
    initTagWidget();
    initSyncCheckBox();
    initPagingWidget();
}

void MainWindow::initPasswordLineEdit() {
    PasswordLineEdit *lineEdit = new PasswordLineEdit(this);
    lineEdit->setSwitchIcons(QIcon("./resource/show.svg"), QIcon("./resource/hide.svg"));
    QWidget *widget = new QWidget(this);
    widget->setLayout(new QHBoxLayout);
    widget->layout()->addWidget(lineEdit);
    int index = ui->stackedWidget->addWidget(widget);
    connect(ui->action_PasswordLineEdit, &QAction::triggered, this,
            [this, index]() { ui->stackedWidget->setCurrentIndex(index); });
}

void MainWindow::initTagWidget() {
    TagWidget *tagWidget = new TagWidget(this);
    int index = ui->stackedWidget->addWidget(tagWidget);
    connect(ui->action_TagWidget, &QAction::triggered, this,
            [this, index]() { ui->stackedWidget->setCurrentIndex(index); });
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
    connect(ui->action_SyncCheckBox, &QAction::triggered, this,
            [this, index]() { ui->stackedWidget->setCurrentIndex(index); });
}

void MainWindow::initPagingWidget() {}
