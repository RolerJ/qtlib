#include "widgets/passwordlineedit.h"

#include <QAction>
#include <QIcon>
#include <QPainter>
#include <QSvgRenderer>

namespace roler {

PasswordLineEdit::PasswordLineEdit(QWidget *parent) : QLineEdit(parent) {
    init();
    m_show->trigger();
}

PasswordLineEdit::~PasswordLineEdit() {}

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
    const char *show_svg =
        R"(<?xml version="1.0" standalone="no"?><!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN" "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd"><svg t="1698891993787" class="icon" viewBox="0 0 1024 1024" version="1.1" xmlns="http://www.w3.org/2000/svg" p-id="6623" xmlns:xlink="http://www.w3.org/1999/xlink" width="200" height="200"><path d="M512 766.7c-209 0-364.2-230.8-370.7-240.6-5.6-8.5-5.6-19.6 0-28.1 6.5-9.8 161.7-240.6 370.7-240.6S876.2 488.2 882.7 498c5.6 8.5 5.6 19.6 0 28.1-6.5 9.8-161.7 240.6-370.7 240.6zM193.9 512c36 48.2 164 203.7 318.1 203.7S794.2 560.2 830.1 512c-36-48.2-164-203.7-318.1-203.7S229.8 463.8 193.9 512z" p-id="6624"></path><path d="M512 637c-68.9 0-124.9-56.1-124.9-125s56-125 124.9-125 124.9 56.1 124.9 125-56 125-124.9 125z m0-199c-40.8 0-74 33.2-74 74s33.2 74 74 74 74-33.2 74-74-33.2-74-74-74z" p-id="6625"></path></svg>)";
    const char *hide_svg =
        R"(<?xml version="1.0" standalone="no"?><!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN" "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd"><svg t="1698891849450" class="icon" viewBox="0 0 1024 1024" version="1.1" xmlns="http://www.w3.org/2000/svg" p-id="6488" data-spm-anchor-id="a313x.manage_type_myprojects.0.i0.6e273a81osr6GK" xmlns:xlink="http://www.w3.org/1999/xlink" width="200" height="200"><path d="M512 572.7c-209 0-364.2-230.8-370.7-240.6-7.8-11.7-4.5-27.5 7.2-35.3 11.6-7.8 27.5-4.6 35.3 7.1 1.4 2.2 146.7 217.8 328.2 217.8S838.8 306.2 840.2 304c7.9-11.8 23.7-14.9 35.3-7.1 11.7 7.8 14.9 23.5 7.2 35.3C876.2 342 721 572.7 512 572.7z" p-id="6489"></path><path d="M512 731.4c-14.1 0-25.5-11.4-25.5-25.5V562.3c0-14.1 11.4-25.5 25.5-25.5s25.5 11.4 25.5 25.5V706c0 14-11.4 25.4-25.5 25.4zM206.1 642.9c-6.5 0-13-2.5-18-7.5-9.9-9.9-9.9-26.1 0-36l114.5-114.5c9.9-9.9 26.1-9.9 36 0s9.9 26.1 0 36L224.1 635.4c-4.9 5-11.4 7.5-18 7.5zM817.7 641.6c-6.5 0-13-2.5-18-7.5l-110-109.9c-9.9-9.9-9.9-26.1 0-36 9.9-9.9 26.1-9.9 36 0l110 109.9c9.9 9.9 9.9 26.1 0 36-5 5-11.5 7.5-18 7.5z" p-id="6490"></path></svg>)";

    QSvgRenderer rd;
    QPixmap pixmap_show(1024, 1024), pixmap_hide(1024, 1024);
    pixmap_show.fill(Qt::transparent);
    pixmap_hide.fill(Qt::transparent);
    QPainter painter_show(&pixmap_show);
    rd.load(QByteArray(show_svg));
    rd.render(&painter_show);
    QPainter painter_hide(&pixmap_hide);
    rd.load(QByteArray(hide_svg));
    rd.render(&painter_hide);

    m_hide = this->addAction(QIcon(pixmap_show), QLineEdit::TrailingPosition);
    m_show = this->addAction(QIcon(pixmap_hide), QLineEdit::TrailingPosition);
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

}  // namespace roler