#include "viewShowPopup.h"
#include "ui_viewShowPopup.h"

ViewShowPopup::ViewShowPopup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewShowPopup)
{
    ui->setupUi(this);

}

ViewShowPopup::~ViewShowPopup()
{
    delete ui;
}

void ViewShowPopup::setView(const QByteArray &jsonView) {
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonView);

    if (!jsonDocument.isNull()) {
        QJsonArray jsonArray = jsonDocument.array();

        QStandardItemModel *model = new QStandardItemModel(jsonArray.size(), 3);

        model->setHorizontalHeaderLabels({ test::database::CUSTOM_VIEW_ID,
                                           test::database::CUSTOM_VIEW_TEXTNAME,
                                           test::database::CUSTOM_VIEW_RECIEVED_DATE });

        // Iterate over the JSON array and populate the model
        for (int i = 0; i < jsonArray.size(); ++i) {
            QJsonObject jsonObject = jsonArray.at(i).toObject();

            // Assuming the keys are the same as the column names
            QString id = QString::number(jsonObject[test::database::CUSTOM_VIEW_ID].toInt());
            QString textName = jsonObject[test::database::CUSTOM_VIEW_TEXTNAME].toString();
            QString receivedDate = jsonObject[test::database::CUSTOM_VIEW_RECIEVED_DATE].toString();

            // Populate the model with the data
            model->setItem(i, 0, new QStandardItem(id));
            model->setItem(i, 1, new QStandardItem(textName));
            model->setItem(i, 2, new QStandardItem(receivedDate));
        }

        // Assuming you have a QTableView named 'tableView' to display the model
        ui->tableView->setModel(model);
    }
}

void ViewShowPopup::closeEvent(QCloseEvent *event) {
  ui->tableView->setModel(nullptr);
  event->accept();
}
