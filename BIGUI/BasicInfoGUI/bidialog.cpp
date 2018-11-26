#include "bidialog.h"
#include "ui_bidialog.h"
#include "qdir.h"
#include "qmessagebox.h"

#include <g3log/g3log.hpp>

#include <OHARBaseLayer/ProcessorNode.h>

#include <OHARStudentLayer/PlainStudentFileHandler.h>
#include <OHARStudentLayer/StudentNetOutputHandler.h>
#include <OHARStudentLayer/StudentDataItem.h>


BIDialog::BIDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BIDialog),
    node(nullptr)
{
    ui->setupUi(this);

    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));
    connect(ui->pingButton, SIGNAL(clicked()), this, SLOT(onPingButtonClicked()));
    connect(ui->addStudentButton, SIGNAL(clicked()), this, SLOT(onAddStudentButtonClicked()));

    node = new OHARBase::ProcessorNode("BasicInfo", this);
    using namespace OHARStudent;
    node->addHandler(new PlainStudentFileHandler(*node));
    node->addHandler(new StudentNetOutputHandler(*node));
}

BIDialog::~BIDialog()
{
    delete ui;
    delete node;
}


void BIDialog::onStartButtonClicked()
{
    LOG(INFO) << "Start/stop button clicked.";
    if (!node->isRunning()) {
        if (configureNode())
        {
            LOG(INFO) << "***** Configured, starting the node";
            showMessage("Node configured, starting the node.");
            node->start();
            ui->pingButton->setDisabled(false);
            ui->readfileButton->setDisabled(false);
            ui->shutdownButton->setDisabled(false);
            ui->addStudentButton->setDisabled(false);
            ui->startButton->setText("Stop");
        } else {
            LOG(INFO) << "Configuration failed, cannot start node.";
            showMessage("Node configuration failed, cannot start node.");
            QMessageBox box;
            box.setText("Create configuration file for the node first!");
            box.exec();
        }


    } else {
        LOG(INFO) << "***** Stopping the node";
        node->stop();
        showMessage("Node stopped");
        ui->pingButton->setDisabled(true);
        ui->readfileButton->setDisabled(true);
        ui->shutdownButton->setDisabled(true);
        ui->addStudentButton->setDisabled(true);
        ui->startButton->setText("Start");
    }
}


void BIDialog::onPingButtonClicked()
{
    showMessage("Sending ping");
    LOG(INFO) << "***** Ping button clicked";
    OHARBase::Package p;
    p.setType(OHARBase::Package::Control);
    p.setData("ping");
    node->sendData(p);
}

void BIDialog::onReadFileButtonClicked()
{

}

void BIDialog::onShutdownButtonClicked()
{

}

void BIDialog::onAddStudentButtonClicked()
{
    QString id = ui->studentId->text();
    if (id.length() > 0)
    {
        QString name = ui->studentName->text();
        if (name.length() > 0)
        {
            QString studyProgram = ui->studyProgram->text();
            if (studyProgram.length() > 0)
            {
                OHARBase::Package p;
                p.setType((OHARBase::Package::Data));
                std::shared_ptr<OHARStudent::StudentDataItem> student(new OHARStudent::StudentDataItem());
                student->setId(id.toStdString());
                student->setName(name.toStdString());
                student->setStudyProgram(studyProgram.toStdString());
                p.setDataItem(student.get());
                node->passToHandlers(p);
            }
        }
    }
}

bool BIDialog::configureNode()
{
    QString configFile = QDir::homePath() + "/StudentPassing/BasicInfoConfig.txt";
    showMessage("Reading configuration from " + configFile);
    return node->configure(configFile.toStdString());
}


void BIDialog::NodeEventHappened(EventType e, const std::string & message)
{
    showMessage(QString::fromStdString(message));
}

void BIDialog::showMessage(const QString & message)
{
    ui->logView->appendPlainText(message);
}