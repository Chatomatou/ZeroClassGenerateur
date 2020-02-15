#include "Window.hpp"

Window::Window() : QWidget{}
{
	setWindowTitle("Zero Class Generator");
	setWindowIcon(QIcon{ QApplication::applicationDirPath() + "/icon.png" });

	// Création des layout
	m_mainLayout = new QVBoxLayout;
	m_classDefinitionLayout = new QFormLayout;
	m_optionsLayout = new QVBoxLayout;
	m_includeLayout = new QHBoxLayout;
	m_includeButtonLayout = new QVBoxLayout;
	m_addCommentaryLayout = new QFormLayout;


	// Création des QGroupBox
	m_groupBoxDefinitionClass = new QGroupBox{ "Definition of the class" };
	m_groupBoxOptions = new QGroupBox{ "Options" };
	m_groupBoxIncludes = new QGroupBox{ "Add library" };
	m_groupBoxCommentary = new QGroupBox{ "Add commentary" };
	m_groupBoxCommentary->setCheckable(true);

	// Définition des layout pour chaque QGroupBox
	m_groupBoxDefinitionClass->setLayout(m_classDefinitionLayout);
	m_groupBoxOptions->setLayout(m_optionsLayout);
	m_groupBoxIncludes->setLayout(m_includeLayout);
	m_groupBoxCommentary->setLayout(m_addCommentaryLayout);


	// Définition de la classe
	m_lineEditName = new QLineEdit;
	m_lineEditParent = new QLineEdit;

	m_classDefinitionLayout->addRow("&Name :", m_lineEditName);
	m_classDefinitionLayout->addRow("&Inheritance :", m_lineEditParent);


	// Options 
	m_checkBoxProtectHeader = new QCheckBox{ "Protect the &header from multiple inclusions" };
	m_checkBoxGenerateDefConstructor = new QCheckBox{ "Generate a default &constructor" };
	m_checkBoxGenerateDefDestructor = new QCheckBox{ "Generate a &destructor" };
	m_checkBoxGPLText = new QCheckBox{ "&GPL License" };

	m_optionsLayout->addWidget(m_checkBoxProtectHeader);
	m_optionsLayout->addWidget(m_checkBoxGenerateDefConstructor);
	m_optionsLayout->addWidget(m_checkBoxGenerateDefDestructor);
	m_optionsLayout->addWidget(m_checkBoxGPLText);

	// Include supplementaire
	m_listWidgetHeaderInclusion = new QListWidget;
	m_pushButtonAdd = new QPushButton{ "Add" };
	m_pushButtonEdit = new QPushButton{ "Edit" };
	m_pushButtonClear = new QPushButton{ "Clear" };

	m_includeLayout->addWidget(m_listWidgetHeaderInclusion);
	m_includeButtonLayout->addWidget(m_pushButtonAdd);
	m_includeButtonLayout->addWidget(m_pushButtonEdit);
	m_includeButtonLayout->addWidget(m_pushButtonClear);
	m_includeLayout->addLayout(m_includeButtonLayout);

	// Commentaire

	m_lineEditAuthor = new QLineEdit;
	m_dateEditDateCreation = new QDateEdit;
	m_textEditRole = new QTextEdit;

	m_addCommentaryLayout->addRow("&Author :", m_lineEditAuthor);
	m_addCommentaryLayout->addRow("Creation da&te :", m_dateEditDateCreation);
	m_addCommentaryLayout->addRow("&Role of the class :", m_textEditRole);

	// Bouton
	m_pushButtonGenerate = new QPushButton{ "Generate !" };
	m_pushButtonQuit = new QPushButton{ "Quit" };

	// Ajoute mes QGroupBox a mon layout principale
	m_mainLayout->addWidget(m_groupBoxDefinitionClass);
	m_mainLayout->addWidget(m_groupBoxOptions);
	m_mainLayout->addWidget(m_groupBoxIncludes);
	m_mainLayout->addWidget(m_groupBoxCommentary);
	m_mainLayout->addWidget(m_pushButtonGenerate);
	m_mainLayout->addWidget(m_pushButtonQuit);

	// Défini le layout principale pour la fenêtre
	setLayout(m_mainLayout);

	// Signaux & Slot 
	QObject::connect(m_pushButtonGenerate, &QPushButton::clicked, this, &Window::generate);
	QObject::connect(m_pushButtonQuit, &QPushButton::clicked, this, &QApplication::quit);
	QObject::connect(m_pushButtonClear, &QPushButton::clicked, m_listWidgetHeaderInclusion, &QListWidget::clear);
	QObject::connect(m_pushButtonAdd, &QPushButton::clicked, this, &Window::pushInList);
	QObject::connect(m_pushButtonEdit, &QPushButton::clicked, this, &Window::editInList);

}


