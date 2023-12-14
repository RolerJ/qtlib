#include "lengthhintlineedit.h"

#include <QHBoxLayout>

LengthHintLineEdit::LengthHintLineEdit(QWidget *parent) : QLineEdit(parent) {
    init();
    setMaximumLength(20);
}

void LengthHintLineEdit::setMaximumLength(int len) {
    this->setMaxLength(len);
    m_hint_label->setText(QString("%1/%2").arg(len).arg(len));
    m_hint_label->adjustSize();
    m_hint_label->setFixedSize(m_hint_label->size());
    m_hint_label->setText(QString("0/%1").arg(len));

    if (this->layout())
        delete this->layout();
    QHBoxLayout *line_edit_layout = new QHBoxLayout;
    this->setLayout(line_edit_layout);
    line_edit_layout->addWidget(m_hint_label);
    line_edit_layout->setAlignment(Qt::AlignRight);
    line_edit_layout->setContentsMargins(0, 0, 5, 0);
    this->setTextMargins(0, 0, m_hint_label->width(), 0);
}

int LengthHintLineEdit::maximumLength() const {
    return this->maxLength();
}

void LengthHintLineEdit::init() {
    m_hint_label = new QLabel(this);
    connect(this, &QLineEdit::textChanged, this, [this]() {
        int size = this->text().size();
        m_hint_label->setText(QString("%1/%2").arg(size).arg(this->maxLength()));
    });
}
