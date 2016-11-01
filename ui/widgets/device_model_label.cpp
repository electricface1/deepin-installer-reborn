// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include "ui/widgets/device_model_label.h"

#include <QFontMetrics>
#include <QPainter>
#include <QPaintEvent>

namespace installer {

namespace {

const int kFontSize = 14;
const int kTextLeftMargin = 40;
const int kLineLeftMargin = 30;

}  // namespace

DeviceModelLabel::DeviceModelLabel(QWidget* parent) : QLabel(parent) {
  this->setObjectName(QStringLiteral("device_model_label"));
}

DeviceModelLabel::DeviceModelLabel(const QString& text, QWidget* parent)
  : DeviceModelLabel(parent) {
  this->setText(text);
}

void DeviceModelLabel::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event);
  QPainter painter(this);

  QFont font;
  font.setPixelSize(kFontSize);
  const QFontMetrics font_metrics(font);
  const int text_width = font_metrics.width(this->text());
  const int text_height = font_metrics.height();
  const QColor text_color(QColor::fromRgb(255, 255, 255, 255));
  painter.setFont(font);
  painter.setPen(QPen(text_color));
  const QRect text_rect(kTextLeftMargin, 0, text_width, text_height);
  painter.drawText(text_rect, Qt::AlignLeft, this->text());

  const QColor line_color(QColor::fromRgb(255, 255, 255, 25));
  painter.setPen(QPen(QBrush(line_color), 2));
  // Add left-margin
  const int line_start_x = kTextLeftMargin + text_width + kLineLeftMargin;
  const int half_height = this->height() / 2;
  painter.drawLine(line_start_x, half_height, this->width(), half_height);
}

}  // namespace installer