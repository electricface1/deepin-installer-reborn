// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include "misc/oem/oem_window.h"

#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QSlider>
#include <QVBoxLayout>

#include "service/system_language.h"

namespace {

const int kGrubTimeoutMinimum = 0;
const int kGrubTimeoutMaximum = 30;

}  // namespace

OemWindow::OemWindow(QWidget* parent) : QFrame(parent) {
  this->setObjectName(QStringLiteral("oem_window"));

  this->initUI();
  this->initConnections();
}

void OemWindow::initConnections() {
  connect(grub_timeout_slider_, &QSlider::valueChanged,
          this, &OemWindow::onGrubTimeoutSliderValueChanged);
  connect(grub_disable_windows_button_, &QCheckBox::toggled,
          this, &OemWindow::onGrubDisableWindowsButtonToggled);
}

void OemWindow::initUI() {
  // Pages
  skip_disk_space_insufficient_page_button_ =
      new QCheckBox("Skip disk space insufficient page");
  skip_virtual_machine_page_button_ =
      new QCheckBox("Skip virtual machine warning page");
  skip_select_language_page_button_ =
      new QCheckBox("Skip language selection page");
  skip_system_info_page_button_ = new QCheckBox("Skip system info page");
  skip_partition_page_button_ = new QCheckBox("Skip partition page");

  // Language selection
  use_default_locale_button_ = new QCheckBox("Use default locale");
  QLabel* default_locale_label = new QLabel("Default locale:");
  default_locale_combo_ = new QComboBox();
  const service::LanguageList language_list = service::GetLanguageList();
  for (const service::LanguageItem& language_item : language_list) {
    default_locale_combo_->addItem(language_item.locale);
  }
  QHBoxLayout* default_locale_layout = new QHBoxLayout();
  default_locale_layout->addWidget(default_locale_label);
  default_locale_layout->addWidget(default_locale_combo_);

  // System info
  vendor_name_edit_ = new QLineEdit();
  vendor_name_edit_->setPlaceholderText("vendor name");
  os_name_edit_ = new QLineEdit();
  os_name_edit_->setPlaceholderText("OS name");
  os_version_edit_ = new QLineEdit();
  os_version_edit_->setPlaceholderText("OS version");
  use_default_username_button_ = new QCheckBox("Use default username");
  use_default_hostname_button_ = new QCheckBox("Use default hostname");
  use_default_password_button_ = new QCheckBox("Use default password");
  default_username_edit_ = new QLineEdit();
  default_username_edit_->setPlaceholderText("default username");
  default_hostname_edit_ = new QLineEdit();
  default_hostname_edit_->setPlaceholderText("default hostname");
  default_password_edit_ = new QLineEdit();
  default_password_edit_->setPlaceholderText("default password");

  // Grub tab
  QLabel* grub_timeout_label = new QLabel();
  grub_timeout_label->setText("Grub menu timeout:");
  grub_timeout_slider_ = new QSlider();
  grub_timeout_slider_->setMinimum(kGrubTimeoutMinimum);
  grub_timeout_slider_->setMaximum(kGrubTimeoutMaximum);
  grub_timeout_slider_->setOrientation(Qt::Horizontal);
  grub_timeout_value_label_ = new QLabel();
  QHBoxLayout* grub_timeout_layout = new QHBoxLayout();
  grub_timeout_layout->addWidget(grub_timeout_label);
  grub_timeout_layout->addWidget(grub_timeout_slider_);
  grub_timeout_layout->addWidget(grub_timeout_value_label_);
  grub_disable_windows_button_ = new QCheckBox("Disable Windows in grub menu");
  grub_disable_windows_button_->setCheckable(true);

  // Packages
  uninstalled_packages_edit_ = new QLineEdit();
  uninstalled_packages_edit_->setPlaceholderText("packages to be uninstalled");
  hold_packages_edit_ = new QLineEdit();
  hold_packages_edit_->setPlaceholderText(
      "packages to be prevented from uninstalling");

  QVBoxLayout* right_layout = new QVBoxLayout();
  right_layout->addWidget(skip_disk_space_insufficient_page_button_);
  right_layout->addWidget(skip_virtual_machine_page_button_);
  right_layout->addWidget(skip_select_language_page_button_);
  right_layout->addWidget(skip_system_info_page_button_);
  right_layout->addWidget(skip_partition_page_button_);

  right_layout->addWidget(use_default_locale_button_);
  right_layout->addLayout(default_locale_layout);

  right_layout->addWidget(vendor_name_edit_);
  right_layout->addWidget(os_name_edit_);
  right_layout->addWidget(os_version_edit_);
  right_layout->addWidget(use_default_username_button_);
  right_layout->addWidget(default_username_edit_);
  right_layout->addWidget(use_default_hostname_button_);
  right_layout->addWidget(default_hostname_edit_);
  right_layout->addWidget(use_default_password_button_);
  right_layout->addWidget(default_password_edit_);

  right_layout->addLayout(grub_timeout_layout);
  right_layout->addWidget(grub_disable_windows_button_);

  right_layout->addWidget(uninstalled_packages_edit_);
  right_layout->addWidget(hold_packages_edit_);

  QHBoxLayout* layout = new QHBoxLayout();
  layout->addLayout(right_layout);
  this->setLayout(layout);
}

void OemWindow::onGrubTimeoutSliderValueChanged(int value) {
  grub_timeout_value_label_->setText(QString("%1 s").arg(value));
}

void OemWindow::onGrubDisableWindowsButtonToggled(bool toggle) {
  Q_UNUSED(toggle);
}