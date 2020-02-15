#pragma once

#include <QtCore/QDebug>

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QInputDialog>

#include "OutputDialog.hpp"

class Window : public QWidget
{
	Q_OBJECT

public:
	Window();
public slots:
	void generate();
	void pushInList();
	void editInList();
signals:

private:
	QVBoxLayout* m_mainLayout;
	QFormLayout* m_classDefinitionLayout;
	QVBoxLayout* m_optionsLayout;
	QHBoxLayout* m_includeLayout;
	QVBoxLayout* m_includeButtonLayout;
	QFormLayout* m_addCommentaryLayout;

	QGroupBox* m_groupBoxDefinitionClass;
	QGroupBox* m_groupBoxOptions;
	QGroupBox* m_groupBoxIncludes;
	QGroupBox* m_groupBoxCommentary;

	QLineEdit* m_lineEditName;
	QLineEdit* m_lineEditParent;

	QCheckBox* m_checkBoxProtectHeader;
	QCheckBox* m_checkBoxGenerateDefConstructor;
	QCheckBox* m_checkBoxGenerateDefDestructor;
	QCheckBox* m_checkBoxGPLText;

	QListWidget* m_listWidgetHeaderInclusion;
	QPushButton* m_pushButtonClear;
	QPushButton* m_pushButtonAdd;
	QPushButton* m_pushButtonEdit;


	QLineEdit* m_lineEditAuthor;
	QDateEdit* m_dateEditDateCreation;
	QTextEdit* m_textEditRole;

	QPushButton* m_pushButtonGenerate;
	QPushButton* m_pushButtonQuit;
};