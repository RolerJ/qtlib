#include "widgets/synccheckbox.h"

using namespace roler;

SyncCheckBox::SyncCheckBox(QWidget *parent) : QCheckBox(parent) {
    init();
}

SyncCheckBox::~SyncCheckBox() {
    clear();
}

void SyncCheckBox::addChildCheckBox(QCheckBox *checkbox) {
    Q_ASSERT(checkbox);
    if (m_list.contains(checkbox))
        return;
    m_list.append(checkbox);
    connect(checkbox, &QCheckBox::stateChanged, this, &SyncCheckBox::updateCheckState);
}

void SyncCheckBox::removeChildCheckBox(QCheckBox *checkbox) {
    if (!m_list.contains(checkbox))
        return;
    disconnect(checkbox, &QCheckBox::stateChanged, this, &SyncCheckBox::updateCheckState);
    m_list.removeOne(checkbox);
}

void SyncCheckBox::setChildCheckBoxList(const QList<QCheckBox *> &list) {
    clear();
    m_list = list;
    for (QCheckBox *cb : m_list) {
        connect(cb, &QCheckBox::stateChanged, this, &SyncCheckBox::updateCheckState);
    }
}

const QList<QCheckBox *> &SyncCheckBox::childCheckBoxList() const {
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

void SyncCheckBox::updateCheckState() {
    if (m_list.isEmpty())
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

    if (checked_count == m_list.count() && this->checkState() != Qt::Checked) {
        this->setCheckState(Qt::Checked);
        return;
    }

    if (checked_count != 0 && checked_count < m_list.count() && this->checkState() != Qt::PartiallyChecked) {
        this->setCheckState(Qt::PartiallyChecked);
        return;
    }
}