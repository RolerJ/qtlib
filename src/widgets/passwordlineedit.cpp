#include "passwordlineedit.h"

#include <QAction>
#include <QIcon>

PasswordLineEdit::PasswordLineEdit(QWidget *parent) : QLineEdit(parent) {
    init();
    m_show->trigger();
}

PasswordLineEdit::~PasswordLineEdit() {
}

void PasswordLineEdit::setSwitchIcons(const QIcon &show_icon, const QIcon &hide_icon) {
    m_show->setIcon(show_icon);
    m_hide->setIcon(hide_icon);
}

void PasswordLineEdit::getSwitchIcons(QIcon *show_icon, QIcon *hide_icon) {
    if (show_icon) {
        *show_icon = m_show->icon();
    }
    if (hide_icon) {
        *hide_icon = m_hide->icon();
    }
}

void PasswordLineEdit::init() {
    m_hide = this->addAction(QIcon(":/images/hide.svg"), QLineEdit::TrailingPosition);
    m_show = this->addAction(QIcon(":/images/show.svg"), QLineEdit::TrailingPosition);
    m_show->setVisible(false);
    connect(m_hide, &QAction::triggered, this, [this]() {
        this->setEchoMode(QLineEdit::Normal);
        m_hide->setVisible(false);
        m_show->setVisible(true);
    });
    connect(m_show, &QAction::triggered, this, [this]() {
        this->setEchoMode(QLineEdit::Password);
        m_hide->setVisible(true);
        m_show->setVisible(false);
    });
}
