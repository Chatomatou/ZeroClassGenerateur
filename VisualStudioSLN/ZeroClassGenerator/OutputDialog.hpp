#pragma once

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>

class OutputDialog : public QDialog
{
	Q_OBJECT

public:
	OutputDialog(const QString& name, const QString& header, const QString& source);
public slots:
	void saveFiles();
signals:
private:
	QString m_className;

	QVBoxLayout* m_mainLayout;
	QPushButton* m_pushButtonClose;
	QPushButton* m_pushButtonSave;
	QTabWidget* m_tabWidgetContent;

	QTextEdit* m_textEditHeader;
	QTextEdit* m_textEditSource;


};