void Window::generate()
{
	QString codeHeader;
	QString codeSource;

	if (!m_lineEditName->text().isEmpty())
	{
		codeHeader += "<pre>";

		if (m_checkBoxGPLText->isChecked())
		{
			codeHeader += "/*\n";
			QFile file{ QApplication::applicationDirPath() + "/gpl.txt" };

			if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
				QMessageBox::critical(this, "Open file", "Impossible to read pgl.txt file");
			else
			{
				while (!file.atEnd())
					codeHeader += file.readLine();
			}
			codeHeader += "*/\n\n";
		}

		if (m_groupBoxCommentary->isChecked())
		{
			codeHeader += "/*\n";
			codeHeader += "Author : " + m_lineEditAuthor->text() + "\n";
			codeHeader += "Creation date : " + m_dateEditDateCreation->text() + "\n";
			codeHeader += "\n\n";
			codeHeader += "Role :\n";
			codeHeader += m_textEditRole->toPlainText();
			codeHeader += "\n*/\n\n";
		}
		codeHeader += (m_checkBoxProtectHeader->isChecked()) ? "#pragma once\n\n" : "\n\n";

		for (auto i{ 0 }; i < m_listWidgetHeaderInclusion->count(); i++)
			codeHeader += m_listWidgetHeaderInclusion->item(i)->text().toHtmlEscaped() + "\n";
		codeHeader += "\n\n";


		codeHeader += "class " + m_lineEditName->text();
		codeHeader += (!m_lineEditParent->text().isEmpty()) ? " : public " + m_lineEditParent->text() + "\n{\n" : "\n{\n";
		codeHeader += (m_checkBoxGenerateDefConstructor->isChecked()) ? "public:\n\t" + m_lineEditName->text() + "();\n" : "public:\n";
		codeHeader += (m_checkBoxGenerateDefDestructor->isChecked()) ? "\t~" + m_lineEditName->text() + "();\n" : "\n";
		codeHeader += "\nprotected:\nprivate:\n";
		codeHeader += "};</pre>";

		codeSource += "<pre>";
		codeSource += "#include \"" + m_lineEditName->text() + ".h\"\n\n";
		codeSource += (m_checkBoxGenerateDefConstructor->isChecked()) ? m_lineEditName->text() + "::" + m_lineEditName->text() + "()\n{\n\n}\n\n" : "\n";
		codeSource += (m_checkBoxGenerateDefDestructor->isChecked()) ? "~" + m_lineEditName->text() + "::" + m_lineEditName->text() + "()\n{\n\n}" : "\n";

		codeSource += "</pre>";

		OutputDialog dialog{ m_lineEditName->text() , codeHeader, codeSource };

		dialog.exec();
	}
	else
	{
		QMessageBox::critical(this, "Erreur", "Veuillez renseigner au minimum le nom de classe !");
	}
}

void Window::pushInList()
{
	m_listWidgetHeaderInclusion->addItem(QInputDialog::getText(this, "Add", "Name :"));
}

void Window::editInList()
{
	QString edited = QInputDialog::getText(this, "Add", "Rename :");
	m_listWidgetHeaderInclusion->currentItem()->setText(edited);
}
