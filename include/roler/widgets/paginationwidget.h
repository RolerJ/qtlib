#pragma once

#include <qpushbutton.h>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QWidget>

class PaginationWidget : public QWidget {
    Q_OBJECT

public:
    explicit PaginationWidget(QWidget *parent = nullptr);
    ~PaginationWidget() override;

private:
    void init();

signals:
    void previous();
    void next();
    void indexChanged(int index);

private:
    QPushButton *m_prev;
    QPushButton *m_next;
    QLineEdit *m_jump_line_edit;
};
