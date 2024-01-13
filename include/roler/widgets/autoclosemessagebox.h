#pragma once

#include "roler/roler_global.h"

#include <QMessageBox>
#include <QTimer>

namespace roler {

class ROLER_EXPORT AutoCloseMessageBox : public QMessageBox {
    Q_OBJECT

public:
    explicit AutoCloseMessageBox(QWidget *parent = nullptr);
    AutoCloseMessageBox(QMessageBox::Icon icon, const QString &title, const QString &text,
                        QMessageBox::StandardButtons buttons = NoButton, QWidget *parent = nullptr,
                        Qt::WindowFlags flags = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    ~AutoCloseMessageBox() override;

    void showWithAutoClose(int ms);
    void execWithAutoClose(int ms);

private:
    void init();

private:
    QTimer m_timer;
};

}  // namespace roler