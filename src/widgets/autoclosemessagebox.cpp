#include "roler/widgets/autoclosemessagebox.h"

namespace roler {

AutoCloseMessageBox::AutoCloseMessageBox(QWidget *parent) : QMessageBox(parent) {
    init();
}

AutoCloseMessageBox::AutoCloseMessageBox(QMessageBox::Icon icon, const QString &title, const QString &text,
                                         QMessageBox::StandardButtons buttons, QWidget *parent, Qt::WindowFlags flags)
    : QMessageBox(icon, title, text, buttons, parent, flags) {
    init();
}

AutoCloseMessageBox::~AutoCloseMessageBox() {
    if (m_timer.isActive()) {
        m_timer.stop();
    }
}

void AutoCloseMessageBox::showWithAutoClose(int ms) {
    m_timer.start(ms);
    this->show();
}

void AutoCloseMessageBox::execWithAutoClose(int ms) {
    m_timer.start(ms);
    this->exec();
}

void AutoCloseMessageBox::init() {
    m_timer.setSingleShot(true);
    connect(&m_timer, &QTimer::timeout, this, &QWidget::close);
}

}  // namespace roler