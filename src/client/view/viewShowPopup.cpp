#include "viewShowPopup.h"

#include "ui_viewShowPopup.h"

ViewShowPopup::ViewShowPopup(QWidget *parent)
    : QDialog(parent), ui(new Ui::ViewShowPopup) {
  ui->setupUi(this);
}

ViewShowPopup::~ViewShowPopup() { delete ui; }

void ViewShowPopup::setView(const QByteArray &jsonView) {
  QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonView);

  if (!jsonDocument.isNull()) {
    QJsonArray jsonArray = jsonDocument.array();

    _model = std::make_unique<QStandardItemModel>(jsonArray.size(), 3);

    _model->setHorizontalHeaderLabels(
        {test::database::CUSTOM_VIEW_ID, test::database::CUSTOM_VIEW_TEXTNAME,
         test::database::CUSTOM_VIEW_RECIEVED_DATE});

    for (int i = 0; i < jsonArray.size(); ++i) {
      QJsonObject jsonObject = jsonArray.at(i).toObject();

      QString id =
          QString::number(jsonObject[test::database::CUSTOM_VIEW_ID].toInt());
      QString textName =
          jsonObject[test::database::CUSTOM_VIEW_TEXTNAME].toString();
      QString receivedDate =
          jsonObject[test::database::CUSTOM_VIEW_RECIEVED_DATE].toString();

      _model->setItem(i, 0, new QStandardItem(id));
      _model->setItem(i, 1, new QStandardItem(textName));
      _model->setItem(i, 2, new QStandardItem(receivedDate));
    }

    ui->tableView->setModel(_model.get());
  }
}
