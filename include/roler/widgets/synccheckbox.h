#pragma once

#include <QCheckBox>
#include <QList>

namespace roler {

class SyncCheckBox : public QCheckBox {
    Q_OBJECT

public:
    SyncCheckBox(QWidget *parent = nullptr);
    ~SyncCheckBox() override;

    // Add child checkbox
    void addChildCheckBox(QCheckBox *checkbox);

    // Remove child
    void removeChildCheckBox(QCheckBox *checkbox);

    // Set child checkbox list
    void setChildCheckBoxList(const QList<QCheckBox *> &list);

    // Get child checkbox set
    const QList<QCheckBox *> &childCheckBoxList() const;

    // Clear child checkbox list
    void clear();

private:
    void init();

private slots:
    void updateCheckState();
    void onStateChanged(int state);
    void onClicked(bool checked);

private:
    QList<QCheckBox *> m_list;
};

}  // namespace roler
