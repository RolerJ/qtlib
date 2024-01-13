#include "roler/widgets/lengthhintlineedit.h"

#include <QHBoxLayout>

namespace roler {

LengthHintLineEdit::LengthHintLineEdit(QWidget *parent) : QLineEdit(parent) {
    init();
    setMaxLength(20);
}

void LengthHintLineEdit::setMaxLength(int len) {
    QLineEdit::setMaxLength(len);
    m_hint_label->setText(QString("0/%1").arg(len));

    QHBoxLayout *line_edit_layout = new QHBoxLayout;
    line_edit_layout->addWidget(m_hint_label);
    line_edit_layout->setAlignment(Qt::AlignRight);
    line_edit_layout->setContentsMargins(5, 0, 5, 0);
    if (m_hint_label->isVisibleTo(this)) {
        int label_width = m_hint_label->fontMetrics().horizontalAdvance(QString("%1/%1").arg(len));
        this->setTextMargins(0, 0, label_width + 3, 0);
    } else {
        this->setTextMargins(0, 0, 0, 0);
    }

    if (this->layout())
        delete this->layout();
    this->setLayout(line_edit_layout);
}

void LengthHintLineEdit::setHintLabelVisible(bool visible) {
    m_hint_label->setVisible(visible);
    if (visible) {
        int len = this->maxLength();
        int label_width = m_hint_label->fontMetrics().horizontalAdvance(QString("%1/%1").arg(len));
        this->setTextMargins(0, 0, label_width + 3, 0);
    } else {
        this->setTextMargins(0, 0, 0, 0);
    }
}

void LengthHintLineEdit::init() {
    m_hint_label = new QLabel(this);
    connect(this, &QLineEdit::textChanged, this, [this]() {
        int size = this->text().size();
        m_hint_label->setText(QString("%1/%2").arg(size).arg(this->maxLength()));
    });
}

}  // namespace roler