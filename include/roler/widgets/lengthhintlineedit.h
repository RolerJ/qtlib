#pragma once

#include <QLabel>
#include <QLineEdit>

namespace roler {

class LengthHintLineEdit : public QLineEdit {
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