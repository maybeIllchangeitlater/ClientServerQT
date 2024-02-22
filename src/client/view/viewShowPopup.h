#ifndef VIEWSHOWPOPUP_H
#define VIEWSHOWPOPUP_H

#include <QCloseEvent>
#include <QDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QStandardItemModel>
#include "../../common/constants/BDNames.h"

namespace Ui {
class ViewShowPopup;
}

class ViewShowPopup : public QDialog
{
    Q_OBJECT

public:
    explicit ViewShowPopup(QWidget *parent = nullptr);
    ~ViewShowPopup();

    void setView(const QByteArray &jsonView);

protected:
 void closeEvent(QCloseEvent *event) override;

private:
    Ui::ViewShowPopup *ui;
};

#endif // VIEWSHOWPOPUP_H
