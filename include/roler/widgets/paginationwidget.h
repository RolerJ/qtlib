#pragma once

#include "roler/roler_global.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

namespace roler {

class ROLER_EXPORT PaginationWidget : public QWidget {
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

}  // namespace roler