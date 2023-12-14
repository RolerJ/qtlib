#pragma once

#include <QLabel>
#include <QLineEdit>

class LengthHintLineEdit : public QLineEdit {
    Q_OBJECT
public:
    explicit LengthHintLineEdit(QWidget *parent = nullptr);

    void setMaximumLength(int max_len);
    int maximumLength() const;

private:
    void init();

private:
    QLabel *m_hint_label;
};
