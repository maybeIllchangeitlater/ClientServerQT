#ifndef CLIENTSERVERQT_CLIENT_VIEW_VIEWSHOWPOPUP_H_
#define CLIENTSERVERQT_CLIENT_VIEW_VIEWSHOWPOPUP_H_

#include <memory>
#include <QDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QStandardItemModel>
#include "../../common/constants/BDNames.h"

namespace Ui {
class ViewShowPopup;
}
/**
 * @brief The ViewShowPopup class предоставляющий функциональность всплывающего окна для просмотра view
 */
class ViewShowPopup : public QDialog
{
    Q_OBJECT

public:
    explicit ViewShowPopup(QWidget *parent = nullptr);
    ~ViewShowPopup();
    /**
     * @brief setView установить view
     * @param jsonView view пришедшее в виде json переведенного в QByteArray
     */
    void setView(const QByteArray &jsonView);


private:
    std::unique_ptr<QStandardItemModel> _model = std::make_unique<QStandardItemModel>();
    Ui::ViewShowPopup *ui;
};

#endif // CLIENTSERVERQT_CLIENT_VIEW_VIEWSHOWPOPUP_H_
