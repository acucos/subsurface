#ifndef SUBSURFACEWEBSERVICES_H
#define SUBSURFACEWEBSERVICES_H

#include <QDialog>
#include <QNetworkReply>
#include <libxml/tree.h>

#include "ui_webservices.h"

class QAbstractButton;
class QNetworkReply;

class WebServices : public QDialog{
	Q_OBJECT
public:
    explicit WebServices(QWidget* parent = 0, Qt::WindowFlags f = 0);
	void hidePassword();
	void hideUpload();

private slots:
	virtual void startDownload() = 0;
	virtual void startUpload() = 0;
	virtual void buttonClicked(QAbstractButton* button) = 0;

protected:
	Ui::WebServices ui;
	QNetworkReply *reply;
	QNetworkAccessManager *manager;
	QByteArray downloadedData;
};

class SubsurfaceWebServices : public WebServices {
	Q_OBJECT
public:
	static SubsurfaceWebServices* instance();

private slots:
	void startDownload();
	void buttonClicked(QAbstractButton* button);
	void downloadFinished();
	void downloadError(QNetworkReply::NetworkError error);
	void startUpload(){} /*no op*/
private:
    explicit SubsurfaceWebServices(QWidget* parent = 0, Qt::WindowFlags f = 0);
	void setStatusText(int status);
	void download_dialog_traverse_xml(xmlNodePtr node, unsigned int *download_status);
	unsigned int download_dialog_parse_response(const QByteArray& length);
};

class DivelogsDeWebServices : public WebServices {
	Q_OBJECT
public:
	static DivelogsDeWebServices * instance();

private slots:
	void startDownload();
	void buttonClicked(QAbstractButton* button);
	void downloadFinished();
	void downloadError(QNetworkReply::NetworkError error);
    void startUpload();
private:
    explicit DivelogsDeWebServices (QWidget* parent = 0, Qt::WindowFlags f = 0);
	void setStatusText(int status);
	void download_dialog_traverse_xml(xmlNodePtr node, unsigned int *download_status);
	unsigned int download_dialog_parse_response(const QByteArray& length);
};

#endif
