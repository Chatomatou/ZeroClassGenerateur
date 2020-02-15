#include "OutputDialog.hpp"

OutputDialog::OutputDialog(const QString& name, const QString& header, const QString& source) : m_className{ name }
{
	setWindowFlag(Qt::Tool);
	setWindowTitle("Source code");

	m_mainLayout = new QVBoxLayout;
	setLayout(m_mainLayout);

	m_tabWidgetContent = new QTabWidget;
	m_pushButtonSave = new QPushButton{ "Save" };
	m_pushButtonClose = new QPushButton{ "Close" };

	m_mainLayout->addWidget(m_tabWidgetContent);
	m_mainLayout->addWidget(m_pushButtonSave);
	m_mainLayout->addWidget(m_pushButtonClose);

	m_textEditHeader = new QTextEdit{ header };
	m_textEditSource = new QTextEdit{ source };
	m_textEditHeader->setReadOnly(true);
	m_textEditSource->setReadOnly(true);
	m_textEditHeader->setFont(QFont{ "Consolas" });
	m_textEditSource->setFont(QFont{ "Consolas" });

	QFontMetrics metrics{ m_textEditHeader->font() };

	m_textEditHeader->setTabStopWidth(metrics.width(' ') * 4);

	m_tabWidgetContent->addTab(m_textEditHeader, ".hpp");
	m_tabWidgetContent->addTab(m_textEditSource, ".cpp");

	QObject::connect(m_pushButtonClose, &QPushButton::clicked, this, &OutputDialog::close);
	QObject::connect(m_pushButtonSave, &QPushButton::clicked, this, &OutputDialog::saveFiles);
}

void OutputDialog::saveFiles()
{
	QString path = QFileDialog::getExistingDirectory(this);
	QFile header{ path + "/" + m_className + ".h" };
	QFile source{ path + "/" + m_className + ".cpp" };

	if (!header.open(QIODevice::WriteOnly | QIODevice::Text) || !source.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QMessageBox::critical(this, "Save", "Impossible to save files.");
		return;
	}
	else
	{
		QTextStream outHeader{ &header };
		outHeader << m_textEditHeader->toPlainText();

		QTextStream outSource{ &source };
		outSource << m_textEditSource->toPlainText();

		QMessageBox::information(this, "Save", "Saving successfully !");
	}

}
