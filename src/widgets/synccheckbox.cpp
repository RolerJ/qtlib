#include "roler/widgets/synccheckbox.h"
#include <qglobal.h>

namespace roler {

SyncCheckBox::SyncCheckBox(QWidget *parent) : QCheckBox(parent) {
    init();
}

SyncCheckBox::~SyncCheckBox() {
    clear();
}

void SyncCheckBox::addChildCheckBox(QCheckBox *checkbox) {
    Q_ASSERT(checkbox);
    auto it = std::find(m_list.begin(), m_list.end(), checkbox);
    if (it != m_list.end()) {
        return;
    }
    m_list.push_back(checkbox);
    connect(checkbox, &QCheckBox::stateChanged, this, &SyncCheckBox::updateCheckState);
    connect(checkbox, &QObject::destroyed, this, &SyncCheckBox::checkBoxDestroyed);
}

void SyncCheckBox::removeChildCheckBox(QCheckBox *checkbox) {
    Q_ASSERT(checkbox);
    auto it = std::find(m_list.begin(), m_list.end(), checkbox);
    if (it == m_list.end()) {
        return;
    }
    disconnect(checkbox, &QCheckBox::stateChanged, this, &SyncCheckBox::updateCheckState);
    disconnect(checkbox, &QObject::destroyed, this, &SyncCheckBox::checkBoxDestroyed);
    m_list.erase(it);
}

void SyncCheckBox::setChildCheckBoxList(const QList<QCheckBox *> &list) {
    clear();
    for (QCheckBox *cb : list) {
        addChildCheckBox(cb);
    }
}

const std::list<QCheckBox *> &SyncCheckBox::childCheckBoxList() const {
    return m_list;
}

void SyncCheckBox::clear() {
    for (QCheckBox *cb : m_list) {
        disconnect(cb, &QCheckBox::stateChanged, this, &SyncCheckBox::updateCheckState);
    }
    m_list.clear();
}

void SyncCheckBox::init() {
    this->setTristate(true);
    connect(this, &QCheckBox::stateChanged, this, &SyncCheckBox::onStateChanged);
    connect(this, &QAbstractButton::clicked, this, &SyncCheckBox::onClicked);
}

void roler::SyncCheckBox::onStateChanged(int state) {
    if (state == Qt::PartiallyChecked) {
        return;
    }

    for (QCheckBox *cb : m_list) {
        if (cb->checkState() != state)
            cb->setCheckState(static_cast<Qt::CheckState>(state));
    }
}

void roler::SyncCheckBox::onClicked(bool checked) {
    if (this->checkState() == Qt::PartiallyChecked)
        this->setCheckState(Qt::Checked);
}

void roler::SyncCheckBox::checkBoxDestroyed(QObject *obj) {
    auto it = std::find(m_list.begin(), m_list.end(), obj);
    if (it == m_list.end()) {
        return;
    }
    m_list.erase(it);
}

void SyncCheckBox::updateCheckState() {
    if (m_list.empty())
        return;

    int checked_count = 0;
    for (QCheckBox *cb : m_list) {
        if (cb->isChecked())
            checked_count++;
    }

    if (checked_count == 0 && this->checkState() != Qt::Unchecked) {
        this->setCheckState(Qt::Unchecked);
        return;
    }

    if (checked_count == m_list.size() && this->checkState() != Qt::Checked) {
        this->setCheckState(Qt::Checked);
        return;
    }

    if (checked_count != 0 && checked_count < m_list.size() && this->checkState() != Qt::PartiallyChecked) {
        this->setCheckState(Qt::PartiallyChecked);
        return;
    }
}

}  // namespace roler