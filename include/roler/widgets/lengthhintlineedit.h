#pragma once

#include "roler/roler_global.h"

#include <QLabel>
#include <QLineEdit>

namespace roler {

class ROLER_EXPORT LengthHintLineEdit : public QLineEdit {
    Q_OBJECT

public:
    explicit LengthHintLineEdit(QWidget *parent = nullptr);

    // Hide QLineEdit::setMaxLength(int)
    void setMaxLength(int max_len);

    void setHintLabelVisible(bool visible = true);

private:
    void init();

private:
    QLabel *m_hint_label;
};

}  // namespace roler