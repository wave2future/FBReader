#ifndef __ZLQTTREEMODEL_H__
#define __ZLQTTREEMODEL_H__

#include <QtCore/QMap>

#include <QtCore/QAbstractListModel>
#include <QtNetwork/QNetworkAccessManager>
#include <QtGui/QDialog>

#include <ZLTreeListener.h>

#include "../view/ImageUtils.h"

class ZLQtTreeModel : public QAbstractListModel {
	Q_OBJECT;

public:
        enum TreeRoles {
                SubTitleRole = Qt::UserRole,
                ActivatableRole,
                PageRole
        };

public:
        explicit ZLQtTreeModel(ZLTreeListener::RootNode& rootNode, QDialog* treeDialog,
                               shared_ptr<ZLExecutionData::Listener> listener, QObject *parent = 0);

public:
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
        const ZLTreeNode* getTreeNode(const QModelIndex& index) const;

public:
	void onNodeBeginInsert(ZLTreeNode *parent, size_t index);
	void onNodeEndInsert();
	void onNodeBeginRemove(ZLTreeNode *parent, size_t index);
	void onNodeEndRemove();
	void onNodeUpdated(ZLTreeNode *node);

signals:

public slots:
	bool back();
	bool enter(QModelIndex index);

private slots: //network
        void onRequestFinished(QNetworkReply*);

private: //network
        QPixmap downloadImage(QUrl url) const;

private:
	ZLTreeListener::RootNode& myRootNode;
	ZLTreeNode* myCurrentNode;
        //TODO remove two-sided pointing (model should not know about ui element)
        QDialog* myTreeDialog;

        shared_ptr<ZLExecutionData::Listener> myListener;

private: //network
        //TODO refactor it: network manager in model is bad
        mutable QNetworkAccessManager myManager;
        QPixmap myEmptyPixmap;
        //TODO cache should not be deleted after closing net library dialog (??)
        QMap<QString,QPixmap> myCache;
};

#endif /* __ZLQTTREEMODEL_H__ */
