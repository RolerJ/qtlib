#include "roler/widgets/tagwidget.h"

#include <QHBoxLayout>
#include <QLabel>

namespace roler {

TagLabel::TagLabel(QWidget *parent) : QWidget(parent) {
    init();
    setCloseable(true);
}

void TagLabel::setText(const QString &text) {
    m_label->setText(text);
    this->setToolTip(text);
}

QString TagLabel::text() const {
    return m_label->text();
}

void TagLabel::setCloseable(bool closeable) {
    m_delete_btn->setVisible(closeable);
}

bool TagLabel::isCloseable() const {
    return m_delete_btn->isVisible();
}

void TagLabel::resizeEvent(QResizeEvent *e) {
    QWidget::resizeEvent(e);
    m_delete_btn->setFixedWidth(m_label->height());
}

void TagLabel::init() {
    setAttribute(Qt::WA_StyledBackground);
    setObjectName("tag_label");
    m_label = new QLabel(this);
    m_delete_btn = new QPushButton(this);
    m_delete_btn->setText("X");
    m_delete_btn->setFlat(true);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_label);
    layout->addWidget(m_delete_btn);
    this->setContentsMargins(5, 0, 0, 0);
    this->setStyleSheet(
        "QWidget#tag_label {background-color: lightblue; border: "
        "1px solid blue;}");
    connect(m_delete_btn, &QPushButton::clicked, this, &TagLabel::closeTag);
}

TagWidget::TagWidget(QWidget *parent) : QWidget(parent) {
    m_inputLineEdit = new QLineEdit(this);
    m_inputLineEdit->setPlaceholderText(tr("Input Label"));
    m_inputLineEdit->setMaximumWidth(100);
    connect(m_inputLineEdit, &QLineEdit::returnPressed, this, qOverload<>(&TagWidget::addTag));
    setCountPerRow(5);
    updateTags();
}

TagWidget::~TagWidget() {
    clear();
}

void TagWidget::setCountPerRow(int count) {
    count = qMax(count, 1);  // 最少一个
    m_count_per_row = count;
}

int TagWidget::countPerRow() const {
    return m_count_per_row;
}

void TagWidget::clear() {
    qDeleteAll(m_tag_vec);
    m_tag_vec.clear();
}

void TagWidget::setLabelList(const QStringList &list) {
    clear();
    for (auto text : list) {
        addTag(text);
    }
}

QStringList TagWidget::labelList() const {
    QStringList list;
    for (auto *tag : qAsConst(m_tag_vec)) {
        list << tag->text();
    }
    return list;
}

void TagWidget::updateTags() {
    // 新的Layout
    QVBoxLayout *layout = new QVBoxLayout;
    int current_size = m_tag_vec.size();
    QHBoxLayout *last_layout = nullptr;
    if (current_size <= m_count_per_row) {
        QHBoxLayout *layout_h = new QHBoxLayout;
        for (auto *tag : qAsConst(m_tag_vec))
            layout_h->addWidget(tag);
        layout->addLayout(layout_h);
        last_layout = layout_h;
    } else {
        int rows = current_size / m_count_per_row;
        if (current_size % m_count_per_row != 0)
            rows++;
        for (int row = 0; row < rows; row++) {
            QHBoxLayout *layout_h = new QHBoxLayout;
            for (int i = 0; i < m_count_per_row; i++) {
                int index = row * m_count_per_row + i;
                if (index < m_tag_vec.size())
                    layout_h->addWidget(m_tag_vec.at(index));
            }
            layout->addLayout(layout_h);
            last_layout = layout_h;
        }
    }

    // 编辑框
    if (last_layout == nullptr || last_layout->count() >= m_count_per_row) {
        QHBoxLayout *line_edit_layout = new QHBoxLayout;
        line_edit_layout->addWidget(m_inputLineEdit);
        line_edit_layout->addStretch();
        layout->addLayout(line_edit_layout);
    } else {
        last_layout->addWidget(m_inputLineEdit);
        last_layout->addStretch();
    }

    // 移除旧的layout
    if (this->layout()) {
        delete this->layout();
    }

    // 使用新的layout
    this->setLayout(layout);
}

void TagWidget::addTag(const QString &text) {
    TagLabel *tagLabel = new TagLabel(this);
    tagLabel->setMaximumWidth(75);
    tagLabel->setText(text);
    connect(tagLabel, &TagLabel::closeTag, this, [this]() {
        TagLabel *tagLabel = qobject_cast<TagLabel *>(sender());
        if (!tagLabel)
            return;
        int index = -1;
        for (int i = 0; i < m_tag_vec.size(); i++) {
            if (m_tag_vec.at(i) == tagLabel) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            m_tag_vec.at(index)->deleteLater();
            m_tag_vec.remove(index);
            updateTags();
        }
    });
    m_tag_vec.append(tagLabel);
    updateTags();
}

void TagWidget::addTag() {
    QString tagText = m_inputLineEdit->text().trimmed();
    if (!tagText.isEmpty()) {
        addTag(tagText);
        m_inputLineEdit->clear();
    }
}

}  // namespace roler